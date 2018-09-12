
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::Simple.


// module header file include
#include "celma/log/files/simple.hpp"


namespace celma { namespace log { namespace files {



/// Constructor.
/// @param[in]  fname_def  The object used to create the file name.
/// @since  1.0.0, 13.12.2017
Simple::Simple( const filename::Definition& fname_def):
   PolicyBase( fname_def)
{
} // Simple::Simple



/// Copy constructor. Copies onle the definition.
/// @param[in]  fname_def  The object used to create the file name.
/// @since  1.0.0, 13.12.2017
Simple::Simple( const Simple& other):
   PolicyBase( other.mFilenameDefinition)
{
} // Simple::Simple



/// Check if the currently opened file is valid for writing into.
/// @return  Always \c true.
/// @since  1.0.0, 13.12.2017
bool Simple::openCheck()
{

   return true;
} // Simple::openCheck



/// Checks if the next message can still be written into the current file.
/// @param[in]  msg       The message object. Ignored.
/// @param[in]  msg_text  The formatted text of the log message. Ignored.
/// @return  Always \c true.
/// @since  1.0.0, 13.12.2017
bool Simple::writeCheck( const detail::LogMsg&, const std::string&)
{

   return true;
} // Simple::writeCheck



/// Called after the log message was written into the current log file. Does
/// nothing in this class.
/// @param[in]  msg       The message object. Ignored.
/// @param[in]  msg_text  The formatted text of the log message. Ignored.
/// @since  1.0.0, 13.12.2017
void Simple::written( const detail::LogMsg&, const std::string&)
{
} // Simple::written



} // namespace files
} // namespace log
} // namespace celma


// =====  END OF simple.cpp  =====

