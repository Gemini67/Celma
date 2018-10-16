
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
/// See documentation of class celma::log::detail::LogMsgProperty.


// module header file include
#include "celma/log/detail/log_msg_property.hpp"


namespace celma { namespace log { namespace detail {


using std::string;



/// Adds the value of a property to the internal container.
///
/// @param[in]  property_name
///    The name of the property.
/// @param[in]  property_value
///    The value for the property.
/// @since  x.y.z, 12.12.2016
void LogMsgProperty::addProperty( const string& property_name,
                                  const string& property_value)
{

   mProperties.push_back( property_t( property_name, property_value));

} // LogMsgProperty::addProperty



/// Returns the value stored for the given property name.<br>
/// If the name of the property is unknown, an empty string is returned.
///
/// @param[in]  property_name
///    The name of the property to return the value for.
/// @return  The value stored for this property or an empty string.
/// @since  x.y.z, 12.12.2016
const string
   LogMsgProperty::getPropertyValue( const string& property_name) const
{

   for (auto const& property : mProperties)
   {
      if (std::get< 0>( property) == property_name)
         return std::get< 1>( property);
   } // end for

   return string();
} // LogMsgProperty::getPropertyValue



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF log_msg_property.cpp  =====

