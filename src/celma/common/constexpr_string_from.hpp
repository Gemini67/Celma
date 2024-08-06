
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::string_from.<br>
/// Code copied from
/// http://stackoverflow.com/questions/23999573/convert-a-number-to-a-string-literal-with-constexpr,
/// answer from user tclamb. Thank you very much!


#pragma once


#include "celma/common/detail/constexpr_string_from.hpp"


namespace celma::common {


/// Finally, the template to use to get a constexpr string conversion of the
/// specified integer value.
/// @tparam  Integer  The type of the value to convert.
/// @tparam  num      The value to convert.
/// @since  0.10, 31.12.2016
template< typename Integer, Integer num>
   struct string_from: detail::explode< (num < 0), detail::cabs( num)>
{
}; // string_from


} // namespace celma::common


// =====  END OF constexpr_string_from.hpp  =====

