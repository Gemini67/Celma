
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
/// See documentation of class celma::log::filter::detail::DuplicatePolicyException.


#ifndef CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP
#define CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP


#include <stdexcept>
#include "celma/common/celma_exception.hpp"
#include "celma/log/filter/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace filter { namespace detail {


/// Implementation of the duplicate handler policy 'exception': Throw an
/// exception.
/// @since  1.15.1, 09.01.2018  (moved into namespace log::filter)
/// @since  0.11, 06.12.2016  (renamed from DuplicatePolicyThrow)
/// @since  0.3, 19.06.2016
class DuplicatePolicyException: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   ~DuplicatePolicyException() override = default;

   /// Returns the policy type.
   /// @return  Policy \a dpThrow.
   /// @since  0.3, 19.06.2016
   DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::exception;
   } // DuplicatePolicyException::policy

   /// Policy: Always throws.
   /// @return  Nothing, actually.
   /// @throw  Always CELMA_RuntimeError.
   /// @since  0.3, 19.06.2016
   bool acceptNew() const noexcept( false) override
   {
      throw CELMA_RuntimeError( "filter already defined");
   } // DuplicatePolicyException::acceptNew

}; // DuplicatePolicyException


} // namespace detail
} // namespace filer
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP


// =====  END OF duplicate_policy_exception.hpp  =====

