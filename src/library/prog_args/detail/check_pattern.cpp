
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckPattern.


// module header file include
#include "celma/prog_args/detail/check_pattern.hpp"


// C++ Standard Library includes
#include <sstream>


// project includes
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
///
/// @param[in]  pattern_str
///    The pattern/regular expression to use for the check.
/// @since  x.y.z, 27.11.2018
CheckPattern::CheckPattern( const std::string& pattern_str):
   mRegExStr( pattern_str),
   mRegEx( pattern_str)
{
} // CheckPattern::CheckPattern



/// Constructor that takes a regular expression.
///
/// @param[in]  reg_ex  The regular expression to use for the check.
/// @since  x.y.z, 27.11.2018
CheckPattern::CheckPattern( const std::regex& reg_ex):
   mRegExStr( "unknown"),
   mRegEx( reg_ex)
{
} // CheckPattern::CheckPattern



/// Checks if the value in \a val matches the pattern given in the
/// constructor.
///
/// @param[in]  val  The value to check in string format.
/// @since  x.y.z, 27.11.2018
void CheckPattern::checkValue( const std::string& val) const
{

   std::smatch  base_match;

   if (!std::regex_match( val, base_match, mRegEx))
      throw std::out_of_range( "value does not match pattern");
} // CheckPattern::checkValue



/// Returns a text description of the check.
///
/// @return  A string with the text description of the check.
/// @since  x.y.z, 27.11.2018
std::string CheckPattern::toString() const
{

   std::ostringstream  oss;


   oss << "Value matches '" << mRegExStr << "'";

   return oss.str();
} // CheckPattern::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF check_pattern.cpp  =====

