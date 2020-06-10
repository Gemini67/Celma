
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
/// specialisations of a simple type.


#ifndef CELMA_PROVIDE_SIMPLE_TYPE_NAME_HPP
#define CELMA_PROVIDE_SIMPLE_TYPE_NAME_HPP


/// Macro to create the template specialisation for a simple type.
/// @param  t  The type to create the partial template specialisation of type<>
///            for.
/// @since  1.12.0, 14.09.2018  (now fully constexpr)
/// @since  0.10, 21.12.2016
#define  PROVIDE_SIMPLE_TYPE_NAME( t) \
   template<> class type< t> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         return mName.data(); \
      } \
      static constexpr auto const  mName = common::string_concat( # t); \
   }


#endif   // CELMA_PROVIDE_SIMPLE_TYPE_NAME_HPP


// =====  END OF provide_simple_type_name.hpp  =====

