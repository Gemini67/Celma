
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
/// See documentation of class celma::prog_args::detail::CheckFunction.


#pragma once


#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks a value using the provided check function.
/// @since  x.y.z, 02.11.2021
class CheckFunction final : public ICheck
{
public:
   /// Type of the check function: Receives the value as string and returns
   /// \c true if the value is valid.
   using check_func_t = std::function<bool(const std::string&)>;

   /// Constructor.
   /// @param[in]  fun   The function to call to check a value.
   /// @param[in]  desc  Description of the function.
   /// @since  x.y.z, 02.11.2021
   CheckFunction( check_func_t fun, const std::string& desc) noexcept;

   /// Default destructor is fine.
   ~CheckFunction() override = default;

   /// Calls the check function, throws if it returns \c false.
   /// @param[in]  val  The value to check in string format.
   /// @throws  std::range_error when the check function returns \c false.
   /// @since  x.y.z, 02.11.2021
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  x.y.z, 02.11.2021
   std::string toString() const noexcept override;

private:
   /// Function to call to check a value.
   check_func_t       mCheckFunc;
   // Description of the function.
   const std::string  mDescription;

}; // CheckFunction


// inlined methods
// ===============


inline CheckFunction::CheckFunction( check_func_t fun, const std::string& desc)
   noexcept:
      ICheck( "check function"),
      mCheckFunc( fun),
      mDescription( desc)
{
} // CheckFunction::CheckFunction


inline void CheckFunction::checkValue( const std::string& val) const
   noexcept( false)
{
   if (!mCheckFunc( val))
      throw std::range_error( "Value " + val + " failed check '"
         + mDescription + "'");
} // CheckFunction::checkValue


inline std::string CheckFunction::toString() const noexcept
{
   std::ostringstream  oss;
   oss << "check function '" << mDescription << "'";
   return oss.str();
} // CheckFunction::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a check that uses a check-function.
/// Usage:  addArgument( ...)->addCheck( check_function( ...));
/// @param[in]  fun   Function object that will be called to check a value.
/// @param[in]  desc  Description of the function for usage.
/// @return  The newly created CheckFunction object.
/// @since  x.y.z, 02.11.2021
[[nodiscard]] inline detail::ICheck*
   check_function( detail::CheckFunction::check_func_t fun,
      const std::string& desc) noexcept
{
   return new detail::CheckFunction( fun, desc);
} // check_function


} // namespace celma::prog_args


// =====  END OF check_function.hpp  =====

