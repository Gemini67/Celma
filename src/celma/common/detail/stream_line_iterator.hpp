
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::StreamLineIterator.


#ifndef CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP
#define CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


#include <fstream>
#include <stdexcept>
#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


/// Iterator for a textfile.
/// @tparam  F  Filter policy.
/// @tparam  H  Policy object to call for each line.
/// @tparam  C  The type of the statistic object.
/// @since  1.3.0, 16.05.2017  (open file here)
/// @since  13.04.2016
template< typename F, typename H, typename C = std::nullptr_t>
   class StreamLineIterator:
      public F, public H
{

   using F::filter;
   using H::handleLine;

public:
   using iterator_category = std::forward_iterator_tag;

   /// Constructor.
   /// @param[in]  source  The source == file name to read from.
   /// @param[in]  atEnd   Set to \c true for end iterator.
   /// @since  1.3.0, 16.05.2017  (changed parameter type of source)
   /// @since  13.04.2016
   explicit StreamLineIterator( const std::string& source, bool atEnd = false)
      noexcept( false);

   /// Constructor that takes a pointer to the statistics object to use.
   /// @param[in]  source    The source == file name to read from.
   /// @param[in]  stat_obj  Pointer to the statistic object to use.
   /// @since  1.3.0, 15.02.2018
   StreamLineIterator( const std::string& source, C* stat_obj) noexcept( false);

   /// Copy constructor.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  1.3.0, 16.05.2017
   StreamLineIterator( const StreamLineIterator& other) noexcept( false);

   /// Equality comparison operator.
   /// @param[in]  other  The other iterator object to compare against.
   /// @return  \c true if \c this and \a other are equal.
   /// @since  1.3.0, 16.05.2017
   bool operator ==( const StreamLineIterator& other) const;

   /// Not-equal comparison operator.
   /// @param[in]  other  The other iterator object to compare against.
   /// @return  \c true if \c this and \a other are not equal.
   /// @since  13.04.2016
   bool operator !=( const StreamLineIterator& other) const;

   /// Pre-increment operator.
   /// @return  This object, pointing to the next line.
   /// @since  13.04.2016
   StreamLineIterator& operator ++();

   /// Post-increment operator.
   /// @return  Object pointing to the current line.
   /// @since  13.04.2016
   StreamLineIterator< F, H, C> operator ++( int);

   /// Dereference operator.
   /// The current line.
   /// @since  13.04.2016
   std::string operator *();

   /// Returns the number of the current line.
   /// @return  The line number of the current line.
   /// @since  13.04.2016
   int lineNbr() const;

private:
   /// The (path and) file name of the source file to read.
   const std::string  mSourceFile;
   /// The stream to read from.
   std::ifstream      mStream;
   /// Set to \c true if this object is at the end of the stream.
   bool               mAtEnd = false;
   /// The current line read from the stream.
   std::string        mCurrentLine;
   /// Line number counter.
   int                mLineNbr = -1;

}; // StreamLineIterator< F, H, C>


// inlined methods
// ===============


template< typename F, typename H, typename C>
   StreamLineIterator< F, H, C>::StreamLineIterator( const std::string& source,
     bool atEnd):
   F(),
   H(),
   mSourceFile( source),
   mStream( source),
   mAtEnd( atEnd),
   mCurrentLine()
{
   if (mSourceFile.empty())
      throw std::runtime_error( "need to specify a file name");
   if (!mStream.is_open())
      throw std::runtime_error( "could not open file '" + mSourceFile + "'");
   if (!mAtEnd)
      operator ++();
} // StreamLineIterator< F, H, C>::StreamLineIterator


template< typename F, typename H, typename C>
   StreamLineIterator< F, H, C>::StreamLineIterator( const std::string& source,
     C* stat_obj):
   F(),
   H( stat_obj),
   mSourceFile( source),
   mStream( source),
   mCurrentLine()
{
   if (mSourceFile.empty())
      throw std::runtime_error( "need to specify a file name");
   if (!mStream.is_open())
      throw std::runtime_error( "could not open file '" + mSourceFile + "'");
   if (!mAtEnd)
      operator ++();
} // StreamLineIterator< F, H, C>::StreamLineIterator


template< typename F, typename H, typename C>
   StreamLineIterator< F, H, C>::StreamLineIterator( const StreamLineIterator& other):
      F( other),
      H( other),
      mSourceFile( other.mSourceFile),
      mStream(),
      mAtEnd( other.mAtEnd),
      mCurrentLine( other.mCurrentLine),
      mLineNbr( other.mLineNbr)
{

   if (!mAtEnd && mStream)
   {
      // ouch
      auto&  unconst_stream = const_cast< StreamLineIterator&>( other);
      mStream.open( mSourceFile);
      if (!mStream.is_open())
         throw std::runtime_error( "could not open file '" + mSourceFile + "'");
      mStream.seekg( unconst_stream.mStream.tellg());
   } // end if

} // StreamLineIterator< F, H, C>::StreamLineIterator


template< typename F, typename H, typename C>
   bool StreamLineIterator< F, H, C>::operator ==( const StreamLineIterator& other) const
{
   return (mSourceFile == other.mSourceFile) && (mAtEnd == other.mAtEnd) &&
          (mAtEnd || (mLineNbr == other.mLineNbr));
} // StreamLineIterator< F, H, C>::operator !=


template< typename F, typename H, typename C>
   bool StreamLineIterator< F, H, C>::operator !=( const StreamLineIterator& other) const
{
   return !(*this == other);
} // StreamLineIterator< F, H, C>::operator !=


template< typename F, typename H, typename C>
   StreamLineIterator< F, H, C>& StreamLineIterator< F, H, C>::operator ++()
{
   for (;;)
   {
      if (!std::getline( mStream, mCurrentLine))
      {
         mCurrentLine.clear();
         mAtEnd = true;
         break;   // for
      } // end if

      ++mLineNbr;
      handleLine( LineHandlerCallPoints::lineRead, mCurrentLine);

      if (!filter( mCurrentLine))
      {
         handleLine( LineHandlerCallPoints::lineProcessed, mCurrentLine);
         break;   // for
      } // end if

      handleLine( LineHandlerCallPoints::lineFiltered, mCurrentLine);
   } // end for
   return *this;
} // StreamLineIterator< F, H, C>::operator ++


template< typename F, typename H, typename C>
   StreamLineIterator< F, H, C> StreamLineIterator< F, H, C>::operator ++( int)
{
   auto  obj_copy( *this);
   ++(*this);
   return obj_copy;
} // StreamLineIterator< F, H, C>::operator ++


template< typename F, typename H, typename C>
   std::string StreamLineIterator< F, H, C>::operator *()
{
   return mCurrentLine;
} // StreamLineIterator< F, H, C>::operator *


template< typename F, typename H, typename C>
   int StreamLineIterator< F, H, C>::lineNbr() const
{
   return mLineNbr;
} // StreamLineIterator< F, H, C>::lineNbr


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


// =====  END OF stream_line_iterator.hpp  =====
