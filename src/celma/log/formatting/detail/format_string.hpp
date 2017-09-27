
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::detail::formatString.


#ifndef CELMA_LOG_FORMATTING_DETAIL_FORMAT_STRING_HPP
#define CELMA_LOG_FORMATTING_DETAIL_FORMAT_STRING_HPP


#include <string>


namespace celma { namespace log { namespace formatting { namespace detail {


/// Used as stream manipulator that stores the format string to use for a date,
/// time or date-time field, until it is stored through the creator in the log
/// format definition object.<br>
/// Since this class is used as IO-manipulator for the log format creator, it
/// does not strictly follow the usual naming convention.
/// @since  x.y.z, 26.09.2017
class formatString
{
public:
   /// Constructor. Stores the given format string.
   /// @param[in]  fmt  The format string to store.
   /// @since  x.y.z, 26.09.2017
   explicit formatString( const std::string& fmt):
      mFormat( fmt)
   {
   } // formatString::formatString

   /// Returns the stored format string.
   /// @return  The format string as passed in the constructor.
   /// @since  x.y.z, 26.09.2017
   const std::string& format() const
   {
      return mFormat;
   } // formatString::format
   
private:
   /// The format string to use.
   const std::string  mFormat;
   
}; // formatString


} // namespace detail
} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_DETAIL_FORMAT_STRING_HPP


// ========================  END OF format_string.hpp  ========================

