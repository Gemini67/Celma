
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
/// See documentation of enum celma::log::detail::DuplicatePolicy.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_HPP


namespace celma { namespace log { namespace detail {


/// List of ways how duplicate filter entries should be handled.<br>
/// This could also be implemented using a policy, but then this class would
/// become a template, and the classes derived from it would become templates
/// too, so we stick to the enum.
enum class DuplicatePolicy
{
   ignore,      //!< Ignore new filter settings when such a filter already exists.
   exception,   //!< Throw an exception if such a filter already exists.
   replace      //!< Replace already existing filter.
};


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_HPP


// =======================  END OF duplicate_policy.hpp  =======================

