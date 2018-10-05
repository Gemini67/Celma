
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for the smart pointer types provided
/// by the STL.


#ifndef CELMA_TYPE_NAME_SMART_PTR_HPP
#define CELMA_TYPE_NAME_SMART_PTR_HPP


#include <memory>
#include "celma/common/detail/provide_template_type_name.hpp"


namespace celma {


PROVIDE_TEMPLATE_TYPE_NAME( std::shared_ptr);
PROVIDE_TEMPLATE_TYPE_NAME( std::unique_ptr);
PROVIDE_TEMPLATE_TYPE_NAME( std::weak_ptr);


} // namespace celma


#endif   // CELMA_TYPE_NAME_SMART_PTR_HPP


// =====  END OF smart_ptr_type_name.hpp  =====

