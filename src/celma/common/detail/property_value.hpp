
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::PropertyValue.


#ifndef CELMA_COMMON_DETAIL_PROPERTY_VALUE_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_VALUE_HPP


#include <iostream>
#include <string>
#include "celma/common/detail/property_entry.hpp"


namespace celma { namespace common { namespace detail {


/// Stores a property, i.e. a named value.
/// @tparam  T  The type of the value.
/// @since  1.2, 19.10.2016
template< typename T> class PropertyValue: public PropertyEntry
{
public:
   /// Constructor.
   /// @param[in]  name   The name of the property.
   /// @param[in]  value  The value of the property.
   /// @since  1.2, 19.10.2016
   PropertyValue( const std::string& name, const T& value);

   /// Empty, virtual destructor.
   /// @since  1.2, 19.10.2016
   virtual ~PropertyValue() = default;

   /// Returns the value.
   /// @return  The value.
   /// @since  1.2, 19.10.2016
   const T& getValue() const;
   
   /// Prints the value stored in the object.
   /// @param[in]  os  The stream to write to.
   /// @param[in]      Required by base class, ignored here.
   /// @since  1.2, 19.10.2016
   virtual void dump( std::ostream& os, std::string) const override;

private:
   /// The value of the property.
   const T  mValue;

}; // PropertyValue< T>


// inlined methods
// ===============


template< typename T>
   PropertyValue< T>::PropertyValue( const std::string& name, const T& value):
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


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_VALUE_HPP


// ========================  END OF property_value.hpp  ========================

