
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
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
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


// Template TypedArgPair
// =====================


/// Helper class to store two destination variables with their native types.
/// For the second variable, the value to set must be specified.
/// @tparam  T1
///    The type of the first value.
/// @tparam  T2
///    The type of the second value.
/// @since
///    1.5.0, 20.06.2018  (derived from TypedArg<> instead of TypedArgBase).
/// @since
///    0.2, 10.04.2016
template< typename T1, typename T2> class TypedArgPair: public TypedArg< T1>
{
public:
   /// Constructor.
   /// @param[in]  dest1
   ///    The first destination variable to store the parameter value in.
   /// @param[in]  vname1
   ///    The name of the first destination variable to store the parameter
   ///    value in.
   /// @param[in]  dest2
   ///    The second destination variable to store the given value in.
   /// @param[in]  vname2
   ///    The name of the second destination variable to store the given value
   ///    in.
   /// @param[in]  value2
   ///    The value to set for the second variable.
   /// @since
   ///    0.16.0, 10.11.2017  (removed key parameter)
   /// @since
   ///    0.2, 10.04.2016
   TypedArgPair( T1& dest1, const std::string& vname1, T2& dest2,
      const std::string& vname2, const T2& value2);

   /// Empty, virtual default destructor.
   ///
   /// @since  x.y.z, 27.08.2019
   virtual ~TypedArgPair() = default;

   /// Prints the two current values of the destination variables.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 05.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os
   ///    The stream to print to.
   /// @since
   ///    0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since
   ///    0.2, 10.04.2016
   virtual void assign( const std::string& value, bool inverted) override;

   /// Reference of the destination variable to store the value in.
   T2&                mDestVar2;
   /// The name of the variable to store the second value in.
   const std::string  mVarName2;
   /// The value to set in the second variable.<br>
   /// Must be copied when the object is created, otherwise we risk keeping a
   /// reference to a temporary value/variable.
   const T2           mValue2;

}; // TypedArgPair< T1, T2>


// inlined methods
// ===============


template< typename T1, typename T2>
   TypedArgPair< T1, T2>::TypedArgPair( T1& dest1, const std::string& vname1,
      T2& dest2, const std::string& vname2, const T2& value2):
         TypedArg< T1>( dest1, vname1),
         mDestVar2( dest2),
         mVarName2( vname2),
         mValue2( value2)
{
} // TypedArgPair< T1, T2>::TypedArgPair


template< typename T1, typename T2>
   void TypedArgPair< T1, T2>::printValue( std::ostream& os,
      bool print_type) const
{
   TypedArg< T1>::printValue( os, print_type);
   os << ", destination 2 = " << mDestVar2;
   if (print_type)
     os << " [" << type< T2>::name() << "]";
} // TypedArgPair< T1, T2>::printValue


template< typename T1, typename T2>
   void TypedArgPair< T1, T2>::dump( std::ostream& os) const
{
   os << "store first value with type '" << type< T1>::name() << "' in '"
      << TypedArg< T1>::mVarName << "', second value with type '"
      << type< T2>::name() << "' in '" << mVarName2  << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgPair< T1, T2>::dump


template< typename T1, typename T2>
   void TypedArgPair< T1, T2>::assign( const std::string& value, bool inverted)
{
   TypedArg< T1>::assign( value, inverted);
   mDestVar2 = mValue2;
} // TypedArgPair< T1, T2>::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_PAIR_HPP


// =====  END OF typed_arg_pair.hpp  =====

