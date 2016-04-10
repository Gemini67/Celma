
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
/// See documentation of class celma::prog_args::detail::CardinalityMax.


// module header file include
#include "celma/prog_args/detail/cardinality_max.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  max_values  The maximum number of calls/values allowed for
///                         the corresponding argument.
/// @since  0.2, 10.04.2016
CardinalityMax::CardinalityMax( int max_values):
   ICardinality(),
   mMaxNumAcceptedValues( max_values)
{
} // end CardinalityMax::CardinalityMax



/// Called by the framework when the argument was detected in the command
/// line (actually may be without a value).
/// @throw  when attempting to add too many values.
/// @since  0.2, 10.04.2016
void CardinalityMax::gotValue()
{

   if ((mMaxNumAcceptedValues != -1) && (++mNumValues > mMaxNumAcceptedValues))
      throw runtime_error( "too many values");

} // end CardinalityMax::gotValue



/// Called by the framework at the end of the command line processing.
/// @throw  never.
/// @since  0.2, 10.04.2016
void CardinalityMax::check()
{
} // end CardinalityMax::check



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF cardinality_max.cpp  =========================

