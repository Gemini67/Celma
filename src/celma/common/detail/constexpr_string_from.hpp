
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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


#ifndef CELMA_COMMON_DETAIL_CONSTEXPR_STRING_FROM_HPP
#define CELMA_COMMON_DETAIL_CONSTEXPR_STRING_FROM_HPP


#include <cstdint>


namespace celma { namespace common { namespace detail {


/// Here we actually create the string representation of the digits of the
/// original number.<br>
/// Specialisation for a positive value.
///
/// @tparam  digits  The single digits of the original number.
/// @since  0.10, 31.12.2016
template< uint8_t... digits> struct positive_to_chars
{
   static constexpr const char value[] = { ('0' + digits)..., 0};
}; // positive_to_chars< digits...>

template< uint8_t... digits>
   constexpr const char positive_to_chars< digits...>::value[];


/// Here we actually create the string representation of the digits of the
/// original number.<br>
/// Specialisation for a negative value.
///
/// @tparam  digits  The single digits of the original number.
/// @since  0.10, 31.12.2016
template< uint8_t... digits> struct negative_to_chars
{
   static constexpr const char value[] = { '-', ('0' + digits)..., 0};
}; // negative_to_chars< digits...>


template< uint8_t... digits>
   constexpr const char negative_to_chars< digits...>::value[];


/// Converts a positive number to a character string.
///
/// @tparam  neg        \c true if the value is negative, but only \c false case
///                     is handled here.
/// @tparam  digits...  Sequence of the digits of the original number.
/// @since  0.10, 31.12.2016
template< bool neg, uint8_t... digits>
   struct to_chars: positive_to_chars< digits...>
{
}; // to_chars< digits...>


/// Converts a negative number to a character string.
///
/// @tparam  neg = true  Partial specialisation for negative numbers.
/// @tparam  digits...   Sequence of the digits of the original number.
/// @since  0.10, 31.12.2016
template< uint8_t... digits>
   struct to_chars< true, digits...>: negative_to_chars< digits...>
{
}; // to_chars< digits...>


/// Handles values > 10. Gets the value of the last digit, calls itself with the
/// remaining value.
///
/// @tparam  neg     \c true if the value is negative.
/// @tparam  rem     The remaining value to convert.
/// @tparam  digits  The single digits of the value.
/// @since  0.10, 31.12.2016
template< bool neg, uintmax_t rem, uint8_t... digits>
   struct explode: explode< neg, rem / 10, rem % 10, digits...>
{
}; // explode< neg, rem, digits...>


/// Handles the final value < 10.
///
/// @tparam  neg     \c true if the value is negative.
/// @tparam  digits  The single digits of the value.
/// @since  0.10, 31.12.2016
template< bool neg, uint8_t... digits>
   struct explode< neg, 0, digits...>: to_chars< neg, digits...>
{
}; // explode< neg, digits...>


/// Absolute value.
///
/// @tparam  T  The type of the value.
/// @param[in]  num  The value to return the absolute value of.
/// @return  The absolute value of \a num.
/// @since  0.10, 31.12.2016
template< typename T> constexpr uintmax_t cabs( T num)
{
   return (num < 0) ? -num : num;
} // cabs


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_CONSTEXPR_STRING_FROM_HPP


// =====  END OF constexpr_string_from.hpp  =====

