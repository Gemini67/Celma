
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
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


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  valueList  The list of allowed values in string format.
/// @since  0.2, 10.04.2016
CheckValues::CheckValues( const string& valueList):
   mValues()
{

   common::Tokenizer  tok( valueList, ',');


   for (auto ti : tok)
   {
      mValues.insert( ti);
   } // end for

   if (mValues.empty())
      throw invalid_argument( "No values found in value list");

} // end CheckValues::CheckValues



/// Checks if the value in \a val exists in the set of allowed values.
/// @param[in]  val  The value to check in string format.
/// @since  0.2, 10.04.2016
void CheckValues::checkValue( const string& val) const
{

   if (mValues.find( val)== mValues.end())
      throw range_error( "Value '" + val + "' is not in the list of allowed values");

} // end CheckValues<T>::checkValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF check_values.cpp  =========================

