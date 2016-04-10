
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
/// See documentation of class celma::prog_args::detail::CheckValues.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_VALUES_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_VALUES_HPP


#include <string>
#include <set>
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks a value if it matches a set of specified, allowed values.
/// @since  0.2, 10.04.2016
class CheckValues: public ICheck
{
public:
   /// Constructor.
   /// @param[in]  valueList  The list of allowed values in string format.
   /// @since  0.2, 10.04.2016
   CheckValues( const std::string& valueList);

   /// Checks if the value in \a val exists in the set of allowed values.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const;

private:
   /// Storage type for the values.
   typedef  std::set< std::string>  StringSet;

   /// The allowed values.
   StringSet  mValues;

}; // CheckValues


} // namespace detail


// helper function
// ===============


/// Helper function to create a lower-limit check more easily: Simply call this
/// function with the check-value as parameter to TypedArgBase::addCheck().
/// @param[in]  valueList  The value-list to check against.
/// @return  The newly created CheckValues object.
/// @since  0.2, 10.04.2016
inline detail::ICheck* values( const std::string& valueList)
{
   return new detail::CheckValues( valueList);
} // end values


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_VALUES_HPP


// =========================  END OF check_values.hpp  =========================

