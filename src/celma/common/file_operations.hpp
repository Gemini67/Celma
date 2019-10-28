
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::FileOperations.


#ifndef CELMA_COMMON_FILE_OPERATIONS_HPP
#define CELMA_COMMON_FILE_OPERATIONS_HPP


#include <memory>
#include <string>
#include "celma/common/detail/file_funcs_base.hpp"


namespace celma { namespace common {


/// Helper class that provides some file-related operations. By default these
/// are directly passed on to their OS/C-library counterpart, but a different
/// file functions implementation can be specified that does something else.
///
/// @since  1.26.0, 21.05.2019
///    (re-added mkdir, originally implemnted 08.03.2018)
/// @since  1.4.0, 20.02.2018
class FileOperations
{
public:
   /// Don't need to create object(s) of this class.
   FileOperations() = delete;
   FileOperations( const FileOperations&) = delete;

   /// Sets a new object which implements the file functions to use.
   ///
   /// @param[in]  obj
   ///    Pointer to the object that implements the file functions. May not be
   ///    NULL.
   /// @throw  std::runtime_error if the given object pointer is NULL.
   /// @since  1.4.0, 20.02.2018
   static void setFuncImpl( detail::FileFuncsBase* obj) noexcept( false);

   /// Renames a file from \a src to \a dest.
   ///
   /// @param[in]  dest
   ///    The new (path and) name for the file.
   /// @param[in]  src
   ///    The (path and) name of the existing file that should be renamed.
   /// @return  The result code from ::rename().
   /// @since  1.4.0, 20.02.2018
   static int rename( const std::string& dest, const std::string& src);

   /// Removes (deletes) a file.
   ///
   /// @param[in]  file  The (path and) name of the %file to delete.
   /// @return  The result code from ::remove().
   /// @since  1.4.0, 28.02.2018
   static int remove( const std::string& file);

   /// Creates a directory.
   ///
   /// @param[in]  dir_name
   ///    The (path and) name of the directory to create.
   /// @param[in]  mode
   ///    The permissions to create the directory with.
   /// @return  The result code from ::remove().
   /// @since  1.26.0, 21.05.2019
   static int mkdir( const std::string& dir_name, int mode = 0755);

private:
   /// Pointer to the object with the implementation of the file functions.
   static std::unique_ptr< detail::FileFuncsBase>  mpFileFuncs;

}; // FileOperations


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_FILE_OPERATIONS_HPP


// =====  END OF file_operations.hpp  =====

