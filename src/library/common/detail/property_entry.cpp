
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
/// See documentation of class celma::common::detail::PropertyEntry.


// module header file include
#include "celma/common/detail/property_entry.hpp"


namespace celma { namespace common { namespace detail {



/// Constructor.
///
/// @param[in]  name
///    The name of the entry.
/// @param[in]  my_type
///    The type of the entry.
/// @since  1.2, 19.10.2016
PropertyEntry::PropertyEntry( const std::string& name, Types my_type):
   mName( name),
   mType( my_type)
{
} // PropertyEntry::PropertyEntry



} // namespace detail
} // namespace common
} // namespace celma


// =====  END OF property_entry.cpp  =====

