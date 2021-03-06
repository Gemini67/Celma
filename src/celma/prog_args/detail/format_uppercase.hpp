
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
/// See documentation of class celma::prog_args::detail::FormatUppercase.


#pragma once


#include "celma/prog_args/detail/i_format.hpp"


namespace celma::prog_args { namespace detail {


/// Changes all the characters in the passed string to uppercase.
/// @since  0.2, 10.04.2016
class FormatUppercase final : public IFormat
{
public:
   /// Default constructor.
   /// Needed to store the name of the formatter in the base class.
   ///
   /// @since  1.33.0, 05.11.2019
   FormatUppercase();

   /// Virtual, empty destructor.
   ///
   /// @since  1.23.0, 11.04.2019
   ~FormatUppercase() override = default;

   /// Converts the text in \a val to uppercase.
   ///
   /// @param[in,out]  val  The text to convert to uppercase.
   /// @since  0.2, 10.04.2016
   void formatValue( std::string& val) const override;

}; // FormatUppercase


} // namespace detail


// helper function
// ===============


/// Helper function to create a uppercase formatter more easily.<br>
/// Usage: addArgument( ...)->addFormat( uppercase());
///
/// @return  The newly created FormatUppercase object.
/// @since  0.2, 10.04.2016
[[nodiscard]] inline detail::IFormat* uppercase()
{
   return new detail::FormatUppercase();
} // end uppercase


} // namespace celma::prog_args


// =====  END OF format_uppercase.hpp  =====

