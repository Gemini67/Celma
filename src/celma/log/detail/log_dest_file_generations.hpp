
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
/// See documentation of class celma::log::detail::@@@.


#ifndef CELMA_LOG_DETAIL_LOG_DEST_FILE_GENERATIONS_HPP
#define CELMA_LOG_DETAIL_LOG_DEST_FILE_GENERATIONS_HPP


#include <fstream>
#include <string>
#include "celma/log/detail/format_stream_default.hpp"
#include "celma/log/detail/i_format_stream.hpp"
#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/no_generation_policy.hpp"


namespace celma { namespace log { namespace detail {


/// @todo  Use ProjectPath for path.
/// @since  x.y.z, 19.06.2016
template< typename P = NoGenerationPolicy> class LogDestFileGenerations:
   public ILogDest, private P
{
public:
   using P::openLogfile;

   /// 
   /// @param[in]  path      .
   /// @param[in]  filename  .
   /// @since  x.y.z, 19.06.2016
   LogDestFileGenerations( const std::string& path, const std::string filename);

   /// Sets the new formatter to use.<br>
   /// Although the pointer type is \a IFormatBase only, objects passed here
   /// must be derived from the \a IFormatStream class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  x.y.z, 19.06.2016
   virtual void setFormatter( IFormatBase* formatter = nullptr) override;

private:
   /// Called through the base class. Writes a log message to the specified log
   /// file.
   /// @param[in]  msg  The message to write.
   /// @since  x.y.z, 19.06.2016
   virtual void message( const LogMsg& msg) override;

   /// The object used for formatting stream output.
   std::unique_ptr< IFormatStream>  mpFormatter;
   std::ofstream                    mDest;

}; // LogDestFileGenerations< P>


// inlined methods
// ===============


template< typename P>
   LogDestFileGenerations< P>::LogDestFileGenerations( const std::string& path,
                                                       const std::string filename):
      P( path, filename),
      mpFormatter( new FormatStreamDefault())
{
} // LogDestFileGenerations< P>::LogDestFileGenerations


template< typename P>
   void LogDestFileGenerations< P>::setFormatter( IFormatBase* formatter)
{
   mpFormatter.reset( (formatter == nullptr) ? new FormatStreamDefault() :
                                               static_cast< IFormatStream*>( formatter));
} // LogDestFileGenerations< P>::setFormatter


template< typename P>
   void LogDestFileGenerations< P>::message( const LogMsg& msg)
{
   openLogfile( mDest);
   mpFormatter->formatMsg( mDest, msg);
} // LogDestFileGenerations< P>::message


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_DEST_FILE_GENERATIONS_HPP


// ==================  END OF log_dest_file_generations.hpp  ==================

