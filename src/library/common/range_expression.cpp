
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
/// See documentation of class celma::common::RangeExpression.


// module header file include
#include "celma/common/range_expression.hpp"


// C/OS library includes
#include <cctype>


// Boost includes
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/celma_exception.hpp"


using namespace std;


namespace celma { namespace common {



/// Constructor, initialises the regular expression.
/// @since  0.2, 07.04.2016
RangeExpression::RangeExpression():
   mRangeString(),
   mMatchedExpression(),
   mFound( 0),
   mStartValue(),
   mEndValue(),
   mIncrementValue(),
   mExcludeValue()
{
} // end RangeExpression::RangeExpression



/// Parses the (first) range expression in the string.<br>
/// The string must begin with a valid range expression. Everything after
/// the parts that could be identified is ignored.
/// @param[in]  s  The string to parse.
/// @since  0.2, 07.04.2016
void RangeExpression::parseString( const string& s)
{

   mRangeString    = s;
   mMatchedExpression.clear();
   mFound          = 0;
   mStartValue     = -1;
   mEndValue       = -1;
   mIncrementValue = -1;
   mExcludeValue.clear();

   if (!parse())
      throw CELMA_RuntimeError( string( "invalid/unexpected character at position ").
                                        append( boost::lexical_cast< string>( mNextPos)));

   mMatchedExpression.assign( mRangeString, 0, mNextPos);

} // end RangeExpression::parseString



/// Parses the string starting from #mNextPos, checks and evaluates the
/// single values, ranges, steps etc.
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
   if ((mNextPos < mRangeString.length()) && (mRangeString[ mNextPos] == '-'))
   {
      // have a range, need at least one digit now
      if (!::isdigit( mRangeString[ ++mNextPos]))
         return false;

      readNumber( mEndValue);
      mFound |= miEndValue;

      // increment and/or exclude-string can only be used together with a range

      // increment?
      if ((mNextPos < mRangeString.length()) && (mRangeString[ mNextPos] == '['))
      {
         // have an increment, need at least one digit now
         if (!::isdigit( mRangeString[ ++mNextPos]))
            return false;

         readNumber( mIncrementValue);

         if (mRangeString[ mNextPos] != ']')
            return false;

         ++mNextPos;
         mFound |= miIncrement;
      } // end if

      // exclude-range?
      if ((mNextPos < mRangeString.length()) && (mRangeString[ mNextPos] == '{'))
      {
         string::size_type  exclude_begin = ++mNextPos;
         string::size_type  inner_exclude = 0;

         // find the end of the exclude range
         // since the exclude-range itself can be a range that contains an
         // exclude range, have to keep track of the { } we find
         while (mNextPos < mRangeString.length())
         {
            if (mRangeString[ mNextPos] == '{')
            {
               ++inner_exclude;
            } else if (mRangeString[ mNextPos] == '}')
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

         if (mRangeString[ mNextPos] != '}')
            return false;

         mExcludeValue.assign( mRangeString, exclude_begin, mNextPos - exclude_begin);
         ++mNextPos;
         mFound |= miExclude;
      } // end if
   } // end if

   return true;
} // end RangeExpression::parse



/// Helper function to read a number from the range string.
/// @param[out]  value  Returns the value read from the string.
/// @since  0.2, 07.04.2016
void RangeExpression::readNumber( int64_t& value)
{

   value = mRangeString[ mNextPos++] - '0';

   while ((mNextPos < mRangeString.length()) &&
          ::isdigit( mRangeString[ mNextPos]))
   {
      value = (value * 10) + (mRangeString[ mNextPos++] - '0');
   } // end while

} // end RangeExpression::readNumber



} // namespace common
} // namespace celma


// =========================  END OF range_expression.cpp  =========================
