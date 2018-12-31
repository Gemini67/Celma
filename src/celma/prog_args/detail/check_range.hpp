
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::CheckRange.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_RANGE_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_RANGE_HPP


#include <stdexcept>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks a value if it is within the range lower <= x < upper.
/// @tparam  T  The native type of the limit to check.
/// @since  0.2, 10.04.2016
template< typename T> class CheckRange : public ICheck
{
public:
   /// Constructor.
   /// @param[in]  lower  The lower limit to check against.
   /// @param[in]  upper  The upper limit to check against.
   /// @since  0.2, 10.04.2016
   CheckRange( T lower, T upper);

   /// Checks if the value in \a val is in the range lower ... upper.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   virtual std::string toString() const override;

private:
   /// The lower limit to check against.
   const T  mLower;
   /// The upper limit to check against.
   const T  mUpper;

}; // CheckRange< T>


// inlined methods
// ===============


template< typename T> CheckRange< T>::CheckRange( T lower, T upper):
   mLower( lower),
   mUpper( upper)
{
   if (mUpper <= mLower)
      throw std::invalid_argument( "Range " + boost::lexical_cast< std::string>( mLower) +
                                   ".." + boost::lexical_cast< std::string>( mUpper) +
                                   " is invalid");
} // CheckRange< T>::CheckRange


template< typename T> void CheckRange< T>::checkValue( const std::string& val) const
{
   T  native = boost::lexical_cast< T>( val);
   if (native < mLower)
      throw std::range_error( "Value " + val + " is below limit " +
                              boost::lexical_cast< std::string>( mLower));
   if (native >= mUpper)
      throw std::range_error( "Value " + val + " is above or equal to limit " +
                              boost::lexical_cast< std::string>( mUpper));
} // CheckRange< T>::checkValue


template< typename T> std::string CheckRange< T>::toString() const
{

   std::ostringstream  oss;

   oss << mLower << " <= value < " << mUpper;

   return oss.str();
} // CheckRange< T>::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a range check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( range( ...));
/// @param[in]  low  The lower limit to check against.
/// @param[in]  upp  The upper limit to check against.
/// @return  The newly created CheckRange object.
/// @since  0.2, 10.04.2016
template< typename T> detail::ICheck* range( T low, T upp)
{
   return new detail::CheckRange< T>( low, upp);
} // end range


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_RANGE_HPP


// =========================  END OF check_range.hpp  =========================

