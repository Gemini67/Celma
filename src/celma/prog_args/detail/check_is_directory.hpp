
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckIsDirectory.


#pragma once


#include <filesystem>
#include <stdexcept>
#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks if a value contains the (path and) name of directory.
/// @since  1.4.1, 02.03.2018
class CheckIsDirectory final : public ICheck
{
public:
   /// Constructor, sets the symbolic name in the base class.
   ///
   /// @since  1.32.0, 24.04.2019
   CheckIsDirectory();

   /// Default destructor is fine.
   ~CheckIsDirectory() override = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// directory.
   /// @param[in]  val  The value to check in string format.
   /// @since  1.4.1, 02.03.2018
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  1.4.1, 02.03.2018
   std::string toString() const override;

}; // CheckIsDirectory


// inlined methods
// ===============


inline CheckIsDirectory::CheckIsDirectory():
   ICheck( "is directory")
{
} // CheckIsDirectory::CheckIsDirectory


inline void CheckIsDirectory::checkValue( const std::string& val) const
{
   if (!std::filesystem::is_directory( val))
      throw std::runtime_error( std::string( "'") + val
         + "' is not an existing directory");
} // CheckIsDirectory::checkValue


inline std::string CheckIsDirectory::toString() const
{
   return std::string( "is a directory");
} // CheckIsDirectory::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a is-directory check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( isDirectory());
/// @return  The newly created CheckIsDirectory object.
/// @since  1.4.1, 02.03.2018
[[nodiscard]] inline detail::ICheck* isDirectory()
{
   return new detail::CheckIsDirectory();
} // isDirectory


} // namespace celma::prog_args


// =====  END OF check_is_directory.hpp  =====

