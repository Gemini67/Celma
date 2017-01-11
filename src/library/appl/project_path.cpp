
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
#include "celma/common/string_util.hpp"


namespace celma { namespace appl {


// static class members
std::string               ProjectPath::mProjectRoot;
ProjectPath::ProjRootSrc  ProjectPath::mProjectRootSource = ProjectPath::ProjRootSrc::unset;



namespace {



/// Tries to determine the value of the environment variable \a envName, throws
/// an exception if it is unknown.
/// @param[in]  envName  The name of the environment variable to return the
///                      value of.
/// @return  The value of the environment variable.
/// @since  0.12, 11.01.2017
inline const char* checkGetEnv( const char* envName) noexcept( false)
{

   const char*  env = ::getenv( envName);


   if (env == nullptr)
      throw std::runtime_error( "could not determine value of '" +
                                std::string( envName) + "'");

   return env;
} // checkGetEnv



} // namespace



/// Initialise the 'project root' directory.<br>
/// If this method is not called explicitly, it is called by the first used
/// constructor with \a srcType set to ProjRootSrc::home.
/// @param[in]  srcType  Base to use to determine the root of the project.
/// @param[in]  source   If \a srcType ProjRootSrc::env or ProjRootSrc::bin
///                      are used, the corresponding value (name of the
///                      environment variable or the program start path,
///                      respectively) must be passed here.
/// @since  0.12, 11.01.2017
void ProjectPath::setProjectRoot( ProjRootSrc srcType, const char* source)
{

   switch (srcType)
   {
   case ProjRootSrc::home:
      mProjectRoot.assign( checkGetEnv( "HOME"));
      mProjectRootSource = ProjRootSrc::home;
      break;
   case ProjRootSrc::env:
      if (source == nullptr)
         throw std::runtime_error( "name of environment variable not specified");
      mProjectRootSource = ProjRootSrc::env;
      mProjectRoot.assign( checkGetEnv( source));
      break;
   case ProjRootSrc::bin:
      if (source == nullptr)
         throw std::runtime_error( "program start path not specified");
      if (const char* pos = ::strstr( source, "bin/"))
      {
         mProjectRootSource = ProjRootSrc::bin;
         mProjectRoot.assign( source, 0, pos - source); 
         break;   // switch
      } // end if
      // intentionally no break here!
   case ProjRootSrc::cwd:
      if (char* currWD = ::get_current_dir_name())
      {
         mProjectRootSource = ProjRootSrc::cwd;
         mProjectRoot.assign( currWD);
         free( currWD);
      } else
      {
         throw std::runtime_error( "could not determine 'current working directory");
      } // end if
      break;
   default:
      throw std::runtime_error( "unknown source type for setting project root directory");
   } // end switch

   common::ensure_last( mProjectRoot);

} // ProjectPath::setProjectRoot



/// Returns if the specified file is beneath the project root.
/// @param[in]  path_file_name  The absolute path and file name to check.
/// @return  \c true if the specified file is beneath the project root.
/// @since  0.12, 11.01.2017
bool ProjectPath::isOnProject( const std::string& path_file_name)
{

   if (path_file_name[ 0] != '/')
      throw std::runtime_error( "must be absolute path and file name");

   if (mProjectRootSource == ProjRootSrc::unset)
      throw std::runtime_error( "project root not set");

   // have to specify the sub-string of the longer string (path_file_name) to
   // compare against the shorter (project root) string
   return path_file_name.compare( 0, mProjectRoot.length(), mProjectRoot) == 0;
} // ProjectPath::isOnProject



/// Constructor.
/// @param[in]  subDir    The sub-directory of the project root path.
/// @param[in]  filename  The name of the file.
/// @param[in]  fileExt   The file extension/suffix.
/// @since  0.12, 11.01.2017
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
/// @since  0.12, 11.01.2017
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
/// @since  0.12, 11.01.2017
std::ostream& operator <<( std::ostream& os, const ProjectPath& pp)
{

   return os << pp.mFullPathFilename;
} // operator <<



/// Builds the absolute path and file name with all components.
/// @param[in]  subDir    The sub-directory of the project root dir, may
///                       be NULL.
/// @param[in]  filename  The file name.
/// @param[in]  fileExt   The file extension/suffix, may be NULL.
/// @since  0.12, 11.01.2017
void ProjectPath::store( const char* subDir, const char* filename,
                         const char* fileExt)
{

   if (mProjectRoot.empty())
      setProjectRoot( ProjRootSrc::home);

   mFullPathFilename.assign( mProjectRoot);

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


// =========================  END OF project_path.cpp  =========================

