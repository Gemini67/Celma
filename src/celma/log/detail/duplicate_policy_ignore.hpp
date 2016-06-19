
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
/// See documentation of class celma::log::detail::DuplicatePolicyIgnore.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_IGNORE_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_IGNORE_HPP


#include "celma/log/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace detail {


/// Implementation of the duplicate handler policy 'ignore': Leave existing
/// filter unchanged.
/// @since  0.3, 19.06.2016
class DuplicatePolicyIgnore: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~DuplicatePolicyIgnore() { }

   /// Returns the policy type.
   /// @return  Policy \a dpIgnore.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const
   {
      return dpIgnore;
   } // end DuplicatePolicyIgnore::policy

   /// Policy: Always return \c false.
   /// @return  \c false.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const
   {
      return false;
   } // end DuplicatePolicyIgnore::acceptNew

}; // DuplicatePolicyIgnore


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_IGNORE_HPP


// ===================  END OF duplicate_policy_ignore.hpp  ===================

