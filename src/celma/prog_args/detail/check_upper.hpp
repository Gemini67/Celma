
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::CheckUpper.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_UPPER_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_UPPER_HPP


#include <stdexcept>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks a value if it is less-than an upper limit.
/// @tparam  T  The native type of the limit to check.
/// @since  0.2, 10.04.2016
template< typename T> class CheckUpper : public ICheck
{
public:
   /// Constructor.
   /// @param[in]  value  The upper limit to check against.
   /// @since  0.2, 10.04.2016
   explicit CheckUpper( T value);

   virtual ~CheckUpper() = default;

   /// Checks if the value in \a val is less-than the stored limit.
   /// @param[in]  val    The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   virtual std::string toString() const override;

private:
   /// The upper limit to check against.
   const T  mCheckValue;

}; // CheckUpper< T>


// inlined methods
// ===============


template< typename T> CheckUpper< T>::CheckUpper( T value):
   mCheckValue( value)
{
} // CheckUpper< T>::CheckUpper


template< typename T> void CheckUpper< T>::checkValue( const std::string& val) const
{
   T  native = boost::lexical_cast< T>( val);
   if (native >= mCheckValue)
      throw std::overflow_error( "Value " + val + " is above or equal to limit " +
                                 boost::lexical_cast< std::string>( mCheckValue));
} // CheckUpper< T>::checkValue


template< typename T> std::string CheckUpper< T>::toString() const
{

   std::ostringstream  oss;

   oss << "Value < " << mCheckValue;

   return oss.str();
} // CheckUpper< T>::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create an upper-limit check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( upper( ...));
/// @param[in]  value  The value to check against.
/// @return  The newly created CheckUpper object.
/// @since  0.2, 10.04.2016
template< typename T> detail::ICheck* upper( T value)
{
   return new detail::CheckUpper< T>( value);
} // end upper


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_UPPER_HPP


// =====  END OF check_upper.hpp  =====

