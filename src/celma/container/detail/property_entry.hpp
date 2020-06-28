
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::detail::PropertyEntry.


#ifndef CELMA_CONTAINER_DETAIL_PROPERTY_ENTRY_HPP
#define CELMA_CONTAINER_DETAIL_PROPERTY_ENTRY_HPP


#include <iosfwd>
#include <string>


namespace celma::container::detail {


/// Base class for entries in the property map: Either a (property) map itself,
/// or a value with a specific type.
///
/// @since  1.22.0, 19.10.2016
class PropertyEntry
{
public:
   /// List of types of the entries in the property map:
   enum class Types
   {
      map,     //!< A map of values.
      value,   //!< A value.
      link     //!< A link to another property entry.
   };

   /// Default construction is not allowed.
   PropertyEntry() = delete;

   /// Constructor.
   ///
   /// @param[in]  name
   ///    The name of the entry.
   /// @param[in]  my_type
   ///    The type of the entry.
   /// @since  1.22.0, 19.10.2016
   PropertyEntry( const std::string& name, Types my_type);

   /// Empty, virtual destructor.
   ///
   /// @since  1.22.0, 19.10.2016
   virtual ~PropertyEntry() = default;

   /// Returns the name of the entry.
   ///
   /// @return  The name of the entry.
   /// @since  1.22.0, 19.10.2016
   const std::string& getName() const;

   /// Returns the type of the entry.
   ///
   /// @return  The type of the entry.
   /// @since  1.22.0, 19.10.2016
   Types entryType() const;

   /// Interface to dump the contents of an entry.
   ///
   /// @param[in]  os
   ///    The stream to write to.
   /// @param[in]  indent
   ///    Indent string.
   /// @since  1.22.0, 19.10.2016
   virtual void dump( std::ostream& os, std::string indent) const = 0;

protected:
   /// The name of the entry.
   const std::string  mName;
   /// The type of the entry.
   const Types        mType;

}; // PropertyEntry


// inlined methods
// ===============


inline const std::string& PropertyEntry::getName() const
{
   return mName;
} // PropertyEntry::getName


inline PropertyEntry::Types PropertyEntry::entryType() const
{
   return mType;
} // PropertyEntry::entryType


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_PROPERTY_ENTRY_HPP


// =====  END OF property_entry.hpp  =====

