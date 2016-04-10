
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
/// See documentation of template celma::prog_args::detail::TypedArgPair.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_PAIR_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_PAIR_HPP


#include <iostream>
#include <boost/lexical_cast.hpp>
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


// Template TypedArgPair
// =====================


/// Helper class to store two destination variables with their native types.
/// For the second variable, the value to set must be specified.
/// @tparam  T1  The type of the first value.
/// @tparam  T2  The type of the second value.
/// @since  0.2, 10.04.2016
template< typename T1, typename T2> class TypedArgPair : public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  dest1     The first destination variable to store the
   ///                       parameter value in.
   /// @param[in]  vname1    The name of the first destination variable to store
   ///                       the parameter value in.
   /// @param[in]  dest2     The second destination variable to store the given
   ///                       value in.
   /// @param[in]  vname2    The name of the second destination variable to store
   ///                       the given value in.
   /// @param[in]  value2    The value to set for the second variable.
   /// @since  0.2, 10.04.2016
   TypedArgPair( const std::string& arg_spec,
                 T1& dest1, const std::string& vname1, T2& dest2,
                 const std::string& vname2, const T2& value2);

   /// Returns if the destination has a value set.
   /// @return  \c true if the destination variable contains a value,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value);

   /// Reference of the destination variable to store the value in.
   T1&                mDestVar1;
   /// Reference of the destination variable to store the value in.
   T2&                mDestVar2;
   /// The name of the variable to store the second value in.
   const std::string  mVarName2;
   /// The value to set in the second variable.<br>
   /// Must be copied when the object is created, otherwise we risk keeping a
   /// reference to a temporary value/variable.
   const T2           mValue2;
   /// Flag, set when the argument was found/the value is set.
   bool               mValueSet;  

}; // TypedArgPair< T1, T2>


// inlined methods
// ===============


template< typename T1, typename T2>
   TypedArgPair< T1, T2>::TypedArgPair( const std::string& arg_spec, 
                                        T1& dest1, const std::string& vname1,
                                        T2& dest2, const std::string& vname2,
                                        const T2& value2):
      TypedArgBase( arg_spec, vname1, vmRequired, false),
      mDestVar1( dest1),
      mDestVar2( dest2),
      mVarName2( vname2),
      mValue2( value2),
      mValueSet( false)
{
} // end TypedArgPair< T1, T2>::TypedArgPair


template< typename T1, typename T2> bool TypedArgPair< T1, T2>::hasValue() const
{
   return mValueSet;
} // end TypedArgPair< T1, T2>::hasValue


template< typename T1, typename T2>
   void TypedArgPair< T1, T2>::dump( std::ostream& os) const
{
   os << "store first value with type '" << type< T1>::name() << "' in '"
      << mVarName << "', second value with type '" << type< T2>::name()
      << "' in '" << mVarName2  << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // end TypedArgPair< T1, T2>::dump


template< typename T1, typename T2>
   void TypedArgPair< T1, T2>::assign( const std::string& value)
{
   check( value);
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      mDestVar1 = boost::lexical_cast< T1>( valCopy);
   } else
   {
      mDestVar1 = boost::lexical_cast< T1>( value);
   } // end if
   mDestVar2 = mValue2;
   mValueSet = true;
} // end TypedArgPair< T1, T2>::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_PAIR_HPP


// =========================  END OF typed_arg_pair.hpp  =========================

