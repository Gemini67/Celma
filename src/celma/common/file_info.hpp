
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


#ifndef CELMA_COMMON_FILE_INFO_HPP
#define CELMA_COMMON_FILE_INFO_HPP


#include <sys/stat.h>
#include <cstdio>
#include <string>


namespace celma { namespace common {


/// This class provides easy access to the data of an object in the file system,
/// a file or a directory. Simply create an object of this class and then call
/// the desired getter methods.<br>
/// The file statistics is collected only in the constructors. If update-to-date
/// infos from a file is needed repeatedly, either create a new object each
/// time, or use the fileInfo() function.
/// @since  1.4.0, 27.02.2018
class FileInfo
{
public:
   /// Constructor with the (path and) file name in an std::string.
   /// @param[in]  filename  The (path and) name of the file or directory to
   ///                       retrieve the statistics from.
   /// @throws  if the given object does not exist or if the statistics could
   ///          not be collected.
   /// @since  1.4.0, 27.02.2018
   explicit FileInfo( const std::string& filename) noexcept( false);

   /// Constructor with the (path and) file name in a C string (character
   /// array).
   /// @param[in]  filename  The (path and) name of the file or directory to
   ///                       retrieve the statistics from.
   /// @throws  if the given object does not exist or if the statistics could
   ///          not be collected.
   /// @since  1.4.0, 27.02.2018
   explicit FileInfo( const char* filename) noexcept( false);

   /// Constructor with a FILE pointer.
   /// @param[in]  fp  The FILE pointer to retrieve the statistics from.
   /// @throws  if the statistics could not be collected.
   /// @since  1.4.0, 27.02.2018
   explicit FileInfo( FILE* fp) noexcept( false);

   /// Constructor with a file descriptor.
   /// @param[in]  fp  The file descriptor to retrieve the statistics from.
   /// @throws  if the statistics could not be collected.
   /// @since  1.4.0, 27.02.2018
   explicit FileInfo( int fd) noexcept( false);

   /// Constructor with file statistics.
   /// @param[in]  stat_data  The statistics data of a file.
   /// @since  1.4.0, 27.02.2018
   explicit FileInfo( struct stat& stat_data);

   /// Default copy constructur and move constructor are just fine.
   FileInfo( const FileInfo& other) = default;
   FileInfo( FileInfo&& other) = default;

   /// Returns the path and name of the parent directory of the current entry.
   ///
   /// @return  The path and name of the parent directory of the current entry.
   /// @throws  If the current object was not created with a file path and name.
   /// @since  1.9.0, 04.08.2018
   std::string parentDirectory() const noexcept( false);

   /// Returns the size of the file.
   /// @return  The size of the file in bytes.
   /// @since  1.4.0, 27.02.2018
   size_t size() const;

   /// Returns if the file system object is a regular file.
   /// @return  \c true if the object in the file system is a regular file.
   /// @since  1.4.0, 27.02.2018
   bool isFile() const;

   /// Returns if the file system object is a directory.
   /// @return  \c true if the object in the file system is a directory.
   /// @since  1.4.0, 27.02.2018
   bool isDirectory() const;

private:
   /// The path and name of the file, as given to the constructor.<br>
   /// Needed for the function parentDirectory(), not const to allow copying.
   std::string  mEntryName;
   /// The data of the file.
   struct stat  mFileStat;

}; // FileInfo


// inlined methods
// ===============


inline size_t FileInfo::size() const
{
   return mFileStat.st_size;
} // FileInfo::size


inline bool FileInfo::isFile() const
{
   return (mFileStat.st_mode & S_IFREG) != 0;
} // FileInfo::isFile


inline bool FileInfo::isDirectory() const
{
   return (mFileStat.st_mode & S_IFDIR) != 0;
} // FileInfo::isDirectory


/// If just one info is needed from a file, e.g. the size, use this function to
/// get a (temporary) FileInfo object.<br>
/// The funcion is implemented as a template in order to support all the
/// different constructors of the class FileInfo.
/// @param[in]  init_value  The value to pass to the constructor of the FileInfo
///                         object.
/// @return  A FileInfo object for the given data.
/// @since  1.4.0, 27.02.2018
template< typename T> FileInfo fileInfo( T init_value)
{
   return FileInfo( init_value);
} // fileInfo


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_FILE_INFO_HPP


// =====  END OF file_info.hpp  =====

