
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckPattern.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_PATTERN_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_PATTERN_HPP


#include <regex>
#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks a value if it matches a set of specified, allowed values.
///
/// @since  1.19.0, 27.11.2018
class CheckPattern: public ICheck
{
public:
   /// Constructor that takes a string with the regular expression.
   ///
   /// @param[in]  pattern_str
   ///    The pattern/regular expression to use for the check.
   /// @since  1.19.0, 27.11.2018
   explicit CheckPattern( const std::string& pattern_str) noexcept( false);

   /// Constructor that takes a regular expression.
   ///
   /// @param[in]  reg_ex  The regular expression to use for the check.
   /// @since  1.19.0, 27.11.2018
   explicit CheckPattern( const std::regex& reg_ex);

   /// Default destructor is fine.
   ~CheckPattern() override = default;

   /// Checks if the value in \a val matches the pattern given in the
   /// constructor.
   ///
   /// @param[in]  val  The value to check in string format.
   /// @since  1.19.0, 27.11.2018
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.19.0, 27.11.2018
   std::string toString() const override;

private:
   /// The string with the regular expression, if known.
   const std::string  mRegExStr;
   /// The regular expression used for the check.
   const std::regex   mRegEx;

}; // CheckPattern


} // namespace detail


// helper function
// ===============


/// Helper function to create a pattern check more easily: Simply call this
/// function with the check pattern string as parameter to
/// celma::prog_args::TypedArgBase::addCheck().
///
/// @param[in]  pattern_str  The regular expression pattern string.
/// @return  The newly created CheckPattern object.
/// @since  1.19.0, 27.11.2018
inline detail::ICheck* pattern( const std::string& pattern_str)
{
   return new detail::CheckPattern( pattern_str);
} // pattern


/// Helper function to create a pattern check more easily: Simply call this
/// function with the regular expression as parameter to
/// celma::prog_args::TypedArgBase::addCheck().
///
/// @param[in]  reg_ex  The regular expression.
/// @return  The newly created CheckPattern object.
/// @since  1.19.0, 27.11.2018
inline detail::ICheck* pattern( const std::regex& reg_ex)
{
   return new detail::CheckPattern( reg_ex);
} // pattern


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_PATTERN_HPP


// =====  END OF check_pattern.hpp  =====

