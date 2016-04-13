
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


#ifndef CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP
#define CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


#include <cassert>
#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


/// Default line handler policy: Does not do anything.
/// @since  0.3, 13.04.2016
class DummyLineHandler
{
protected:
   /// Policy method, does not do anything.
   /// @since  6.0, 13.04.2016
   void handleLine( LineHandlerCallPoints, const std::string&) const
   {
   } // end DummyLineHandler::handleLine

}; // DummyLineHandler


/// Structure which contains all the counters.
/// @since  0.3, 13.04.2016
struct FileLineStat
{
   /// Number of lines read from the file.
   int  linesRead;
   /// Thereof: Number of lines filtered.
   int  linesFiltered;
   /// Number of lines actually processed.
   int  linesProcessed;

}; // FileLineStat


/// Example of a line handler policy that counts all lines processed.
/// @since  0.3, 13.04.2016
class StatLineHandler
{
public:
   /// 
   /// @since  0.3, 13.04.2016
   StatLineHandler():
      mLinesRead( 0),
      mLinesFiltered( 0),
      mLinesProcessed( 0),
      mpFileLineStat( nullptr)
   {
   }

   ///
   /// @since  0.3, 13.04.2016
   ~StatLineHandler()
   {
      if (mpFileLineStat != nullptr)
      {
         mpFileLineStat->linesRead      = mLinesRead;
         mpFileLineStat->linesFiltered  = mLinesFiltered;
         mpFileLineStat->linesProcessed = mLinesProcessed;
      }
   }

   void setEndStat( FileLineStat* fls)
   {
      mpFileLineStat = fls;
   }

   int linesRead() const
   {
      return mLinesRead;
   }

   int linesFiltered() const
   {
      return mLinesFiltered;
   }

   int linesProcessed() const
   {
      return mLinesProcessed;
   }

protected:
   void handleLine( LineHandlerCallPoints lhcp, const std::string&) 
   {
      switch (lhcp)
      {
      case LineHandlerCallPoints::lineRead:       ++mLinesRead;       break;
      case LineHandlerCallPoints::lineFiltered:   ++mLinesFiltered;   break;
      case LineHandlerCallPoints::lineProcessed:  ++mLinesProcessed;  break;
      default:                                    assert( false);     break;
      } // end switch
   }

private:
   int  mLinesRead;
   int  mLinesFiltered;
   int  mLinesProcessed;
   FileLineStat*  mpFileLineStat;

};


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


// ===================  END OF line_handler_policy.hpp  ===================

