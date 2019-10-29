
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
/// See documentation of class celma::prog_args::detail::ICheck.


#ifndef CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP
#define CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP


#include <iostream>
#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Base class for value checks.
///
/// @since  0.2, 10.04.2016
class ICheck
{
public:
   /// Empty, virtual destructor.
   ///
   /// @since  0.2, 10.04.2016
   virtual ~ICheck() = default;

   /// The method that must be implemented by the derived classes: Should check
   /// the passed value and throw an exception if the value is invalid/out of
   /// range.
   ///
   /// @param[in]  val  The value to check.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const std::string& val) const = 0;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   virtual std::string toString() const = 0;

   /// Returns if a combination of the current check with the \a other check is
   /// allowed.
   ///
   /// @param[in]  other
   ///    The other check object to verify if combinations with are allowed.
   /// @return  \c false if two checks with the same name would be combined.
   /// @since  1.32.0, 24.04.2019
   virtual bool combinationAllowed( const ICheck* other) const;

protected:
   /// Constructor, stores the symbolic name of the check.
   ///
   /// @param[in]  check_name  The symbolic name of the check.
   /// @since  1.32.0, 24.04.2019
   ICheck( const std::string check_name);

   /// Symbolic name of the check, used for verifying if combinations of two
   /// checks are allowed.<br>
   /// Storing this here in the base class saves another virtual method.
   const std::string  mName;

}; // ICheck


// inlined methods
// ===============


inline ICheck::ICheck( const std::string check_name):
   mName( check_name)
{
} // ICheck::ICheck


inline bool ICheck::combinationAllowed( const ICheck* other) const
{
   return mName != other->mName;
} // ICheck::combinationAllowed


/// Prints a text description of the check using the toString() method.
///
/// @param[in]  os
///    The stream to print to.
/// @param[in]  pc
///    Pointer to the chck object to print the description of.
/// @return
///    The stream as passed in.
/// @since
///    0.16.0, 12.08.2017
inline std::ostream& operator <<( std::ostream& os, ICheck* pc)
{

   return os << pc->toString();
} // operator <<


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_CHECK_HPP


// =====  END OF i_check.hpp  =====

