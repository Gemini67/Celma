
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for types provided by Celma itself.


#pragma once


#include "celma/common/constexpr_string_concat.hpp"
#include "celma/common/constexpr_string_from.hpp"
#include "celma/common/detail/type_name.hpp"
#include "celma/common/fixed_string.hpp"
#include "celma/container/dynamic_bitset.hpp"


namespace celma {


/// Specialisation of type<> for type 'celma::container::DynamicBitset'.
///
/// @since  1.37.0, 28.06.2020
template<> class type< container::DynamicBitset>
{
public:
   /// Returns the name of the type.
   ///
   /// @return  'celma::container::DynamicBitset>'.
   /// @since  1.37.0, 28.06.2020
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< container::DynamicBitset>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName = "celma::container::DynamicBitset";

}; // type< celma::container::DynamicBitset>


/// Specialisation for type 'celma::common::FixedString<>'.
///
/// @tparam  L  The maximum length of the fixed string.
/// @since  1.46.0, 16.03.2021
template< std::size_t L> class type< common::FixedString< L>>
{
public:
   /// Returns the name of the type.
   /// @return  'celma::common::FixedString< <number> >' (without the spaces).
   /// @since  1.46.0, 16.03.2021
   static constexpr const char* name()
   {
      return mName.data();
   } // type< common::FixedString< L>>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( "celma::common::FixedString< ",
         common::string_from< std::size_t, L>::value, ">");

}; // type< common::FixedString< L>>


} // namespace celma


// =====  END OF type_name_celma.hpp  =====

