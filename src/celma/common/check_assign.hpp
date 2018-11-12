
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
/// See documentation of template celma::common::CheckAssign.


#ifndef CELMA_COMMON_CHECK_ASSIGN_HPP
#define CELMA_COMMON_CHECK_ASSIGN_HPP


#include <stdexcept>


namespace celma { namespace common {


/// Small helper template to check if a value was assigned to a variable or not.<br>
/// Use this template if it is difficult to define a default value for a
/// variable, or just if you need to make sure that a mandatory argument is set.
/// Then this template tells you if a value was really set or not (no need to
/// define a separate 'is set' flag variable.
/// @tparam  T  The type of the value to manage with this template.
/// @since  0.2, 10.04.2016
template< typename T> class CheckAssign
{
public:
   /// Default constructor. The internal value is not initialised (default
   /// constructed), the 'is assigned' flag is set to \c false.
   /// @since  0.2, 10.04.2016
   CheckAssign() = default;

   /// Constructor that allows to set a default value for the variable.<br>
   /// This means that afterwards the value() can always be used since it should
   /// always be set to a meaningful value. The hasValue() function becomes the
   /// meaning of 'value was changed after construction'.
   /// @param[in]  defVal  The default value to set.
   /// @since  0.2, 10.04.2016
   explicit CheckAssign( const T& defVal):
      mValue( defVal)
   {
   } // CheckAssign< T>::CheckAssign

   /// Copy constructor.
   /// @param[in]  other  The other check-assign object to copy the value (and
   ///                    flag) from.
   /// @since  0.2, 10.04.2016
   CheckAssign( const CheckAssign& other) = default;

   /// Assignes a value.
   /// @param[in]  newValue  The value to assign.
   /// @since  0.2, 10.04.2016
   void assign( const T& newValue)
   {
      mValue      = newValue;
      mIsAssigned = true;
   } // CheckAssign< T>::assign

   /// Returns if a value was assigned or not.
   /// @return  \c true if a value was assigned.
   /// @since  0.2, 10.04.2016
   bool hasValue() const
   {
      return mIsAssigned;
   } // CheckAssign< T>::hasValue

   /// Returns the value that was assigned.
   /// @return  The value that was assigned.
   /// @throw  Exception when the value was not assigned.
   /// @since  0.2, 10.04.2016
   const T& value() const
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mValue;
   } // CheckAssign< T>::value

   /// Resets the 'is assign' flag, but does *not* change the internal value.
   /// @since  0.2, 10.04.2016
   void reset()
   {
      mIsAssigned = false;
   } // CheckAssign< T>::reset

   /// Assignment operator.
   /// @param[in]  new_value  The value to assign.
   /// @return  This object.
   /// @since  0.2, 10.04.2016
   CheckAssign& operator =( const T& new_value)
   {
      mValue      = new_value;
      mIsAssigned = true;
      return *this;
   } // CheckAssign< T>::operator =

   /// Assignment operator, copies the values from another check-assign object.
   /// @param[in]  other  The other check-assign object to copy the value (and
   ///                    flag) from.
   /// @return  This object.
   /// @since  0.2, 10.04.2016
   CheckAssign& operator =( const CheckAssign& other)
   {
      if (&other != this)
      {
         if ((mIsAssigned = other.mIsAssigned))
            mValue = other.mValue;
      } // end if
      return *this;
   } // CheckAssign< T>::operator =

   /// Typecast operator.
   /// @return  The internally stored value.
   /// @throw  Exception when the value was not set.
   /// @since  0.2, 10.04.2016
   operator T&()
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mValue;
   } // CheckAssign< T>::operator T

   /// Typecast operator.
   /// @return  The internally stored value.
   /// @throw  Exception when the value was not set.
   /// @since  0.2, 10.04.2016
   operator const T&() const
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mValue;
   } // CheckAssign< T>::operator T

private:
   /// The value.
   T     mValue;
   /// Flag if the value was set or not.
   bool  mIsAssigned = false;

}; // CheckAssign< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CHECK_ASSIGN_HPP


// =====  END OF check_assign.hpp  =====

