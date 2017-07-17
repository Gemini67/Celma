
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
/// See documentation of classes celma::common::detail::DummyLineHandler and
/// celma::common::detail::StatLineHandler.


#ifndef CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP
#define CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


#include <cassert>
#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


/// Default line handler policy: Does not do anything.
/// @since  x.y.z, 13.04.2016
class DummyLineHandler
{
protected:
   /// Policy method, does not do anything.
   /// @since  x.y.z, 13.04.2016
   void handleLine( LineHandlerCallPoints, const std::string&) const
   {
   } // DummyLineHandler::handleLine

}; // DummyLineHandler


/// Structure which contains all the counters.
/// @since  x.y.z, 13.04.2016
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
/// @since  x.y.z, 13.04.2016
class StatLineHandler
{
public:
   /// 
   /// @since  x.y.z, 13.04.2016
   StatLineHandler() = default;

   /// 
   /// @since  x.y.z, 16.05.2017
   StatLineHandler( const StatLineHandler& other):
      mLinesRead( other.mLinesRead),
      mLinesFiltered( other.mLinesFiltered),
      mLinesProcessed( other.mLinesProcessed),
      mpFileLineStat( nullptr)
   {
   } // StatLineHandler::StatLineHandler

   /// Destructor, stores the final values in the destination statistic object.
   /// @since  x.y.z, 13.04.2016
   ~StatLineHandler()
   {
      if (mpFileLineStat != nullptr)
      {
         mpFileLineStat->linesRead      = mLinesRead;
         mpFileLineStat->linesFiltered  = mLinesFiltered;
         mpFileLineStat->linesProcessed = mLinesProcessed;
      } // end if
   } // StatLineHandler::~StatLineHandler

   /// Sets the object in which the final statistic should be stored.
   /// @param  fls  Pointer to the file line statistic object.
   /// @since  x.y.z, 13.04.2016
   void setEndStat( FileLineStat* fls)
   {
      mpFileLineStat = fls;
   } // StatLineHandler::setEndStat

   /// Returns the number of lines read.
   /// @return  Number of lines read.
   /// @since  x.y.z, 13.04.2016
   int linesRead() const
   {
      return mLinesRead;
   } // end StatLineHandler::linesRead

   /// Returns the number of lines that were ignored by the filter.
   /// @return  Number of lines ignored by the filter.
   /// @since  x.y.z, 13.04.2016
   int linesFiltered() const
   {
      return mLinesFiltered;
   } // StatLineHandler::linesFiltered

   /// Returns the number of lines that were actually processed, i.e. returned
   /// by the iterator to the application.
   /// @return  .
   /// @since  x.y.z, 13.04.2016
   int linesProcessed() const
   {
      return mLinesProcessed;
   } // StatLineHandler::linesProcessed

protected:
   /// Increments the counter depending on the type of the call point.
   /// @param[in]  lhcp  The call point from which this methd was called.
   /// @param[in]        The current line, ignored.
   /// @since  x.y.z, 13.04.2016
   void handleLine( LineHandlerCallPoints lhcp, const std::string&) 
   {
      switch (lhcp)
      {
      case LineHandlerCallPoints::lineRead:       ++mLinesRead;       break;
      case LineHandlerCallPoints::lineFiltered:   ++mLinesFiltered;   break;
      case LineHandlerCallPoints::lineProcessed:  ++mLinesProcessed;  break;
      default:                                    assert( false);     break;
      } // end switch
   } // StatLineHandler::handleLine

private:
   /// Counter how many lines were read from the file.
   int            mLinesRead = 0;
   /// Counter how many lines were filtered.
   int            mLinesFiltered = 0;
   /// Counter how many lines were processed.
   int            mLinesProcessed = 0;
   /// Pointer to the object to store the final values in.
   FileLineStat*  mpFileLineStat = nullptr;

}; // StatLineHandler



} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


// =====================  END OF line_handler_policy.hpp  =====================

