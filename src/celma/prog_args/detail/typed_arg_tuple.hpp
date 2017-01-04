
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArgTuple.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_TUPLE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_TUPLE_HPP


#include <iostream>
#include <tuple>
#include <boost/lexical_cast.hpp>
#include "celma/common/tokenizer.hpp"
#include "celma/common/tuple_at_index.hpp"
#include "celma/common/tuple_length.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Helper class used to assign a value to a tuple element with type
/// conversion.<br>
/// Can be replaced by a lambda, once the decltype works for boost::lexical_cast.
class TupleElementValueAssign
{
public:
   /// Constructor.
   /// @param[in]  value  The value to assign to the tuple element.
   /// @since  0.11, 04.01.2017
   TupleElementValueAssign( const std::string& value):
      mValue( value)
   {
   } // TupleElementValueAssign::TupleElementValueAssign

   /// Operator called for the tuple element. Converts the value from #mValue to
   /// the required destination type and assigns it to \a tuple_value, i.e. the
   /// tuple element.
   /// @param[out]  tuple_element  The element of the the tuple to assign the
   ///                             value to.
   /// @return  .
   /// @since  6.0, 04.01.2017
   template< typename T> void operator ()( T& tuple_element)
   {
      tuple_element = boost::lexical_cast< T>( mValue);
   } // TupleElementValueAssign::operator ()

private:
   /// The value to assign in the operator.
   const std::string  mValue;

}; // TupleElementValueAssign


// Template TypedArgTuple
// ======================


/// Helper class to store a destination variable with its native type.
/// @tparam  T  The type of the value.
/// @since  0.11, 19.12.2016
template< typename... T> class TypedArgTuple: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the value in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.11, 19.12.2016
   TypedArgTuple( const std::string& arg_spec, std::tuple< T...>& dest,
                  const std::string& vname);

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.11, 19.12.2016
   virtual bool hasValue() const override;

   /// Adds the value of the destination variable to the string.
   /// @param[in]  dest  The string to append the default value to.
   /// @since  0.11, 19.12.2016
   virtual void defaultValue( std::string& dest) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For tuples it is possible/allowed to activate this feature.
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   virtual TypedArgBase* setListSep( char sep) override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.11, 19.12.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.11, 19.12.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   std::tuple< T...>&  mDestVar;
   /// The length, i.e. the number of elements, of the tuple.
   const size_t        mTupleLength;
   /// Counter for the number of values set.
   size_t              mNumValuesSet = 0;
   /// The character to use a list separator, default: ,
   char                mListSep = ',';

}; // TypedArgTuple< T...>


// inlined methods
// ===============


template< typename... T>
   TypedArgTuple< T...>::TypedArgTuple( const std::string& arg_spec,
                                        std::tuple< T...>& dest,
                                        const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::required, false),
      mDestVar( dest),
      mTupleLength( common::tuple_length( dest))
{
   mpCardinality.reset( new CardinalityMax( mTupleLength));
} // TypedArgTuple< T...>::TypedArgTuple


template< typename... T> bool TypedArgTuple< T...>::hasValue() const
{
   return mNumValuesSet == mTupleLength;
} // TypedArgTuple< T...>::hasValue


template< typename... T> void TypedArgTuple< T...>::defaultValue( std::string& dest) const
{
   dest.append( "<");
   for (size_t i = 0; i < mTupleLength; ++i)
   {
      if (i > 0)
         dest.append(",");

      common::tuple_at_index( i, mDestVar, [&dest]( auto const& value)
         {
            dest.append( boost::lexical_cast< std::string>( value));
         });
   } // end for

   dest.append( ">");
} // TypedArgTuple< T...>::defaultValue


template< typename... T> TypedArgBase* TypedArgTuple< T...>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArgTuple< T...>::setTakesMultiValue


template< typename... T>
   TypedArgBase* TypedArgTuple< T...>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArgTuple< T...>::setListSep


template< typename... T> void TypedArgTuple< T...>::dump( std::ostream& os) const
{
   os << "value type '" << type< decltype( mDestVar)>::name() << "', destination '"
      << mVarName << "', ";
   if (hasValue())
   {
      os << "value = <";
      for (size_t i = 0; i < mTupleLength; ++i)
      {
         if (i > 0)
            os << ",";

         common::tuple_at_index( i, mDestVar, [&os]( auto const& value)
            {
               os << value;
            });
      } // end for
      os << ">." << std::endl;
   } else
   { 
      os << "value not set." << std::endl;
   } // end if
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgTuple< T...>::dump


template< typename... T>
   void TypedArgTuple< T...>::assign( const std::string& value)
{
   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin_counting(); it != tok.end_counting(); ++it)
   {
      if ((it.currentNum() > 0) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      const std::string&  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         std::string  valCopy( listVal);
         format( valCopy);
         TupleElementValueAssign  teva( valCopy);
         common::tuple_at_index( mNumValuesSet, mDestVar, teva);
      } else
      {
         TupleElementValueAssign  teva( listVal);
         common::tuple_at_index( mNumValuesSet, mDestVar, teva);

#if 0
         // this should work ...
         common::tuple_at_index( mNumValuesSet, mDestVar,
                                 [&listVal]( auto& tuple_value)
           {
              tuple_value = boost::lexical_cast< decltype( tuple_value)>( listVal);
           });
#endif
      } // end if
      ++mNumValuesSet;
   } // end for
} // TypedArgTuple< T...>::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_TUPLE_HPP


// =======================  END OF typed_arg_tuple.hpp  =======================

