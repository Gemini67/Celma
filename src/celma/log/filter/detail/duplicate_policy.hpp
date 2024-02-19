
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
/// See documentation of enum celma::log::filter::detail::DuplicatePolicy.


#pragma once


#include <cstdint>


namespace celma::log::filter::detail {


/// List of ways how duplicate filter entries should be handled.<br>
/// This could also be implemented using a policy, but then this class would
/// become a template, and the classes derived from it would become templates
/// too, so we stick to the enum.
enum class DuplicatePolicy : uint8_t
{
   ignore,      //!< Ignore new filter settings when such a filter already exists.
   exception,   //!< Throw an exception if such a filter already exists.
   replace      //!< Replace already existing filter.
};


} // namespace celma::log::filter::detail


// =====  END OF duplicate_policy.hpp  =====

