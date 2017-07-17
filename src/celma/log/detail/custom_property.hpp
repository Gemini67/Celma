
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
/// See documentation of class celma::log::detail::customProperty.


#ifndef CELMA_LOG_DETAIL_CUSTOM_PROPERTY_HPP
#define CELMA_LOG_DETAIL_CUSTOM_PROPERTY_HPP


#include <string>


namespace celma { namespace log { namespace detail {


/// Since this class is used as IO-manipulator for the StreamLog, it does not
/// follow the usual naming convention.
/// @since  0.11, 12.12.2016
class customProperty
{
public:
   explicit customProperty( const std::string& name):
      mPropertyName( name)
   {
   }

   const std::string& name() const
   {
      return mPropertyName;
   } // customProperty::name
   
private:
   const std::string  mPropertyName;
   
}; // customProperty


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_CUSTOM_PROPERTY_HPP


// =======================  END OF custom_property.hpp  =======================

