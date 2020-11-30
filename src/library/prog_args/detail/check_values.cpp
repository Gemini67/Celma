
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckValues.


// module header file include
#include "celma/prog_args/detail/check_values.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost Library includes
#include <boost/algorithm/string/predicate.hpp>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/format/to_string.hpp"


namespace celma::prog_args::detail {



/// Constructor.
///
/// @param[in]  value_list   The list of allowed values in string format.
/// @param[in]  ignore_case  Set if the value comparison should ignore lower/
///                          uppercase.
/// @since  1.42.0, 12.11.2020
///    (added parameter \a ignore_case)
/// @since  0.2, 10.04.2016
CheckValues::CheckValues( const std::string& valueList, bool ignore_case):
   ICheck( "values"),
   mValues(),
   mIgnoreCase( ignore_case)
{

   common::Tokenizer  tokenizer( valueList, ',');


   for (auto const& token : tokenizer)
   {
      mValues.insert( token);
   } // end for

   if (mValues.empty())
      throw std::invalid_argument( "No values found in value list");

} // CheckValues::CheckValues



/// Checks if the value in \a val exists in the set of allowed values.
/// @param[in]  val  The value to check in string format.
/// @since  0.2, 10.04.2016
void CheckValues::checkValue( const std::string& val) const
{

   if (mIgnoreCase)
   {
      for (auto const& v : mValues)
      {
         if (boost::iequals( val, v))
            return;
      } // end for
      throw std::out_of_range( "Value '" + val + "' is not in the list of allowed values");
   } // end if

   if (mValues.find( val)== mValues.end())
      throw std::out_of_range( "Value '" + val + "' is not in the list of allowed values");

} // CheckValues::checkValue



/// Returns a text description of the check.
/// @return  A string with the text description of the check.
/// @since  0.16.0, 12.08.2017
std::string CheckValues::toString() const
{

   std::ostringstream  oss;


   oss << "Value in ( " << format::toString( mValues.begin(), mValues.end()) << ")";

   return oss.str();
} // CheckValues::toString



} // namespace celma::prog_args::detail


// =====  END OF check_values.cpp  =====

