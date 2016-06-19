
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
/// See documentation of class celma::log::detail::DuplicatePolicyThrow.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_THROW_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_THROW_HPP


#include <stdexcept>
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/i_duplicate_policy.hpp"


namespace celma { namespace log { namespace detail {


/// Implementation of the duplicate handler policy 'throw': Throw an exception.
/// @since  0.3, 19.06.2016
class DuplicatePolicyThrow: public IDuplicatePolicy
{
public:
   /// Virtual, empty destructor.
   /// @since  0.3, 19.06.2016
   virtual ~DuplicatePolicyThrow() { }

   /// Returns the policy type.
   /// @return  Policy \a dpThrow.
   /// @since  0.3, 19.06.2016
   virtual DuplicatePolicy policy() const
   {
      return dpThrow;
   } // end DuplicatePolicyThrow::policy

   /// Policy: Always throws.
   /// @return  Nothing, actually.
   /// @throw  Always CELMA_RuntimeError.
   /// @since  0.3, 19.06.2016
   virtual bool acceptNew() const noexcept( false)
   {
      throw CELMA_RuntimeError( "filter already defined");
   } // endDuplicatePolicyThrow::acceptNew

}; // DuplicatePolicyThrow


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_THROW_HPP


// ====================  END OF duplicate_policy_throw.hpp  ====================

