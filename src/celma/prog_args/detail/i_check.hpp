
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
/// See documentation of class celma::prog_args::detail::ICheck.


#ifndef CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP
#define CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP


#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Base class for value checks.
/// @since  0.2, 10.04.2016
class ICheck
{
public:
   /// Empty, virtual destructor.
   /// @since  0.2, 10.04.2016
   virtual ~ICheck() { }

   /// The method that must be implemented by the derived classes: Should check
   /// the passed value and throw an exception if the value is invalid/out of
   /// range.
   /// @param[in]  val  The value to check.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const = 0;

}; // ICheck


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP


// =========================  END OF i_check.hpp  =========================

