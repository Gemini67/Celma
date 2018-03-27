
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
/// See documentation of class celma::log::detail::DuplicatePolicyException.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP


#include <stdexcept>
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace detail {


/// Implementation of the duplicate handler policy 'exception': Throw an
/// exception.
/// @since  0.11, 06.12.2016  (renamed from DuplicatePolicyThrow)
/// @since  0.3, 19.06.2016
class DuplicatePolicyException: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~DuplicatePolicyException() { }

   /// Returns the policy type.
   /// @return  Policy \a dpThrow.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const override
   {
      return DuplicatePolicy::exception;
   } // end DuplicatePolicyException::policy

   /// Policy: Always throws.
   /// @return  Nothing, actually.
   /// @throw  Always CELMA_RuntimeError.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const noexcept( false) override
   {
      throw CELMA_RuntimeError( "filter already defined");
   } // endDuplicatePolicyException::acceptNew

}; // DuplicatePolicyException


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_EXCEPTION_HPP


// ==================  END OF duplicate_policy_exception.hpp  ==================

