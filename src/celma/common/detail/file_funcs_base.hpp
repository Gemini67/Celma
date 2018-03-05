
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
/// See documentation of class celma::common::detail::FileFuncsBase.


#ifndef CELMA_COMMON_DETAIL_FILE_FUNCS_BASE_HPP
#define CELMA_COMMON_DETAIL_FILE_FUNCS_BASE_HPP


#include <string>


namespace celma { namespace common { namespace detail {


/// Base class for modules that implement file functions.
/// @since  1.4.0, 20.02.2018
class FileFuncsBase
{
public:
   /// Empty, virtual destructor for base class.
   /// @since  1.4.0, 20.02.2018
   virtual ~FileFuncsBase() = default;

   /// Gets called when a file should be renamed.
   /// @param[in]  dest  The new (pah and) name for the file.
   /// @param[in]  src   The (path and) name of the existing file that should be
   ///                   renamed.
   /// @return  The result of the %rename operation.
   /// @since  1.4.0, 20.02.2018
   virtual int rename( const std::string& dest, const std::string& src) = 0;

   /// Gets called when a %file should be removed.
   /// @param[in]  file  The (path and) name of the %file to delete.
   /// @return  The result code of the %remove operation.
   /// @since  1.4.0, 28.02.2018
   virtual int remove( const std::string& file) = 0;

}; // FileFuncsBase


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_FILE_FUNCS_BASE_HPP


// =====  END OF file_funcs_base.hpp  =====

