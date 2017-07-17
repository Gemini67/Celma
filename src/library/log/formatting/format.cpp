
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
/// See documentation of class celma::log::formatting::Format.


// module header file include
#include "celma/log/formatting/format.hpp"


// OS/C library includes
#include <ctime>


// C++ Standard Library include
#include <iomanip>
#include <ostream>


namespace celma { namespace log { namespace formatting {



Format::Format( const Definition& def):
   Definition( def)
{
} // Format::Format



void Format::handleMsg( std::ostream& dest, const detail::LogMsg& msg) const
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
         {
            char  buffer[ 64];
            ::sprintf( buffer, "%d", msg.getProcessId());
            append( dest, field_def, buffer);
         } // end scope
         break;
      case FieldTypes::lineNbr:
         {
            char  buffer[ 64];
            ::sprintf( buffer, "%d", msg.getLineNbr());
            append( dest, field_def, buffer);
         } // end scope
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
         {
            char  buffer[ 64];
            ::sprintf( buffer, "%d", msg.getErrorNbr());
            append( dest, field_def, buffer);
         } // end scope
         break;
      case FieldTypes::text:
         append( dest, field_def, msg.getText());
         break;
      case FieldTypes::customProperty:
         append( dest, field_def, msg.getPropertyValue( field_def.mConstant));
         break;
      } // end switch
   } // end for

} // Format::handleMsg



/// 
/// @param[in]  dest        .
/// @param[in]  field_def   .
/// @param[in]  format_str  .
/// @param[in]  timestamp   .
/// @since  0.11, 11.12.2016
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



/// @since  0.11, 07.12.2016
void Format::append( std::ostream& dest, const Field& def, const std::string& str) const
{

   if (def.mFixedWidth > 0)
      dest << std::setw( def.mFixedWidth);
   if (def.mAlignRight)
      dest << std::right;
   dest << str;

} // Format::append



} // namespace formatting
} // namespace log
} // namespace celma


// ============================  END OF format.cpp  ============================

