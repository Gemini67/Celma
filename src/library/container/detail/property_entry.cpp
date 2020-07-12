
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


// module header file include
#include "celma/container/detail/property_entry.hpp"


namespace celma::container::detail {



/// Constructor.
///
/// @param[in]  name
///    The name of the entry.
/// @param[in]  my_type
///    The type of the entry.
/// @since  1.22.0, 19.10.2016
PropertyEntry::PropertyEntry( const std::string& name, Types my_type):
   mName( name),
   mType( my_type)
{
} // PropertyEntry::PropertyEntry



} // namespace celma::container::detail


// =====  END OF property_entry.cpp  =====

