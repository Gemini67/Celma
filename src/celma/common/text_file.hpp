
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::TextFile.


#pragma once


#include <functional>
#include <string>
#include <stdexcept>
#include <type_traits>
#include "celma/common/detail/stream_line_iterator.hpp"
#include "celma/common/detail/filter_policy.hpp"
#include "celma/common/detail/line_handler_policy.hpp"
#include "celma/common/reset_at_exit.hpp"


namespace celma::common {


using detail::EmptyLineFilter;
using detail::FileLineStat;
using detail::NoFilter;
using detail::StatLineHandler;


/// Class that provides iterator access to the contents of a textfile, plus
/// policies that can be used to filter or do other stuff.
/// @tparam  F  Line filter policy, can be used to ignore lines from the file.
///             See celma::common::detail::NoFilter for an example
///             implementation.
/// @tparam  H  Additional policy object that is called for each line.<br>
///             See celma::common::detail::DummyLineHandler for an example
///             implementation.
/// @tparam  S  The type of the statistics object used by the line handler class
///             to compute a statistic.
/// @since  1.3.0, 13.04.2016
template< typename F = detail::NoFilter,
          typename H = detail::DummyLineHandler,
          typename S = std::nullptr_t> class TextFile
{
public:
   /// Default constructor. Call set() afterwards to specify the file to read.
   /// @since  1.3.0, 13.04.2016
   TextFile();

   /// Constructor with file parameter.
   /// @param[in]  fname  The (path and) name of the file to read.
   /// @since  1.3.0, 13.04.2016
   explicit TextFile( const std::string& fname) noexcept( false);

   /// Copy constructor,<br>
   /// The pointer to an eventually set statistics object is not copied.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  1.3.0, 15.02.2018
   TextFile( const TextFile& other);

   ~TextFile() = default;
   TextFile& operator =( const TextFile&) = default;

   /// Specifies the (path and) name of the file to read.
   /// @param[in]  fname  The file to read.
   /// @since  1.3.0, 13.04.2016
   void set( const std::string& fname) noexcept( false);

   /// Specifies the object to use to calculate the statistic while iterating
   /// over the contents of a text file.<br>
   /// The object will be passed to the next iterator that is created.
   /// @param[in]  stat_obj  The object to use. Its type must correspond to the
   ///                       type expected/used by the line handler.
   /// @since  1.3.0, 13.02.2018
   void setStatObj( S& stat_obj);

   /// Type of the iterator.
   using const_iterator = detail::StreamLineIterator< F, H, S>;

   /// Returns the iterator pointing to the beginning of the file.
   /// @return  Iterator set on the beginning of the file.
   /// @since  1.3.0, 13.04.2016
   [[nodiscard]] const_iterator begin() const noexcept( false);

   /// Returns the iterator pointing to the beginning of the file.
   /// @return  Iterator set on the beginning of the file.
   /// @since  1.3.0, 16.05.2017
   [[nodiscard]] const_iterator cbegin() const noexcept( false);

   /// Returns the iterator pointing to the end of the file.
   /// @return  Iterator set on the end of the file.
   /// @since  1.3.0, 13.04.2016
   [[nodiscard]] const_iterator end() const noexcept( false);

   /// Returns the iterator pointing to the end of the file.
   /// @return  Iterator set on the end of the file.
   /// @since  1.3.0, 16.05.2017
   [[nodiscard]] const_iterator cend() const noexcept( false);

private:
   /// Internal method that actually creates a new iterator object.<br>
   /// This specific method creates an iterator that accepts/uses a statistic
   /// object.
   /// @tparam  T  The type of the statistic object.<br>
   ///             Must be a separate template parameter here for SFINAE to
   ///             work (enable_if).
   /// @param  Not used.
   /// @return  A new iterator.
   /// @since  1.3.0, 13.02.2018
   template< typename T>
      typename std::enable_if< !std::is_same< T, std::nullptr_t>::value,
                               const_iterator
                             >::type
         beginStatIter( T*) const
   {
      const ResetAtExit< S*>  rae( mpStatObject, nullptr);
      return const_iterator( mFilename, mpStatObject);
   } // TextFile< F, H, S>::beginStatIter

   /// Internal method that actually creates a new iterator object.<br>
   /// This specific method creates an iterator that does not accept/use a
   /// statistic object.
   /// @tparam  T  Accepts only std::nullptr_t.
   /// @param  Not used.
   /// @return  A new iterator.
   /// @since  1.3.0, 13.02.2018
   template< typename T>
      typename std::enable_if< std::is_same< T, std::nullptr_t>::value,
                               const_iterator
                             >::type
         beginStatIter( T*) const
   {
      return const_iterator( mFilename);
   } // TextFile< F, H, S>::beginStatIter

   /// The file to read from.
   std::string  mFilename;
   /// The object to use for calculating the file statistics. Will be passed to
   /// the next iterator object that is created through a begin()/cbegin() call.
   mutable S*   mpStatObject = nullptr;

}; // TextFile< F, H, S>


// inlined methods
// ===============


template< typename F, typename H, typename S> TextFile< F, H, S>::TextFile():
   mFilename()
{
} // TextFile< F, H, S>::TextFile


template< typename F, typename H, typename S>
   TextFile< F, H, S>::TextFile( const std::string& fname):
      mFilename( fname)
{
   if (fname.empty())
      throw std::runtime_error( "file name may not be empty");
} // TextFile< F, H, S>::TextFile


template< typename F, typename H, typename S>
   TextFile< F, H, S>::TextFile( const TextFile& other):
      mFilename( other.mFilename),
      mpStatObject( nullptr)
{
} // TextFile< F, H, S>::TextFile


template< typename F, typename H, typename S>
   void TextFile< F, H, S>::TextFile::set( const std::string& fname)
{
   if (fname.empty())
      throw std::runtime_error( "file name may not be empty");
   mFilename = fname;
} // TextFile< F, H, S>::set


template< typename F, typename H, typename S>
   void TextFile< F, H, S>::setStatObj( S& stat_obj)
{
   mpStatObject = &stat_obj;
} // TextFile< F, H, S>::setStatObj


template< typename F, typename H, typename S>
   typename TextFile< F, H, S>::const_iterator
      TextFile< F, H, S>::TextFile::begin() const
{
   return beginStatIter( mpStatObject);
} // TextFile< F, H, S>::begin


template< typename F, typename H, typename S>
   typename TextFile< F, H, S>::const_iterator
      TextFile< F, H, S>::TextFile::cbegin() const
{
   return beginStatIter( mpStatObject);
} // TextFile< F, H, S>::cbegin


template< typename F, typename H, typename S>
   typename TextFile< F, H, S>::const_iterator
      TextFile< F, H, S>::TextFile::end() const
{
   return const_iterator( mFilename, true);
} // TextFile< F, H, S>::end


template< typename F, typename H, typename S>
   typename TextFile< F, H, S>::const_iterator
      TextFile< F, H, S>::TextFile::cend() const
{
   return const_iterator( mFilename, true);
} // TextFile< F, H, S>::cend


} // namespace celma::common


// =====  END OF text_file.hpp  =====

