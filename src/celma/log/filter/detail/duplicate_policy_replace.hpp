
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filter::detail::DuplicatePolicyReplace.


#ifndef CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_REPLACE_HPP
#define CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_REPLACE_HPP


#include "celma/log/filter/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace filter { namespace detail {


/// Implementation of the duplicate handler policy 'replace': Replace existing
/// filter with new filter object/value.
/// @since  1.15.1, 09.01.2018  (moved into namespace log::filter)
/// @since  0.3, 19.06.2016
class DuplicatePolicyReplace: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   ~DuplicatePolicyReplace() override = default;

   /// Returns the policy type.
   /// @return  Policy \a dpReplace.
   /// @since  0.3, 19.06.2016
   DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::replace;
   } // DuplicatePolicyReplace::policy

   /// Policy: Always return \c true.
   /// @return  \c true.
   /// @since  0.3, 19.06.2016
   bool acceptNew() const override
   {
      return true;
   } // DuplicatePolicyReplace::acceptNew

}; // DuplicatePolicyReplace


} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_REPLACE_HPP


// =====  END OF duplicate_policy_replace.hpp  =====

