
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
/// See documentation of class celma::prog_args::detail::FormatLowercase.


#pragma once


#include "celma/prog_args/detail/i_format.hpp"


namespace celma::prog_args { namespace detail {


/// Changes all the characters in the passed string to lowercase.
/// @since  0.2, 10.04.2016
class FormatLowercase final : public IFormat
{
public:
   /// Default constructor.
   /// Needed to store the name of the formatter in the base class.
   ///
   /// @since  1.33.0, 05.11.2019
   FormatLowercase();

   /// Virtual, empty destructor.
   ///
   /// @since  1.23.0, 11.04.2019
   ~FormatLowercase() override = default;

   /// Converts the text in \a val to lowercase.
   ///
   /// @param[in,out]  val  The text to convert to lowercase.
   /// @since  0.2, 10.04.2016
   void formatValue( std::string& val) const override;

}; // FormatLowercase


} // namespace detail


// helper function
// ===============


/// Helper function to create a lowercase formatter more easily.<br>
/// Usage:  addArgument()->addFormat( lowercase());
///
/// @return  The newly created FormatLowercase object.
/// @since  0.2, 10.04.2016
inline detail::IFormat* lowercase()
{
   return new detail::FormatLowercase();
} // lowercase


} // namespace celma::prog_args


// =====  END OF format_lowercase.hpp  =====

