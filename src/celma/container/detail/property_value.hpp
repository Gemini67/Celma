
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::container::detail::PropertyValue<>.


#pragma once


#include <iostream>
#include <string>
#include "celma/container/detail/property_entry.hpp"


namespace celma::container::detail {


/// Stores a property, i.e. a named value.
///
/// @tparam  T  The type of the value.
/// @since  1.22.0, 19.10.2016
template< typename T> class PropertyValue final : public PropertyEntry
{
public:
   /// Constructor.
   ///
   /// @param[in]  name
   ///    The name of the property.
   /// @param[in]  full_path_name
   ///    The full path and name of a link destination. Not used here.
   /// @param[in]  value
   ///    The value of the property.
   /// @since  1.22.0, 19.10.2016
   PropertyValue( const std::string& name, const std::string& full_path_name,
      const T& value);

   /// Empty, virtual destructor.
   ///
   /// @since  1.22.0, 19.10.2016
   ~PropertyValue() override = default;

   /// Returns the value.
   ///
   /// @return  The value.
   /// @since  1.22.0, 19.10.2016
   const T& getValue() const;
   
   /// Prints the value stored in the object.
   ///
   /// @param[in]  os
   ///    The stream to write to.
   /// @param[in]  indent
   ///    Required by base class, ignored here.
   /// @since  1.22.0, 19.10.2016
   void dump( std::ostream& os, std::string indent) const override;

private:
   /// The value of the property.
   const T  mValue;

}; // PropertyValue< T>


// inlined methods
// ===============


template< typename T>
   PropertyValue< T>::PropertyValue( const std::string& name,
      const std::string&, const T& value):
      PropertyEntry( name, Types::value),
      mValue( value)
{
} // PropertyValue< T>::PropertyValue


template< typename T> const T& PropertyValue< T>::getValue() const
{
   return mValue;
} // PropertyValue< T>::getValue
   

template< typename T>
   void PropertyValue< T>::dump( std::ostream& os, std::string) const
{
   os << mValue << '\n';
} // PropertyValue< T>::dump


} // namespace celma::container::detail


// =====  END OF property_value.hpp  =====

