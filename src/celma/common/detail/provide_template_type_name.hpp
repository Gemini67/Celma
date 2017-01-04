
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
/// Defines the macro that can be used to easily create the partial template
/// specialisations of a template type.


#ifndef CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP
#define CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP


#include <cstring>


/// Macro to create the specialisation of type<> for an STL container.
/// @param  c  The type of the container to create the specialisation for.
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_TEMPLATE_TYPE_NAME( c) \
   template< typename T> class type< c< T>> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         if (mName[ 0] == 0) \
         { \
            ::strcpy( mName, # c); \
            ::strcat( mName, "<"); \
            ::strcat( mName, type< T>::name()); \
            ::strcat( mName, ">"); \
         } \
         return mName; \
      } \
   private: \
      static char  mName[ 128]; \
   }; \
   template< typename T> char  type< c< T>>::mName[ 128] = { 0 }


#endif   // CELMA_PROVIDE_TEMPLATE_TYPE_NAME_HPP


// ==================  END OF provide_template_type_name.hpp  ==================

