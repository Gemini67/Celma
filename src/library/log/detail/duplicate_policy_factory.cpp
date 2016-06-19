
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


// module header file include
#include "celma/log/detail/duplicate_policy_factory.hpp"


#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/duplicate_policy_ignore.hpp"
#include "celma/log/detail/duplicate_policy_replace.hpp"
#include "celma/log/detail/duplicate_policy_throw.hpp"


namespace celma { namespace log { namespace detail {



/// Creates the object that implements the specified policy.
/// @param[in]  policy  The policy to create the object for.
/// @return  Pointer to the newly created object.
/// @since  0.3, 19.06.2016
IDuplicatePolicy* DuplicatePolicyFactory::createPolicy( DuplicatePolicy policy)
{

   switch (policy)
   {
   case dpIgnore:   return new DuplicatePolicyIgnore;
   case dpThrow:    return new DuplicatePolicyThrow;
   case dpReplace:  return new DuplicatePolicyReplace;
   default:         throw CELMA_RuntimeError( "invalid value for duplicate policy");
   } // end switch
} // end DuplicatePolicyFactory::createPolicy



} // namespace detail
} // namespace log
} // namespace celma


// ===================  END OF duplicate_policy_factory.cpp  ===================

