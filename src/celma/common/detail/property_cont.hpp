
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::PropertyCont.


#ifndef CELMA_COMMON_DETAIL_PROPERTY_CONT_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_CONT_HPP


#include <iosfwd>
#include <string>
#include "celma/common/detail/name_path_remain.hpp"
#include "celma/common/detail/property_entry.hpp"
#include "celma/common/detail/property_factory.hpp"
#include "celma/common/detail/property_map_t.hpp"
#include "celma/common/detail/property_value.hpp"


namespace celma { namespace common { namespace detail {


/// Handles a property map which can contain values and property maps.
///
/// @since  x.y.z, 19.10.2016
class PropertyCont: public PropertyEntry
{
public:
   /// Constructor.
   ///
   /// @param[in]  name  The name of the subtree entry.
   /// @since  x.y.z, 19.10.2016
   explicit PropertyCont( const std::string& name);

   /// Destructor, clears the entries in the map.
   ///
   /// @since  x.y.z, 19.10.2016
   virtual ~PropertyCont();

   /// Adds a property, i.e. a named value.<br>
   /// If the property already exists, the value is overwritten.
   ///
   /// @tparam  T  The type of the value.
   /// @param[in]  name
   ///    The name of the property, may be a path.
   /// @param[in]  value
   ///    The value of the property.
   /// @param[in]  separator
   ///    The separator character to use to split the path.
   /// @return
   ///    \c true if the property could be stored, \c false when the path name
   ///    conflicts with an existing property value.
   /// @since  x.y.z, 19.10.2016
   template< typename T>
      bool addProperty( const std::string& name,
         const std::string& full_path_name, const T& value, char separator);

   /// Returns if a property with the specified name exists.
   ///
   /// @param[in]  name
   ///    The name of the property, may be a path.
   /// @param[in]  separator
   ///    The separator character to use to split the path.
   /// @return  \c true if a property with the specified name exists.
   /// @since  x.y.z, 19.10.2016
   bool hasProperty( const std::string& name, char separator) const;

   /// Returns the value of the specified property.
   ///
   /// @tparam  T  The type of the value.
   /// @param[out]  value
   ///    Returns the value of the property, if found.
   /// @param[in]   name
   ///    The name of the property, may be a path.
   /// @param[in]  separator
   ///    The separator character to use to split the path.
   /// @return  \c true if the property with the specified name was found.
   /// @since  x.y.z, 19.10.2016
   template< typename T>
      bool getProperty( T& value, const std::string& name, char separator) const;

   /// Dumps the contents of the map.
   ///
   /// @param[in]  os
   ///    The stream to write to.
   /// @param[in]  indent
   ///    Indent string.
   /// @since  x.y.z, 19.10.2016
   virtual void dump( std::ostream& os, std::string indent = "") const override;

   /// Returns the internal container in which the properties are stored.
   ///
   /// @return  The internal property container.
   /// @since  x.y.z, 20.03.2019
   property_map_t& map();

   /// Returns the internal container in which the properties are stored.
   ///
   /// @return  The internal property container.
   /// @since  x.y.z, 20.03.2019
   const property_map_t& map() const;

   using result_t = std::pair< bool, typename property_map_t::const_iterator>;

   /// Searches for an entry with the given path.
   ///
   /// @param[in]  name
   ///    The path and name of the entry to search for.
   /// @param[in]  separator
   ///    Path separator character.
   /// @return
   ///    A pair of values: A boolean that is set to \c true if the entry was
   ///    found, and an iterator that points to the entry.
   /// @since  x.y.z, 19.03.2019
   result_t findEntry( const std::string& name, char separator) const;

private:
   /// The container with the properties.
   property_map_t  mProperties;

}; // PropertyCont


// inlined methods
// ===============


template< typename T>
   bool PropertyCont::addProperty( const std::string& name,
      const std::string& full_path_name, const T& value,
      char separator)
{
   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      const detail::NamePathRemain  npr( name, separator);
      auto                          subtree_iter = mProperties.find( npr.firstName());
      if (subtree_iter == mProperties.end())
         subtree_iter = mProperties.emplace(
            npr.firstName(), new PropertyCont( npr.firstName())).first;
      else if (subtree_iter->second->entryType() == PropertyEntry::Types::value)
         return false;

      if (subtree_iter->second->entryType() == PropertyEntry::Types::link)
      {
         // link must point to a map
         auto  link_entry = static_cast< PropertyLink*>( subtree_iter->second);
         auto  linked_entry = link_entry->iterator()->second;
         if (linked_entry->entryType() != PropertyEntry::Types::map)
            return false;

         auto  map_entry = static_cast< PropertyCont*>( linked_entry);
         return map_entry->addProperty( npr.remain(), full_path_name, value,
            separator);
      } // end if

      auto  subtree = static_cast< PropertyCont*>( subtree_iter->second);
      return subtree->addProperty( npr.remain(), full_path_name, value,
         separator);
   } // end if

   auto  value_entry_iter = mProperties.find( name);
   if (value_entry_iter != mProperties.end())
   {
      if (value_entry_iter->second->entryType() != PropertyEntry::Types::value)
         return false;

      // because the type could change, and because the members in
      // PropertyValue are const: delete existing entry, create a new one
      delete value_entry_iter->second;
      value_entry_iter->second = propertyFactory( name, full_path_name, value);
   } else
   {
      mProperties.emplace( name, propertyFactory( name, full_path_name, value));
   } // end if

   return true;
} // PropertyCont::addProperty


template< typename T>
   bool PropertyCont::getProperty( T& value, const std::string& name,
      char separator) const
{
   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      const detail::NamePathRemain  npr( name, separator);
      auto const                    subtree_iter = mProperties.find( npr.firstName());
      if ((subtree_iter == mProperties.end())
          || (subtree_iter->second->entryType() == PropertyEntry::Types::value))
         return false;

      if (subtree_iter->second->entryType() == PropertyEntry::Types::link)
      {
         // link must point to a map
         auto const  link_entry = static_cast< const PropertyLink*>( subtree_iter->second);
         auto const  linked_entry = link_entry->iterator()->second;
         if (linked_entry->entryType() != PropertyEntry::Types::map)
            return false;

         auto const  map_entry = static_cast< const PropertyCont*>( linked_entry);
         return map_entry->getProperty( value, npr.remain(), separator);
      } // end if

      auto const  subtree = static_cast< const PropertyCont*>( subtree_iter->second);
      return subtree->getProperty( value, npr.remain(), separator);
   } // end if

   auto const  value_entry_iter = mProperties.find( name);
   if ((value_entry_iter == mProperties.end())
       || (value_entry_iter->second->entryType() == PropertyEntry::Types::map))
      return false;

   if (value_entry_iter->second->entryType() == PropertyEntry::Types::link)
   {
      // end of path reached, so entry pointed to by the link must be value
      auto const  link_entry = static_cast< const PropertyLink*>( value_entry_iter->second);
      auto const  linked_entry = link_entry->iterator()->second;
      if (linked_entry->entryType() != PropertyEntry::Types::value)
         return false;

      auto const  value_entry = static_cast< const PropertyValue< T>*>( linked_entry);
      value = value_entry->getValue();
      return true;
   } // end if

   auto const  value_entry = static_cast< const PropertyValue< T>*>( value_entry_iter->second);
   value = value_entry->getValue();
   return true;
} // PropertyCont::getProperty


inline property_map_t& PropertyCont::map()
{
   return mProperties;
} // PropertyCont::map


inline const property_map_t& PropertyCont::map() const
{
   return mProperties;
} // PropertyCont::map


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_CONT_HPP


// =====  END OF property_cont.hpp  =====

