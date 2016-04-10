
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


#ifndef CELMA_PROG_ARGS_DETAIL_CARDINALITY_EXACT_HPP
#define CELMA_PROG_ARGS_DETAIL_CARDINALITY_EXACT_HPP


#include "celma/prog_args/detail/i_cardinality.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks cardinality exact, i.e. the argument must be used with exactly the
/// specified number of values:
/// - gotValue() throws when attempting to process more values than allowed.
/// - check() throws at the end-check when not enough values were passed.
///
/// @since  0.2, 10.04.2016
class CardinalityExact: public ICardinality
{
public:
   /// Constructor.
   /// @param[in]  num_values  The number of calls/values that are expected for
   ///                         the corresponding argument.
   /// @since  0.2, 10.04.2016
   CardinalityExact( int num_values);

   /// Virtual, empty destructor.
   /// @since  0.2, 10.04.2016
   virtual ~CardinalityExact() { }

   /// Called by the framework when the argument was detected in the command
   /// line (actually may be without a value).
   /// @throw  when attempting to add too many values.
   /// @since  0.2, 10.04.2016
   virtual void gotValue();

   /// Called by the framework at the end of the command line processing.
   /// @throw  if not all execpted values were passed.
   /// @since  0.2, 10.04.2016
   virtual void check();

private:
   /// Number of calls/values expected for the corresponding argument.
   const int  mNumExpectedValues;

}; // CardinalityExact


} // namespace detail


// helper function
// ===============


/// Helper method to hide the class name from the library users.<br>
/// Use this function as parameter to TypedArgBase::setCardinality().
/// @param[in]  num_values  Number of values expected by the corresponding
///                         argument.
/// @return  The newly created object for checking exact cardinality.
/// @since  0.2, 10.04.2016
inline detail::ICardinality* cardinality_exact( int num_values)
{
   return new detail::CardinalityExact( num_values);
} // end cardinality_exact


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CARDINALITY_EXACT_HPP


// =========================  END OF cardinality_exact.hpp  =========================

