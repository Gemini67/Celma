
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
/// See documentation of class celma::common::Properties.


#ifndef CELMA_COMMON_PROPERTIES_HPP
#define CELMA_COMMON_PROPERTIES_HPP


#include <iosfwd>
#include <string>
#include "celma/common/detail/property_iterator.hpp"
#include "celma/common/detail/property_map.hpp"


namespace celma { namespace common {


/// Stores properties, configuration parameters etc.<br>
/// Generally, a property is a value with a name. Of course the name is the key,
/// and the value is stored in the native format (e.g. std::string, int
/// etc.).<br>
/// Names are unique, e.g. there can only be one 'Name', but it is possible to
/// store multiple values for a name, e.g. in a vector.<br>
/// It is also possible to build a hierarchical structure, then the path to a
/// value is the list of names concatenated by the specified separator, which is
/// defaulted to '.'.<br>
/// Finally it is possible to add a link from one name to another name (or
/// hierarchy).
///
/// @since  1.2, 19.10.2016
class Properties
{
public:
   /// Constructor.
   ///
   /// @param[in]  separator  The spearator to use for this instance.
   /// @since  1.2, 19.10.2016
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
   /// @since  1.2, 19.10.2016
   void addProperty( const std::string& name, const char* value);

   /// Stores a (new) value for the specified property.
   ///
   /// @tparam  The type of the value.
   /// @param[in]  name
   ///    The name of the property, may be a path.
   /// @param[in]  value
   ///    The value to store for this property.
   /// @since  1.2, 19.10.2016
   template< typename T>
      void addProperty( const std::string& name, const T& value);

   /// Returns if a property with the specified name exists.
   ///
   /// @param[in]  name  The name to check for.
   /// @return  \c true if the specified property exists.
   /// @since  1.2, 19.10.2016
   bool hasProperty( const std::string& name) const;

   /// Returns the value of the specified property.
   ///
   /// @tparam  T  The type of the value.
   /// @param[out]  value
   ///    Returns the value of the property, if found.
   /// @param[in]   name
   ///    The name of the property, may be a path.
   /// @return  \c true if the property with the specified name was found.
   /// @since  1.2, 19.10.2016
   template< typename T>
      bool getProperty( T& value, const std::string& name) const;

   /// Using our own iterator implementation that handles maps in maps.
   using iterator = detail::PropertyIterator;

   /// Returns an iterator pointing to the first property value.
   ///
   /// @return  Iterator pointing to the first property value.
   /// @since  x.y.z, 12.03.2019
   iterator begin();

   /// Returns an iterator pointing behind the last property entry.
   ///
   /// @return  Iterator pointing behind the last property entry.
   /// @since  x.y.z, 12.03.2019
   iterator end();

   /// Insertion operator for a Properties object.
   ///
   /// @param[out]  os
   ///    The stream to write to.
   /// @param[in]   props
   ///    The object to dump the contents of.
   /// @return  The stream as passed in.
   /// @since  1.2, 19.10.2016
   friend std::ostream& operator <<( std::ostream& os, const Properties& props);

private:
   /// The separator character to use.
   const char           mSeparator;
   /// The properties.
   detail::PropertyMap  mProperties;

}; // Properties


// inlined methods
// ===============


inline void Properties::addProperty( const std::string& name, const char* value)
{
   mProperties.addProperty( name, std::string( value), mSeparator);
} // Properties::addProperty


template< typename T>
   void Properties::addProperty( const std::string& name, const T& value)
{
   mProperties.addProperty( name, value, mSeparator);
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


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_PROPERTIES_HPP


// =====  END OF properties.hpp  =====

