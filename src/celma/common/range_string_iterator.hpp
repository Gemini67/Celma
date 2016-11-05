
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
/// See documentation of template celma::common::RangeStringIterator.


#ifndef CELMA_COMMON_RANGE_STRING_ITERATOR_HPP
#define CELMA_COMMON_RANGE_STRING_ITERATOR_HPP


#include <iterator>
#include <memory>
#include <stdexcept>
#include "celma/common/pre_postfix.hpp"
#include "celma/common/range_expression.hpp"
#include "celma/common/range_generator.hpp"


namespace celma { namespace common {


/// @tparam  T   The object with the range expression: An std::string.
/// @tparam  TF  The type of the values to generate.
/// Range string iterator, returning the next value computed from the specified
/// range.
/// @since  0.2, 07.04.2016
template< typename T, typename TF>
   class RangeStringIterator: public std::iterator< std::forward_iterator_tag,
                                                    void*>
{
public:
   /// End-of-range constructor.
   /// @since  0.2, 07.04.2016
   RangeStringIterator();

   /// Constructor.
   /// @param[in]  src  The object with the range expression to handle.
   /// @since  0.2, 07.04.2016
   explicit RangeStringIterator( const T& src);

   /// Copy constructor. Needed because of internal \c auto_ptr.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  0.2, 07.04.2016
   RangeStringIterator( const RangeStringIterator& other);

   /// Prefix increment operator.
   /// @return  The incremented iterator.
   /// @since  0.2, 07.04.2016
   RangeStringIterator& operator ++( std::prefix);

   /// Postfix increment operator.
   /// @return  An iterator object with the previous value.
   /// @since  0.2, 07.04.2016
   RangeStringIterator operator ++( std::postfix);

   /// Returns if the two iterators point to the same position.<br>
   /// Not a really foolproof check for equality, since the position is
   /// updated only after a sub-expression is processed. If a more meaningful
   /// test for equality would be needed, the current value of the iterator
   /// could be checked too.
   /// @param[in]  other  The other iterator object to compare against.
   /// @return  \c true if the two iterators point to the same position.
   /// @since  0.2, 07.04.2016
   bool operator ==( const RangeStringIterator& other) const;

   /// Returns if the two iterators point to different possitions.
   /// @param[in]  other  The other iterator object to compare against.
   /// @return  \c true if the two iterators point to different positions.
   /// @since  0.2, 07.04.2016
   bool operator !=( const RangeStringIterator& other) const;

   /// Instead of de-referencing the iterator: Use a typecast to the field/
   /// value type to get the current value.
   /// @return  The current value.
   /// @since  0.2, 07.04.2016
   operator TF() const;

private:
   /// The type of the range (value) generator used internally.
   typedef RangeGenerator< int>  Ranger;

   /// Nice little function that creates the range generator object for the
   /// current range expression.
   /// @param[in]  re  The range expression to create the generator for.
   /// @return  Pointer to the newly created range generator object.
   /// @since  0.2, 07.04.2016
   Ranger* createRanger( const RangeExpression& re);

   /// The string to parse.
   const T                 mSource;
   /// Start position of the current expression in the string, set to
   /// \c std::string::npos when the complete expression was handled.
   std::string::size_type  mPos;
   /// The current expression.
   RangeExpression         mMainExpression;
   /// Value generator for the current range.
   std::auto_ptr< Ranger>  mpRanger;
   /// The current value created by the range (value) generator.
   TF                      mCurrentValue;

}; // RangeStringIterator< T, TF>


// inlined methods
// ===============


template< typename T, typename TF>
   RangeStringIterator< T, TF>::RangeStringIterator():
      mSource(),
      mPos( std::string::npos),
      mMainExpression(),
      mpRanger(),
      mCurrentValue()
{
} // end RangeStringIterator< T, TF>::RangeStringIterator


template< typename T, typename TF>
   RangeStringIterator< T, TF>::RangeStringIterator( const T& src):
      mSource( src),
      mPos( 0),
      mMainExpression(),
      mpRanger(),
      mCurrentValue()
{
   mMainExpression.parseString( mSource);
   if (mMainExpression.matchedExpression().length() == 0)
      throw std::runtime_error( "no valid expression found in string");
   mpRanger.reset( createRanger( mMainExpression));
   mCurrentValue = static_cast< TF>( *mpRanger);
} // end RangeStringIterator< T, TF>::RangeStringIterator


template< typename T, typename TF>
   RangeStringIterator< T, TF>::RangeStringIterator( const RangeStringIterator& other):
      mSource( other.mSource),
      mPos( other.mPos),
      mMainExpression(),
      mpRanger(),
      mCurrentValue( other.mCurrentValue)
{
   if (other.mpRanger.get() != nullptr)
      mpRanger.reset( new Ranger( *other.mpRanger.get()));
} // end RangeStringIterator< T, TF>::RangeStringIterator


template< typename T, typename TF>
   RangeStringIterator< T, TF>& RangeStringIterator< T, TF>::operator ++( std::prefix)
{
   if (mPos == std::string::npos)
      throw std::runtime_error( "attempt to increment after end-of-range");

   ++(*mpRanger);
   if (*mpRanger == mpRanger->end())
   {
      mPos += mMainExpression.matchedExpression().length();
      if (mPos >= mSource.length())
      {
         // end reached
         mPos = std::string::npos;
         mpRanger.reset();
         mCurrentValue = TF();
         return *this;
      } // end if

      if (mSource[ mPos] != ',')
         throw std::runtime_error( "invalid character in range string");

      mPos++;
      mMainExpression.parseString( mSource.substr( mPos));
      
      if (mMainExpression.matchedExpression().length() == 0)
         throw std::runtime_error( "invalid expression in range string");

      mpRanger.reset( createRanger( mMainExpression));
   } // end if

   mCurrentValue = static_cast< TF>( *mpRanger);
   return *this;
} // end RangeStringIterator< T, TF>::operator ++


template< typename T, typename TF>
   RangeStringIterator< T, TF> RangeStringIterator< T, TF>::operator ++( std::postfix)
{
   RangeStringIterator  result( *this);

   operator ++();

   return *this;
} // end RangeStringIterator< T, TF>::operator ++


template< typename T, typename TF>
   bool RangeStringIterator< T, TF>::operator ==( const RangeStringIterator& other) const
{
   return mPos == other.mPos;
} // end RangeStringIterator< T, TF>::operator ==


template< typename T, typename TF>
   bool RangeStringIterator< T, TF>::operator !=( const RangeStringIterator& other) const
{
   return mPos != other.mPos;
} // end RangeStringIterator< T, TF>::operator !=


template< typename T, typename TF>
   RangeStringIterator< T, TF>::operator TF() const
{
   return mCurrentValue;
} // end RangeStringIterator< T, TF>::operator TF


template< typename T, typename TF>
   typename RangeStringIterator< T, TF>::Ranger*
      RangeStringIterator< T, TF>::createRanger( const RangeExpression& re)
{
   if (!re.hasRangeEnd())
      // single value
      return new Ranger( static_cast< TF>( re.startValue()));

   Ranger*  newRanger = nullptr;

   if (re.hasIncrement())
      // range with increment
      newRanger = new Ranger( static_cast< TF>( re.startValue()),
                              static_cast< TF>( re.endValue()),
                              static_cast< TF>( re.incrementValue()));
   else
      // range without increment
      newRanger = new Ranger( static_cast< TF>( re.startValue()),
                              static_cast< TF>( re.endValue()));

   if (re.hasExcludeExpr())
   {
      // an exclude expression can be a full-fledged expression string itself
      // therefore we need a RangeStringIter (myself :-) to evaluate it
      // this means that an exclude expression could even include an
      // exclude expression (which includes the values again )...
      // since we are parsing a string, the danger of endless recursion is
      // small and we don't check for it
      for (RangeStringIterator< T, TF> it( re.excludeExpression()), end;
           it != end; ++it)
      {
         newRanger->excludeValue( static_cast< TF>( it));
      } // end for
   } // end if

   return newRanger;
} // end RangeStringIterator< T, TF>::createRanger


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RANGE_STRING_ITERATOR_HPP


// ====================  END OF range_string_iterator.hpp  ====================

