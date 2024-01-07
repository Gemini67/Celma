
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::RangeExpression.


#pragma once


#include <cstdint>
#include <string>


namespace celma::common::detail {


/// Helper class to extract the different parts of a range expression.
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
   /// Delimiter between ranges and single values.
   static constexpr char  NextRangeSeparator = ',';
   /// The character that separates the two values of a range: A dash/minus/
   /// hyphen.
   static constexpr char  RangeSeparator = '-';
   /// The start character for an increment expression: Opening square bracket.
   static constexpr char  IncrementStart = '[';
   /// The end character for an increment expression: Closing square bracket.
   static constexpr char  IncrementEnd = ']';
   /// The start character for an exclude expression: Opening curly brace.
   static constexpr char  ExcludeStart = '{';
   /// The end character for an exclude expression: Closing curly brace.
   static constexpr char  ExcludeEnd = '}';

   /// Constructor.
   ///
   /// @since  0.2, 07.04.2016
   RangeExpression() = default;

   /// Parses the (first) range expression in the string.
   /// The string must begin with a valid range expression. Everything after
   /// the parts that could be identified is ignored.
   ///
   /// @param[in]  s  The string to parse.
   /// @throw
   ///    celma::common::CelmaRuntimeError if the string contains an invalid
   ///    charater.
   /// @since  0.2, 07.04.2016
   void parseString( const std::string& s) noexcept( false);

   /// Returns the full string that was matched.
   ///
   /// @return  The string that was matched.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& matchedExpression() const;

   /// Returns the single/range start value.
   ///
   /// @return  The start value.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] int64_t startValue() const;

   /// Returns if an end-value was found in the string.
   ///
   /// @return  \c true if an end-value was found in the string.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] bool hasRangeEnd() const;

   /// Returns the range end value, if one was set.
   ///
   /// @return  The range end value, may be empty.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] int64_t endValue() const;

   /// Returns if an increment value was found in the string.
   ///
   /// @return  \c true if an increment value was found in the string.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] bool hasIncrement() const;

   /// Returns the range increment value, if one was set.
   ///
   /// @return  The range increment value, may be empty.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] int64_t incrementValue() const;

   /// Returns if an exclude expression was found in the string.
   ///
   /// @return  \c true if an exclude expression was found in the string.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] bool hasExcludeExpr() const;

   /// Returns the range exclude expression, if one was set.
   ///
   /// @return  The range exclude expression, may be empty.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& excludeExpression() const;

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
   ///
   /// @return  \c true if the contents of the string are syntactically correct.
   /// @since  0.2, 07.04.2016
   bool parse();

   /// Helper function to read a number from the range string.
   ///
   /// @param[out]  value  Returns the value read from the string.
   /// @since  0.2, 07.04.2016
   void readNumber( int64_t& value);

   /// Copy of the range string that we parse.
   std::string             mRangeString;
   /// Whole matched expression.
   std::string             mMatchedExpression;
   /// Set of flags, which values/expressions were found in the range string.
   int                     mFound = 0;
   /// Single/Range start value.
   int64_t                 mStartValue = 0;
   /// Range end value.
   int64_t                 mEndValue = 0;
   /// Range increment value.
   int64_t                 mIncrementValue = 0;
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
} // RangeExpression::matchedExpression


inline int64_t RangeExpression::startValue() const
{
   return mStartValue;
} // RangeExpression::startValue


inline bool RangeExpression::hasRangeEnd() const
{
   return mFound & miEndValue;
} // RangeExpression::hasRangeEnd


inline int64_t RangeExpression::endValue() const
{
   return mEndValue;
} // RangeExpression::endValue


inline bool RangeExpression::hasIncrement() const
{
   return mFound & miIncrement;
} // RangeExpression::hasIncrement


inline int64_t RangeExpression::incrementValue() const
{
   return mIncrementValue;
} // RangeExpression::incrementValue


inline bool RangeExpression::hasExcludeExpr() const
{
   return mFound & miExclude;
} // RangeExpression::hasExcludeExpr


inline const std::string& RangeExpression::excludeExpression() const
{
   return mExcludeValue;
} // RangeExpression::excludeExpression


} // namespace celma::common::detail


// =====  END OF range_expression.hpp  =====

