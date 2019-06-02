
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
/// See documentation of class celma::common::detail::FileFuncsOs.


// module header file include
#include "celma/common/detail/file_funcs_os.hpp"


// OS/C lib includes
#include <cstdio>
#include <sys/stat.h>


namespace celma { namespace common { namespace detail {



/// Calls ::rename() to actually rename a file.
///
/// @param[in]  dest
///    The new (path and) name for the file.
/// @param[in]  src
///    The (path and) name of the existing file that should be renamed.
/// @return  The return code from ::rename().
/// @since  1.4.0, 20.02.2018
int FileFuncsOs::rename( const std::string& dest, const std::string& src)
{

   return ::rename( src.c_str(), dest.c_str());
} // FileFuncsOs::rename



/// Removes (deletes) a file.
///
/// @param[in]  file  The (path and) name of the %file to delete.
/// @return  The result code from ::remove().
/// @since  1.4.0, 28.02.2018
int FileFuncsOs::remove( const std::string& file)
{

   return ::remove( file.c_str());
} // FileFuncsOs::remove



/// Creates a directory.
///
/// @param[in]  dir_name
///    The (path and) name of the directory to create.
/// @param[in]  mode
///    The permissions to create the directory with.
/// @return  The result code of the %mkdir operation.
/// @since  1.26.0, 21.05.2019
int FileFuncsOs::mkdir( const std::string& dir_name, int mode)
{
   return ::mkdir( dir_name.c_str(), mode);
} // FileFuncsOs::mkdir



} // namespace detail
} // namespace common
} // namespace celma


// =====  END OF file_funcs_os.cpp  =====

