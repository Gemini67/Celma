
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
/// Defines the base template for getting the name of the type of a variable.


#ifndef CELMA_COMMON_VAR_TYPE_NAME_HPP
#define CELMA_COMMON_VAR_TYPE_NAME_HPP


#include "celma/common/type_name.hpp"


namespace celma { namespace common {


/// Class that allows to get the name of the type of a variable. No object
/// requried.<br>
/// Usage:<br>
///    cout << "type of my_variable = " << var::name( my_variable) << endl;
///
/// @since  0.2, 10.04.2016
class var
{
public:
   /// This function returns the name of the type of the passed variable.
   /// @tparam  T  The type of the variable.
   /// @return  The name of the type of the variable.
   /// @since  0.2, 10.04.2016
   template< typename T> static const char* name( const T&)
   {
      return type< T>::name();
   } // end var::name

private:
   /// Don't need to create object(s) of this class.
   var() = delete;

}; // var


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_VAR_TYPE_NAME_HPP


// =========================  END OF var_type_name.hpp  =========================
