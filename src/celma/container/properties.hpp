
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::Properties.


#pragma once


#include <iosfwd>
#include <string>
#include "celma/container/detail/property_iterator.hpp"
#include "celma/container/detail/property_cont.hpp"


namespace celma::container {


/// Stores properties, configuration parameters etc.<br>
/// Generally, a property is a value with a name. Of course the name is the key,
/// and the value is stored in the native format (e.g. std::string, int
/// etc.).<br>
/// Names are unique on each level, e.g. there can only be one 'Name', but it is
/// possible to store multiple values for a name, e.g. in a vector.<br>
/// It is also possible to build a hierarchical structure, then the path to a
/// value is the list of names concatenated by the specified separator, which is
/// defaulted to '.'.<br>
/// Finally it is possible to add a link from one name to another name (or
/// hierarchy). Afterwards, the values can be accessed using the original path
/// and name, or the one created with the link. It is also possible to add
/// entries using the link path, and of course these entries will be available
/// through both paths.
///
/// @since  1.22.0, 19.10.2016
class Properties
{
public:
   /// Constructor.
   ///
   /// @param[in]  separator  The spearator to use for this instance.
   /// @since  1.22.0, 19.10.2016
   explicit Properties( char separator = '.');

   /// Don't copy this object.
   Properties( const Properties&) = delete;
   /// Don't assign to this object.
   Properties& operator =( const Properties&) = delete;
   /// Default destructor is fine.
   ~Properties() = default;

   /// Special version for adding a property where the value is provided as a
   /// character pointer. The value is then stored as an std::string.
   ///
   /// @param[in]  name
   ///    The name of the property, may be a path.
   /// @param[in]  value
   ///    The value to store for this property.
   /// @return
   ///    - \c true if the property (value) could be addd/stored.
   ///    - \c false if the given path conflicts with an existing property
   ///      value.
   /// @since  1.22.0, 19.10.2016
   bool addProperty( const std::string& name, const char* value);

   /// Stores a (new) value for the specified property.
   ///
   /// @tparam  The type of the value.
   /// @param[in]  name
   ///    The name of the property, may be a path.
   /// @param[in]  value
   ///    The value to store for this property.
   /// @return
   ///    - \c true if the property (value) could be addd/stored.
   ///    - \c false if the given path conflicts with an existing property
   ///      value.
   /// @since  1.22.0, 19.10.2016
   template< typename T>
      bool addProperty( const std::string& name, const T& value);

   /// Returns if a property with the specified name exists.
   ///
   /// @param[in]  name  The name to check for.
   /// @return  \c true if the specified property exists.
   /// @since  1.22.0, 19.10.2016
   bool hasProperty( const std::string& name) const;

   /// Returns the value of the specified property.
   ///
   /// @tparam  T  The type of the value.
   /// @param[out]  value
   ///    Returns the value of the property, if found.
   /// @param[in]   name
   ///    The name of the property, may be a path.
   /// @return  \c true if the property with the specified name was found.
   /// @since  1.22.0, 19.10.2016
   template< typename T>
      bool getProperty( T& value, const std::string& name) const;

   /// Creates an entry under \a link that points to the \a from entry, which
   /// may be a property map or a value.
   ///
   /// @param[in]  link
   ///    The path and name of the link to create.
   /// @param[in]  from
   ///    The path and name of the existing property entry (value or map) to
   ///    which the new link should point.
   /// @return
   ///    \c true if the link could be created, i.e. the destination entry was
   ///    found.
   /// @since
   ///    1.22.0, 19.03.2019
   bool addLink( const std::string& link, const std::string& from);

   /// Using our own iterator implementation that handles maps in maps.
   using iterator = detail::PropertyIterator;

   /// Returns an iterator pointing to the first property value.
   ///
   /// @return  Iterator pointing to the first property value.
   /// @since  1.22.0, 12.03.2019
   [[nodiscard]] iterator begin();

   /// Returns an iterator pointing behind the last property entry.
   ///
   /// @return  Iterator pointing behind the last property entry.
   /// @since  1.22.0, 12.03.2019
   [[nodiscard]] iterator end();

   /// Insertion operator for a Properties object.<br>
   /// Prints all property values, one per line as "name = value", displaying
   /// sub-trees by indented blocks.<br>
   /// Links are shown by their name and the entry they link to. Since the
   /// position of the link destination is not known at this time, "[?]" is
   /// printed before the name of the destination entry.
   ///
   /// @param[out]  os
   ///    The stream to write to.
   /// @param[in]   props
   ///    The object to dump the contents of.
   /// @return  The stream as passed in.
   /// @since  1.22.0, 19.10.2016
   friend std::ostream& operator <<( std::ostream& os, const Properties& props);

private:
   /// The separator character to use.
   const char            mSeparator;
   /// The properties.
   detail::PropertyCont  mProperties;

}; // Properties


// inlined methods
// ===============


inline bool Properties::addProperty( const std::string& name, const char* value)
{
   return mProperties.addProperty( name, name, std::string( value), mSeparator);
} // Properties::addProperty


template< typename T>
   bool Properties::addProperty( const std::string& name, const T& value)
{
   return mProperties.addProperty( name, name, value, mSeparator);
} // Properties::addProperty


inline bool Properties::hasProperty( const std::string& name) const
{
   return mProperties.hasProperty( name, mSeparator);
} // Properties::hasProperty


template< typename T>
   bool Properties::getProperty( T& value, const std::string& name) const
{
   return mProperties.getProperty( value, name, mSeparator);
} // Properties::getProperty


inline typename Properties::iterator Properties::begin()
{
   return iterator( mProperties, mSeparator);
} // Properties::begin


inline typename Properties::iterator Properties::end()
{
   return iterator();
} // Properties::end


} // namespace celma::container


// =====  END OF properties.hpp  =====

