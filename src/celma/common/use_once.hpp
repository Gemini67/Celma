
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
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_USE_ONCE_HPP
#define CELMA_COMMON_USE_ONCE_HPP


namespace celma { namespace common {


/// Helper class used to ensure that a certain value is used only once.
/// @tparam  T          The type of the value to handle.
/// @tparam  reset_val  The value to set when the actual value was used.
/// @since  x.y.z, 09.08.2017
template< typename T, T reset_val = 0> class UseOnce
{
public:
   /// Constructor.<br>
   /// Either specify the value to handle here, or use the set() method.
   /// @param[in]  value  The value to handle.
   /// @since  x.y.z, 09.08.2017
   UseOnce( const T& value = reset_val):
      mValue( value)
   {
   } // UseOnce< T, reset_val>::UseOnce

   /// Copy constructor: Actually don't copy the value.
   /// @param[in]  Ignored.
   /// @since  x.y.z, 09.08.2017
   UseOnce( const UseOnce&):
      mValue( reset_val)
   {
   } // UseOnce< T, reset_val>::UseOnce

   /// Move constructor. Moves the value here.
   /// @param[in,out]  other  The other object to move the value from.
   /// @since  x.y.z, 09.08.2017
   UseOnce( UseOnce&& other):
      mValue( other.mValue)
   {
      other.mValue = reset_val;
   } // UseOnce< T, reset_val>::UseOnce

   /// Sets a new value. An existing, unused value is simply overwritten.
   /// @param[in]  value  The new value.
   /// @since  x.y.z, 09.08.2017
   void set( const T& value)
   {
      mValue = value;
   } // UseOnce< T, reset_val>::set

   T release()
   {
      T old_value = mValue;
      mValue = reset_val;
      return old_value;
   } // UseOnce< T, reset_val>::release

private:
   T  mValue;

}; // UseOnce< T, reset_val>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_USE_ONCE_HPP


// ===========================  END OF use_once.hpp  ===========================

