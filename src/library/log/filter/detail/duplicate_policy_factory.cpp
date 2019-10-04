
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
/// See documentation of class celma::log::filter::detail::DuplicatePolicyFactory.


// module header file include
#include "celma/log/filter/detail/duplicate_policy_factory.hpp"


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/filter/detail/duplicate_policy_ignore.hpp"
#include "celma/log/filter/detail/duplicate_policy_replace.hpp"
#include "celma/log/filter/detail/duplicate_policy_exception.hpp"


namespace celma { namespace log { namespace filter { namespace detail {



/// Creates the object that implements the specified policy.
/// @param[in]  policy  The policy to create the object for.
/// @return  Pointer to the newly created object.
/// @since  0.3, 19.06.2016
IDuplicatePolicy* DuplicatePolicyFactory::createPolicy( DuplicatePolicy policy)
{

   switch (policy)
   {
   case DuplicatePolicy::ignore:     return new DuplicatePolicyIgnore;
   case DuplicatePolicy::exception:  return new DuplicatePolicyException;
   case DuplicatePolicy::replace:    return new DuplicatePolicyReplace;
   default:
      throw CELMA_RuntimeError( "invalid value for duplicate policy");
   } // end switch
} // DuplicatePolicyFactory::createPolicy



} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


// =====  END OF duplicate_policy_factory.cpp  =====

