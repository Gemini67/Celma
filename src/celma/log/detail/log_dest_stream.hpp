
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
/// See documentation of class celma::log::detail::LogDestStream.


#ifndef CELMA_LOG_DETAIL_LOG_DEST_STREAM_HPP
#define CELMA_LOG_DETAIL_LOG_DEST_STREAM_HPP


#include <iosfwd>
#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/i_format_stream.hpp"


namespace celma { namespace log { namespace detail {


class LogMsg;


/// Log destination: (o) Stream.
/// @since  1.0.0, 19.06.2016
class LogDestStream: public ILogDest
{
public:
   /// Constructor.<br>
   /// A default stream formatter (FormatStreamDefault) is created for
   /// formatting the log messages. Use setFormatter() to specify another
   /// formatter if necessary.
   /// @param[in]  dest         The stream to write into.
   /// @param[in]  add_newline  Set to \c true if a newline character should be
   ///                          added to log message(s).
   /// @since  1.0.0, 19.06.2016
   explicit LogDestStream( std::ostream& dest, bool add_newline = false);

   /// Empty, virtual destructor.
   /// @since  1.0.0, 19.06.2016
   virtual ~LogDestStream() = default;

   /// Sets the new formatter to use.<br>
   /// Although the pointer type is \a IFormatBase only, objects passed here
   /// must be derived from the \a IFormatStream class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  1.0.0, 19.06.2016
   virtual void setFormatter( IFormatBase* formatter = nullptr) override;

private:
   /// Called through the base class. Writes a log message to the specified
   /// stream.
   /// @param[in]  msg  The message to write.
   /// @since  1.0.0, 19.06.2016
   virtual void message( const LogMsg& msg) override;

   /// The stream to write into.
   std::ostream&                    mDest;
   /// Flag if a newline should be added to the output stream.
   const bool                       mAddNewline;
   /// The object used for formatting stream output.
   std::unique_ptr< IFormatStream>  mpFormatter;

}; // LogDestStream


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_DEST_STREAM_HPP


// =======================  END OF log_dest_stream.hpp  =======================

