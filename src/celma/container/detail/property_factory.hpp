
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
/// See documentation of functions celma::container::detail::propetyFactory().


#pragma once


#include <string>
#include "celma/container/detail/property_entry.hpp"
#include "celma/container/detail/property_link.hpp"
#include "celma/container/detail/property_map_t.hpp"
#include "celma/container/detail/property_value.hpp"


namespace celma::container::detail {


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
/// @since  1.22.0, 20.03.2019
template< typename T> [[nodiscard]] PropertyEntry*
   propertyFactory( const std::string& name, const std::string& full_path_name,
      const T& value)
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
/// @since  1.22.0, 20.03.2019
[[nodiscard]] inline PropertyEntry* propertyFactory( const std::string& name,
   const std::string& full_path_name,
   const property_map_t::const_iterator link_dest)
{
   return new PropertyLink( name, full_path_name, link_dest);
} // propertyFactory


} // namespace celma::container::detail


// =====  END OF property_factory.hpp  =====

