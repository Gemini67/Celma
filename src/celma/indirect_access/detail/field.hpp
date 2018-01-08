
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See description of template class celma::indirect_access::detail::Field.


#ifndef CELMA_INDIRECT_ACCESS_FIELD_HPP
#define CELMA_INDIRECT_ACCESS_FIELD_HPP


#include <string>
#include <boost/lexical_cast.hpp>
#include "celma/common/type_name.hpp"
#include "celma/indirect_access/detail/i_field.hpp"


namespace celma { namespace indirect_access { namespace detail {


/// This class actually handles the access indirect to a field.
/// @tparam  T  The type of the field/variable.
/// @since  1.2.1, 08.01.2018  (renamed to Field, copying is not allowed)
/// @since  0.5, 03.11.2016  (feature renamed to 'indirect access')
/// @since  0.4, 02.05.2016
template< typename T> class Field: public IField
{
public:
   /// Constructor.
   /// @param[in]  name       The name of the field/variable.
   /// @param[in]  value_ref  The variable.
   /// @since  0.4, 02.05.2016
   Field( const std::string& name, T& value_ref);

   /// Prevent copying.
   Field( const Field&) = delete;
   Field& operator =( const Field&) = delete;

   /// Default destructor.
   ~Field() = default;

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

}; // Field< T>


// inlined methods
// ===============


template< typename T> Field< T>::Field( const std::string& name, T& value_ref):
   IField( name, type< T>::name()),
   mValueRef( value_ref)
{
} // Field< T>::Field


template< typename T> void Field< T>::set( const T& new_value) noexcept( true)
{
   mValueRef = new_value;
} // Field< T>::set


template< typename T> const T& Field< T>::get() const noexcept( true)
{
   return mValueRef;
} // Field< T>::get


template< typename T> const std::string Field< T>::str() const noexcept( false)
{
   return boost::lexical_cast< std::string>( mValueRef);
} // Field< T>::str


} // namespace detail
} // namespace indirect_access
} // namespace celma


#endif   // CELMA_INDIRECT_ACCESS_FIELD_HPP


// =====  END OF field.hpp  =====

