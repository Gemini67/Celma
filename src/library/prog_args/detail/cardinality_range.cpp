
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
/// See documentation of class celma::prog_args::detail::CardinalityRange.


// module header file include
#include "celma/prog_args/detail/cardinality_range.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {


/// Constructor.
/// @param[in]  min_num_values  Minimum number of calls/values for the
///                             corresponding argument.
/// @param[in]  max_num_values  Maximum number of calls/values for the
///                             corresponding argument.
/// @since  0.2, 10.04.2016
CardinalityRange::CardinalityRange( int min_num_values, int max_num_values):
   mMinNumValues( min_num_values),
   mMaxNumValues( max_num_values)
{
} // end CardinalityRange::CardinalityRange



/// Called by the framework when the argument was detected in the command
/// line (actually may be without a value).
/// @throw  when attempting to add too many values.
/// @since  0.2, 10.04.2016
void CardinalityRange::gotValue()
{

   if ((mMaxNumValues != -1) && (++mNumValues > mMaxNumValues))
      throw runtime_error( "too many values");

} // end CardinalityRange::gotValue



/// Called by the framework at the end of the command line processing.
/// @throw  if the minimum of calls/values was not reached.
/// @since  0.2, 10.04.2016
void CardinalityRange::check()
{

   if (mNumValues < mMinNumValues)
      throw runtime_error( "not all expected values");

} // end CardinalityRange::check



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF cardinality_range.cpp  =========================

