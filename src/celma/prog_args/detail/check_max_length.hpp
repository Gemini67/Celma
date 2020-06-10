
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::CheckMaxLength.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_MAX_LENGTH_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_MAX_LENGTH_HPP


#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks that a given string value has a maximum length.
///
/// @since  1.23.0, 12.04.2019
class CheckMaxLength : public ICheck
{
public:
   /// Constructor, stores the maximum length that will be checked.
   ///
   /// @param[in]  min_length  The maximum length to check against.
   /// @throw  std::invalid_argument if the given length is 0.
   /// @since  1.23.0, 12.04.2019
   explicit CheckMaxLength( std::string::size_type min_length) noexcept( false);

   /// Default destructor is fine.
   /// @since  1.23.0, 12.04.2019
   ~CheckMaxLength() override = default;

   /// Checks if the value in \a val meets the "maximum length" requirement.
   ///
   /// @param[in]  val  The value to check.
   /// @throw  std::overflow_error if the given string is too long.
   /// @since  1.23.0, 12.04.2019
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.23.0, 12.04.2019
   std::string toString() const override;

private:
   /// The maximum length to check against.
   const std::string::size_type  mMaxLength;

}; // CheckMaxLength


} // namespace detail


// helper function
// ===============


/// Helper function to create a maximum-length check more easily.
/// Usage:  addArgument( ...)->addCheck( maxLength( ...));
///
/// @param[in]  max_length  The maximum length check against.
/// @return  The newly created CheckMaxLength object.
/// @since  1.23.0, 12.04.2019
inline detail::ICheck* maxLength( std::string::size_type max_length)
{
   return new detail::CheckMaxLength( max_length);
} // maxLength


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_MAX_LENGTH_HPP


// =====  END OF check_max_length.hpp  =====

