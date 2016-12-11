
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
/// Defines the base template for getting the name of a type.


#ifndef CELMA_TYPE_NAME_HPP
#define CELMA_TYPE_NAME_HPP


namespace celma {


/// Base template for getting the name of a type. Partial template specialisation
/// is used to provide the name of a type.<br>
/// The design with the static \b method was chosen because the solution with a
/// static member variable led to 'multiple instance' error messages. Maybe this
/// would not happen with C++11x 'constexpr'.<br>
/// The template was added to the 'std' namespace on purpose.
/// @tparam  T  The type to provide the name of.
/// @since  0.1, 15.03.2016
template< typename T> class type
{
public:
   /// Returns the name of the type.
   /// @return  'unknown'.
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      return "unknown";
   } // end type< T>::name

}; // type< T>


} // namespace celma


#endif   // CELMA_TYPE_NAME_HPP


// ==========================  END OF type_name.hpp  ==========================
