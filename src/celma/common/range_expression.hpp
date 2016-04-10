
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


#ifndef CELMA_COMMON_RANGE_EXPRESSION_HPP
#define CELMA_COMMON_RANGE_EXPRESSION_HPP


#include <cstdint>
#include <string>


namespace celma { namespace common {


/// Helper class to extract the different parts of a range expression.<br>
/// After parsing an expression with parseString(), check the strings for the
/// results:
/// - matchedExpression() returns the full expression that was matched. If this
///   string is empty, the string did not contain a valid range expression.
/// - startValue() contains the single/range start value.
/// - endValue() contains the range end value, if a range was defined.
/// - incrementValue() contains the increment value for the range, may be empty.
/// - excludeExpression() contains the expression for the values to exclude,
///   may be empty.
///
/// @since  0.2, 07.04.2016
class RangeExpression
{
public:
   /// Constructor, initialises the regular expression.
   /// @since  0.2, 07.04.2016
   RangeExpression();

   /// Parses the (first) range expression in the string.<br>
   /// The string must begin with a valid range expression. Everything after
   /// the parts that could be identified is ignored.
   /// @param[in]  s  The string to parse.
   /// @since  0.2, 07.04.2016
   void parseString( const std::string& s);

   /// Returns the full string that was matched.
   /// @return  The string that was matched.
   /// @since  0.2, 07.04.2016
   const std::string& matchedExpression() const;

   /// Returns the single/range start value.
   /// @return  The start value.
   /// @since  0.2, 07.04.2016
   int64_t startValue() const;

   /// Returns if an end-value was found in the string.
   /// @return  \c true if an end-value was found in the string.
   /// @since  0.2, 07.04.2016
   bool hasRangeEnd() const;

   /// Returns the range end value, if one was set.
   /// @return  The range end value, may be empty.
   /// @since  0.2, 07.04.2016
   int64_t endValue() const;

   /// Returns if an increment value was found in the string.
   /// @return  \c true if an increment value was found in the string.
   /// @since  0.2, 07.04.2016
   bool hasIncrement() const;

   /// Returns the range increment value, if one was set.
   /// @return  The range increment value, may be empty.
   /// @since  0.2, 07.04.2016
   int64_t incrementValue() const;

   /// Returns if an exclude expression was found in the string.
   /// @return  \c true if an exclude expression was found in the string.
   /// @since  0.2, 07.04.2016
   bool hasExcludeExpr() const;

   /// Returns the range exclude expression, if one was set
   /// @return  The range exclude expression, may be empty.
   /// @since  0.2, 07.04.2016
   const std::string& excludeExpression() const;

private:
   /// Indices to the match object:
   enum MatchIndex
   {
      miStartValue = 0x01,                //!< Single/range start value.
      miEndValue   = miStartValue << 1,   //!< Range end value.
      miIncrement  = miEndValue   << 1,   //!< Range increment value.
      miExclude    = miIncrement  << 1    //!< Range exclude expression.
   };

   /// Parses the string starting from #mNextPos, checks and evaluates the
   /// single values, ranges, steps etc.
   /// @return  \c true if the contents of the string are syntactically correct.
   /// @since  0.2, 07.04.2016
   bool parse();

   /// Helper function to read a number from the range string.
   /// @param[out]  value  Returns the value read from the string.
   /// @since  0.2, 07.04.2016
   void readNumber( int64_t& value);

   /// Copy of the range string that we parse.
   std::string             mRangeString;
   /// Whole matched expression.
   std::string             mMatchedExpression;
   /// Set of flags, which values/expressions were found in the range string.
   int                     mFound;
   /// Single/Range start value.
   int64_t                 mStartValue;
   /// Range end value.
   int64_t                 mEndValue;
   /// Range increment value.
   int64_t                 mIncrementValue;
   /// Range exclude value.
   std::string             mExcludeValue;
   /// The position in the string to parse.
   std::string::size_type  mNextPos;

}; // RangeExpression


// inlined methods
// ===============


inline const std::string& RangeExpression::matchedExpression() const
{
   return mMatchedExpression;
} // end RangeExpression::matchedExpression


inline int64_t RangeExpression::startValue() const
{
   return mStartValue;
} // end RangeExpression::startValue


inline bool RangeExpression::hasRangeEnd() const
{
   return mFound & miEndValue;
} // end RangeExpression::hasRangeEnd


inline int64_t RangeExpression::endValue() const
{
   return mEndValue;
} // end RangeExpression::endValue


inline bool RangeExpression::hasIncrement() const
{
   return mFound & miIncrement;
} // end RangeExpression::hasIncrement


inline int64_t RangeExpression::incrementValue() const
{
   return mIncrementValue;
} // end RangeExpression::incrementValue


inline bool RangeExpression::hasExcludeExpr() const
{
   return mFound & miExclude;
} // end RangeExpression::hasExcludeExpr


inline const std::string& RangeExpression::excludeExpression() const
{
   return mExcludeValue;
} // end RangeExpression::excludeExpression


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RANGE_EXPRESSION_HPP


// =========================  END OF range_expression.hpp  =========================

