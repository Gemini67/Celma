
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckValues.


// module header file include
#include "celma/prog_args/detail/check_values.hpp"


// project ncludes
#include "celma/common/tokenizer.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  valueList  The list of allowed values in string format.
/// @since  0.2, 10.04.2016
CheckValues::CheckValues( const std::string& valueList):
   mValues()
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

   if (mValues.find( val)== mValues.end())
      throw std::range_error( "Value '" + val + "' is not in the list of allowed values");

} // CheckValues<T>::checkValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF check_values.cpp  =========================

