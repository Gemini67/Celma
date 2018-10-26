
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CardinalityMax.


#ifndef CELMA_PROG_ARGS_DETAIL_CARDINALITY_MAX_HPP
#define CELMA_PROG_ARGS_DETAIL_CARDINALITY_MAX_HPP


#include <string>
#include "celma/prog_args/detail/i_cardinality.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks cardinality for a maximum of values:
/// - gotValue() throws when attempting to process more values than allowed.
/// - check() never throws.
///
/// @since  0.2, 10.04.2016
class CardinalityMax: public ICardinality
{
public:
   /// Constructor.
   ///
   /// @param[in]  max_values  The maximum number of calls/values allowed for
   ///                         the corresponding argument.
   /// @since  0.2, 10.04.2016
   CardinalityMax( int max_values);

   /// Empty, virtual destructor.
   ///
   /// @since  0.2, 10.04.2016
   virtual ~CardinalityMax() = default;

   /// Called by the framework when the argument was detected in the command
   /// line (actually may be without a value).
   ///
   /// @throw  when attempting to add too many values.
   /// @since  0.2, 10.04.2016
   virtual void gotValue() noexcept( false) override;

   /// Called by the framework at the end of the command line processing.
   ///
   /// @throw  never.
   /// @since  0.2, 10.04.2016
   virtual void check() override;

   /// Returns the text description of the cardinality "maximum".
   ///
   /// @return  String with the text description of the cardinality.
   /// @since  1.14.0, 02.10.2018
   virtual std::string cardinalityStr() const override;

private:
   /// Maximum number of calls/values accepted for the corresponding argument.
   const int  mMaxNumAcceptedValues;

}; // CardinalityMax


} // namespace detail


// helper function
// ===============


/// Helper method to hide the class name from the library users.<br>
/// Use this function as parameter to TypedArgBase::setCardinality().
///
/// @param[in]  max_calls  Maximum number of calls/values for the corresponding
///                        argument.
/// @return  The newly created object for checking maximum cardinality.
/// @since  0.2, 10.04.2016
inline detail::ICardinality* cardinality_max( int max_calls)
{
   return new detail::CardinalityMax( max_calls);
} // cardinality_max


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CARDINALITY_MAX_HPP


// =====  END OF cardinality_max.hpp  =====

