
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArg.<br>
/// This file contains the base template plus all specialisations:
/// - TypedArg< bool>
/// - TypedArg< CheckAssign< T> >
/// - TypedArg< CheckAssign< bool> >
/// - TypedArg< std::vector< T>>


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP


#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "celma/common/check_assign.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/common/type_name.hpp"
#include "celma/common/var_type_name.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


// Template TypedArg
// =================


/// Helper class to store a destination variable with its native type.
/// @tparam  T  The type of the value.
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the value in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArg( const std::string& arg_spec, T& dest, const std::string& vname);

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Adds the value of the destination variable to the string.
   /// @param[in]  dest  The string to append the default value to.
   /// @since  0.2, 10.04.2016
   virtual void defaultValue( std::string& dest) const override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   T&    mDestVar;
   /// Flag, set when the argument was found/the value is set.
   bool  mHasValueSet;  

}; // TypedArg< T>


// inlined methods
// ===============


template< typename T>
   TypedArg< T>::TypedArg( const std::string& arg_spec, T& dest,
                           const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::required, true),
      mDestVar( dest),
      mHasValueSet( false)
{
   mpCardinality.reset( new CardinalityMax( 1));
} // TypedArg< T>::TypedArg


template< typename T> bool TypedArg< T>::hasValue() const
{
   return mHasValueSet;
} // TypedArg< T>::hasValue


template< typename T> void TypedArg< T>::defaultValue( std::string& dest) const
{
   dest.append( boost::lexical_cast< std::string>( mDestVar));
} // TypedArg< T>::defaultValue


template< typename T> void TypedArg< T>::dump( std::ostream& os) const
{
   os << "value type '" << type< T>::name() << "', destination '"
      << mVarName << "', ";
   if (mHasValueSet)
      os << "value = " << mDestVar << "." << std::endl;
   else 
      os << "value not set." << std::endl;
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< T>::dump


template< typename T>
   void TypedArg< T>::assign( const std::string& value)
{
   check( value);
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      mDestVar = boost::lexical_cast< T>( valCopy);
   } else
   {
      mDestVar = boost::lexical_cast< T>( value);
   } // end if
   mHasValueSet = true;
} // TypedArg< T>::assign


// Template TypedArg< bool>
// ========================


/// Specialisation of template TypedArg<> for boolean variables.
/// since  6.0, 18.09.2013
template<> class TypedArg< bool>: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the value in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArg( const std::string& arg_spec, bool& dest, const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::none, false),
      mDestVar( dest),
      mHasValueSet( false),
      mValue2Set( true)
   {
      mpCardinality.reset( new CardinalityMax( 1));
   } // TypedArg< bool>::TypedArg

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override
   {
      return mHasValueSet;
   } // TypedArg< bool>::hasValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   /// @return  Nothing, always throws.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< bool>::setIsMandatory

   /// Unset the flag (set to \c false) when the argument is detected, instead
   /// of setting it (the default).
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* unsetFlag() override
   {
      mValue2Set = false;
      return this;
   } // TypedArg< bool>::unsetFlag

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override
   {
      os << "boolean flag, destination '" << mVarName << "', "
         << (mHasValueSet ? "not set." : "set.") << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< bool>::dump

private:
   /// Stores the value in the destination variable.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& /* value */) override
   {
      mDestVar     = mValue2Set;
      mHasValueSet = true;
   } // TypedArg< bool>::assign

   /// Reference of the destination variable to store the value in.
   bool&  mDestVar;
   /// Flag set when a value was assigned through an argument.
   bool   mHasValueSet;
   /// The value to set when assign is called. Default = \c true.
   bool   mValue2Set;

}; // TypedArg< bool>


// Template TypedArg< common::CheckAssign< T>>
// ===========================================


/// Specialisation of TypedArg<> for values wrapped in CheckAssign<>.
/// @tparam  T  The native type of the value.
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg< common::CheckAssign< T>>:
   public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the value in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArg( const std::string& arg_spec, common::CheckAssign< T>& dest,
             const std::string& vname);

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   common::CheckAssign< T>&  mDestVar;

}; // TypedArg< CheckAssign< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< common::CheckAssign< T>>::TypedArg( const std::string& arg_spec,
                                                 common::CheckAssign< T>& dest,
                                                 const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::required, false),
      mDestVar( dest)
{
} // TypedArg< common::CheckAssign< T>>::TypedArg


template< typename T> bool TypedArg< common::CheckAssign< T>>::hasValue() const
{
   return mDestVar.hasValue();
} // TypedArg< common::CheckAssign< T>>::hasValue


