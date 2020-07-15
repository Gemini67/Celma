
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
/// See documentation of class celma::prog_args::detail::CardinalityRange.


#pragma once


#include <string>
#include "celma/prog_args/detail/i_cardinality.hpp"


namespace celma::prog_args { namespace detail {


/// Checks cardinality for a range of calls/values:
/// - gotValue() throws when attempting to process more values than allowed.
/// - check() throws if the specified minimum of calls/values was not reached.
///
/// @since  0.2, 10.04.2016
class CardinalityRange final : public ICardinality
{
public:
   /// Constructor.
   ///
   /// @param[in]  min_num_values  Minimum number of calls/values for the
   ///                             corresponding argument.
   /// @param[in]  max_num_values  Maximum number of calls/values for the
   ///                             corresponding argument.
   /// @since  0.2, 10.04.2016
   CardinalityRange( int min_num_values, int max_num_values);

   /// Empty, virtual destructor.
   ///
   /// @since  0.2, 10.04.2016
   ~CardinalityRange() override = default;

   /// Called by the framework when the argument was detected in the command
   /// line (actually may be without a value).
   ///
   /// @throw  when attempting to add too many values.
   /// @since  0.2, 10.04.2016
   void gotValue() noexcept( false) override;

   /// Called by the framework at the end of the command line processing.
   ///
   /// @throw  if the minimum of calls/values was not reached.
   /// @since  0.2, 10.04.2016
   void check() noexcept( false) override;

   /// Returns the text description of the cardinality "range".
   ///
   /// @return  String with the text description of the cardinality.
   /// @since  1.14.0, 02.10.2018
   std::string cardinalityStr() const override;

private:
   /// Minimum number of calls/values for the corresponding argument.
   const int  mMinNumValues;
   /// Maximum number of calls/values for the corresponding argument.
   const int  mMaxNumValues;

}; // CardinalityRange


} // namespace detail


// helper function
// ===============


/// Helper method to hide the class name from the library users.<br>
/// Use this function as parameter to TypedArgBase::setCardinality().
///
/// @param[in]  min_num_values  Minimum number of calls/values for the
///                             corresponding argument.
/// @param[in]  max_num_values  Maximum number of calls/values for the
///                             corresponding argument.
/// @return  The newly created object for checking maximum cardinality.
/// @since  0.2, 10.04.2016
inline detail::ICardinality* cardinality_range( int min_num_values,
                                                int max_num_values)
{
   return new detail::CardinalityRange( min_num_values, max_num_values);
} // cardinality_range


} // namespace celma::prog_args


// =====  END OF cardinality_range.hpp  =====

