
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


// module header file include
#include "celma/log/log_attributes.hpp"


using std::string;


namespace celma { namespace log {



/// Constructor, immediately adds the attribute value to the internal
/// container.
///
/// @param[in] attr_name  The name of the attribute.
/// @param[in] attr_value The value for the attribute.
/// @since  1.15.0, 16.10.2018
LogAttributes::LogAttributes( const string& attr_name, const string& attr_value):
   detail::LogAttributesContainer()
{

   addAttribute( attr_name, attr_value);

} // LogAttributes::LogAttributes



/// Not the copy constructor, but a destructor that stores the pointer to a
/// parent/master log attributes object.
///
/// @param[in]  outer  Pointer to the parent/master log attributes object.
/// @since  1.15.0, 16.10.2018
LogAttributes::LogAttributes( const LogAttributes* outer):
   detail::LogAttributesContainer(),
   mpOuter( outer)
{
} // LogAttributes::LogAttributes



/// Returns the value for the given attribute.<br>
/// If no attribute with the given name is found, an empty string is
/// returned.<br>
/// If multiple atributes with the same name exist, the value of the last
/// attribute is returned.
///
/// @param[in]  attr_name  The name of the attribute to return the value of.
/// @return
//     The value of the requested attribute, an empty string when not found.
/// @since  1.15.0, 16.10.2018
string LogAttributes::getAttribute( const string& attr_name) const
{

   auto  my_attr = detail::LogAttributesContainer::getAttribute( attr_name);


   if (my_attr.empty() && (mpOuter != nullptr))
      return mpOuter->getAttribute( attr_name);

   return my_attr;
} // LogAttributes::getAttribute



} // namespace log
} // namespace celma


// =====  END OF log_attributes.cpp  =====

