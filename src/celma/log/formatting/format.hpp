
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


#ifndef CELMA_LOG_FORMATTING_FORMAT_HPP
#define CELMA_LOG_FORMATTING_FORMAT_HPP


#include <iosfwd>
#include <string>
#include "celma/log/formatting/definition.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace formatting {


/// @since  0.11, 07.12.2016
class Format: private Definition
{
public:
   Format( const Definition& def);

   void handleMsg( std::ostream& dest, const detail::LogMsg& msg) const;

private:
   void formatDateTime( std::ostream& dest, const Field& field_def,
                        const char* format_str, time_t timestamp) const;
   void append( std::ostream& dest, const Field& def, const std::string& str) const;

}; // Format


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_FORMAT_HPP


// ============================  END OF format.hpp  ============================

