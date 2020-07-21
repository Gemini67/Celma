
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
/// celma::prog_args::detail::CheckFileModification<>.


#pragma once


#include <chrono>
#include <functional>
#include <stdexcept>
#include <string>
#include "celma/common/file_info.hpp"
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/i_check.hpp"


namespace celma::prog_args { namespace detail {


/// Checks the "last modification" timestamp of a file.
/// The time difference between the current time and the last modification time
/// of the file is compared against the given time difference in seconds.
///
/// @tparam  C  The type of the size comparison class.
/// @since  1.39.0, 11.07.2020
template< template< typename> class C> class CheckFileModification final :
   public ICheck
{
public:
   /// Constructor, stores the duration to compare against.
   ///
   /// @param[in]  mod_time_diff
   ///    The time difference for the modification time to compare against.
   /// @since  1.39.0, 11.07.2020
   CheckFileModification( std::chrono::seconds mod_time_diff);

   /// Default destructor is fine.
   ~CheckFileModification() override = default;

   /// Checks if the difference between the current time and the modification
   /// time of the file given by \a val (the "age" of the file) fulfills the
   /// comparison with the defined time.
   ///
   /// @param[in]  val  The (path and) filename to check.
   /// @throw
   ///    std::runtime_error if the specified file does not exist.
   /// @throw
   ///    std::invalid_argument if the time-since-last-modification does not
   ///    fulfill the comparison with the defined time.
   /// @since  1.39.0, 11.07.2020
   void checkValue( const std::string& val) const noexcept( false) override;

   /// Returns a text description of the check.
   ///
   /// @return  A string with the text description of the check.
   /// @since  1.39.0, 11.07.2020
   std::string toString() const override;

private:
   /// The file size to compare against.
   const std::chrono::seconds  mModTimeDiff;
  
}; // CheckFileModification< C>


// inlined methods
// ===============


template< template< typename> class C>
   CheckFileModification< C>::CheckFileModification( std::chrono::seconds mod_time_diff):
      ICheck( "file modification time"),
      mModTimeDiff( mod_time_diff)
{
} // CheckFileModification< C>::CheckFileModification


template< template< typename> class C>
   void CheckFileModification< C>::checkValue( const std::string& val) const
{
   auto const  now = std::chrono::system_clock::now();
   auto const  mod_time = common::fileInfo( val).modTime();
   if (!C()( now - mod_time, mModTimeDiff))
      throw std::invalid_argument( "file modification time check failed");
} // CheckFileModification< C>::checkValue


template< template< typename> class C>
   std::string CheckFileModification< C>::toString() const
{
   return std::string( "file modification time check ")
      + type< C< void>>::name() + " " + format::toString( mModTimeDiff.count());
} // CheckFileModification< C>::toString


} // namespace detail


// helper function
// ===============


/// Helper function to create a file-size check more easily.
/// Usage:  addArgument( ...)->addCheck( fileSize< std::less>( 512));
///
/// @tparam  C  The type of the size comparison class.
/// @param[in]  mod_time_diff  The file size to compare against.
/// @return  The newly created CheckFileSize object.
/// @since  1.39.0, 08.07.2020
template< template< typename> class C>
   [[nodiscard]] detail::ICheck* fileMod( std::chrono::seconds mod_time_diff)
{
   return new detail::CheckFileModification< C>( mod_time_diff);
} // fileSize


} // namespace celma::prog_args


// =====  END OF check_file_modification.hpp  =====

