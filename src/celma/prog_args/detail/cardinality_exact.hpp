
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
/// See documentation of class celma::prog_args::detail::CardinalityExact.


#pragma once
#define CELMA_PROG_ARGS_DETAIL_CARDINALITY_EXACT_HPP


#include <string>
#include "celma/prog_args/detail/i_cardinality.hpp"


namespace celma::prog_args { namespace detail {


/// Checks cardinality exact, i.e. the argument must be used with exactly the
/// specified number of values:
/// - gotValue() throws when attempting to process more values than allowed.
/// - check() throws at the end-check when not enough values were passed.
///
/// @since  0.2, 10.04.2016
class CardinalityExact final : public ICardinality
{
public:
   /// Constructor.
   ///
   /// @param[in]  num_values  The number of calls/values that are expected for
   ///                         the corresponding argument.
   /// @since  0.2, 10.04.2016
   explicit CardinalityExact( int num_values);

   /// Virtual, empty destructor.
   ///
   /// @since  0.2, 10.04.2016
   ~CardinalityExact() override = default;

   /// Called by the framework when the argument was detected in the command
   /// line (actually may be without a value).
   ///
   /// @throw  when attempting to add too many values.
   /// @since  0.2, 10.04.2016
   void gotValue() noexcept( false) override;

   /// Called by the framework at the end of the command line processing.<br>
   /// Here we check that the exact number of values was processed, if any.
   ///
   /// @throw  runtime_error
   ///    if at least one but not all execpted values were passed.
   /// @since  0.2, 10.04.2016
   void check() noexcept( false) override;

   /// Returns the text description of the cardinality "exact".
   ///
   /// @return  String with the text description of the cardinality.
   /// @since  1.14.0, 02.10.2018
   std::string cardinalityStr() const override;

private:
   /// Number of calls/values expected for the corresponding argument.
   const int  mNumExpectedValues;

}; // CardinalityExact


} // namespace detail


// helper function
// ===============


/// Helper method to hide the class name from the library users.<br>
/// Use this function as parameter to TypedArgBase::setCardinality().
///
/// @param[in]  num_values  Number of values expected by the corresponding
///                         argument.
/// @return  The newly created object for checking exact cardinality.
/// @since  0.2, 10.04.2016
inline detail::ICardinality* cardinality_exact( int num_values)
{
   return new detail::CardinalityExact( num_values);
} // cardinality_exact


} // namespace celma::prog_args


// =====  END OF cardinality_exact.hpp  =====

