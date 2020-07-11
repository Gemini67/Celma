
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class
/// celma::prog_args::detail::CheckFileSize<>.


#ifndef CELMA_PROG_ARGS_DETAIL_CHECK_FILE_SIZE_HPP
#define CELMA_PROG_ARGS_DETAIL_CHECK_FILE_SIZE_HPP


#include <functional>
#include <stdexcept>
#include <string>
#include "celma/common/file_info.hpp"
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks the size of a file.
///
/// @tparam  C  The type of the size comparison class.
/// @since  x.y.z, 08.07.2020
template< template< typename> class C> class CheckFileSize: public ICheck
{
public:
   /// Constructor, stores the file size to compare against.
   ///
   /// @param[in]  file_size  The file size to compare against.
   /// @since  x.y.z, 08.07.2020
   CheckFileSize( size_t file_size);

   /// Default destructor is fine.
   ~CheckFileSize() override = default;

   /// Checks if the value in \a val contains the (path and) name of an existing
   /// file.
   ///
   /// @param[in]  val  The value to check in string format.
   /// @throw  std::invalid_argument if the specified file does not exist.
   /// @since  x.y.z, 08.07.2020
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  x.y.z, 08.07.2020
   std::string toString() const override;

private:
   /// The file size to compare against.
   const size_t  mFileSize;
  
}; // CheckFileSize< C>


// inlined methods
// ===============


template< template< typename> class C>
   CheckFileSize< C>::CheckFileSize( size_t file_size):
      ICheck( "file size"),
      mFileSize( file_size)
{
} // CheckFileSize< C>::CheckFileSize


template< template< typename> class C>
   void CheckFileSize< C>::checkValue( const std::string& val) const
{
   if (!C()( common::fileInfo( val).size(), mFileSize))
      throw std::invalid_argument( "file size check failed");
} // CheckFileSize< C>::checkValue


template< template< typename> class C> std::string CheckFileSize< C>::toString() const
{
   return std::string( "file size check ") + type< C< void>>::name() + " "
      + format::toString( mFileSize);
} // CheckFileSize< C>::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a file-size check more easily.
/// Usage:  addArgument( ...)->addCheck( fileSize< std::less>( 512));
///
/// @tparam  C  The type of the size comparison class.
/// @param[in]  file_size  The file size to compare against.
/// @return  The newly created CheckFileSize object.
/// @since  x.y.z, 08.07.2020
template< template< typename> class C>
   detail::ICheck* fileSize( size_t file_size)
{
   return new detail::CheckFileSize< C>( file_size);
} // fileSize


} // namespace celma::prog_args


#endif   // CELMA_PROG_ARGS_DETAIL_CHECK_FILE_SIZE_HPP


// =====  END OF check_file_size.hpp  =====

