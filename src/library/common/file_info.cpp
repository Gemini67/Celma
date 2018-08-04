
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
/// See documentation of class celma::common::FileInfo and the
/// function fileInfo.


// module header file include
#include "celma/common/file_info.hpp"


// OS/C library includes
#include <cerrno>
#include <cstring>
#include <libgen.h>


// C++ Standard Library includes
#include <memory>
#include <stdexcept>


namespace celma { namespace common {



/// Constructor with the (path and) file name in an std::string.
/// @param[in]  filename  The (path and) name of the file or directory to
///                       retrieve the statistics from.
/// @throws  if the given object does not exist or if the statistics could
///          not be collected.
/// @since  1.4.0, 27.02.2018
FileInfo::FileInfo( const std::string& filename):
   FileInfo( filename.c_str())
{
} // FileInfo::FileInfo



/// Constructor with the (path and) file name in a C string (character
/// array).
/// @param[in]  filename  The (path and) name of the file or directory to
///                       retrieve the statistics from.
/// @throws  if the given object does not exist or if the statistics could
///          not be collected.
/// @since  1.4.0, 27.02.2018
FileInfo::FileInfo( const char* filename):
   mEntryName( filename)
{

   if (::stat( filename, &mFileStat) != 0)
      throw std::runtime_error( std::string( "could not stat path '")
         + filename + "': error " + std::to_string( errno) + " = " +
         ::strerror( errno));

} // FileInfo::FileInfo



/// Constructor with a FILE pointer.
/// @param[in]  fp  The FILE pointer to retrieve the statistics from.
/// @throws  if the statistics could not be collected.
/// @since  1.4.0, 27.02.2018
FileInfo::FileInfo( FILE* fp):
   FileInfo( ::fileno( fp))
{
} // FileInfo::FileInfo



/// Constructor with a file descriptor.
/// @param[in]  fp  The file descriptor to retrieve the statistics from.
/// @throws  if the statistics could not be collected.
/// @since  1.4.0, 27.02.2018
FileInfo::FileInfo( int fd):
   mEntryName()
{

   if (::fstat( fd, &mFileStat) != 0)
      throw std::runtime_error( std::string( "could not stat given "
         "filedescriptor: error ") + std::to_string( errno) + " = " +
         ::strerror( errno));

} // FileInfo::FileInfo



/// Constructor with file statistics.
/// @param[in]  stat_data  The statistics data of a file.
/// @since  1.4.0, 27.02.2018
FileInfo::FileInfo( struct stat& stat_data):
   mEntryName(),
   mFileStat( stat_data)
{
} // FileInfo::FileInfo



/// Returns the path and name of the parent directory of the current entry.
///
/// @return  The path and name of the parent directory of the current entry.
/// @since  1.9.0, 04.08.2018
std::string FileInfo::parentDirectory() const
{

   if (mEntryName.empty())
      throw std::runtime_error( "cannot determine parent directory since path "
         "and file name are unknown");

   std::unique_ptr< char>  copy( new char[ mEntryName.length()]);
   ::strcpy( copy.get(), mEntryName.c_str());

   const std::string  result( ::dirname( copy.get()));

   return result;  
} // FileInfo::parentDirectory



} // namespace common
} // namespace celma


// =====  END OF file_info.cpp  =====

