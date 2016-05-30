
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
/// See documentation of template celma::common::TextFile.


#ifndef CELMA_COMMON_TEXT_FILE_HPP
#define CELMA_COMMON_TEXT_FILE_HPP


#include <string>
#include <fstream>
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
///                             line. See celma::common::detail::DummyLineHandler
///                             for an example implementation.
/// @since  0.3, 13.04.2016
template< typename FilterPolicy = detail::NoFilter,
          typename LineHandlerPolicy = detail::DummyLineHandler> class TextFile
{
public:
   /// Default constructor. Call set() afterwards to specify the file to read.
   /// @since  0.3, 13.04.2016
   TextFile();

   /// Constructor with file parameter.
   /// @param[in]  fname  The (path and) name of the file to read.
   /// @since  0.3, 13.04.2016
   explicit TextFile( const std::string& fname);

   /// Destructor for cleanup.
   /// @since  0.3, 13.04.2016
   ~TextFile();

   /// Don't allow copy-constructing objects.
   TextFile( const TextFile&) = delete;
   /// Don't allow assignment.
   TextFile& operator =( const TextFile&) = delete;

   /// Specifies the (path and) name of the file to read.
   /// @param[in]  fname  The file to read.
   /// @since  0.3, 13.04.2016
   void set( const std::string& fname);

   /// Type of the iterator.
   typedef detail::StreamLineIterator< std::ifstream, FilterPolicy, LineHandlerPolicy>  const_iterator;

   /// Returns the iterator pointing to the beginning of the file.
   /// @return  Iterator set on the beginning of the file.
   /// @since  0.3, 13.04.2016
   const_iterator begin();

   /// Returns the iterator pointing to the end of the file.
   /// @return  Iterator set on the end of the file.
   /// @since  0.3, 13.04.2016
   const_iterator end();

private:
   /// The file to read from.
   std::ifstream  mStream;

}; // TextFile< FilterPolicy, LineHandlerPolicy>


// inlined methods
// ===============


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile():
      mStream()
{
} // end TextFile< FilterPolicy, LineHandlerPolicy>::TextFile


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile( const std::string& fname):
      mStream( fname)
{
   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "could not open file '" + fname + "'");
} // end TextFile< FilterPolicy, LineHandlerPolicy>::TextFile


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::~TextFile()
{
   mStream.close();
} // end TextFile< FilterPolicy, LineHandlerPolicy>::~FilterPolicy

template< typename FilterPolicy, typename LineHandlerPolicy>
   void TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::set( const std::string& fname)
{

   if (mStream && mStream.is_open())
      mStream.close();

   mStream.open( fname);

   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "could not open file '" + fname + "'");
} // end TextFile< FilterPolicy, LineHandlerPolicy>::set


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::begin()
{
   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "file is not open");
   mStream.seekg( 0);
   return const_iterator( mStream);
} // end TextFile< FilterPolicy, LineHandlerPolicy>::begin


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::const_iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::end()
{
   return const_iterator( mStream, true);
} // end TextFile< FilterPolicy, LineHandlerPolicy>::end


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TEXT_FILE_HPP


// ==========================  END OF text_file.hpp  ==========================

