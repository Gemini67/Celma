
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
/// See documentation of class celma::appla::ProjectRoot.


// module header file include
#include "celma/appl/project_root.hpp"


// OS/C library includes
#include <unistd.h>
#include <cstdlib>
#include <cstring>


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/string_util.hpp"


namespace celma { namespace appl {


namespace {


/// Tries to determine the value of the environment variable \a envName, throws
/// an exception if it is unknown.
///
/// @param[in]  envName
///    The name of the environment variable to return the value of.
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



/// Initialise the 'project root' directory.<br>
/// If this method is not called explicitly, it is called when the singleton
/// object is created.
///
/// @param[in]  srcType
///    Base to use to determine the root of the project.
/// @param[in]  source
///    If \a srcType ProjRootSrc::env or ProjRootSrc::bin are used, the
///    corresponding value (name of the environment variable or the program
///    start path, respectively) must be passed here.
/// @since  1.0.0, 11.01.2017
void ProjectRoot::setProjectRoot( ProjRootSrc srcType, const char* source)
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
      [[fallthrough]];  // intentionally no break here!
   case ProjRootSrc::cwd:
      if (char* currWD = ::get_current_dir_name())
      {
         mProjectRootSource = ProjRootSrc::cwd;
         mProjectRoot.assign( currWD);
         free( currWD);
      } else
      {
         throw std::runtime_error( "could not determine 'current working "
                                   "directory");
      } // end if
      break;
   default:
      throw std::runtime_error( "unknown source type for setting project root "
                                "directory");
   } // end switch

   common::ensure_last( mProjectRoot);

} // ProjectRoot::setProjectRoot



/// Returns if the specified file is beneath the project root.
/// @param[in]  path_file_name  The absolute path and file name to check.
/// @return  \c true if the specified file is beneath the project root.
/// @since  1.0.0, 11.01.2017
bool ProjectRoot::isOnProject( const std::string& path_file_name)
{

   if (path_file_name[ 0] != '/')
      throw std::runtime_error( "must be absolute path and file name");

   if (mProjectRootSource == ProjRootSrc::unset)
      throw std::runtime_error( "project root not set");

   // have to specify the sub-string of the longer string (path_file_name) to
   // compare against the shorter (project root) string
   return path_file_name.compare( 0, mProjectRoot.length(), mProjectRoot) == 0;
} // ProjectRoot::isOnProject



/// Default constructor, sets the home directory as project root.
///
/// @since  1.0.0, 18.10.2017
ProjectRoot::ProjectRoot():
   ProjectRoot( ProjRootSrc::home)
{
} // ProjectRoot::ProjectRoot



/// Constructor, initialises the project root path with the given parameters.
///
/// @param[in]  srcType
///    The type of initialisation to use for the project root.
/// @param[in]  source
///    For some initialisation types, additional value (e.g. name of
///    environment variable).
/// @since  1.0.0, 18.10.2017
ProjectRoot::ProjectRoot( ProjRootSrc srcType, const char* source):
   mProjectRoot()
{

   setProjectRoot( srcType, source);

} // ProjectRoot::ProjectRoot



} // namespace appl
} // namespace celma


// =====  END OF project_root.cpp  =====

