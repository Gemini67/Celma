
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
/// Defines the macro that can be used to easily create the partial template
/// specialisations of a template type.


#ifndef CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP
#define CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP


#include <cstring>


/// Macro to create the specialisation of type<> for an STL container.
/// @param  c  The type of the container to create the specialisation for.
/// @since  1.12.0, 14.09.2018  (now fully constexpr)
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_TEMPLATE_TYPE_NAME( c) \
   template< typename T> class type< c< T>> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         return &mName[ 0]; \
      } \
      static constexpr auto const  mName = \
         common::string_concat( # c, "<", type< T>::mName, ">"); \
   }


#endif   // CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP


// =====  END OF provide_template_type_name.hpp  =====

