
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::FormatFunction.


#pragma once


#include <functional>
#include <string>
#include "celma/prog_args/detail/i_format.hpp"


namespace celma::prog_args { namespace detail {


/// Passes the value string to a function taht can apply any formatting.
///
/// @since  1.47.0, 21.11.2021
class FormatFunction final : public IFormat
{
public:
   /// Type of the check function: Receives the value as string and returns
   /// \c true if the value is valid.
   using format_func_t = std::function<void(std::string&)>;

   /// Constructor, stores the function to call to format the value.
   ///
   /// @param[in]  fun   The function to call to format a value.
   /// @param[in]  desc  Description of the function.
   /// @since  1.47.0, 21.11.2021
   FormatFunction( format_func_t fun, const std::string& desc) noexcept;

   /// Default destructor is fine.
   ~FormatFunction() override = default;

   /// Calls the format function.
   ///
   /// @param[in,out]  val  The value string to format.
   /// @since  1.47.0, 21.11.2021
   void formatValue( std::string& val) const override;

private:
   /// Function to call to format a value.
   format_func_t      mFormatFunc;
   // Description of the function.
   const std::string  mDescription;

}; // FormatFunction


} // namespace detail


// helper function
// ===============


/// Helper function to create a format function formatter more easily.
/// Usage: addArgument( ...)->addFormat( formatFunction( ...));
///
/// @param[in]  fun   Function object that will be called to format a value.
/// @param[in]  desc  Description of the function for usage.
/// @return  The newly created FormatFunction object.
/// @since  1.47.0, 21.11.2021
[[nodiscard]] inline detail::IFormat*
   formatFunction( detail::FormatFunction::format_func_t fun,
      const std::string& desc)
{
   return new detail::FormatFunction( fun, desc);
} // formatFunction


} // namespace celma::prog_args


// =====  END OF format_function.hpp  =====

