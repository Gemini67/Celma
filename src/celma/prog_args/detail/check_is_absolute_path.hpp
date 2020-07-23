
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
/// See documentation of class celma::prog_args::detail::CheckIsAbsolutePath.


#pragma once


#include <stdexcept>
#include "celma/common/file_info.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks if a value contains an absolute path.
/// @since  1.4.2, 12.04.2018
class CheckIsAbsolutePath final : public ICheck
{
public:
   /// Constructor, sets the symbolic name in the base class.
   ///
   /// @since  1.32.0, 24.04.2019
   CheckIsAbsolutePath();

   /// Default destructor is fine.
   ~CheckIsAbsolutePath() override = default;

   /// Checks if the value in \a val contains an absolute path.
   /// @param[in]  val  The value to check in string format.
   /// @since  1.4.2, 12.04.2018
   void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  1.4.2, 12.04.2018
   std::string toString() const override;

}; // CheckIsAbsolutePath


// inlined methods
// ===============


inline CheckIsAbsolutePath::CheckIsAbsolutePath():
   ICheck( "is absolute path")
{
} // CheckIsAbsolutePath::CheckIsAbsolutePath


inline void CheckIsAbsolutePath::checkValue( const std::string& val) const
{
   if (val[ 0] != '/')
      throw std::runtime_error( std::string( "'") + val
         + "' is not an absolute path");
} // CheckIsAbsolutePath::checkValue


inline std::string CheckIsAbsolutePath::toString() const
{
   return std::string( "is an absolute path");
} // CheckIsAbsolutePath::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create an is-absolute-path check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( isAbsolutePath());
/// @return  The newly created CheckIsAbsolutePath object.
/// @since  1.4.2, 12.04.2018
[[nodiscard]] inline detail::ICheck* isAbsolutePath()
{
   return new detail::CheckIsAbsolutePath();
} // isAbsolutePath


} // namespace celma::prog_args


// =====  END OF check_is_absolute_path.hpp  =====

