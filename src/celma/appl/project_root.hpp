
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::appl::ProjectRoot.


#pragma once


#include <string>
#include "celma/common/singleton.hpp"


namespace celma::appl {


/// Provides the path of the root directory of a project.
/// @since  1.0.0, 18.10.2017  (extracted from ProjectPath)
class ProjectRoot final : public common::Singleton< ProjectRoot>
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

   /// Empty, virtual default destructor.
   /// @since  1.35.0, 10.03.2020
   ~ProjectRoot() override = default;

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

   /// Default constructor, sets the home directory as project root.
   ///
   /// @since  1.0.0, 18.10.2017
   ProjectRoot();

   /// Constructor, initialises the project root path with the given parameters.
   ///
   /// @param[in]  srcType
   ///    The type of initialisation to use for the project root.
   /// @param[in]  source
   ///    For some initialisation types, additional value (e.g. name of
   ///    environment variable).
   /// @since  1.0.0, 18.10.2017
   explicit ProjectRoot( ProjRootSrc srcType,
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
   return mProjectRoot;
} // ProjectRoot::dir


inline ProjectRoot::ProjRootSrc ProjectRoot::projectRootSrc()
{
   return mProjectRootSource;
} // ProjectRoot::projectRootSrc


} // namespace celma::appl


// =====  END OF project_root.hpp  =====

