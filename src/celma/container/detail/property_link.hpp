
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
/// See documentation of class celma::container::detail::PropertyLink.


#ifndef CELMA_CONTAINER_DETAIL_PROPERTY_LINK_HPP
#define CELMA_CONTAINER_DETAIL_PROPERTY_LINK_HPP


#include <iostream>
#include <string>
#include "celma/container/detail/property_entry.hpp"
#include "celma/container/detail/property_map_t.hpp"


namespace celma::container::detail {


/// Stores a link to another property.<br>
/// Since the entry could be replaced by a new entry e.g. when the value is
/// updated, the iterator pointing to the entry is stored, and not the pointer
/// to the entry itself.
///
/// @since  1.22.0, 20.03.2019
class PropertyLink: public PropertyEntry
{
public:
   /// Constructor.
   ///
   /// @param[in]  name
   ///    The name of the link.
   /// @param[in]  full_path_name
   ///    The full path and name of the destination of the link.
   /// @param[in]  dest
   ///    Iterator pointing to the other property to link to.
   /// @since  1.22.0, 20.03.2019
   PropertyLink( const std::string& name, const std::string& full_path_name,
      const property_map_t::const_iterator dest);

   /// Empty, virtual destructor.
   ///
   /// @since  1.22.0, 20.03.2019
   ~PropertyLink() override = default;

   /// Return s the internally stored iterator that points to the destination
   /// property.
   ///
   /// @return  The iterator pointing to the destination.
   /// @since  1.22.0, 21.03.2019
   property_map_t::const_iterator iterator() const;

   /// Prints the value stored in the object.
   ///
   /// @param[in]  os
   ///    The stream to write to.
   /// @param[in]  indent
   ///    Indent string.
   /// @since  1.22.0, 20.03.2019
   void dump( std::ostream& os, std::string indent) const override;

private:
   /// The full path and name of the destination of the link.
   const std::string                     mFullPathName;
   /// The pointer to the other property.
   const property_map_t::const_iterator  mDest;

}; // PropertyLink


// inlined methods
// ===============


inline PropertyLink::PropertyLink( const std::string& name,
   const std::string& full_path_name, const property_map_t::const_iterator dest):
      PropertyEntry( name, Types::link),
      mFullPathName( full_path_name),
      mDest( dest)
{
} // PropertyLink::PropertyLink


inline property_map_t::const_iterator PropertyLink::iterator() const
{
   return mDest;
} // PropertyLink::iterator


inline void PropertyLink::dump( std::ostream& os, std::string indent) const
{
   os << indent << mName << " -> " << mFullPathName << std::endl;
} // PropertyLink::dump


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_PROPERTY_LINK_HPP


// =====  END OF property_link.hpp  =====

