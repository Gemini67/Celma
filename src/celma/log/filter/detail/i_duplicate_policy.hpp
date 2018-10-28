
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
/// See documentation of class celma::log::filter::detail::IDuplicatePolicy.


#ifndef CELMA_LOG_FILTER_DETAIL_I_DUPLICATE_POLICY_HPP
#define CELMA_LOG_FILTER_DETAIL_I_DUPLICATE_POLICY_HPP


#include "celma/log/filter/detail/duplicate_policy.hpp"


namespace celma { namespace log { namespace filter { namespace detail {


/// Interface definition class for duplicate (filter) handling policies.
/// @since  x.y.z, 09.01.2018  (moved into namespace log::filter)
/// @since  0.3, 19.06.2016
class IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~IDuplicatePolicy() = default;

   /// Must be implemented by derived classes: Return the policy type.
   /// @return  In derived classes: The policy implemented by this object.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const = 0;

   /// Must be implemented by derived classes: If a filter of a specific type
   /// already exists when a nerw filter should be set, returns if the new
   /// filter value should be used.
   /// @return  \c true if the new filter value should be used.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const noexcept( false) = 0;

}; // IDuplicatePolicy


} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_I_DUPLICATE_POLICY_HPP


// =====  END OF i_duplicate_policy.hpp  =====

