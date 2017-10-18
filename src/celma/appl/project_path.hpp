
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
/// See documentation of class celma::appl::ProjectPath.


#ifndef CELMA_APPL_PROJECT_PATH_HPP
#define CELMA_APPL_PROJECT_PATH_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace appl {


/// Helper class to create a file path for a project specific file.<br>
/// The aim is to create absolute path names. The constructors always prepend
/// the project root directory, which can either be set by the application
/// using the setProjectRoot() method, otherwise it is set internally to $HOME.
/// @since  x.y.z, 11.01.2017
class ProjectPath
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
   /// If this method is not called explicitly, it is called by the first used
   /// constructor with \a srcType set to ProjRootSrc::home.
   /// @param[in]  srcType  Base to use to determine the root of the project.
   /// @param[in]  source   If \a srcType ProjRootSrc::env or ProjRootSrc::bin
   ///                      are used, the corresponding value (name of the
   ///                      environment variable or the program start path,
   ///                      respectively) must be passed here.
   /// @since  x.y.z, 11.01.2017
   static void setProjectRoot( ProjRootSrc srcType,
                               const char* source = nullptr) noexcept( false);

   /// Returns the project root dir.
   /// @return  The path set for the project root directory.
   /// @since  x.y.z, 11.01.2017
   static const std::string& projectRoot();

   /// Returns the type of the source that was used to determine the project
   /// root.
   /// @return  Source type used for setting the project root.
   /// @since  x.y.z, 11.01.2017
   static ProjRootSrc projectRootSrc();

   /// Returns if the specified file is beneath the project root.
   /// @param[in]  path_file_name  The absolute path and file name to check.
   /// @return  \c true if the specified file is beneath the project root.
   /// @since  x.y.z, 11.01.2017
   static bool isOnProject( const std::string& path_file_name) noexcept( false);

   /// Constructor.
   /// @param[in]  subDir    The sub-directory of the project root path.
   /// @param[in]  filename  The name of the file.
   /// @param[in]  fileExt   The file extension/suffix.
   /// @since  x.y.z, 11.01.2017
   ProjectPath( const char* subDir, const char* filename,
                const char* fileExt) noexcept( false);

   /// Constructor.
   /// @param[in]  subDir    The sub-directory of the project root path.
   /// @param[in]  filename  The name of the file, maybe with suffix.
   /// @since  x.y.z, 11.01.2017
   ProjectPath( const char* subDir, const char* filename) noexcept( false);

   /// Constructor.
   /// @param[in]  filename  The (path and) name of the file, maybe with suffix.
   /// @since  x.y.z, 11.01.2017
   explicit ProjectPath( const char* filename) noexcept( false);

   ProjectPath( const ProjectPath&) = default;
   ~ProjectPath() = default;
   ProjectPath& operator =( const ProjectPath&) = default;

   /// Returns the absolute path and file name.
   /// @return  The complete, absolute path and file name.
   /// @since  x.y.z, 11.01.2017
   const std::string& str() const;

   /// Returns the absolute path and file name.
   /// @return  The complete, absolute path and file name.
   /// @since  x.y.z, 11.01.2017
   operator const std::string&() const;

   /// Returns the absolute path and file name as a C string.
   /// @return  The complete, absolute path and file name as a C string.
   /// @since  x.y.z, 11.01.2017
   const char* c_str() const;

   /// Returns the absolute path and file name as a C string.
   /// @return  The complete, absolute path and file name as a C string.
   /// @since  x.y.z, 11.01.2017
   operator const char*() const;

   /// Streams the absolute path and file name.
   /// @param[out]  os  The stream to write to.
   /// @param[in]   pp  The object to stream the path/filename of.
   /// @return  The stream as passed in \a os.
   /// @since  x.y.z, 11.01.2017
   friend std::ostream& operator <<( std::ostream& os, const ProjectPath& pp);

private:
   /// The project root path, same for all instances of this class (only one
   /// project for one process).
   static std::string  mProjectRoot;
   /// The type of the source used to set the project root.
   static ProjRootSrc  mProjectRootSource;

   /// Builds the absolute path and file name with all components.
   /// @param[in]  subDir    The sub-directory of the project root dir, may
   ///                       be NULL.
   /// @param[in]  filename  The file name.
   /// @param[in]  fileExt   The file extension/suffix, may be NULL.
   /// @since  x.y.z, 11.01.2017
   void store( const char* subDir, const char* filename, const char* fileExt);

   /// The full path and file name as generated by the constructor.
   std::string  mFullPathFilename;

}; // ProjectPath


// inlined methods
// ===============


inline const std::string& ProjectPath::projectRoot()
{
   if (mProjectRoot.empty())
      setProjectRoot( ProjRootSrc::home);
   return mProjectRoot;
} // ProjectPath::projectRoot


inline ProjectPath::ProjRootSrc ProjectPath::projectRootSrc()
{
   return mProjectRootSource;
} // ProjectPath::projectRootSrc


inline const std::string& ProjectPath::str() const
{
   return mFullPathFilename;
} // ProjectPath::str


inline ProjectPath::operator const std::string&() const
{
   return mFullPathFilename;
} // ProjectPath::operator const std::string&


inline const char* ProjectPath::c_str() const
{
   return mFullPathFilename.c_str();
} // ProjectPath::c_str


inline ProjectPath::operator const char*() const
{
   return mFullPathFilename.c_str();
} // ProjectPath::operator const char*


} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_PROJECT_PATH_HPP


// =========================  END OF project_path.hpp  =========================

