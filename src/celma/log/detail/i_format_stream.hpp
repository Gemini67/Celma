
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
/// See documentation of class celma::log::detail::IFormatStream.


#pragma once


#include <iosfwd>
#include "i_format_base.hpp"
#include "log_msg.hpp"


namespace celma::log::detail {


/// Interface definition of a (log) stream output formatter.
/// @since  0.3, 19.06.2016
class IFormatStream : public IFormatBase
{
public:
   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   ~IFormatStream() override = default;

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
} // IFormatStream::formatMsg


} // namespace celma::log::detail


// =====  END OF i_format_stream.hpp  =====

