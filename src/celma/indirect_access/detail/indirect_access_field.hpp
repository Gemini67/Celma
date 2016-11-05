
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
/// See description of class celma::indirect_access::detail::IndirectAccessField.


#ifndef CELMA_INDIRECT_ACCESS_INDIRECT_ACCESS_FIELD_HPP
#define CELMA_INDIRECT_ACCESS_INDIRECT_ACCESS_FIELD_HPP


#include <string>
#include <boost/lexical_cast.hpp>
#include "celma/common/type_name.hpp"
#include "celma/indirect_access/detail/i_indirect_access_field.hpp"


namespace celma { namespace indirect_access { namespace detail {


/// This class actually handles the access indirect to a field.
/// @tparam  T  The type of the field/variable.
/// @since  0.5, 03.11.2016  (renamed to 'indirect access')
/// @since  0.4, 02.05.2016
template< typename T> class IndirectAccessField: public IIndirectAccess
{
public:
   /// Constructor.
   /// @param[in]  name       The name of the field/variable.
   /// @param[in]  value_ref  The variable.
   /// @since  0.4, 02.05.2016
   IndirectAccessField( const std::string& name, T& value_ref);

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
   virtual const std::string str() const noexcept( false) override;

protected:
   /// The variable.
   T&  mValueRef;

}; // IndirectAccessField


// inlined methods
// ===============


template< typename T>
   IndirectAccessField< T>::IndirectAccessField( const std::string& name, T& value_ref):
   IIndirectAccess( name, type< T>::name()),
   mValueRef( value_ref)
{
} // end IndirectAccessField< T>::IndirectAccessField


template< typename T>
   void IndirectAccessField< T>::set( const T& new_value) noexcept( true)
{
   mValueRef = new_value;
} // end IndirectAccessField< T>::set


template< typename T>
   const T& IndirectAccessField< T>::get() const noexcept( true)
{
   return mValueRef;
} // end IndirectAccessField< T>::get


template< typename T>
   const std::string IndirectAccessField< T>::str() const noexcept( false)
{
   return boost::lexical_cast< std::string>( mValueRef);
} // end IndirectAccessField< T>::str


} // namespace detail
} // namespace indirect_access
} // namespace celma


#endif   // CELMA_INDIRECT_ACCESS_INDIRECT_ACCESS_FIELD_HPP


// ====================  END OF indirect_access_field.hpp  ====================

