
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
/// See documentation of classes celma::common::detail::DummyLineHandler and
/// celma::common::detail::StatLineHandler.


#ifndef CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP
#define CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


template< typename S, typename FilterPolicy, typename LineHandlerPolicy>
   class StreamLineIterator:
      public FilterPolicy, public LineHandlerPolicy
{

   using FilterPolicy::filter;
   using LineHandlerPolicy::handleLine;

public:
   StreamLineIterator( S& source, bool atEnd = false):
      FilterPolicy(),
      LineHandlerPolicy(),
      mSource( source),
      mAtEnd( atEnd),
      mCurrentLine(),
      mLineNbr( -1)
   {
      if (!mAtEnd)
         operator ++();
   }

   bool operator !=( const StreamLineIterator< S, FilterPolicy, LineHandlerPolicy>& other) const
   {
      return (&mSource != &other.mSource) || (mAtEnd != other.mAtEnd) ||
             (!mAtEnd && (mLineNbr != other.mLineNbr));
   }

   StreamLineIterator< S, FilterPolicy, LineHandlerPolicy>& operator ++()
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
   }

   StreamLineIterator< S, FilterPolicy, LineHandlerPolicy> operator ++( int)
   {
       // StreamLineIterator< S>  copy( *this);
      auto  obj_copy( *this);
      ++(*this);
      return obj_copy;
   }

   std::string operator *()
   {
      return mCurrentLine;
   }

   int lineNbr() const
   {
      return mLineNbr;
   }

private:
   S&           mSource;
   bool         mAtEnd;
   std::string  mCurrentLine;
   int          mLineNbr;

};


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_STREAM_LINE_ITERATOR_HPP


// =====================  END OF stream_line_iterator.hpp  =====================


