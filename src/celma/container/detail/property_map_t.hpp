
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of type celma::container::detail::property_map_t.


#ifndef CELMA_CONTAINER_DETAIL_PROPERTY_MAP_T_HPP
#define CELMA_CONTAINER_DETAIL_PROPERTY_MAP_T_HPP


#include <map>
#include <string>
#include "celma/container/detail/property_entry.hpp"


namespace celma::container::detail {


/// The type used for the property tree internally in the property container.<br>
/// Definition moved here to get rid of circular dependencies.
using property_map_t = std::map< std::string, PropertyEntry*>;


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_PROPERTY_MAP_T_HPP


// =====  END OF property_map_t.hpp  =====

