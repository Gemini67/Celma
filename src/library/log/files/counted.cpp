
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::Counted.


// module header file include
#include "celma/log/files/counted.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/file_operations.hpp"
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Checks that the given log filename definition contains a log
/// generation number.
///
/// @param[in]  fname_def
///    Log filename definition.
/// @param[in]  max_entries
///    The maximum number of entries to write into a log file.
/// @param[in]  max_gen
///    Maximum number of log file generations to keep.
/// @since  x.y.z, 05.09.2018
Counted::Counted( const filename::Definition& fname_def, size_t max_entries,
                  int max_gen):
   PolicyBase( fname_def),
   mMaxEntries( max_entries),
   mMaxGenerations( max_gen)
{

   if (!mFilenameDefinition.hasGenerationNbr())
      throw std::runtime_error( "a log filename definition for log files "
         "limited by number of entries must include a log file generation number");

} // Counted::Counted



/// Copy constructor. Copies only the settings but not any eventually open
/// log file.
///
/// @param[in]  other  The other object to copy the data from.
/// @since  x.y.z, 05.09.2018
Counted::Counted( const Counted& other):
   PolicyBase( other),
   mMaxEntries( other.mMaxEntries),
   mMaxGenerations( other.mMaxGenerations)
{
} // Counted::Counted



/// Checks the currently open file if it can still be used, i.e. it is empty.
///
/// @return
///    \c true if the current log file can still be used, \c false if the log
///    file(s) should be rolled.
/// @since  x.y.z, 05.09.2018
bool Counted::openCheck()
{
   return fileSize() == 0;
} // Counted::openCheck



/// Called when openCheck() return \c false. Rolls the existing log file
/// generations.
///
/// @since  x.y.z, 05.09.2018
void Counted::rollFiles()
{

   const filename::Builder  fname_builder( mFilenameDefinition);

   for (int file_nbr = mMaxGenerations - 1; file_nbr > 0; --file_nbr)
   {
      std::string  dest_filename;
      std::string  src_filename;

      fname_builder.filename( dest_filename, file_nbr,     ::time( nullptr));
      fname_builder.filename( src_filename,  file_nbr - 1, ::time( nullptr));
      // ignore errors of files that don't exist
      common::FileOperations::rename( dest_filename, src_filename);
   } // end for

} // Counted::rollFiles



/// Called to check if the next log message can still be written into the
/// current log file.<br>
/// Here, checks if the maximum number of entries is not yet reached.
///
/// @param[in]  msg
///    Ignored.
/// @param[in]  msg_text
///    Ignored.
/// @return
///    \c true if the log message text can be written into the current log
///    file.
/// @since  x.y.z, 05.09.2018
bool Counted::writeCheck( const detail::LogMsg&, const std::string&)
{

   return mNumberOfEntries + 1 <= mMaxEntries;
} // Counted::writeCheck



/// Called after the log message was written into the log file. Here, updates
/// the #mNumberOfEntries variable.
///
/// @param[in]  msg
///    Ignored.
/// @param[in]  msg_text
///    Ignored.
/// @since  x.y.z, 05.09.2018
void Counted::written( const detail::LogMsg&, const std::string&)
{

   ++mNumberOfEntries;

} // Counted::written



} // namespace files
} // namespace log
} // namespace celma


// =====  END OF counted.cpp  =====

