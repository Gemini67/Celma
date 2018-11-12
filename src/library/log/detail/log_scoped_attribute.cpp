
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::ScopedAttribute.


// module header file include
#include "celma/log/detail/log_scoped_attribute.hpp"


// project includes
#include "celma/log/logging.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor, adds the log attribute to the global log(ging) object.
///
/// @param[in]  name
///    The name of the attribute.
/// @param[in]  value
///    The value to insert for this attribute.
/// @since
///    1.15.0, 11.10.2018
ScopedAttribute::ScopedAttribute( const std::string& name,
   const std::string& value):
      mAttributeName( name)
{

   Logging::instance().addAttribute( name, value);
} // ScopedAttribute::ScopedAttribute



/// Destructor, removes the attribute again.
///
/// @since  1.15.0, 11.10.2018
ScopedAttribute::~ScopedAttribute()
{

   Logging::instance().removeAttribute( mAttributeName);

} // ScopedAttribute::~ScopedAttribute



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF log_scoped_attribute.cpp  =====

