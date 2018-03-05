
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
/// See documentation of class celma::FileOperations.


// module header file include
#include "celma/common/file_operations.hpp"


// project includes
#include "celma/common/detail/file_funcs_os.hpp"


namespace celma { namespace common {



std::unique_ptr< detail::FileFuncsBase>
   FileOperations::mpFileFuncs( std::make_unique< detail::FileFuncsOs>());



/// Sets a new object which implements the file functions to use.
/// @param[in]  obj  Pointer to the object that implements the file
///                  functions. May not be NULL.
/// @throws  if the given object pointer is NULL.
/// @since  1.4.0, 20.02.2018
void FileOperations::setFuncImpl( detail::FileFuncsBase* obj)
{

   if (obj == nullptr)
      throw std::runtime_error( "file functions object pointer may not be NULL");


   mpFileFuncs.reset( obj);

} // FileOperations::setFuncImpl



/// Renames a file from \a src to \a dest.
/// @param[in]  dest  The new (path and) name for the file.
/// @param[in]  src   The (path and) name of the existing file that should be
///                   renamed.
/// @return  The result code from ::rename().
/// @since  1.4.0, 20.02.2018
int FileOperations::rename( const std::string& dest, const std::string& src)
{

   return mpFileFuncs->rename( dest, src);
} // FileOperations::rename



/// Removes (deletes) a file.
/// @param[in]  file  The (path and) name of the %file to delete.
/// @return  The result code from ::remove().
/// @since  1.4.0, 28.02.2018
int FileOperations::remove( const std::string& file)
{

   return mpFileFuncs->remove( file);
} // FileOperations::remove



} // namespace common
} // namespace celma


// =====  END OF file_operations.cpp  =====

