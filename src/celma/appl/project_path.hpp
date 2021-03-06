
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
/// @since  1.0.0, 11.01.2017
class ProjectPath
{
public:
   /// Constructor.
   /// @param[in]  subDir    The sub-directory of the project root path.
   /// @param[in]  filename  The name of the file.
   /// @param[in]  fileExt   The file extension/suffix.
   /// @since  1.0.0, 11.01.2017
   ProjectPath( const char* subDir, const char* filename,
                const char* fileExt) noexcept( false);

   /// Constructor.
   /// @param[in]  subDir    The sub-directory of the project root path.
   /// @param[in]  filename  The name of the file, maybe with suffix.
   /// @since  1.0.0, 11.01.2017
   ProjectPath( const char* subDir, const char* filename) noexcept( false);

   /// Constructor.
   /// @param[in]  filename  The (path and) name of the file, maybe with suffix.
   /// @since  1.0.0, 11.01.2017
   explicit ProjectPath( const char* filename) noexcept( false);

   ProjectPath( const ProjectPath&) = default;
   ~ProjectPath() = default;
   ProjectPath& operator =( const ProjectPath&) = default;

   /// Returns the absolute path and file name.
   /// @return  The complete, absolute path and file name.
   /// @since  1.0.0, 11.01.2017
   const std::string& str() const;

   /// Returns the absolute path and file name.
   /// @return  The complete, absolute path and file name.
   /// @since  1.0.0, 11.01.2017
   operator const std::string&() const;

   /// Returns the absolute path and file name as a C string.
   /// @return  The complete, absolute path and file name as a C string.
   /// @since  1.0.0, 11.01.2017
   const char* c_str() const;

   /// Returns the absolute path and file name as a C string.
   /// @return  The complete, absolute path and file name as a C string.
   /// @since  1.0.0, 11.01.2017
   operator const char*() const;

   /// Streams the absolute path and file name.
   /// @param[out]  os  The stream to write to.
   /// @param[in]   pp  The object to stream the path/filename of.
   /// @return  The stream as passed in \a os.
   /// @since  1.0.0, 11.01.2017
   friend std::ostream& operator <<( std::ostream& os, const ProjectPath& pp);

private:
   /// Builds the absolute path and file name with all components.
   /// @param[in]  subDir    The sub-directory of the project root dir, may
   ///                       be NULL.
   /// @param[in]  filename  The file name.
   /// @param[in]  fileExt   The file extension/suffix, may be NULL.
   /// @since  1.0.0, 11.01.2017
   void store( const char* subDir, const char* filename, const char* fileExt);

   /// The full path and file name as generated by the constructor.
   std::string  mFullPathFilename;

}; // ProjectPath


// inlined methods
// ===============


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

