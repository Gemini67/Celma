
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


// module header file include
#include "celma/common/detail/property_cont.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/common/clear_container.hpp"


namespace celma { namespace common { namespace detail {



/// Constructor.
///
/// @param[in]  name  The name of the subtree entry.
/// @since  1.2, 19.10.2016
PropertyCont::PropertyCont( const std::string& name):
   PropertyEntry( name, Types::map),
   mProperties()
{
} // PropertyCont::PropertyCont



/// Destructor, clears the entries in the map.
///
/// @since  1.2, 19.10.2016
PropertyCont::~PropertyCont()
{

   Map::clear( mProperties);   

} // PropertyCont::~PropertyCont



/// Returns if a property with the specified name exists.
///
/// @param[in]  name
///    The name of the property, may be a path.
/// @param[in]  separator
///    The separator character to use to split the path.
/// @return  \c true if a property with the specified name exists.
/// @since  1.2, 19.10.2016
bool PropertyCont::hasProperty( const std::string& name, char separator) const
{

   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      detail::NamePathRemain  npr( name, separator);
      auto const              subtree_iter = mProperties.find( npr.firstName());
      if (subtree_iter == mProperties.end())
         return false;
      auto  subtree = static_cast< PropertyCont*>( subtree_iter->second);
      return subtree->hasProperty( npr.remain(), separator);
   } // end if

   return mProperties.find( name) != mProperties.end();
} // PropertyCont::hasProperty



/// Dumps the contents of the map.
///
/// @param[in]  os
///    The stream to write to.
/// @param[in]  indent
///    Indent string.
/// @since  1.2, 19.10.2016
void PropertyCont::dump( std::ostream& os, std::string indent) const
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

} // PropertyCont::dump



/// Searches for an entry with the given path.
///
/// @param[in]  name
///    The path and name of the entry to search for.
/// @param[in]  separator
///    Path separator character.
/// @return
///    A pair of values: A boolean that is set to \c true if the entry was
///    found, and an iterator that points to the entry.
/// @since  1.22.0, 19.03.2019
typename PropertyCont::result_t
   PropertyCont::findEntry( const std::string& name, char separator) const
{

   if (detail::NamePathRemain::nameHasSeparator( name, separator))
   {
      const detail::NamePathRemain  npr( name, separator);
      auto                          subtree_iter = mProperties.find( npr.firstName());

      if ((subtree_iter == mProperties.end())
          || (subtree_iter->second->entryType() != PropertyEntry::Types::map))
         return result_t( false, mProperties.end());

      auto  subtree = static_cast< PropertyCont*>( subtree_iter->second);
      return subtree->findEntry( npr.remain(), separator);
   } // end if

   auto  entry_iter = mProperties.find( name);
   return result_t( entry_iter != mProperties.end(), entry_iter);
} // PropertyCont::findEntry



} // namespace detail
} // namespace common
} // namespace celma


// =====  END OF property_cont.cpp  =====

