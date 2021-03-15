
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
/// See documentation of class celma::prog_args::detail::CheckIsFile.


#pragma once


#include <filesystem>
#include <stdexcept>
#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks if a value contains the (path and) name of file.
///
/// @since  1.4.1, 02.03.2018
class CheckIsFile final : public ICheck
{
public:
   /// Constructor, sets the symbolic name in the base class.
   ///
   /// @since  1.32.0, 24.04.2019
   CheckIsFile();

   /// Default destructor is fine.
   ~CheckIsFile() override = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// file.
   ///
   /// @param[in]  val  The value to check in string format.
   /// @throw  std::invalid_argument if the specified file does not exist.
   /// @since  1.4.1, 02.03.2018
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.4.1, 02.03.2018
   std::string toString() const override;

}; // CheckIsFile


// inlined methods
// ===============


inline CheckIsFile::CheckIsFile():
   ICheck( "is file")
{
} // CheckIsFile::CheckIsFile


inline void CheckIsFile::checkValue( const std::string& val) const
{
   if (!std::filesystem::is_regular_file( val))
      throw std::invalid_argument( std::string( "'") + val
         + "' is not an existing file");
} // CheckIsFile::checkValue


inline std::string CheckIsFile::toString() const
{
   return std::string( "is a file");
} // CheckIsFile::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a is-file check more easily.
/// Usage:  addArgument( ...)->addCheck( isFile());
///
/// @return  The newly created CheckIsFile object.
/// @since  1.4.1, 02.03.2018
[[nodiscard]] inline detail::ICheck* isFile()
{
   return new detail::CheckIsFile();
} // isFile


} // namespace celma::prog_args


// =====  END OF check_is_file.hpp  =====

