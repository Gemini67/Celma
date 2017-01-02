
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
/// See documentation of template class celma::common::string_from.<br>
/// Code copied from
/// http://stackoverflow.com/questions/23999573/convert-a-number-to-a-string-literal-with-constexpr,
/// answer from user tclamb. Thank you very much!


#ifndef CELMA_COMMON_CONSTEXPR_STRING_FROM_HPP
#define CELMA_COMMON_CONSTEXPR_STRING_FROM_HPP


#include "celma/common/detail/constexpr_string_from.hpp"


namespace celma { namespace common {


/// Finally, the template to use to get a constrexpr string conversion of the
/// specified integer value.
/// @tparam  Integer  The type of the value to convert.
/// @tparam  num      The value to convert.
/// @since  0.10, 31.12.2016
template< typename Integer, Integer num>
   struct string_from: detail::explode< (num < 0), detail::cabs( num)>
{
}; // string_from


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CONSTEXPR_STRING_FROM_HPP


// ====================  END OF constexpr_string_from.hpp  ====================

