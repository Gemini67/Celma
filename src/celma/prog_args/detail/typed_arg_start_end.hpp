
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArgStartEnd<>.


#pragma once


#include <iostream>
#include "celma/prog_args/detail/typed_arg.hpp"


namespace celma::prog_args::detail {


// Template TypedArgStartEnd
// =========================


/// Special case: Two destination variables, the same value is assigned to the
/// second variable too if it has not been assigned a value yet.
///
/// @tparam  T
///    The type of the destination variables.
/// @since   x.y.z, 21.07.2020
template< typename T> class TypedArgStartEnd final : public TypedArg< T>
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest1
   ///    The first destination variable to store the parameter value in.
   /// @param[in]  vname1
   ///    The name of the first destination variable to store the parameter
   ///    value in.
   /// @param[in]  dest2
   ///    The second destination variable to store the given value in.
   /// @since   x.y.z, 21.07.2020
   TypedArgStartEnd( T& dest1, const std::string& vname1, T& dest2);

   /// Empty, virtual default destructor.
   ///
   /// @since   x.y.z, 21.07.2020
   ~TypedArgStartEnd() override = default;

private:
   /// Stores the value in the destination variable(s).
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since   x.y.z, 21.07.2020
   void assign( const std::string& value, bool inverted) override;

   using TypedArg< T>::mDestVar;

   T&       mDestVar2;
   const T  mDestVar2InitValue;

}; // TypedArgStartEnd< T>


// inlined methods
// ===============


template< typename T>
   TypedArgStartEnd< T>::TypedArgStartEnd( T& dest1, const std::string& vname1,
      T& dest2):
         TypedArg< T>( dest1, vname1),
         mDestVar2( dest2),
         mDestVar2InitValue( dest2)
{
} // TypedArgStartEnd< T>::TypedArgStartEnd


template< typename T>
   void TypedArgStartEnd< T>::assign( const std::string& value, bool inverted)
{
   TypedArg< T>::assign( value, inverted);
   if (mDestVar2 == mDestVar2InitValue)
      mDestVar2 = mDestVar;
} // TypedArgStartEnd< T>::assign


} // namespace celma::prog_args::detail


// =====  END OF typed_arg_start_end.hpp  =====

