
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
/// See documentation of classes celma::common::detail::DummyLineHandler and
/// celma::common::detail::StatLineHandler.


#ifndef CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP
#define CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


#include <cassert>
#include <string>
#include "celma/common/detail/line_handler_call_points.hpp"


namespace celma { namespace common { namespace detail {


/// Default line handler policy: Does not do anything.
/// @since  1.3.0, 13.04.2016
class DummyLineHandler
{
protected:
   /// Policy method, does not do anything.
   /// @since  1.3.0, 13.04.2016
   void handleLine( LineHandlerCallPoints, const std::string&) const
   {
   } // DummyLineHandler::handleLine

}; // DummyLineHandler


/// Structure which contains all the counters.
/// @since  1.3.0, 13.04.2016
struct FileLineStat
{
   /// Number of lines read from the file.
   int  linesRead = 0;
   /// Thereof: Number of lines filtered.
   int  linesFiltered = 0;
   /// Number of lines actually processed.
   int  linesProcessed = 0;

}; // FileLineStat


/// Example of a line handler policy that counts all lines processed.
/// @since  1.3.0, 13.04.2016
class StatLineHandler
{
public:
   /// Constructor, expects a pointer to the statistic object to use.<br>
   /// If no object pointer is passed (NULL), no statistic is calculated.
   /// @param[in]  stat_obj  Pointer to the statistic object to use.
   /// @since  1.3.0, 13.04.2016
   StatLineHandler( FileLineStat* stat_obj = nullptr):
      mpFileLineStat( stat_obj)
   {
   } // StatLineHandler::StatLineHandler

   /// Copy constructor. Does *not* copy the pointer to the statistic object.
   /// @since  1.3.0, 16.05.2017
   StatLineHandler( const StatLineHandler&):
      mpFileLineStat( nullptr)
   {
   } // StatLineHandler::StatLineHandler

   /// Move constructor. Takes the pointer to the statistic object from the
   /// other object.
   /// @since  1.3.0, 15.02.2018
   StatLineHandler( StatLineHandler&& other):
      mpFileLineStat( other.mpFileLineStat)
   {
      other.mpFileLineStat = nullptr;
   } // StatLineHandler::StatLineHandler

   /// Destructor, nothing to do.
   /// @since  1.3.0, 13.04.2016
   ~StatLineHandler() = default;

   /// Returns the pointer to the internal statistic object.
   /// @return  The pointer to the internally used statistic object. May be NULL.
   /// @since  1.3.0, 15.02.2017
   FileLineStat* stat() const
   {
      return mpFileLineStat;
   } // StatLineHandler::stat

protected:
   /// Increments the counter depending on the type of the call point.
   /// @param[in]  lhcp  The call point from which this methd was called.
   /// @param[in]        The current line, ignored.
   /// @since  1.3.0, 13.04.2016
   void handleLine( LineHandlerCallPoints lhcp, const std::string&)
   {
      if (mpFileLineStat == nullptr)
         return;
      switch (lhcp)
      {
      case LineHandlerCallPoints::lineRead:
         ++mpFileLineStat->linesRead;
         break;
      case LineHandlerCallPoints::lineFiltered:
         ++mpFileLineStat->linesFiltered;
         break;
      case LineHandlerCallPoints::lineProcessed:
         ++mpFileLineStat->linesProcessed;
         break;
      default:
         assert( false);
         break;
      } // end switch
   } // StatLineHandler::handleLine

private:
   /// Pointer to the object to store the final values in.
   FileLineStat*  mpFileLineStat = nullptr;

}; // StatLineHandler


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_LINE_HANDLER_POLICY_HPP


// =====  END OF line_handler_policy.hpp  =====

