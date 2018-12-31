
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::appla::ProjectPath.


// module header file include
#include "celma/appl/project_path.hpp"


// C/OS library includes
#include <unistd.h>
#include <cstdlib>
#include <cstring>


// C++ Standard Library includes
#include <iostream>
#include <stdexcept>


// project includes
#include "celma/appl/project_root.hpp"
#include "celma/common/string_util.hpp"


namespace celma { namespace appl {


namespace {



/// Tries to determine the value of the environment variable \a envName, throws
/// an exception if it is unknown.
/// @param[in]  envName  The name of the environment variable to return the
///                      value of.
/// @return  The value of the environment variable.
/// @since  1.0.0, 11.01.2017
inline const char* checkGetEnv( const char* envName) noexcept( false)
{

   const char*  env = ::getenv( envName);


   if (env == nullptr)
      throw std::runtime_error( "could not determine value of '" +
                                std::string( envName) + "'");

   return env;
} // checkGetEnv



} // namespace



/// Constructor.
/// @param[in]  subDir    The sub-directory of the project root path.
/// @param[in]  filename  The name of the file.
/// @param[in]  fileExt   The file extension/suffix.
/// @since  1.0.0, 11.01.2017
ProjectPath::ProjectPath( const char* subDir, const char* filename,
                          const char* fileExt)
{

   if ((subDir == nullptr) || (filename == nullptr) || (fileExt == nullptr))
      throw std::runtime_error( "parameter may not be set to NULL");

   store( subDir, filename, fileExt);

} // ProjectPath::ProjectPath



/// Constructor.
/// @param[in]  subDir    The sub-directory of the project root path.
/// @param[in]  filename  The name of the file, maybe with suffix.
/// @since  1.0, 12.03.2015
ProjectPath::ProjectPath( const char* subDir, const char* filename)
{

   if ((subDir == nullptr) || (filename == nullptr))
      throw std::runtime_error( "parameter may not be set to NULL");

   store( subDir, filename, nullptr);

} // ProjectPath::ProjectPath



/// Constructor.
/// @param[in]  filename  The (path and) name of the file, maybe with suffix.
/// @since  1.0.0, 11.01.2017
ProjectPath::ProjectPath( const char* filename)
{

   if (filename == nullptr)
      throw std::runtime_error( "parameter may not be set to NULL");

   store( nullptr, filename, nullptr);

} // ProjectPath::ProjectPath



/// Streams the absolute path and file name.
/// @param[out]  os  The stream to write to.
/// @param[in]   pp  The object to stream the path/filename of.
/// @return  The stream as passed in \a os.
/// @since  1.0.0, 11.01.2017
std::ostream& operator <<( std::ostream& os, const ProjectPath& pp)
{

   return os << pp.mFullPathFilename;
} // operator <<



/// Builds the absolute path and file name with all components.
/// @param[in]  subDir    The sub-directory of the project root dir, may
///                       be NULL.
/// @param[in]  filename  The file name.
/// @param[in]  fileExt   The file extension/suffix, may be NULL.
/// @since  1.0.0, 11.01.2017
void ProjectPath::store( const char* subDir, const char* filename,
                         const char* fileExt)
{

   mFullPathFilename.assign( ProjectRoot::instance().path());

   if (subDir != nullptr)
   {
      if (subDir[ 0] == '/')
         mFullPathFilename.append( subDir, 1, ::strlen( subDir) - 1);
      else
         mFullPathFilename.append( subDir);
   } // end if

   // filename is never NULL
   if (filename[ 0] != '/')
      common::ensure_last( mFullPathFilename);

   mFullPathFilename.append( filename);

   if (fileExt != nullptr)
   {
      if (fileExt[ 0] != '.')
         common::ensure_last( mFullPathFilename, '.');
      mFullPathFilename.append( fileExt);
   } // end if

} // ProjectPath::store



} // namespace appl
} // namespace celma


// =====  END OF project_path.cpp  =====

