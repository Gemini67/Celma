
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
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


/// Used as stream manipulator that stores the name of the custom property
/// until it is stored through the creator in the log format definition
/// object.<br>
/// Since this class is used as IO-manipulator for the StreamLog, it does not
/// follow the usual naming convention.
/// @since  x.y.z, 12.12.2016
class customProperty
{
public:
   /// Constructor. Stores the name of the property.
   /// @param[in]  name  The name of the property to store.
   /// @since  x.y.z, 12.12.2016
   explicit customProperty( const std::string& name):
      mPropertyName( name)
   {
   } // customProperty::customProperty

   /// Returns the name of the custom property.
   /// @return  The name of the custom property.
   /// @since  x.y.z, 12.12.2016
   const std::string& name() const
   {
      return mPropertyName;
   } // customProperty::name
   
private:
   /// The name of the custom property to store.
   const std::string  mPropertyName;
   
}; // customProperty


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_CUSTOM_PROPERTY_HPP


// =======================  END OF custom_property.hpp  =======================

