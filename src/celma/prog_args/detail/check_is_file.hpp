
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::CheckIsFile.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_IS_FILE_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_IS_FILE_HPP


#include <stdexcept>
#include "celma/common/file_info.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Checks if a value contains the (path and) name of file.
/// @since  1.4.1, 02.03.2018
class CheckIsFile: public ICheck
{
public:
   /// Constructor, sets the symbolic name in the base class.
   ///
   /// @since  1.32.0, 24.04.2019
   CheckIsFile();

   /// Default destructor isa fine.
   virtual ~CheckIsFile() = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// file.
   /// @param[in]  val  The value to check in string format.
   /// @since  1.4.1, 02.03.2018
   virtual void checkValue( const std::string& val) const override;

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  1.4.1, 02.03.2018
   virtual std::string toString() const override;

}; // CheckIsFile


// inlined methods
// ===============


inline CheckIsFile::CheckIsFile():
   ICheck( "is file")
{
} // CheckIsFile::CheckIsFile


inline void CheckIsFile::checkValue( const std::string& val) const
{
   if (!common::fileInfo( val).isFile())
      throw std::runtime_error( std::string( "'") + val
         + "' is not an existing file");
} // CheckIsFile::checkValue


inline std::string CheckIsFile::toString() const
{
   return std::string( "is a file");
} // CheckIsFile::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a is-file check more easily.<br>
/// Usage:  addArgument( ...)->addCheck( isFile());
/// @return  The newly created CheckIsFile object.
/// @since  1.4.1, 02.03.2018
inline detail::ICheck* isFile()
{
   return new detail::CheckIsFile();
} // isFile


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_IS_FILE_HPP


// =====  END OF check_is_file.hpp  =====

