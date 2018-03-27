
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
/// See documentation of class celma::log::detail::DuplicatePolicyReplace.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_REPLACE_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_REPLACE_HPP


#include "celma/log/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace detail {


/// Implementation of the duplicate handler policy 'replace': Replace existing
/// filter with new filter object/value.
/// @since  0.3, 19.06.2016
class DuplicatePolicyReplace: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~DuplicatePolicyReplace() { }

   /// Returns the policy type.
   /// @return  Policy \a dpReplace.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::replace;
   } // end DuplicatePolicyReplace::policy

   /// Policy: Always return \c true.
   /// @return  \c true.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const override
   {
      return true;
   } // end DuplicatePolicyReplace::acceptNew

}; // DuplicatePolicyReplace


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_REPLACE_HPP


// ===================  END OF duplicate_policy_replace.hpp  ===================

