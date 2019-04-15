
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckMinLength.


// module header file include
#include "celma/prog_args/detail/check_min_length.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// project includes
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the minimum length that will be checked,
///
/// @param[in]  min_length  The minimum length to check against.
/// @throws  "invalid argument" if the given length is 0.
/// @since  1.23.0, 11.04.2019
CheckMinLength::CheckMinLength( std::string::size_type min_length):
   mMinLength( min_length)
{

   if (min_length == 0)
      throw std::invalid_argument( "minimum length may not be 0");

} // CheckMinLength::CheckMinLength



/// Checks if the value in \a val meets the "minimum length" requirement.
///
/// @param[in]  val  The value to check.
/// @throws "underflow error" if the given string is too short.
/// @since  1.23.0, 11.04.2019
void CheckMinLength::checkValue( const std::string& val) const
{

   if (val.length() < mMinLength)
      throw std::underflow_error( "Value '" + val + "' is too short, should be "
         "at least " + format::toString( mMinLength) + " characters");

} // CheckMinLength::checkValue



/// Returns a text description of the check.
///
/// @return  A string with the text description of the check.
/// @since  1.23.0, 11.04.2019
std::string CheckMinLength::toString() const
{

   std::ostringstream  oss;


   oss << "Length >= " << mMinLength;

   return oss.str();
} // CheckMinLength::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF check_min_length.cpp  =====

