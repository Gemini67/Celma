
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
/// See documentation of class celma::log::filter::detail::DuplicatePolicyIgnore.


#ifndef CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_IGNORE_HPP
#define CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_IGNORE_HPP


#include "celma/log/filter/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace filter { namespace detail {


/// Implementation of the duplicate handler policy 'ignore': Leave existing
/// filter unchanged.
/// @since  x.y.z, 09.01.2018  (moved into namespace log::filter)
/// @since  0.3, 19.06.2016
class DuplicatePolicyIgnore: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~DuplicatePolicyIgnore() = default;

   /// Returns the policy type.
   /// @return  Policy \a dpIgnore.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::ignore;
   } // DuplicatePolicyIgnore::policy

   /// Policy: Always return \c false.
   /// @return  \c false.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const override
   {
      return false;
   } // DuplicatePolicyIgnore::acceptNew

}; // DuplicatePolicyIgnore


} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_IGNORE_HPP


// =====  END OF duplicate_policy_ignore.hpp  =====

