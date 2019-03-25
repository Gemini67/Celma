
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
/// See documentation of functions celma::common::detail::propetyFactory().


#ifndef CELMA_COMMON_DETAIL_PROPERTY_FACTORY_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_FACTORY_HPP


#include <string>
#include "celma/common/detail/property_entry.hpp"
#include "celma/common/detail/property_link.hpp"
#include "celma/common/detail/property_map_t.hpp"
#include "celma/common/detail/property_value.hpp"


namespace celma { namespace common { namespace detail {


/// Creates a property entry that contains a value.
///
/// @tparam  T  The type of the value to store in the entry.
/// @param[in]  name
///    The name of the new entry.
/// @param[in]  full_path_name
///    The full path and name of a link destination.
/// @param[in]  value
///    The value to store as property.
/// @return  New propety value object.
/// @since  x.y.z, 20.03.2019
template< typename T> PropertyEntry* propertyFactory( const std::string& name,
   const std::string& full_path_name, const T& value)
{
   return new PropertyValue< T>( name, full_path_name, value);
} // propertyFactory


/// Creates a property entry that contains a link to another entry.
///
/// @param[in]  name
///    The name of the link entry.
/// @param[in]  full_path_name
///    The full path and name of a link destination.
/// @param[in]  link_dest
///    The iterator pointing to the other entry to link to.
/// @return  New propety link object.
/// @since  x.y.z, 20.03.2019
inline PropertyEntry* propertyFactory( const std::string& name,
   const std::string& full_path_name,
   const property_map_t::const_iterator link_dest)
{
   return new PropertyLink( name, full_path_name, link_dest);
} // propertyFactory


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_FACTORY_HPP


// =====  END OF property_factory.hpp  =====

