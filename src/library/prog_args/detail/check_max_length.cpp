
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
/// See documentation of class celma::prog_args::detail::CheckMaxLength.


// module header file include
#include "celma/prog_args/detail/check_max_length.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// project includes
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the maximum length that will be checked,
///
/// @param[in]  min_length  The minimum length to check against.
/// @throws  "invalid argument" if the given length is 0.
/// @since  1.23.0, 12.04.2019
CheckMaxLength::CheckMaxLength( std::string::size_type max_length):
   mMaxLength( max_length)
{

   if (max_length == 0)
      throw std::invalid_argument( "maximum length may not be 0");

} // CheckMaxLength::CheckMaxLength



/// Checks if the value in \a val meets the "maximum length" requirement.
///
/// @param[in]  val  The value to check.
/// @throws "overflow error" if the given string is too long.
/// @since  1.23.0, 12.04.2019
void CheckMaxLength::checkValue( const std::string& val) const
{

   if (val.length() > mMaxLength)
      throw std::overflow_error( "Value '" + val + "' is too long, should be "
         "at most " + format::toString( mMaxLength) + " characters");

} // CheckMaxLength::checkValue



/// Returns a text description of the check.
///
/// @return  A string with the text description of the check.
/// @since  1.23.0, 12.04.2019
std::string CheckMaxLength::toString() const
{

   std::ostringstream  oss;


   oss << "Length <= " << mMaxLength;

   return oss.str();
} // CheckMaxLength::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF check_max_length.cpp  =====

