
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
/// See documentation of class celma::log::detail::LogMsg.


// module header file include
#include "celma/log/detail/log_msg.hpp"


// OS/C library includes
#include <unistd.h>
#include <ctime>


// project includes
#include "celma/common/extract_funcname.hpp"
#include "celma/common/string_util.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor, sets the properties where this log message was created.<br>
/// Internally, also the process id is set.
/// @param[in]  file_name             The name of the source file.
/// @param[in]  pretty_function_name  The name of the function.
/// @param[in]  line_nbr              The line number.
/// @since  0.3, 19.06.2016
LogMsg::LogMsg( const std::string& file_name, const char* const pretty_function_name,
                int line_nbr):
   mTimestamp( ::time( nullptr)),
   mProcessId( ::getpid()),
   mFileName( file_name),
   mFunctionName( common::extractFuncname( pretty_function_name)),
   mLineNbr( line_nbr),
   mClass( LogClass::undefined),
   mLevel( LogLevel::undefined),
   mErrNbr( 0),
   mText()
{

   common::remove_to_if_last_incl( mFileName, '/');

} // end LogMsg::LogMsg



/// Stores the data of an exception.<br>
/// Note that also the line number, function name etc. are copied.
/// @param[in]  eb  The exception to copy the data from.
/// @since  0.3, 19.06.2016
void LogMsg::assign( const common::ExceptionBase& eb)
{

   mFileName     = eb.sourceFilename();
   mFunctionName = eb.functionName();
   mLineNbr      = eb.lineNbr();
   // text will be assigned separately

} // end LogMsg::assign



} // namespace detail
} // namespace log
} // namespace celma


// ===========================  END OF log_msg.cpp  ===========================

