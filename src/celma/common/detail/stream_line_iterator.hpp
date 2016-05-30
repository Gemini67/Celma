
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
/// See documentation of class celma::common::detail::StreamLineIterator.


#ifndef CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP
#define CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


/// Iterator for a textfile.
/// @tparam  S  Type of the stream to read.
/// @tparam  F  Filter policy.
/// @tparam  H  Policy object call for each line.
/// @since  0.3, 13.04.2016
template< typename S, typename F, typename H> class StreamLineIterator:
   public F, public H
{

   using F::filter;
   using H::handleLine;

public:
   /// Constructor.
   /// @param[in]  source  The source == file stream to read from.
   /// @param[in]  atEnd   Set to \c true for end iterator.
   /// @since  0.3, 13.04.2016
   StreamLineIterator( S& source, bool atEnd = false);

   /// Not-equal comparison operator.
   /// @param[in]  other  The other iterator object to compare against.
   /// @return  \c true if \c this and \a other are not equal.
   /// @since  0.3, 13.04.2016
   bool operator !=( const StreamLineIterator& other) const;

   /// Pre-increment operator.
   /// @return  This object, pointing to the next line.
   /// @since  0.3, 13.04.2016
   StreamLineIterator& operator ++();

   /// Post-increment operator.
   /// @return  Object pointing to the current line.
   /// @since  0.3, 13.04.2016
   StreamLineIterator< S, F, H> operator ++( int);

   /// Dereference operator.
   /// The current line.
   /// @since  0.3, 13.04.2016
   std::string operator *();

   /// Returns the number of the current line.
   /// @return  The line number of the current line.
   /// @since  0.3, 13.04.2016
   int lineNbr() const;

private:
   /// The stream to read from.
   S&           mSource;
   /// Set to \c true if this object is at the end of the stream.
   bool         mAtEnd;
   /// The current line read from the stream.
   std::string  mCurrentLine;
   /// Line number counter.
   int          mLineNbr;

}; // StreamLineIterator< S, F, H>


// inlined methods
// ===============

template< typename S, typename F, typename H>
   StreamLineIterator< S, F, H>::StreamLineIterator( S& source, bool atEnd):
         F(),
         H(),
         mSource( source),
         mAtEnd( atEnd),
         mCurrentLine(),
         mLineNbr( -1)
{
   if (!mAtEnd)
      operator ++();
} // end StreamLineIterator< S, F, H>::StreamLineIterator


template< typename S, typename F, typename H>
   bool StreamLineIterator< S, F, H>::operator !=( const StreamLineIterator& other) const
{
   return (&mSource != &other.mSource) || (mAtEnd != other.mAtEnd) ||
          (!mAtEnd && (mLineNbr != other.mLineNbr));
} // end StreamLineIterator< S, F, H>::operator !=


template< typename S, typename F, typename H>
   StreamLineIterator< S, F, H>& StreamLineIterator< S, F, H>::operator ++()
{
   for (;;)
   {
      if (!std::getline( mSource, mCurrentLine))
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
} // end StreamLineIterator< S, F, H>::operator ++


template< typename S, typename F, typename H>
   StreamLineIterator< S, F, H> StreamLineIterator< S, F, H>::operator ++( int)
{
   auto  obj_copy( *this);
   ++(*this);
   return obj_copy;
} // end StreamLineIterator< S, F, H>::operator ++


template< typename S, typename F, typename H>
   std::string StreamLineIterator< S, F, H>::operator *()
{
   return mCurrentLine;
} // end StreamLineIterator< S, F, H>::operator *


template< typename S, typename F, typename H>
   int StreamLineIterator< S, F, H>::lineNbr() const
{
   return mLineNbr;
} // end StreamLineIterator< S, F, H>::lineNbr


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


// =====================  END OF stream_line_iterator.hpp  =====================


