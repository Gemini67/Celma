
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
/// See documentation of function celma::log::detail::vprintf.


// module header file include
#include "celma/log/detail/log_printf.hpp"


// OS/C lib includes
#include <cstdio>


// project includes
#include "celma/common/celma_exception.hpp"


namespace celma { namespace log { namespace detail {



/// Function put here to reduce the complexity of the header file/template
/// function: Format the message text and store the data in the log message
/// object.
/// @param[out]  myMsg   The log message object to copy the data in.
/// @param[in]   ll      The log level to set.
/// @param[in]   lc      The log class to set.
/// @param[in]   format  The format string.
/// @param[in]   ap      Additional parameters.
/// @since  0.3, 19.06.2016
void vprintf( LogMsg& myMsg, LogLevel ll, LogClass lc, const char* format,
              va_list ap)
{

   char*  text = nullptr;


   if (::vasprintf( &text, format, ap) == -1)
   {
      throw CELMA_RuntimeError( "could not format text");
   } // end if

   myMsg.setLevel( ll);
   myMsg.setClass( lc);
   myMsg.setText( text);

   delete [] text;

} // end vprintf



} // namespace detail
} // namespace log
} // namespace celma


// ==========================  END OF log_printf.cpp  ==========================

