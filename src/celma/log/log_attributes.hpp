
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::LogAttributes.


#ifndef CELMA_LOG_LOG_ATTRIBUTES_HPP
#define CELMA_LOG_LOG_ATTRIBUTES_HPP


#include <string>
#include "celma/log/detail/log_attributes_container.hpp"


namespace celma { namespace log {


/// Allows to store attributes and their values and to build a hierarchy of log
/// attributes.<br>
/// Use this class to manage attributes with a scope like a class:
/// - Create an object of this class in your class (or whatever scope you need).
/// - Add the values for the atteibutes you want to use in this scope.
/// - Pass the log attributes object to the log messages/message objects, either
///   by using the corresponding macros or doint it manually: Simply pass the
///   object as stream input parameter.
/// - Afterwards, when the value for an attribute is requested, log attributes
///   objects and their attributes/values have precedence over the global log
///   attributes.
/// - You can also build a hierarchy of log attributes objects: Pass the parent/
///   master log attribute object to the log attribute object in the lower
///   scope, e.g. in a subclass.
/// - Afterwards it depends, which log attribute object you pass to the log
///   message. Normally this would be the object with the nearest scope.
/// - Then, log attribute values are first searched for in the log attribute
///   objects, then in the parent object(s), and finally in the global logging
///   object (last step does not happen here).
///
/// @since  x.y.z, 16.10.2018
class LogAttributes: public detail::LogAttributesContainer
{
public:
   /// Default constructor, initialises an empty attribute container and no
   /// parent object.
   ///
   /// @since  x.y.z, 16.10.2018
   LogAttributes() = default;

   /// Constructor, immediately adds the attribute value to the internal
   /// container.
   ///
   /// @param[in] attr_name  The name of the attribute.
   /// @param[in] attr_value The value for the attribute.
   /// @since  x.y.z, 16.10.2018
   LogAttributes( const std::string& attr_name, const std::string& attr_value);

   /// Not the copy constructor, but a destructor that stores the pointer to a
   /// parent/master log attributes object.
   ///
   /// @param[in]  outer  Pointer to the parent/master log attributes object.
   /// @since  x.y.z, 16.10.2018
   explicit LogAttributes( const LogAttributes* outer);

   /// Returns the value for the given attribute.<br>
   /// If no attribute with the given name is found, an empty string is
   /// returned.<br>
   /// If multiple atributes with the same name exist, the value of the last
   /// attribute is returned.
   ///
   /// @param[in]  attr_name  The name of the attribute to return the value of.
   /// @return
   ///    The value of the requested attribute, an empty string when not found.
   /// @since  x.y.z, 16.10.2018
   std::string getAttribute( const std::string& attr_name) const;

private:
   /// Pointer to the optional parent/master log attributes object.
   const LogAttributes* const  mpOuter = nullptr;

}; // LogAttributes


} // namespace log
} // namespace celma


#endif   // CELMA_LOG_LOG_ATTRIBUTES_HPP


// =====  END OF log_attributes.hpp  =====

