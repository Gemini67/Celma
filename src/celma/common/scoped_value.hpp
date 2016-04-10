
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::ScopedValue.


#ifndef CELMA_COMMON_SCOPED_VALUE_HPP
#define CELMA_COMMON_SCOPED_VALUE_HPP


namespace celma { namespace common {


/// Assigns a value within a certain scope, when the scope is left the previous
/// value is restored.
/// @tparam  T  The type of the variable to assign a scoped value to.
/// @since  0.2, 10.04.2016
template< typename T> class ScopedValue
{
public:
   /// Constructor. Stores the current value of the passed variable and assigns
   /// the new value.
   /// @param[in]  dest_var  The variable to assign the new value to.
   /// @param[in]  value     The value to assign.
   /// @since  0.2, 10.04.2016
   ScopedValue( T& dest_var, T value):
      mDestVar( dest_var),
      mOldValue( dest_var)
   {
      mDestVar = value;
   } // end ScopedValue< T>::ScopedValue

   /// Destructor, restores the previous value.
   /// @since  0.2, 10.04.2016
   ~ScopedValue()
   {
      mDestVar = mOldValue;
   } // end ScopedValue< T>::~ScopedValue

private:
   /// The variable to handle
   T&        mDestVar;
   /// The previous value to restore.
   const T   mOldValue;

}; // ScopedValue< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SCOPED_VALUE_HPP


// =========================  END OF scoped_value.hpp  =========================

