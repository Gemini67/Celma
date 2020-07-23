
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


#pragma once


#include <string>
#include <set>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks a value if it matches a set of specified, allowed values.
///
/// @since  0.2, 10.04.2016
class CheckValues final : public ICheck
{
public:
   /// Constructor.
   /// @param[in]  valueList  The list of allowed values in string format.
   /// @since  0.2, 10.04.2016
   explicit CheckValues( const std::string& valueList) noexcept( false);

   /// Default destructor is fine.
   ~CheckValues() override = default;

   /// Checks if the value in \a val exists in the set of allowed values.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   std::string toString() const override;

private:
   /// Storage type for the values.
   using StringSet = std::set< std::string>;

   /// The allowed values.
   StringSet  mValues;

}; // CheckValues


} // namespace detail


// helper function
// ===============


/// Helper function to create a lower-limit check more easily: Simply call this
/// function with the check-value as parameter to TypedArgBase::addCheck().
/// @param[in]  valueList  The value-list to check against.
/// @return  The newly created CheckValues object.
/// @since  0.2, 10.04.2016
[[nodiscard]] inline detail::ICheck* values( const std::string& valueList)
{
   return new detail::CheckValues( valueList);
} // end values


} // namespace celma::prog_args


// =====  END OF check_values.hpp  =====

