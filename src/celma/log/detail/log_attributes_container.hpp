
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
/// See documentation of class celma::log::detail::LogAttributesContainer.


#ifndef CELMA_LOG_DETAIL_LOG_ATTRIBUTES_CONTAINER_HPP
#define CELMA_LOG_DETAIL_LOG_ATTRIBUTES_CONTAINER_HPP


#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>


namespace celma { namespace log { namespace detail {


/// Used to store attributes (named values) that may be inserted into log
/// messages.<br>
/// All attributes that are added are stored internally, even if e.g. an
/// attribute with the same name would already exist.<br>
/// When the value of an attribute is requested, the value of the latest added
/// attribute with the given name is returned.
///
/// @since  1.15.0, 10.10.2018  (new attempt to integrate into the library)
/// @since  1.15.0, 16.03.2018
///    (completed functionality, renamed from LogAttributes, no singleton
///    anymore)
/// @since  1.15.0, 19.06.2016
class LogAttributesContainer
{
public:
   /// Default constructor.
   /// @since  0.3, 16.03.2018
   LogAttributesContainer() = default;

   LogAttributesContainer( const LogAttributesContainer&) = delete;
   LogAttributesContainer& operator =( const LogAttributesContainer&) = delete;

   /// Default destructor.
   ///
   /// @since  1.15.0, 21.03.2018
   ~LogAttributesContainer() = default;

   /// Adds an attribute with type string to the internal list of attributes.
   ///
   /// @param[in]  attr_name
   ///    The name of the attribute.
   /// @param[in]  attr_value
   ///    The value of the attribute.
   /// @since  1.15.0, 19.06.2016
   void addAttribute( const std::string& attr_name, const std::string& attr_value);

   /// Adds an attribute with "any" type to the internal list of attributes.<br>
   /// The type of the attribute value must be convertible to string.
   ///
   /// @tparam  T
   ///    The type of the attribute value.
   /// @param[in]  attr_name
   ///    The name of the attribute.
   /// @param[in]  attr_value
   ///    The value of the attribute.
   /// @since  1.15.0, 19.06.2016
   template< typename T>
      void addAttribute( const std::string& attr_name, T value);

   /// Returns the value for the given attribute.<br>
   /// If no attribute with the given name is found, an empty string is
   /// returned.<br>
   /// If multiple atributes with the same name exist, the value of the last
   /// attribute is returned.
   ///
   /// @param[in]  attr_name  The name of the attribute to return the value of.
   /// @return
   //     The value of the requested attribute, an empty string when not found.
   /// @since  1.15.0, 16.03.2018
   std::string getAttribute( const std::string& attr_name) const;

   /// Removes the atribute that was added last.
   ///
   /// @since  1.15.0, 16.03.2018
   void removeAttribute();

   /// Removes the latest added attribute with the given name.
   ///
   /// @param[in]  attr_name  The name of the attribute to erase.
   /// @since  1.15.0, 20.03.2018
   void removeAttribute( const std::string& attr_name);

private:
   /// Value type stored in the internal container.
   using attr_pair_t = std::pair< std::string, std::string>;
   /// Type of the internal container where the attributes are stored.
   using attr_cont_t = std::vector< attr_pair_t>;

   /// The container in which the attributes and their values are stored.
   attr_cont_t  mAttributes;

}; // LogAttributesContainer


// inlined methods
// ===============


template< typename T>
   void LogAttributesContainer::addAttribute( const std::string& attr_name, T value)
{
   addAttribute( attr_name, boost::lexical_cast< std::string>( value));
} // LogAttributesContainer::addAttribute


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_ATTRIBUTES_CONTAINER_HPP


// =====  END OF log_attributes_container.hpp  =====

