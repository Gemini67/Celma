
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::FileFuncsBase.


#pragma once


#include <string>


namespace celma::common::detail {


/// Base class for modules that implement file functions.
///
/// @since  1.26.0, 08.03.2018
///    (added mkdir)
/// @since  1.4.0, 20.02.2018
class FileFuncsBase
{
public:
   /// Empty, virtual destructor for base class.
   ///
   /// @since  1.4.0, 20.02.2018
   virtual ~FileFuncsBase() = default;

   /// Gets called when a file should be renamed.
   ///
   /// @param[in]  dest
   ///     New (path and) name for the file.
   /// @param[in]  src
   ///    (Path and) Name of the existing file that should be renamed.
   /// @returns  Result of the %rename operation.
   /// @since  1.4.0, 20.02.2018
   virtual int rename( const std::string& dest, const std::string& src) = 0;

   /// Gets called when a %file should be removed.
   ///
   /// @param[in]  file  (Path and) Name of the %file to delete.
   /// @returns  Result code of the %remove operation.
   /// @since  1.4.0, 28.02.2018
   virtual int remove( const std::string& file) = 0;

   /// Gets called when a directory should be created.
   ///
   /// @param[in]  dir_name
   ///    (Path and) Name of the directory to create.
   /// @param[in]  mode
   ///    Permissions to create the directory with.
   /// @returns  Result code of the %mkdir operation.
   /// @since  1.26.0, 08.03.2018
   virtual int mkdir( const std::string& dir_name, int mode) = 0;

}; // FileFuncsBase


} // namespace celma::common::detail


// =====  END OF file_funcs_base.hpp  =====

