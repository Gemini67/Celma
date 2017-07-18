
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


// module header file include
#include "celma/common/detail/property_map.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/common/clear_container.hpp"


namespace celma { namespace common { namespace detail {



/// Constructor.
/// @param[in]  name  The name of the subtree entry.
/// @since  1.2, 19.10.2016
PropertyMap::PropertyMap( const std::string& name):
   PropertyEntry( name, Types::map),
   mProperties()
{
} // PropertyMap::PropertyMap



/// Destructor, clears the entries in the map.
/// @since  1.2, 19.10.2016
PropertyMap::~PropertyMap()
{

   Map::clear( mProperties);   

} // PropertyMap::~PropertyMap



/// Returns if a property with the specified name exists.
/// @param[in]  name       The name of the property, may be a path.
/// @param[in]  separator  The separator character to use to split the path.
/// @return  \c true if a property with the specified name exists.
/// @since  1.2, 19.10.2016
bool PropertyMap::hasProperty( const std::string& name, char separator) const
{

   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      detail::NamePathRemain  npr( name, separator);
      auto const              subtree_iter = mProperties.find( npr.firstName());
      if (subtree_iter == mProperties.end())
         return false;
      auto  subtree = static_cast< PropertyMap*>( subtree_iter->second);
      return subtree->hasProperty( npr.remain(), separator);
   } // end if

   return mProperties.find( name) != mProperties.end();
} // PropertyMap::hasProperty



/// Dumps the contents of the map.
/// @param[in]  os      The stream to write to.
/// @param[in]  indent  Indent string.
/// @since  1.2, 19.10.2016
void PropertyMap::dump( std::ostream& os, std::string indent) const
{

   if (!mName.empty())
   {
      os << indent << mName << ":\n";
      indent.append( "   ");
   } // end if

   for (auto & curr_property : mProperties)
   {
      if (curr_property.second->entryType() == Types::value)
         os << indent << curr_property.first << " = ";
      curr_property.second->dump( os, indent);
   } // end for

} // PropertyMap::dump



} // namespace detail
} // namespace common
} // namespace celma


// =========================  END OF property_map.cpp  =========================

