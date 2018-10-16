
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


#ifndef CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP
#define CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP


#include <string>
#include <tuple>
#include <vector>


namespace celma { namespace log { namespace detail {


/// It is possible to use "custom properties" in the definition of the format of
/// a log message. This class is then used to store the values of these
/// properties , so they can be inserted into the log message.
///
/// @since x.y.z, 11.12.2016
class LogMsgProperty
{
public:
   /// Default constructor.
   ///
   /// @since  x.y.z, 16.03.2018
   LogMsgProperty() = default;

   /// Copying of such an object should not be necessary.
   ///
   /// @since  x.y.z, 16.03.2018
   LogMsgProperty( const LogMsgProperty&) = delete;

   /// Default destructor.
   ///
   /// @since  x.y.z, 16.03.2018
   ~LogMsgProperty() = default;

   /// Adds the value of a property to the internal container.
   ///
   /// @param[in]  property_name
   ///    The name of the property.
   /// @param[in]  property_value
   ///    The value for the property.
   /// @since  x.y.z, 12.12.2016
   void addProperty( const std::string& property_name,
                     const std::string& property_value);

   /// Returns the value stored for the given property name.<br>
   /// If the name of the property is unknown, an empty string is returned.
   ///
   /// @param[in]  property_name
   ///    The name of the property to return the value for.
   /// @return  The value stored for this property or an empty string.
   /// @since  x.y.z, 12.12.2016
   const std::string getPropertyValue( const std::string& property_name) const;

private:
   /// Storage type in the container: Property name and value.
   using property_t = std::tuple< std::string, std::string>;
   /// Type of the container to store the property name and value.
   using property_cont_t = std::vector< property_t>;

   /// Container used to store the values for the properties.
   property_cont_t  mProperties;

}; // LogMsgProperty


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP


// =====  END OF log_msg_property.hpp  =====

