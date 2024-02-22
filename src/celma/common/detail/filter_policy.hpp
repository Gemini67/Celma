
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
/// See documentation of classes celma::common::detail::NoFilter and
/// celma::common::detail::EmptyLineFilter.


#pragma once


#include <string>


namespace celma::common::detail {


/// Default filter policy: Does not filter anything.
/// @since  1.3.0, 13.04.2016
class NoFilter
{
protected:
   /// Policy method, does not do anything.
   /// @returns  Always \c false.
   /// @since  1.3.0, 13.04.2016
   [[nodiscard]] bool filter( const std::string&) const
   {
      return false;
   } // NoFilter::filter

}; // NoFilter


/// Empty line filter policy: Does filter out empty lines.
/// @since  1.3.0, 13.04.2016
class EmptyLineFilter
{
protected:
   /// Policy method. Filters out empty lines.
   /// @param[in]  line  Line to check.
   /// @returns  \c true if the line is empty.
   /// @since  1.3.0, 13.04.2016
   [[nodiscard]] bool filter( const std::string& line) const
   {
      return line.empty();
   } // EmptyLineFilter::filter

}; // EmptyLineFilter


} // namespace celma::common::detail


// =====  END OF filter_policy.hpp  =====

