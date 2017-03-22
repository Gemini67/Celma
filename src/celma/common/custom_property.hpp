
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
/// See documentation of class celma::common::customProperty.


#ifndef CELMA_COMMON_CUSTOM_PROPERTY_HPP
#define CELMA_COMMON_CUSTOM_PROPERTY_HPP


#include <string>


namespace celma { namespace common {


/// Since this class is used as IO-manipulator for the StreamLog, it does not
/// follow the usual naming convention.
/// @since  0.12, 12.12.2016
class customProperty
{
public:
   /// Constructor. Stores name of the property.
   /// @param[in]  name  The name of the property.
   /// @since  0.12, 12.12.2016
   explicit customProperty( const std::string& name):
      mPropertyName( name)
   {
   } // customProperty::customProperty

   /// Returns the internally stored name of the custom property.
   /// @return  The name of the property.
   /// @since  0.12, 12.12.2016
   const std::string& name() const
   {
      return mPropertyName;
   } // customProperty::name
   
private:
   /// The name of the property.
   const std::string  mPropertyName;
   
}; // customProperty


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CUSTOM_PROPERTY_HPP


// =======================  END OF custom_property.hpp  =======================

