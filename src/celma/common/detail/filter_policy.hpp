
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
/// See documentation of classes celma::common::detail::NoFilter and
/// celma::common::detail::EmptyLineFilter.


#ifndef CELMA_COMMON_DETAIL_FILTER_POLICY_HPP
#define CELMA_COMMON_DETAIL_FILTER_POLICY_HPP


#include <string>


namespace celma { namespace common { namespace detail {


/// Default filter policy: Does not filter anything.
/// @since  x.y.z, 13.04.2016
class NoFilter
{
protected:
   /// Policy method, does not do anything.
   /// @return  Always \c false.
   /// @since  x.y.z, 13.04.2016
   bool filter( const std::string&) const
   {
      return false;
   } // NoFilter::filter

}; // NoFilter


/// Empty line filter policy: Does filter out empty lines.
/// @since  x.y.z, 13.04.2016
class EmptyLineFilter
{
protected:
   /// Policy method. Filters out empty lines.
   /// @param[in]  line  The line to check.
   /// @return  \c true if the line is empty.
   /// @since  x.y.z, 13.04.2016
   bool filter( const std::string& line) const
   {
      return line.empty();
   } // EmptyLineFilter::filter

}; // EmptyLineFilter


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_FILTER_POLICY_HPP


// ========================  END OF filter_policy.hpp  ========================

