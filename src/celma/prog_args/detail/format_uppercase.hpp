
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
/// See documentation of class celma::prog_args::detail::FormatUppercase.


#ifndef CELMA_PROG_ARGS_DETAIL_FORMAT_UPPERCASE_HPP
#define CELMA_PROG_ARGS_DETAIL_FORMAT_UPPERCASE_HPP


#include "celma/prog_args/detail/i_format.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Changes all the characters in the passed string to uppercase.
/// @since  0.2, 10.04.2016
class FormatUppercase: public IFormat
{
public:
   /// Virtual, empty destructor.
   ///
   /// @since  x.y.z, 11.04.2019
   virtual ~FormatUppercase() = default;

   /// Converts the text in \a val to uppercase.
   ///
   /// @param[in,out]  val  The text to convert to uppercase.
   /// @since  0.2, 10.04.2016
   virtual void formatValue( std::string& val) const override;

}; // FormatUppercase


} // namespace detail


// helper function
// ===============


/// Helper function to create a uppercase formatter more easily.<br>
/// Usage: addArgument( ...)->addFormat( uppercase());
///
/// @return  The newly created FormatUppercase object.
/// @since  0.2, 10.04.2016
inline detail::IFormat* uppercase()
{
   return new detail::FormatUppercase();
} // end uppercase


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_FORMAT_UPPERCASE_HPP


// =====  END OF format_uppercase.hpp  =====

