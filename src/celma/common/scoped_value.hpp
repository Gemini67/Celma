
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes celma::common::ScopedValue<> and
/// celma::common::ScopedFlag<>.


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
   } // ScopedValue< T>::ScopedValue

   /// Destructor, restores the previous value.
   /// @since  0.2, 10.04.2016
   ~ScopedValue()
   {
      mDestVar = mOldValue;
   } // ScopedValue< T>::~ScopedValue

private:
   /// The variable to handle.
   T&        mDestVar;
   /// The previous value to restore.
   const T   mOldValue;

}; // ScopedValue< T>


/// Sets a flag in the destination bit set, when the scope is left the previous
/// value of the flag is restored.
///
/// @tparam  S  The type of the variable to assign a scoped value to.
/// @since  1.22.0, 01.04.2019
template< typename S> class ScopedFlag
{
public:
   /// Constructor. Stores the current value of the flag and sets it.
   ///
   /// @param[in]  dest_var
   ///    The variable to set the flag in.
   /// @param[in]  flag
   ///    The bit value/flag to set.
   /// @since  1.22.0, 01.04.2019
   ScopedFlag( S& dest_var, int value):
      mDestVar( dest_var),
      mFlagBit( value),
      mOldValue( dest_var & value)
   {
      mDestVar |= value;
   } // ScopedFlag< S>::ScopedFlag

   /// Destructor, restores the previous value of the flag.
   ///
   /// @since  1.22.0, 01.04.2019
   ~ScopedFlag()
   {
      if ((mOldValue != 0) && ((mDestVar & mFlagBit) == 0))
      {
         mDestVar |= mFlagBit;
      } else if ((mOldValue == 0) && ((mDestVar & mFlagBit) != 0))
      {
         mDestVar -= mFlagBit;
      } // end if
   } // ScopedFlag< S>::~ScopedFlag

private:
   /// The variable to handle.
   S&         mDestVar;
   /// The bit to set and eventually clear again at the end.
   const int  mFlagBit;
   /// The previous value of the flag.
   const S    mOldValue;

}; // ScopedFlag< S>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SCOPED_VALUE_HPP


// =====  END OF scoped_value.hpp  =====

