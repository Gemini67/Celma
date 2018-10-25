
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


#ifndef CELMA_LOG_DETAIL_SCOPED_ATTRIBUTE_HPP
#define CELMA_LOG_DETAIL_SCOPED_ATTRIBUTE_HPP


#include <string>


namespace celma { namespace log { namespace detail {


/// Small helper class to manage a scoped log attribute:
/// A log attribute that is only visible/valid within a specific scope.<br>
/// When the object is ceated, the log attribute is added, and when the object
/// is deleted, the log attribute is removed again.
///
/// @since  1.15.0, 11.10.2018  (redesigned)
class ScopedAttribute
{
public:
   /// Constructor, adds the log attribute to the global log(ging) object.
   ///
   /// @param[in]  name
   ///    The name of the attribute.
   /// @param[in]  value
   ///    The value to insert for this attribute.
   /// @since
   ///    1.15.0, 11.10.2018
   ScopedAttribute( const std::string& name, const std::string& value);

   /// Destructor, removes the attribute again.
   ///
   /// @since  1.15.0, 11.10.2018
   ~ScopedAttribute();

private:
   /// The name of the attribute. Used to remove the attribute again.
   const std::string  mAttributeName;

}; // ScopedAttribute


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_SCOPED_ATTRIBUTE_HPP


// =====  END OF log_scoped_attribute.hpp  =====

