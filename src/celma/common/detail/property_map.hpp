
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::PropertyMap.


#ifndef CELMA_COMMON_DETAIL_PROPERTY_MAP_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_MAP_HPP


#include <iosfwd>
#include <map>
#include <string>
#include "celma/common/detail/name_path_remain.hpp"
#include "celma/common/detail/property_entry.hpp"
#include "celma/common/detail/property_value.hpp"


namespace celma { namespace common { namespace detail {


/// Handles a property map which can contain values and property maps.
/// @since  1.2, 19.10.2016
class PropertyMap: public PropertyEntry
{
public:
   /// Constructor.
   /// @param[in]  name  The name of the subtree entry.
   /// @since  1.2, 19.10.2016
   explicit PropertyMap( const std::string& name);

   /// Destructor, clears the entries in the map.
   /// @since  1.2, 19.10.2016
   virtual ~PropertyMap();

   /// Adds a property, i.e. a named value.<br>
   /// If the property already exists, the value is overwritten.
   /// @tparam  T  The type of the value.
   /// @param[in]  name       The name of the property, may be a path.
   /// @param[in]  value      The value of the property.
   /// @param[in]  separator  The separator character to use to split the path.
   /// @since  1.2, 19.10.2016
   template< typename T> void addProperty( const std::string& name,
                                           const T& value,
                                           char separator);

   /// Returns if a property with the specified name exists.
   /// @param[in]  name       The name of the property, may be a path.
   /// @param[in]  separator  The separator character to use to split the path.
   /// @return  \c true if a property with the specified name exists.
   /// @since  1.2, 19.10.2016
   bool hasProperty( const std::string& name, char separator) const;

   /// Returns the value of the specified property.
   /// @tparam  T  The type of the value.
   /// @param[out]  value     Returns the value of the property, if found.
   /// @param[in]   name      The name of the property, may be a path.
   /// @param[in]  separator  The separator character to use to split the path.
   /// @return  \c true if the property with the specified name was found.
   /// @since  1.2, 19.10.2016
   template< typename T> bool getProperty( T& value, const std::string& name,
                                           char separator) const;

   /// Dumps the contents of the map.
   /// @param[in]  os      The stream to write to.
   /// @param[in]  indent  Indent string.
   /// @since  1.2, 19.10.2016
   virtual void dump( std::ostream& os, std::string indent = "") const override;

private:
   /// The type used for the property tree internally.
   typedef std::map< std::string, PropertyEntry*>  map_t;

   /// The container with the properties.
   map_t  mProperties;

}; // PropertyMap


// inlined methods
// ===============


template< typename T> void PropertyMap::addProperty( const std::string& name,
                                                     const T& value,
                                                     char separator)
{
   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      const detail::NamePathRemain  npr( name, separator);
      auto                          subtree_iter = mProperties.find( npr.firstName());
      if (subtree_iter == mProperties.end())
         subtree_iter = mProperties.insert( map_t::value_type( npr.firstName(),
                                                               new PropertyMap( npr.firstName()))).first;
      auto  subtree = static_cast< PropertyMap*>( subtree_iter->second);
      subtree->addProperty( npr.remain(), value, separator);
   } else
   {
      auto  value_entry_iter = mProperties.find( name);
      if (value_entry_iter != mProperties.end())
      {
         // because the type could change, and because the members in
         // PropertyValue are const: delete existing entry, create a new one
         delete value_entry_iter->second;
         value_entry_iter->second = new PropertyValue< T>( name, value);
      } else
      {
         mProperties.insert( map_t::value_type( name,
                             new PropertyValue< T>( name, value)));
      } // end if
   } // end if
} // PropertyMap::addProperty


template< typename T> bool PropertyMap::getProperty( T& value,
                                                     const std::string& name,
                                                     char separator) const
{
   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      const detail::NamePathRemain  npr( name, separator);
      auto const                    subtree_iter = mProperties.find( npr.firstName());
      if (subtree_iter == mProperties.end())
         return false;
      auto const  subtree = static_cast< const PropertyMap*>( subtree_iter->second);
      return subtree->getProperty( value, npr.remain(), separator);
   } // end if

   auto const  value_entry_iter = mProperties.find( name);
   if (value_entry_iter == mProperties.end())
      return false;

   auto const  value_entry = static_cast< const PropertyValue< T>*>( value_entry_iter->second);
   value = value_entry->getValue();
   return true;
} // PropertyMap::getProperty


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_MAP_HPP


// =========================  END OF property_map.hpp  =========================

