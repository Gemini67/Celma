
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::TextFile.


#ifndef CELMA_COMMON_TEXT_FILE_HPP
#define CELMA_COMMON_TEXT_FILE_HPP


#include <string>
#include <stdexcept>
#include "celma/common/detail/stream_line_iterator.hpp"
#include "celma/common/detail/filter_policy.hpp"
#include "celma/common/detail/line_handler_policy.hpp"


namespace celma { namespace common {


using detail::EmptyLineFilter;
using detail::FileLineStat;
using detail::NoFilter;
using detail::StatLineHandler;


/// Class that provides iterator access to the contents of a textfile, plus
/// policies that can be used to filter or do other stuff.
/// @tparam  FilterPolicy       Line filter policy, can be used to ignore lines
///                             from the file. See
///                             celma::common::detail::NoFilter for an example
///                             implementation.
/// @tparam  LineHandlerPolicy  Additional policy object that is called for each
///                             line.<br>
///                             See celma::common::detail::DummyLineHandler for
///                             an example implementation.
/// @since  x.y.z, 13.04.2016
template< typename FilterPolicy = detail::NoFilter,
          typename LineHandlerPolicy = detail::DummyLineHandler> class TextFile
{
public:
   /// Default constructor. Call set() afterwards to specify the file to read.
   /// @since  x.y.z, 13.04.2016
   TextFile();

   /// Constructor with file parameter.
   /// @param[in]  fname  The (path and) name of the file to read.
   /// @since  x.y.z, 13.04.2016
   explicit TextFile( const std::string& fname) noexcept( false);

   ~TextFile() = default;
   TextFile( const TextFile&) = default;
   TextFile& operator =( const TextFile&) = default;

   /// Specifies the (path and) name of the file to read.
   /// @param[in]  fname  The file to read.
   /// @since  x.y.z, 13.04.2016
   void set( const std::string& fname) noexcept( false);

   /// Type of the iterator.
   using const_iterator = detail::StreamLineIterator<
      FilterPolicy, LineHandlerPolicy
   >;

   /// Returns the iterator pointing to the beginning of the file.
   /// @return  Iterator set on the beginning of the file.
   /// @since  x.y.z, 13.04.2016
   const_iterator begin() const noexcept( false);

   /// Returns the iterator pointing to the beginning of the file.
   /// @return  Iterator set on the beginning of the file.
   /// @since  x.y.z, 16.05.2017
   const_iterator cbegin() const noexcept( false);

   /// Returns the iterator pointing to the end of the file.
   /// @return  Iterator set on the end of the file.
   /// @since  x.y.z, 13.04.2016
   const_iterator end() const noexcept( false);

   /// Returns the iterator pointing to the end of the file.
   /// @return  Iterator set on the end of the file.
   /// @since  x.y.z, 16.05.20178
   const_iterator cend() const noexcept( false);

private:
   /// The file to read from.
   std::string  mFilename;

}; // TextFile< FilterPolicy, LineHandlerPolicy>


// inlined methods
// ===============


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile():
      mFilename()
{
} // TextFile< FilterPolicy, LineHandlerPolicy>::TextFile


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile( const std::string& fname):
      mFilename( fname)
{
   if (fname.empty())
      throw std::runtime_error( "file name may not be empty");
} // TextFile< FilterPolicy, LineHandlerPolicy>::TextFile


template< typename FilterPolicy, typename LineHandlerPolicy>
   void TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::set(
      const std::string& fname
   )
{
   if (fname.empty())
      throw std::runtime_error( "file name may not be empty");
   mFilename = fname;
} // TextFile< FilterPolicy, LineHandlerPolicy>::set


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::begin() const
{
   return const_iterator( mFilename);
} // TextFile< FilterPolicy, LineHandlerPolicy>::begin


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::cbegin() const
{
   return const_iterator( mFilename);
} // TextFile< FilterPolicy, LineHandlerPolicy>::cbegin


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::end() const
{
   return const_iterator( mFilename, true);
} // TextFile< FilterPolicy, LineHandlerPolicy>::end


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::cend() const
{
   return const_iterator( mFilename, true);
} // TextFile< FilterPolicy, LineHandlerPolicy>::cend


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TEXT_FILE_HPP


// ==========================  END OF text_file.hpp  ==========================

