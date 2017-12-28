
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
/// See documentation of class celma::appl::ProjectRoot.


#ifndef CELMA_APPL_PROJECT_ROOT_HPP
#define CELMA_APPL_PROJECT_ROOT_HPP


#include <string>
#include "celma/common/singleton.hpp"


namespace celma { namespace appl {


/// Provides the path of the root directory of a project.
/// @since  1.0.0, 18.10.2017  (extracted from ProjectPath)
class ProjectRoot: public common::Singleton< ProjectRoot>
{
public:
   /// Specifies how the value for the 'project root' directory is determined:
   enum class ProjRootSrc
   {
      unset,   //!< Project root not set yet.
      home,    //!< Use environment variable $HOME.
      env,     //!< Use the value of the environment variable specified in the
               //!< 'source' parameter.
      bin,     //!< Extract project root dir from binary path passed in
               //!< 'source'. Path must be in the form
               //!< '<proj-root-dir>/bin/prog'.
      cwd      //!< Use 'current working directory'.
   };

   /// Initialise the 'project root' directory.<br>
   /// If this method is not called explicitly, it is called when the singleton
   /// object is created.
   /// @param[in]  srcType  Base to use to determine the root of the project.
   /// @param[in]  source   If \a srcType ProjRootSrc::env or ProjRootSrc::bin
   ///                      are used, the corresponding value (name of the
   ///                      environment variable or the program start path,
   ///                      respectively) must be passed here.
   /// @since  1.0.0, 11.01.2017
   void setProjectRoot( ProjRootSrc srcType,
                        const char* source = nullptr) noexcept( false);

   /// Returns the project root dir.
   /// @return  The path set for the project root directory.
   /// @since  1.0.0, 11.01.2017
   const std::string& path();

   /// Returns the type of the source that was used to determine the project
   /// root.
   /// @return  Source type used for setting the project root.
   /// @since  1.0.0, 11.01.2017
   ProjRootSrc projectRootSrc();

   /// Returns if the specified file is beneath the project root.
   /// @param[in]  path_file_name  The absolute path and file name to check.
   /// @return  \c true if the specified file is beneath the project root.
   /// @since  1.0.0, 11.01.2017
   bool isOnProject( const std::string& path_file_name) noexcept( false);

protected:
   friend class common::Singleton< ProjectRoot>;

   ProjectRoot();

   /// 
   /// @param[in]  srcType  .
   /// @param[in]  source   .
   /// @return  .
   /// @since  1.0.0, 18.10.2017
   ProjectRoot( ProjRootSrc srcType,
                const char* source = nullptr) noexcept( false);

private:
   /// The project root path, same for all instances of this class (only one
   /// project for one process).
   std::string  mProjectRoot;
   /// The type of the source used to set the project root.
   ProjRootSrc  mProjectRootSource = ProjRootSrc::unset;

}; // ProjectRoot


// inlined methods
// ===============


inline const std::string& ProjectRoot::path()
{
   if (mProjectRoot.empty())
      setProjectRoot( ProjRootSrc::home);
   return mProjectRoot;
} // ProjectRoot::dir


inline ProjectRoot::ProjRootSrc ProjectRoot::projectRootSrc()
{
   return mProjectRootSource;
} // ProjectRoot::projectRootSrc


} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_PROJECT_ROOT_HPP


// =========================  END OF project_root.hpp  =========================
