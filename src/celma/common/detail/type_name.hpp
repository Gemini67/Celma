
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
/// Defines the base template for getting the name of a type.


#ifndef CELMA_TYPE_NAME_HPP
#define CELMA_TYPE_NAME_HPP


namespace celma {


/// Base template for getting the name of a type. Partial template specialisation
/// is used to provide the name of a type.
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
   } // type< T>::name

   static constexpr char const  mName[] = "unknown";

}; // type< T>


} // namespace celma


#endif   // CELMA_TYPE_NAME_HPP


// =====  END OF type_name.hpp  =====
