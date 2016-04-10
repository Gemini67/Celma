
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::CheckLower.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_LOWER_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_LOWER_HPP


#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks a value if it is greater-than or equal to a lower limit.
/// @tparam  T  The native type of the limit to check.
/// @since  0.2, 10.04.2016
template< typename T> class CheckLower : public ICheck
{
public:
   /// Constructor.
   /// @param[in]  value  The lower limit to check against.
   /// @since  0.2, 10.04.2016
   CheckLower( T value);

   /// Checks if the value in \a val is greater-than or equal to the stored
   /// limit.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const;

private:
   /// The lower limit to check against.
   T  mCheckValue;

}; // CheckLower<T>


// inlined methods
// ===============


template< typename T> CheckLower<T>::CheckLower( T value):
                                   mCheckValue( value)
{
} // end CheckLower<T>::CheckLower


template< typename T> void CheckLower<T>::checkValue( const std::string& val) const
{
   T  native = boost::lexical_cast< T>( val);
   if (native < mCheckValue)
      throw std::underflow_error( "Value " + val + " is below limit " +
                                  boost::lexical_cast< std::string>( mCheckValue));
} // end CheckLower<T>::checkValue


} // namespace detail


// helper function
// ===============


/// Helper function to create a lower-limit check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( lower( ...));
/// @param[in]  value  The value to check against.
/// @return  The newly created CheckLower object.
/// @since  0.2, 10.04.2016
template< typename T> detail::ICheck* lower( T value)
{
   return new detail::CheckLower< T>( value);
} // end lower


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_LOWER_HPP


// =========================  END OF check_lower.hpp  =========================

