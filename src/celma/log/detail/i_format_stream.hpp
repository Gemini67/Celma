
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
/// See documentation of class celma::log::detail::IFormatStream.


#ifndef CELMA_LOG_DETAIL_I_FORMAT_STREAM_HPP
#define CELMA_LOG_DETAIL_I_FORMAT_STREAM_HPP


#include <iosfwd>
#include "i_format_base.hpp"
#include "log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Interface definition of a (log) stream output formatter.
/// @since  0.3, 19.06.2016
class IFormatStream: public IFormatBase
{
public:
   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   virtual ~IFormatStream() { }

   /// Visible interface. Calls format() (from the derived classes).
   /// @param[out]  out  The stream to write into.
   /// @param[in]   msg  The message to format the data of.
   /// @since  0.3, 19.06.2016
   void formatMsg( std::ostream& out, const LogMsg& msg) const;

private:
   /// Interface definition of the method to be implmented by derived classes.
   /// @param[out]  out  The stream to write into.
   /// @param[in]   msg  The message to format the data of.
   /// @since  0.3, 19.06.2016
   virtual void format( std::ostream& out, const LogMsg& msg) const = 0;

}; // IFormatStream


// inlined methods
// ===============


inline void IFormatStream::formatMsg( std::ostream& out, const LogMsg& msg) const
{
   format( out, msg);
} // end IFormatStream::formatMsg


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_I_FORMAT_STREAM_HPP


// =======================  END OF i_format_stream.hpp  =======================

