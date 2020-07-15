
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogDestStream.


#pragma once


#include <iosfwd>
#include <memory>
#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/i_format_stream.hpp"


namespace celma::log::detail {


class LogMsg;


/// Log destination: (o) Stream.
///
/// @since  1.24.1, 22.04.2019  (removed unused feature "add newline")
/// @since  1.0.0, 19.06.2016
class LogDestStream final : public ILogDest
{
public:
   /// Constructor.<br>
   /// A default stream formatter (FormatStreamDefault) is created for
   /// formatting the log messages. Use setFormatter() to specify another
   /// formatter if necessary.
   ///
   /// @param[in]  dest  The stream to write into.
   /// @since  1.24.1, 22.04.2019  (removed unused parameter add_newline)
   /// @since  1.0.0, 19.06.2016
   explicit LogDestStream( std::ostream& dest);

   /// Empty, virtual destructor.
   /// @since  1.0.0, 19.06.2016
   ~LogDestStream() override = default;

   /// Sets the new formatter to use.<br>
   /// Although the pointer type is \a IFormatBase only, objects passed here
   /// must be derived from the \a IFormatStream class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  1.0.0, 19.06.2016
   void setFormatter( IFormatBase* formatter = nullptr) override;

private:
   /// Called through the base class. Writes a log message to the specified
   /// stream.
   /// @param[in]  msg  The message to write.
   /// @since  1.0.0, 19.06.2016
   void message( const LogMsg& msg) override;

   /// The stream to write into.
   std::ostream&                    mDest;
   /// The object used for formatting stream output.
   std::unique_ptr< IFormatStream>  mpFormatter;

}; // LogDestStream


} // namespace celma::log::detail


// =====  END OF log_dest_stream.hpp  =====

