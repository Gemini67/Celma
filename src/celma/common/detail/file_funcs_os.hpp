
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
/// See documentation of class celma::common::detail::FileFuncsOs.


#ifndef CELMA_COMMON_DETAIL_FILE_FUNCS_OS_HPP
#define CELMA_COMMON_DETAIL_FILE_FUNCS_OS_HPP


#include <string>
#include "celma/common/detail/file_funcs_base.hpp"


namespace celma { namespace common { namespace detail {


/// Implmenetation of file functions for really calling the OS functions.
/// @since  1.4.0, 20.02.2018
class FileFuncsOs: public FileFuncsBase
{
public:
   /// Empty, virtual destructor.
   /// @since  1.4.0, 20.02.2018
   virtual ~FileFuncsOs() = default;

   /// Calls ::rename() to actually rename a file.
   /// @param[in]  dest  The new (path and) name for the file.
   /// @param[in]  src   The (path and) name of the existing file that should be
   ///                   renamed.
   /// @return  The return code from ::rename().
   /// @since  1.4.0, 20.02.2018
   virtual int rename( const std::string& dest, const std::string& src) override;

   /// Removes (deletes) a file.
   /// @param[in]  file  The (path and) name of the %file to delete.
   /// @return  The result code from ::remove().
   /// @since  1.4.0, 28.02.2018
   virtual int remove( const std::string& file) override;

}; // FileFuncsOs


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_FILE_FUNCS_OS_HPP


// =====  END OF file_funcs_os.hpp  =====

