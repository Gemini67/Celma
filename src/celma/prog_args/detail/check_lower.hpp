
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
/// See documentation of template celma::prog_args::detail::CheckLower.


#pragma once


#include <stdexcept>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks a value if it is greater-than or equal to a lower limit.
/// @tparam  T  The native type of the limit to check.
/// @since  0.2, 10.04.2016
template< typename T> class CheckLower final : public ICheck
{
public:
   /// Constructor.
   /// @param[in]  value  The lower limit to check against.
   /// @since  0.2, 10.04.2016
   explicit CheckLower( T value);

   /// Default destructor is fine.
   ~CheckLower() override = default;

   /// Checks if the value in \a val is greater-than or equal to the stored
   /// limit.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   std::string toString() const override;

private:
   /// The lower limit to check against.
   const T  mCheckValue;

}; // CheckLower< T>


// inlined methods
// ===============


template< typename T> CheckLower< T>::CheckLower( T value):
   ICheck( "lower"),
   mCheckValue( value)
{
} // CheckLower< T>::CheckLower


template< typename T> void CheckLower< T>::checkValue( const std::string& val) const
{
   T  native = boost::lexical_cast< T>( val);
   if (native < mCheckValue)
      throw std::underflow_error( "Value " + val + " is below limit "
         + boost::lexical_cast< std::string>( mCheckValue));
} // CheckLower< T>::checkValue


template< typename T> std::string CheckLower< T>::toString() const
{
   std::ostringstream  oss;
   oss << "Value >= " << mCheckValue;
   return oss.str();
} // CheckLower< T>::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a lower-limit check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( lower( ...));
/// @param[in]  value  The value to check against.
/// @return  The newly created CheckLower object.
/// @since  0.2, 10.04.2016
template< typename T> [[nodiscard]] detail::ICheck* lower( T value)
{
   return new detail::CheckLower< T>( value);
} // lower


} // namespace celma::prog_args


// =====  END OF check_lower.hpp  =====

