
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckFileSuffix.


#pragma once


#include <stdexcept>
#include <string>
#include "celma/common/string_util.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks if a value contains a file name with a specific suffix.
/// @since  1.38.0, 06.07.2020
class CheckFileSuffix final : public ICheck
{
public:
   /// Constructor, stores the suffix to check and sets the symbolic name in the
   /// base class.
   ///
   /// @param[in]  suffix  Suffix to check the file name(s) for.
   /// @throw  std::invalid_argument if the suffix string is empty.
   /// @since  1.38.0, 06.07.2020
   CheckFileSuffix( const std::string& suffix) noexcept( false);

   /// Default destructor is fine.
   ~CheckFileSuffix() override = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// file.
   ///
   /// @param[in]  val  Value to check in string format.
   /// @throws
   ///    std::runtime_error if the given values does not contain the suffix.
   /// @since  1.38.0, 06.07.2020
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.38.0, 06.07.2020
   [[nodiscard]] std::string toString() const override;

private:
   /// The suffix to check.
   std::string  mSuffix;

}; // CheckFileSuffix


// inlined methods
// ===============


inline CheckFileSuffix::CheckFileSuffix( const std::string& suffix):
   ICheck( "is file"),
   mSuffix( suffix)
{

   if (mSuffix.empty())
      throw std::invalid_argument( "file suffix should not be empty");
   if (mSuffix == ".")
      throw std::invalid_argument( "file suffix must contain at least one other"
         " character than a dot");

   if (mSuffix[ 0] != '.')
      mSuffix.insert( 0, ".");

} // CheckFileSuffix::CheckFileSuffix


inline void CheckFileSuffix::checkValue( const std::string& val) const
{
   if (!val.ends_with( mSuffix))
      throw std::invalid_argument( "value '" + val + "' does not end with '"
         + mSuffix + "'");
} // CheckFileSuffix::checkValue


inline std::string CheckFileSuffix::toString() const
{
   return std::string( "check file suffix '") + mSuffix + "'";
} // CheckFileSuffix::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a file-suffix check more easily.
/// Usage:  addArgument( ...)->addCheck( fileSuffix( "txt"));
///
/// @return  Newly created CheckFileSuffix object.
/// @since  1.38.0, 06.07.2020
[[nodiscard]] inline detail::ICheck* fileSuffix( const std::string& suffix)
{
   return new detail::CheckFileSuffix( suffix);
} // fileSuffix


} // namespace celma::prog_args


// =====  END OF check_file_suffix.hpp  =====

