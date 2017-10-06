
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::Format.


// module header file include
#include "celma/log/formatting/format.hpp"


// OS/C library includes
#include <ctime>


// C++ Standard Library include
#include <iomanip>
#include <ostream>


// project includes
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace formatting {



/// Constructor.
/// @param[in]  def  The object with the format definition.
/// @since  x.y.z, 07.12.2016
Format::Format( const Definition& def):
   Definition( def)
{
} // Format::Format



/// Formats the data of the log messagr object according to the format
/// definition passed into the constructor.
/// @param[out]  dest  The destination stream to write the formatted log
///                    message data into.
/// @param[in]   msg   The log message whose data should be formatted.
/// @since  x.y.z, 07.12.2016
void Format::format( std::ostream& dest, const detail::LogMsg& msg) const
{

   for (auto const& field_def : mFields)
   {
      switch (field_def.mType)
      {
      case FieldTypes::constant:
         append( dest, field_def, field_def.mConstant);
         break;
      case FieldTypes::date:
         formatDateTime( dest, field_def, "%F", msg.getTimestamp());
         break;
      case FieldTypes::time:
         formatDateTime( dest, field_def, "%T", msg.getTimestamp());
         break;
      case FieldTypes::dateTime:
         formatDateTime( dest, field_def, "%F %T", msg.getTimestamp());
         break;
      case FieldTypes::pid:
         append( dest, field_def, std::to_string( msg.getProcessId()));
         break;
      case FieldTypes::threadId:
         append( dest, field_def, std::to_string( msg.getThreadId()));
         break;
      case FieldTypes::lineNbr:
         append( dest, field_def, std::to_string( msg.getLineNbr()));
         break;
      case FieldTypes::functionName:
         append( dest, field_def, msg.getFunctionName());
         break;
      case FieldTypes::fileName:
         append( dest, field_def, msg.getFileName());
         break;
      case FieldTypes::msgLevel:
         append( dest, field_def, detail::logLevel2text( msg.getLevel()));
         break;
      case FieldTypes::msgClass:
         append( dest, field_def, detail::logClass2text( msg.getClass()));
         break;
      case FieldTypes::errorNbr:
         append( dest, field_def, std::to_string( msg.getErrorNbr()));
         break;
      case FieldTypes::text:
         append( dest, field_def, msg.getText());
         break;
      case FieldTypes::customProperty:
         append( dest, field_def, msg.getPropertyValue( field_def.mConstant));
         break;
      } // end switch
   } // end for

} // Format::format



/// Formats a date, time or timestamp.
/// @param[out]  dest        The stream to write into.
/// @param[in]   field_def   The object with may contain the custom format
///                          string.
/// @param[in]   format_str  The default format string, used when no custom
///                          format string is available.
/// @param[in]   timestamp   The timestamp to format.
/// @since  x.y.z, 11.12.2016
void Format::formatDateTime( std::ostream& dest, const Field& field_def,
                             const char* format_str, time_t timestamp) const
{

   // format date, time or timestamp
   auto const  use_format_str = field_def.mConstant.empty() ? format_str :
                                field_def.mConstant.c_str();
   char        timestamp_str[ 128];


   ::strftime( timestamp_str, sizeof( timestamp_str) - 1, use_format_str,
               ::localtime( &timestamp));
   append( dest, field_def, timestamp_str);

} // Format::formatDateTime



/// Write a field into the output stream, including width and alignment
/// settings.
/// @param[out]  dest  The destination stream to write into.
/// @param[in]   def   The object with the width and alignment settings.
/// @param[in]   str   The string to write.
/// @since  x.y.z, 07.12.2016
void Format::append( std::ostream& dest, const Field& def,
                     const std::string& str) const
{

   if (def.mFixedWidth > 0)
      dest << std::setw( def.mFixedWidth);
   if (def.mAlignLeft)
      dest << std::left;

   dest << str;

   // reset again?
   if (def.mAlignLeft)
      dest << std::right;

} // Format::append



} // namespace formatting
} // namespace log
} // namespace celma


// ============================  END OF format.cpp  ============================