template< typename T> void TypedArg< common::CheckAssign< T>>::dump( std::ostream& os) const
{
   os << "value type '" << type< T>::name()
      << "', destination 'CheckAssign< " << mVarName << ">', value ";
   if (mDestVar.hasValue())
      os << " = " << static_cast< T>( mDestVar) << "." << std::endl;
   else
      os << "not set." << std::endl;
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< common::CheckAssign< T>>::dump


template< typename T>
   void TypedArg< common::CheckAssign< T>>::assign( const std::string& value)
{
   check( value);
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      mDestVar = boost::lexical_cast< T>( valCopy);
   } else
   {
      mDestVar = boost::lexical_cast< T>( value);
   } // end if
} // TypedArg< CheckAssign< T> >::assign


// Template TypedArg< common::CheckAssign< bool>>
// ==============================================


/// Specialization of the TypedArg< CheckAssign< T> > template for boolean flags.
/// @since  0.2, 10.04.2016
template<> class TypedArg< common::CheckAssign< bool>>: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the value in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArg( const std::string& arg_spec, common::CheckAssign< bool>& dest,
             const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::none, false),
      mDestVar( dest),
      mValue2Set( true)
   {
   } // TypedArg< common::CheckAssign< bool>>::TypedArg

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override
   {
      return mDestVar.hasValue();
   } // TypedArg< common::CheckAssign< bool>>::hasValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   /// @return  Nothing, always throws.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< common::CheckAssign< bool>>::setIsMandatory

   /// Unset the flag (set to \c false) when the argument is detected, instead
   /// of setting it (the default).
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* unsetFlag() override
   {
      mValue2Set = false;
      return this;
   } // TypedArg< common::CheckAssign< bool>>::unsetFlag

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override
   {
      os << "sets boolean flag on 'CheckAssign< " << mVarName << ">'." << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< common::CheckAssign< bool>>::dump

private:
   /// Stores the value in the destination variable.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& /* value */) override
   {
      mDestVar = mValue2Set;
   } // TypedArg< common::CheckAssign< bool>>::assign

   /// Reference of the destination variable to store the value in.
   common::CheckAssign< bool>&  mDestVar;
   /// The value to set when assign is called. Default = \c true.
   bool                         mValue2Set;

}; // TypedArg< common::CheckAssign< bool>>


// Template TypedArg< std::vector< T>>
// ====================================


/// Specialisation of TypedArg<> for values wrapped in a vector.
/// @tparam  T  The type of the value(s) stored in the vector.
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg< std::vector< T>>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   typedef typename std::vector< T>  vector_type;

   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest      The destination variable to store the values in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArg( const std::string& arg_spec, vector_type& dest,
             const std::string& vname);

   /// Returns if the destination has (at least) one value set.
   /// @return  \c true if the destination variable contains (at least) one
   ///          value, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For vectors it is possible/allowed to activate this feature.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setListSep( char sep) override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value(s) in.
   vector_type&  mDestVar;
   /// The character to use a list separator, default: ,
   char          mListSep;

}; // TypedArg< std::vector< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< std::vector< T>>::TypedArg( const std::string& arg_spec,
                                          vector_type& dest,
                                          const std::string& vname):
      TypedArgBase( arg_spec, vname, ValueMode::required, false),
      mDestVar( dest),
      mListSep( ',')
{
   mpCardinality.reset();
} // TypedArg< std::vector< T>>::TypedArg


template< typename T> bool TypedArg< std::vector< T>>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArg< std::vector< T>>::hasValue


template< typename T> TypedArgBase* TypedArg< std::vector< T>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< std::vector< T>>::setTakesMultiValue


template< typename T> TypedArgBase* TypedArg< std::vector< T>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< std::vector< T>>::setListSep


template< typename T> void TypedArg< std::vector< T>>::dump( std::ostream& os) const
{
   os << "value type '" << type< vector_type>::name()
      << "', destination vector '" << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : boost::lexical_cast< std::string>( mDestVar.size()))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< std::vector< T>>::dump


template< typename T>
   void TypedArg< std::vector< T>>::assign( const std::string& value)
{
   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if ((it != tok.begin()) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      const std::string&  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         std::string  valCopy( listVal);
         format( valCopy);
         mDestVar.push_back( boost::lexical_cast< T>( valCopy));
      } else
      {
         mDestVar.push_back( boost::lexical_cast< T>( listVal));
      } // end if
   } // end for
} // TypedArg< std::vector< T>>::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP


// ==========================  END OF typed_arg.hpp  ==========================

