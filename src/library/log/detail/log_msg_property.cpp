
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogMsgProperty.


#include "celma/log/detail/log_msg_property.hpp"


namespace celma { namespace log { namespace detail {



void LogMsgProperty::addProperty( const std::string& property_name,
                                  const std::string& property_value)
{

   mProperties.push_back( property_t( property_name, property_value));

} // LogMsgProperty::addProperty



const std::string
   LogMsgProperty::getPropertyValue( const std::string& property_name) const
{

   for (auto const& property : mProperties)
   {
      if (std::get< 0>( property) == property_name)
         return std::get< 1>( property);
   } // end for

   return std::string();
} // LogMsg::getPropertyValue



} // namespace detail
} // namespace log
} // namespace celma


// =======================  END OF log_msg_property.cpp  =======================

