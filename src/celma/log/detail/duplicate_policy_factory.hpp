
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
/// See documentation of class celma::log::detail::DuplicatePolicyFactory.


#ifndef CELMA_LOG_DETAIL_DUPLICATE_POLICY_FACTORY_HPP
#define CELMA_LOG_DETAIL_DUPLICATE_POLICY_FACTORY_HPP


#include "celma/log/detail/duplicate_policy.hpp"


namespace celma { namespace log { namespace detail {


class IDuplicatePolicy;


/// Factory class that creates the duplicate policy handler object for the
/// specified policy.
/// @since  0.3, 19.06.2016
class DuplicatePolicyFactory
{
public:
   /// Creates the object that implements the specified policy.
   /// @param[in]  policy  The policy to create the object for.
   /// @return  Pointer to the newly created object.
   /// @since  0.3, 19.06.2016
   static IDuplicatePolicy* createPolicy( DuplicatePolicy policy);

private:
   /// Don't need to create object(s) of this class.
   DuplicatePolicyFactory();

}; // DuplicatePolicyFactory


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_DUPLICATE_POLICY_FACTORY_HPP


// ===================  END OF duplicate_policy_factory.hpp  ===================

