
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckIsDirectory.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_IS_DIRECTORY_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_IS_DIRECTORY_HPP


#include <stdexcept>
#include "celma/common/file_info.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks if a value contains the (path and) name of directory.
/// @since  1.4.1, 02.03.2018
class CheckIsDirectory: public ICheck
{
public:
   CheckIsDirectory() = default;
   virtual ~CheckIsDirectory() = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// directory.
   /// @param[in]  val  The value to check in string format.
   /// @since  1.4.1, 02.03.2018
   virtual void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  1.4.1, 02.03.2018
   virtual std::string toString() const override;

}; // CheckIsDirectory


// inlined methods
// ===============


inline void CheckIsDirectory::checkValue( const std::string& val) const
{
   if (!common::fileInfo( val).isDirectory())
      throw std::runtime_error( std::string( "'") + val
         + "' is not an existing directory");
} // CheckIsDirectory::checkValue


inline std::string CheckIsDirectory::toString() const
{
   return std::string( "is a directory");
} // CheckIsDirectory::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a is-directory check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( isDirectory());
/// @return  The newly created CheckIsDirectory object.
/// @since  1.4.1, 02.03.2018
inline detail::ICheck* isDirectory()
{
   return new detail::CheckIsDirectory();
} // isDirectory


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_IS_DIRECTORY_HPP


// =====  END OF check_is_directory.hpp  =====

