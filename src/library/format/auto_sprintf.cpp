
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
/// See documentation of class celma::format::AutoSprintf.


// module header file include
#include "celma/format/auto_sprintf.hpp"


// OS/C lib includes
#include <cstdarg>
#include <cstdio>
#include <cstdlib>


// project includes
#include "celma/common/celma_exception.hpp"


using namespace std;


namespace celma { namespace format {



/// Constructor.
/// @param[in]  format  The format string.
/// @param[in]  ...     Additional parameters for the string formatting.
/// @throw  CelmaRuntimeError when the string formatting failed.
/// @since  0.2, 08.04.2016
AutoSprintf::AutoSprintf( const char* format, ...):
   mpString( nullptr),
   mLength( 0)
{

   va_list  ap;


   ::va_start( ap, format);

   if ((mLength = ::vasprintf( &mpString, format, ap)) == -1)
   {
      mpString = nullptr;
      throw CELMA_RuntimeError( "could not format text");
   } // end if

   ::va_end( ap);

} // end AutoSprintf::AutoSprintf



/// Destructor, ensures that the buffer is free'd again.
/// @since  0.2, 08.04.2016
AutoSprintf::~AutoSprintf()
{

   free( mpString);

} // end AutoSprintf::~AutoSprintf



} // namespace format
} // namespace celma


// =========================  END OF auto_sprintf.cpp  =========================

