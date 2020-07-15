
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class
/// celma::prog_args::detail::CheckParentDirectoryExists.


#pragma once


#include <cstring>
#include <libgen.h>
#include <memory>
#include <stdexcept>
#include <string>
#include "celma/common/file_info.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks if the parent directory of the given value/path exists.
///
/// @since  1.9.0, 04.08.2018
class CheckParentDirectoryExists final : public ICheck
{
public:
   /// Constructor, sets the symbolic name in the base class.
   ///
   /// @since  1.32.0, 24.04.2019
   CheckParentDirectoryExists();

   /// Default destructor is fine.
   ~CheckParentDirectoryExists() override = default;

   /// Checks if parent directory of the path in the value \a val exists.
   ///
   /// @param[in]  val  The value to check in string format.
   /// @since  1.9.0, 04.08.2018
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.9.0, 04.08.2018
   std::string toString() const override;

}; // CheckParentDirectoryExists


// inlined methods
// ===============


inline CheckParentDirectoryExists::CheckParentDirectoryExists():
   ICheck( "parent directory exists")
{
} // CheckParentDirectoryExists::CheckParentDirectoryExists


inline void CheckParentDirectoryExists::checkValue( const std::string& val) const
{
   // cannot use FileInfo here, since the file may not exist
   std::unique_ptr< char[]>  copy( new char[ val.length()]);
   ::strcpy( copy.get(), val.c_str());

   auto const  parentDir( ::dirname( copy.get()));

   if (!common::fileInfo( parentDir).isDirectory())
      throw std::runtime_error( std::string( "'") + parentDir
         + "' is not an existing directory");
} // CheckParentDirectoryExists::checkValue


inline std::string CheckParentDirectoryExists::toString() const
{
   return std::string( "parent directory exists");
} // CheckParentDirectoryExists::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a parent-directory-exists check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( parentDirectory());
///
/// @return  The newly created CheckParentDirectoryExists object.
/// @since  1.9.0, 04.08.2018
inline detail::ICheck* parentDirectoryExists()
{
   return new detail::CheckParentDirectoryExists();
} // parentDirectoryExists


} // namespace celma::prog_args


// =====  END OF check_parent_directory_exists.hpp  =====

