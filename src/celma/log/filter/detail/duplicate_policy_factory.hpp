
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
/// See documentation of class celma::log::filer::detail::DuplicatePolicyFactory.


#ifndef CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_FACTORY_HPP
#define CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_FACTORY_HPP


#include "celma/log/filter/detail/duplicate_policy.hpp"


namespace celma { namespace log { namespace filter { namespace detail {


class IDuplicatePolicy;


/// Factory class that creates the duplicate policy handler object for the
/// specified policy.
/// @since  1.15.1, 09.01.2018  (moved into namespace log::filter)
/// @since  0.3, 19.06.2016
class DuplicatePolicyFactory
{
public:
   /// Creates the object that implements the specified policy.
   /// @param[in]  policy  The policy to create the object for.
   /// @return  Pointer to the newly created object.
   /// @since  0.3, 19.06.2016
   static IDuplicatePolicy* createPolicy( DuplicatePolicy policy) noexcept( false);

private:
   /// Don't need to create object(s) of this class.
   DuplicatePolicyFactory();

}; // DuplicatePolicyFactory


} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_DUPLICATE_POLICY_FACTORY_HPP


// =====  END OF duplicate_policy_factory.hpp  =====

