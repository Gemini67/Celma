
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
/// See documentation of class celma::log::filter::detail::DuplicatePolicyIgnore.


#pragma once


#include "celma/log/filter/detail/i_duplicate_policy.hpp"


namespace celma::log::filter::detail {


/// Implementation of the duplicate handler policy 'ignore': Leave existing
/// filter unchanged.
/// @since  1.15.1, 09.01.2018  (moved into namespace log::filter)
/// @since  0.3, 19.06.2016
class DuplicatePolicyIgnore final : public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   ~DuplicatePolicyIgnore() override = default;

   /// Returns the policy type.
   /// @return  Policy \a dpIgnore.
   /// @since  0.3, 19.06.2016
   DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::ignore;
   } // DuplicatePolicyIgnore::policy

   /// Policy: Always return \c false.
   /// @return  \c false.
   /// @since  0.3, 19.06.2016
   bool acceptNew() const override
   {
      return false;
   } // DuplicatePolicyIgnore::acceptNew

}; // DuplicatePolicyIgnore


} // namespace celma::log::filter::detail


// =====  END OF duplicate_policy_ignore.hpp  =====

