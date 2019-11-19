
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::FormatLowercase.


#ifndef CELMA_PROG_ARGS_DETAIL_FORMAT_LOWERCASE_HPP
#define CELMA_PROG_ARGS_DETAIL_FORMAT_LOWERCASE_HPP


#include "celma/prog_args/detail/i_format.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Changes all the characters in the passed string to lowercase.
/// @since  0.2, 10.04.2016
class FormatLowercase: public IFormat
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
   virtual ~FormatLowercase() = default;

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


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_FORMAT_LOWERCASE_HPP


// =====  END OF format_lowercase.hpp  =====

