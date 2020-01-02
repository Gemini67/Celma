
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


#ifndef CELMA_LOG_TEST_TEST_FILE_FUNCS_IMPL_HPP
#define CELMA_LOG_TEST_TEST_FILE_FUNCS_IMPL_HPP


#include <string>
#include "celma/common/detail/file_funcs_base.hpp"
#include "celma/common/detail/file_funcs_os.hpp"
#include "test_i_dir_list.hpp"


namespace celma { namespace log {


/// Helper class for cleaning up the temporary directories that were created
/// during the log file types tests.<br>
/// This module calls the functions of the "normal" FileFuncsOs class, only in
/// the function that is called when a directory should be created, it
/// additionally calls the function in the object given in the constructor.
/// @since  1.26.0, 08.03.2018
class TestFileFuncsImpl: public common::detail::FileFuncsBase
{
public:
   /// Constructor, stores the object whose callback function is called when
   /// a directory is created.
   /// @param[in]  dir_handler  The object whose callback should be called when
   ///                          a directory is created.
   /// @since  1.26.0, 08.03.2018
   TestFileFuncsImpl( TestIDirList* dir_handler):
      mOsFuncs(),
      mpDirHandler( dir_handler)
   {
   } // TestFileFuncsImpl::TestFileFuncsImpl
      
   /// Empty, virtual destructor for base class.
   /// @since  1.4.0, 08.03.2018
   virtual ~TestFileFuncsImpl() = default;

   /// Gets called when a file should be renamed.
   /// @param[in]  dest  The new (pah and) name for the file.
   /// @param[in]  src   The (path and) name of the existing file that should be
   ///                   renamed.
   /// @return  The result of the %rename operation.
   /// @since  1.26.0, 08.03.2018
   int rename( const std::string& dest, const std::string& src) override
   {
      return mOsFuncs.rename( dest, src);
   } // TestFileFuncsImpl::rename

   /// Gets called when a %file should be removed.
   /// @param[in]  file  The (path and) name of the %file to delete.
   /// @return  The result code of the %remove operation.
   /// @since  1.26.0, 08.03.2018
   int remove( const std::string& file) override
   {
      return mOsFuncs.remove( file);
   } // TestFileFuncsImpl::remove

   /// Creates a directory.
   /// @param[in]  dir_name  The (path and) name of the directory to create.
   /// @param[in]  mode      The permissions to create the directory with.
   /// @return  The result code of the %mkdir operation.
   /// @since  1.26.0, 08.03.2018
   int mkdir( const std::string& dir_name, int mode) override
   {
      // insert the name of the directory into the directory list
      mpDirHandler->dirCreated( dir_name);
      return mOsFuncs.mkdir( dir_name, mode);
   } // TestFileFuncsImpl::mkdir

private:
   /// Object that implements the real OS functions.
   common::detail::FileFuncsOs  mOsFuncs;
   /// Pointer to the object whose callback function is called when a new
   /// directory is created.
   TestIDirList*                mpDirHandler;

}; // FileFuncsBase


} // namespace log
} // namespace celma


#endif   // CELMA_LOG_TEST_TEST_FILE_FUNCS_IMPL_HPP


// =====  END OF test_file_funcs_impl.hpp  =====

