
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::RangeExpression.


// module headerfile include
#include "celma/common/detail/range_expression.hpp"


// OS/C lib includes
#include <cctype>


// Boost includes
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/celma_exception.hpp"


namespace celma { namespace common { namespace detail {


using std::string;



/// Parses the (first) range expression in the string.
/// The string must begin with a valid range expression. Everything after
/// the parts that could be identified is ignored.
///
/// @param[in]  s  The string to parse.
/// @throw
///    celma::common::CelmaRuntimeError if the string contains an invalid
///    charater.
/// @since  0.2, 07.04.2016
void RangeExpression::parseString( const string& s) noexcept( false)
{

   mRangeString    = s;
   mMatchedExpression.clear();
   mFound          = 0;
   mStartValue     = -1;
   mEndValue       = -1;
   mIncrementValue = -1;
   mExcludeValue.clear();

   if (!parse())
      throw CELMA_RuntimeError( string( "invalid/unexpected character at "
         "position ").append( boost::lexical_cast< string>( mNextPos)));

   mMatchedExpression.assign( mRangeString, 0, mNextPos);

} // RangeExpression::parseString



/// Parses the string starting from #mNextPos, checks and evaluates the
/// single values, ranges, steps etc.
///
/// @return  \c true if the contents of the string are syntactically correct.
/// @since  0.2, 07.04.2016
bool RangeExpression::parse()
{

   // first there must always be a number
   if (!::isdigit( mRangeString[ 0]))
      return false;

   mNextPos = 0;
   readNumber( mStartValue);

   mFound = miStartValue;

   // range?
   if (mNextPos < mRangeString.length())
   {
      if (mRangeString[ mNextPos] == RangeSeparator)
      {
         // have a range, need at least one digit now
         if (!::isdigit( mRangeString[ ++mNextPos]))
            return false;

         readNumber( mEndValue);
         mFound |= miEndValue;

         // increment and/or exclude-string can only be used together with a
         // range

         // increment?
         if ((mNextPos < mRangeString.length())
             && (mRangeString[ mNextPos] == IncrementStart))
         {
            // have an increment, need at least one digit now
            if (!::isdigit( mRangeString[ ++mNextPos]))
               return false;

            readNumber( mIncrementValue);

            if (mRangeString[ mNextPos] != IncrementEnd)
               return false;

            ++mNextPos;
            mFound |= miIncrement;
         } // end if

         // exclude-range?
         if ((mNextPos < mRangeString.length())
             && (mRangeString[ mNextPos] == ExcludeStart))
         {
            auto const  exclude_begin = ++mNextPos;
            auto        inner_exclude = 0;

            // find the end of the exclude range
            // since the exclude-range itself can be a range that contains an
            // exclude range, have to keep track of the { } we find
            while (mNextPos < mRangeString.length())
            {
               if (mRangeString[ mNextPos] == ExcludeStart)
               {
                  ++inner_exclude;
               } else if (mRangeString[ mNextPos] == ExcludeEnd)
               {
                  if (inner_exclude > 0)
                  {
                     --inner_exclude;
                  } else
                  {
                     break;   // while
                  } // end if
               } // end if
               ++mNextPos;
            } // end while

            if (mRangeString[ mNextPos] != ExcludeEnd)
               return false;

            mExcludeValue.assign( mRangeString, exclude_begin,
               mNextPos - exclude_begin);
            ++mNextPos;
            mFound |= miExclude;
         } // end if
      } else if (mRangeString[ mNextPos] != NextRangeSeparator)
      {
         return false;
      } // end if
   } // end if

   return true;
} // RangeExpression::parse



/// Helper function to read a number from the range string.
///
/// @param[out]  value  Returns the value read from the string.
/// @since  0.2, 07.04.2016
void RangeExpression::readNumber( int64_t& value)
{

   value = mRangeString[ mNextPos++] - '0';

   while ((mNextPos < mRangeString.length())
          && (::isdigit( mRangeString[ mNextPos]) != 0))
   {
      value = (value * 10) + (mRangeString[ mNextPos++] - '0');
   } // end while

} // RangeExpression::readNumber



} // namespace detail
} // namespace common
} // namespace celma


// =====  END OF range_expression.cpp  =====

