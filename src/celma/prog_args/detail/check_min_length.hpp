
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::CheckMinLength.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_MIN_LENGTH_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_MIN_LENGTH_HPP


#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks that a given string value has a minimum length.
///
/// @since  1.23.0, 11.04.2019
class CheckMinLength : public ICheck
{
public:
   /// Constructor, stores the minimum length that will be checked,
   ///
   /// @param[in]  min_length  The minimum length to check against.
   /// @throws  "invalid argument" if the given length is 0.
   /// @since  1.23.0, 11.04.2019
   explicit CheckMinLength( std::string::size_type min_length) noexcept( false);

   /// Default destructor is fine.
   /// @since  1.23.0, 11.04.2019
   virtual ~CheckMinLength() = default;

   /// Checks if the value in \a val meets the "minimum length" requirement.
   ///
   /// @param[in]  val  The value to check.
   /// @throws "underflow error" if the given string is too short.
   /// @since  1.23.0, 11.04.2019
   virtual void checkValue( const std::string& val) const noexcept( false)
      override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.23.0, 11.04.2019
   virtual std::string toString() const override;

private:
   /// The minimum length to check against.
   const std::string::size_type  mMinLength;

}; // CheckMinLength


} // namespace detail


// helper function
// ===============


/// Helper function to create a minimum-length check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( minLength( ...));
///
/// @param[in]  min_length  The minimum length check against.
/// @return  The newly created CheckMinLength object.
/// @since  1.23.0, 11.04.2019
inline detail::ICheck* minLength( std::string::size_type min_length)
{
   return new detail::CheckMinLength( min_length);
} // minLength


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_MIN_LENGTH_HPP


// =====  END OF check_min_length.hpp  =====

