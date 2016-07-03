
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See description of class celma::reflection::detail::ReflectedField.


#ifndef CELMA_REFLECTION_RELFECTED_FIELD_HPP
#define CELMA_REFLECTION_RELFECTED_FIELD_HPP


#include <string>
#include <boost/lexical_cast.hpp>
#include "celma/common/type_name.hpp"
#include "celma/reflection/detail/i_reflected_field.hpp"


namespace celma { namespace reflection { namespace detail {


/// This class actually handles the access to a reflected field.
/// @tparam  T  The type of the field/variable.
/// @since  0.4, 02.05.2016
template< typename T> class ReflectedField: public IReflectedField
{
public:
   /// Constructor.
   /// @param[in]  name       The name of the field/variable.
   /// @param[in]  value_ref  The variable.
   /// @since  0.4, 02.05.2016
   ReflectedField( const std::string& name, T& value_ref);

   /// Sets a new value.
   /// @param[in]  new_value  The new value to set.
   /// @since  0.4, 02.05.2016
   void set( const T& new_value) noexcept( true);

   /// Returns the current value.
   /// @return  The current value.
   /// @since  0.4, 02.05.2016
   const T& get() const noexcept( true);

   /// Returns the value of the variable as string.
   /// @return  The current value as string.
   /// @since  0.4, 02.07.2016
   virtual const std::string str() const  noexcept( false) override;

protected:
   /// The variable.
   T&  mValueRef;

}; // ReflectedField


// inlined methods
// ===============


template< typename T>
   ReflectedField< T>::ReflectedField( const std::string& name, T& value_ref):
   IReflectedField( name, type< T>::name()),
   mValueRef( value_ref)
{
} // end ReflectedField< T>::ReflectedField


template< typename T>
   void ReflectedField< T>::set( const T& new_value) noexcept( true)
{
   mValueRef = new_value;
} // end ReflectedField< T>::set


template< typename T> const T& ReflectedField< T>::get() const noexcept( true)
{
   return mValueRef;
} // end ReflectedField< T>::get


template< typename T>
   const std::string ReflectedField< T>::str() const noexcept( false)
{
   return boost::lexical_cast< std::string>( mValueRef);
} // end ReflectedField< T>::str


} // namespace detail
} // namespace reflection
} // namespace celma


#endif   // CELMA_REFLECTION_RELFECTED_FIELD_HPP


// =======================  END OF reflected_field.hpp  =======================

