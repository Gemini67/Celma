
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
/// See documentation of class celma::log::files::MaxSize.


// module header file include
#include "celma/log/files/max_size.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Checks that the given log filename definition contains a log
/// generation number.
/// @param[in]  fname_def      Log filename definition.
/// @param[in]  max_file_size  The maximum size of a log file.
/// @param[in]  max_gen        Maximum number of log file generations to
///                            keep.
/// @since  1.0.0, 13.12.2017
MaxSize::MaxSize( const filename::Definition& fname_def, size_t max_file_size,
                  int max_gen):
   PolicyBase( fname_def),
   mMaxFileSize( max_file_size),
   mCurrentFilesize( 0),
   mMaxGenerations( max_gen)
{

   if (!mFilenameDefinition.hasGenerationNbr())
      throw std::runtime_error( "a log filename definition for log files "
         "limited by size must include a log file generation number");

} // MaxSize::MaxSize



/// Copy constructor. Copies only the settings but not any eventually open
/// log file.
/// @param[in]  other  The other object to copy the data from.
/// @since  1.0.0, 13.12.2017
MaxSize::MaxSize( const MaxSize& other):
   PolicyBase( other),
   mMaxFileSize( other.mMaxFileSize),
   mCurrentFilesize( 0),
   mMaxGenerations( other.mMaxGenerations)
{
} // MaxSize::MaxSize



/// Checks the currently open file if the file limit is reached.
/// @return  \c true if the current log file can still be used, \c false if
///          the log file(s) should be rolled.
/// @since  1.0.0, 13.12.2017
bool MaxSize::openCheck()
{
   mCurrentFilesize = mFile.tellp();
   return mCurrentFilesize < mMaxFileSize;
} // MaxSize::openCheck



/// Called when openCheck() return \c false. Rolls the existing log file
/// generations.
/// @since  1.0.0, 13.12.2017
void MaxSize::rollFiles()
{

   for (int file_nbr = mMaxGenerations - 1; file_nbr > 0; --file_nbr)
   {
      filename::Builder  fname_builder( mFilenameDefinition);
      std::string        dest_filename;
      std::string        src_filename;

      fname_builder.filename( dest_filename, file_nbr,     ::time( nullptr));
      fname_builder.filename( src_filename,  file_nbr - 1, ::time( nullptr));
      // ignore errors of files that don't exist
      ::rename( dest_filename.c_str(), src_filename.c_str());
   } // end for

} // MaxSize::rollFiles



/// Called to check if the next log message can still be written into the
/// current log file.<br>
/// Here, checks if the log file size still allows to write the given log
/// message into the file
/// @param[in]  msg       Ignored.
/// @param[in]  msg_text  The formatted text of the log message.
/// @return  \c true if the log message text can be written into the current
///          log file.
/// @since  1.0.0, 13.12.2017
bool MaxSize::writeCheck( const detail::LogMsg&, const std::string& msg_text)
{

   return mCurrentFilesize + msg_text.length() < mMaxFileSize;
} // MaxSize::writeCheck



/// Called after the log message was written into the log file. Here, updates
/// the #mCurrentFilesize variable.
/// @param[in]  msg       Ignored.
/// @param[in]  msg_text  The formatted text of the log message that was
///                       written into the log file.
/// @since  1.0.0, 13.12.2017
void MaxSize::written( const detail::LogMsg&, const std::string& msg_text)
{

   mCurrentFilesize += msg_text.length();

} // MaxSize::written



} // namespace files
} // namespace log
} // namespace celma


// ===========================  END OF max_size.cpp  ===========================

