
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
/// See documentation of template class celma::log::files::Handler.


#ifndef CELMA_LOG_FILES_HANDLER_HPP
#define CELMA_LOG_FILES_HANDLER_HPP


#include <memory>
#include <sstream>
#include "celma/log/detail/format_stream_default.hpp"
#include "celma/log/detail/i_format_base.hpp"
#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace files {


/// Handles log files as log destinations.<br>
/// The path and file name of the log files is defined through a
/// filename::Definition object that is passed to the log file policy.<br>
/// The policy defines when a nw log file should be opened and knows how to
/// roll the log file generations, if necessary.<br>
/// The formatting for the log messages is defined through classes that
/// implement the IFormatBase interfac.<br>
/// This class finally brings all this together.
/// @since  x.y.z, 13.12.2017
template< typename P> class Handler: public detail::ILogDest
{
public:
   /// Constructor. Tries to open the current log file according to the given
   /// policy.
   /// @param[in]  file_policy  Pointer to the policy for handling the log
   ///                          file(s). This class takes ownership of the
   ///                          object.
   /// @since  x.y.z, 13.12.2017
   Handler( P* file_policy);

   Handler( const Handler&) = delete;
   virtual ~Handler() = default;
   Handler& operator =( const Handler&) = delete;

   /// Sets the new formatter to use.<br>
   /// Although the pointer type is \a IFormatBase only, objects passed here
   /// must be derived from the \a IFormatStream class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  x.y.z, 14.12.2017
   virtual void setFormatter( detail::IFormatBase* formatter = nullptr) override;

private:
   /// Implementation of the ILogDest interface: Formats the given log message
   /// and writes the log message text into the log file.
   /// @param[in]  msg  The object with the data of the log message to write.
   /// @since  x.y.z, 13.12.2017
   virtual void message( const detail::LogMsg& msg) override;

   /// The policy object to handle the log file(s).
   std::unique_ptr< P>                      mpFilePolicy;
   /// The object used for formatting stream output.
   std::unique_ptr< detail::IFormatStream>  mpFormatter;

}; // Handler< P>


// inlined methods
// ===============


template< typename P> Handler< P>::Handler( P* file_policy):
   mpFilePolicy( file_policy)
{
   mpFilePolicy->open();
} // Handler< P>::Handler


template< typename P>
   void Handler< P>::setFormatter( detail::IFormatBase* formatter)
{
   mpFormatter.reset(
      (formatter == nullptr) ? new detail::FormatStreamDefault() :
                               static_cast< detail::IFormatStream*>( formatter));
} // Handler< P>::setFormatter


template< typename P> void Handler< P>::message( const detail::LogMsg& msg)
{
   std::ostringstream  msg_text;

   mpFormatter->formatMsg( msg_text, msg);
   mpFilePolicy->writeMessage( msg, msg_text.str());
} // Handler< P>::message


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_HANDLER_HPP


// ===========================  END OF handler.hpp  ===========================

