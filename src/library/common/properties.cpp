
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


// module header file include
#include "celma/common/properties.hpp"


// C++ Standard Library includes
#include <iostream>


namespace celma { namespace common {



/// Constructor.
///
/// @param[in]  separator  The spearator to use for this instance.
/// @since  1.22.0, 19.10.2016
Properties::Properties( char separator):
   mSeparator( separator),
   mProperties( "")
{
} // Properties::Properties



/// Creates an entry under \a link that points to the \a from entry, which
/// may be a property map or a value.
///
/// @param[in]  link
///    The path and name of the link to create.
/// @param[in]  from
///    The path and name of the existing property entry (value or map) to
///    which the new link should point.
/// @returnindE
///    \c true if the link could be created, i.e. the destination entry was
///    found.
/// @since
///    1.22.0, 19.03.2019
bool Properties::addLink( const std::string& link, const std::string& from)
{

   auto  dest_entry = mProperties.findEntry( from, mSeparator);


   return dest_entry.first && mProperties.addProperty( link, from,
      dest_entry.second, mSeparator);
} // Properties::addLink



/// Insertion operator for a Properties object.
///
/// @param[out]  os
///    The stream to write to.
/// @param[in]   props
///    The object to dump the contents of.
/// @return  The stream as passed in.
/// @since  1.22.0, 19.10.2016
std::ostream& operator <<( std::ostream& os, const Properties& props)
{

   props.mProperties.dump( os);

   return os;
} // operator <<



} // namespace common
} // namespace celma


// =====  END OF properties.cpp  =====

