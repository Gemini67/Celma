
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of type celma::common::detail::property_map_t.


#ifndef CELMA_COMMON_DETAIL_PROPERTY_MAP_T_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_MAP_T_HPP


#include <map>
#include <string>
#include "celma/common/detail/property_entry.hpp"


namespace celma { namespace common { namespace detail {


/// The type used for the property tree internally in the property container.<br>
/// Definition moved here to get rid of circular dependencies.
using property_map_t = std::map< std::string, PropertyEntry*>;


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_MAP_T_HPP


// =====  END OF property_map_t.hpp  =====

