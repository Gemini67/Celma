
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
/// Adds partial template specialisations for the 'plain old data types'.


#ifndef CELMA_POD_TYPE_NAME_HPP
#define CELMA_POD_TYPE_NAME_HPP


#include "celma/common/detail/type_name.hpp"


namespace celma {


/// Macro to create the template specialisation for a POD type.
/// @param  t  The type to create the partial template specialisation of type<>
///            for.
/// @since  0.1, 15.03..2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_SIMPLE_TYPE_NAME( t) \
   template<> class type< t> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         return #t ; \
      } \
   }


/// Provides the name of the type 'bool'.
PROVIDE_SIMPLE_TYPE_NAME( bool);
/// Provides the name of the type 'char'.
PROVIDE_SIMPLE_TYPE_NAME( char);
/// Provides the name of the type 'unsigned char'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned char);
/// Provides the name of the type 'short'.
PROVIDE_SIMPLE_TYPE_NAME( short);
/// Provides the name of the type 'unsigned short'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned short);
/// Provides the name of the type 'int'.
PROVIDE_SIMPLE_TYPE_NAME( int);
/// Provides the name of the type 'unsigned int'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned int);
/// Provides the name of the type 'long'.
PROVIDE_SIMPLE_TYPE_NAME( long);
/// Provides the name of the type 'unsigned long'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned long);
/// Provides the name of the type 'float'.
PROVIDE_SIMPLE_TYPE_NAME( float);
/// Provides the name of the type 'double'.
PROVIDE_SIMPLE_TYPE_NAME( double);


} // namespace celma


#endif   // CELMA_POD_TYPE_NAME_HPP


// ========================  END OF pod_type_name.hpp  ========================

