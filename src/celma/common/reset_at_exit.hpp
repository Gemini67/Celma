
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
/// See documentation of template celma::common::ResetAtExit.


#ifndef CELMA_COMMON_RESET_AT_EXIT_HPP
#define CELMA_COMMON_RESET_AT_EXIT_HPP


namespace celma { namespace common {


/// Helper class that (re-) sets a variable to a specific value when this object
/// is deleted, i.e. the scope is left.
/// @tparam  T  The type of the variable (and value) to handle.
/// @since  0.2, 09.04.2016
template< typename T> class ResetAtExit
{
public:
   /// Constructor.
   /// @param[in]  var        The variable to set the value for when the object
   ///                        is deleted.<br>
   ///                        The variable must support the assignment operator.
   /// @param[in]  reset_val  The value to set.
   /// @since  0.2, 09.04.2016
   ResetAtExit( T& var, const T& reset_val);

   /// Don't copy.
   /// @since  0.2, 09.04.2016
   ResetAtExit( const ResetAtExit&) = delete;

   /// Don't assign.
   /// @since  0.2, 09.04.2016
   ResetAtExit& operator =( const ResetAtExit&) = delete;

   /// Destructor, assigns the value to the variable.
   /// @since  0.2, 09.04.2016
   ~ResetAtExit();

private:
   /// The variable to assign the value to in the destructor of this class.
   T&       mVariable;
   /// The value to assign.
   const T  mResetValue;

}; // ResetAtExit< T>


// inlined methods
// ===============


template< typename T> ResetAtExit< T>::ResetAtExit( T& var, const T& reset_val):
   mVariable( var),
   mResetValue( reset_val)
{
} // ResetAtExit< T>::ResetAtExit


template< typename T> ResetAtExit< T>::~ResetAtExit()
{
   mVariable = mResetValue;
} // ResetAtExit< T>::~ResetAtExit


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RESET_AT_EXIT_HPP


// =====  END OF reset_at_exit.hpp  =====

