
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
/// See documentation of class celma::prog_args::detail::CardinalityExact.


// module header file include
#include "celma/prog_args/detail/cardinality_exact.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  num_values  The number of calls/values that are expected for
///                         the corresponding argument.
/// @since  0.2, 10.04.2016
CardinalityExact::CardinalityExact( int num_values):
   ICardinality(),
   mNumExpectedValues( num_values)
{
} // end CardinalityExact::CardinalityExact



/// Called by the framework when the argument was detected in the command
/// line (actually may be without a value).
/// @throw  when attempting to add too many values.
/// @since  0.2, 10.04.2016
void CardinalityExact::gotValue()
{

   if (++mNumValues > mNumExpectedValues)
      throw runtime_error( "too many values");

} // end CardinalityExact::gotValue



/// Called by the framework at the end of the command line processing.
/// @throw  if not all execpted values were passed.
/// @since  0.2, 10.04.2016
void CardinalityExact::check()
{

   if (mNumValues != mNumExpectedValues)
      throw runtime_error( "not all expected values");

} // end CardinalityExact::check



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF cardinality_exact.cpp  =========================

