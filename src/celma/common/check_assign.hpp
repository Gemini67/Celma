
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
/// See documentation of template classes celma::common::CheckAssignRef<> and
/// celma::common::CheckAssign<>.


#ifndef CELMA_COMMON_CHECK_ASSIGN_HPP
#define CELMA_COMMON_CHECK_ASSIGN_HPP


#include <stdexcept>
#include "celma/common/comparable.hpp"


namespace celma { namespace common {


/// Small helper template to check if a value was assigned to a variable or not.<br>
/// Use this template if it is difficult to define a default value for a
/// variable, or just if you need to make sure that a mandatory argument is set.
/// Then this template tells you if a value was really set or not (no need to
/// define a separate 'is set' flag variable.<br>
/// This template only manages the access to a variable, the variable itself
/// must be defined elsewhere. Of course, if the variable is assigned a value
/// through another way, or event through another CheckAssignRef object, the
/// status maintained in this class may not be correct anymore.
///
/// @tparam  T  The type of the value to manage with this template.
/// @since  1.31.0, 16.10.2019  (extracted from CheckAssign<>)
template< typename T> class CheckAssignRef
{
public:
   /// Constructor, stores the reference to the variable to control the access
   /// to.
   ///
   /// @since  1.31.0, 16.10.2019
   CheckAssignRef( T& dest):
      mDest( dest)
   {
   } // CheckAssignRef< T>::CheckAssignRef

   /// Copying is not allowed.
   CheckAssignRef( const CheckAssignRef&) = delete;

   /// Moving is allowed.
   CheckAssignRef( CheckAssignRef&&) = default;

   /// Assigns a value.
   ///
   /// @param[in]  newValue
   ///    The value to assign.
   /// @since  1.31.0, 16.10.2019
   void assign( const T& newValue)
   {
      mDest       = newValue;
      mIsAssigned = true;
   } // CheckAssignRef< T>::assign

   /// Returns if a value was assigned or not.
   ///
   /// @return  \c true if a value was assigned.
   /// @since  1.31.0, 16.10.2019
   bool hasValue() const
   {
      return mIsAssigned;
   } // CheckAssignRef< T>::hasValue

   /// Returns the value that was assigned.
   ///
   /// @return  The value that was assigned.
   /// @throw  std::runtime_error when the value was not assigned.
   /// @since  1.31.0, 16.10.2019
   const T& value() const
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mDest;
   } // CheckAssignRef< T>::value

   /// Resets the 'is assigned' flag.
   ///
   /// @since  1.31.0, 16.10.2019
   void reset()
   {
      mIsAssigned = false;
   } // CheckAssignRef< T>::reset

   /// Assignment operator.
   ///
   /// @param[in]  new_value  The value to assign.
   /// @return  This object.
   /// @since  1.31.0, 16.10.2019
   CheckAssignRef& operator =( const T& new_value)
   {
      mDest       = new_value;
      mIsAssigned = true;
      return *this;
   } // CheckAssignRef< T>::operator =

   /// Assignment is not allowed.
   CheckAssignRef& operator =( const CheckAssignRef&) = delete;

   /// Move-assignment is allowed.
   CheckAssignRef& operator =( CheckAssignRef&&) = default;

   /// Typecast operator.
   ///
   /// @return  The internally stored value.
   /// @throw  std::runtime_error when the value was not set.
   /// @since  1.31.0, 16.10.2019
   operator T&()
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mDest;
   } // CheckAssignRef< T>::operator T

   /// Const typecast operator.
   ///
   /// @return  The internally stored value.
   /// @throw  std::runtime_error shen the value was not set.
   /// @since  1.31.0, 16.10.2019
   operator const T&() const
   {
      if (!mIsAssigned)
         throw std::runtime_error( "value not assigned!");
      return mDest;
   } // CheckAssignRef< T>::operator T

protected:
   /// The value.
   T&    mDest;
   /// Flag if the value was set or not.
   bool  mIsAssigned = false;

}; // CheckAssignRef< T>


/// Small helper template to check if a value was assigned to a variable or not.<br>
/// Use this template if it is difficult to define a default value for a
/// variable, or just if you need to make sure that a mandatory argument is set.
/// Then this template tells you if a value was really set or not (no need to
/// define a separate 'is set' flag variable.<br>
/// Unlike std::optional<>, this template does not use a dynamically allocated
/// variable.
///
/// @tparam  T  The type of the value to manage with this template.
/// @since  1.31.0, 16.10.2019
///    (removed default constructor, derive from new class CheckAssignRef)
/// @since  0.2, 10.04.2016
template< typename T> class CheckAssign: public CheckAssignRef< T>
{
public:
   /// Default constructor. The internal value is not initialised (actually
   /// default constructed), the 'is assigned' flag is set to \c false.
   ///
   /// @since  0.2, 10.04.2016
   CheckAssign():
      CheckAssignRef< T>( mValue),
      mValue()
   {
   } // CheckAssign< T>:: CheckAssign

   /// Copy constructor.
   ///
   /// @param[in]  other
   ///    The other check-assign object to copy the value (and flag) from.
   /// @since  0.2, 10.04.2016
   CheckAssign( const CheckAssign& other):
      CheckAssignRef< T>( mValue)
   {
      if ((this != &other) && (mIsAssigned = other.mIsAssigned))
      {
         mValue = other.mValue;
      } // end if
   } // CheckAssign< T>:: CheckAssign

   /// Assignment operator.
   ///
   /// @param[in]  new_value  The value to assign.
   /// @since  0.2, 10.04.2016
   CheckAssign& operator =( const T& new_value)
   {
      mValue = new_value;
      mIsAssigned = true;
      return *this;
   } // CheckAssign< T>::operator =

   /// Assignment operator, copies the values from another check-assign object.
   ///
   /// @param[in]  other
   ///    The other check-assign object to copy the value (and flag) from.
   /// @return  This object.
   /// @since  0.2, 10.04.2016
   CheckAssign& operator =( const CheckAssign& other)
   {
      if ((&other != this) && (mIsAssigned = other.mIsAssigned))
      {
         mValue = other.mValue;
      } // end if
      return *this;
   } // CheckAssign< T>::operator =

private:
   using CheckAssignRef< T>::mIsAssigned;

   /// The value.
   T  mValue;

}; // CheckAssign< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CHECK_ASSIGN_HPP


// =====  END OF check_assign.hpp  =====

