
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::FileFuncsOs.


#pragma once


#include <string>
#include "celma/common/detail/file_funcs_base.hpp"


namespace celma::common::detail {


/// Implementation of file functions for really calling the OS functions.
///
/// @since  1.26.0, 21.05.2019
///    (re-added mkdir, originally implemented 08.03.2018)
/// @since  1.4.0, 20.02.2018
class FileFuncsOs final : public FileFuncsBase
{
public:
   /// Empty, virtual destructor.
   ///
   /// @since  1.4.0, 20.02.2018
   ~FileFuncsOs() override = default;

   /// Calls ::rename() to actually rename a file.
   ///
   /// @param[in]  dest
   ///    The new (path and) name for the file.
   /// @param[in]  src
   ///    The (path and) name of the existing file that should be renamed.
   /// @return  The return code from ::rename().
   /// @since  1.4.0, 20.02.2018
   int rename( const std::string& dest, const std::string& src) override;

   /// Removes (deletes) a file.
   ///
   /// @param[in]  file  The (path and) name of the %file to delete.
   /// @return  The result code from ::remove().
   /// @since  1.4.0, 28.02.2018
   int remove( const std::string& file) override;

   /// Creates a directory.
   ///
   /// @param[in]  dir_name
   ///    The (path and) name of the directory to create.
   /// @param[in]  mode
   ///    The permissions to create the directory with.
   /// @return  The result code of the %mkdir operation.
   /// @since  1.26.0, 21.05.2019
   int mkdir( const std::string& dir_name, int mode) override;

}; // FileFuncsOs


} // namespace celma::common::detail


// =====  END OF file_funcs_os.hpp  =====

