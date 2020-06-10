
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::TokenizerBase.


#ifndef CELMA_COMMON_TOKENIZER_BASE_HPP
#define CELMA_COMMON_TOKENIZER_BASE_HPP


#include <string>
#include <boost/tokenizer.hpp>
#include "celma/common/counting_iterator.hpp"


namespace celma { namespace common {


/// Helper class to easily set up a string tokenizer for various separators.
/// Internally, the Boost.Tokenizer is used.
///
/// @tparam  T  The type of the separator to use.
/// @since  0.2, 04.04.2016
template< typename T> class TokenizerBase: public ICountResult
{
public:
   /// Type of the tokenizer.
   using BoostTokenizer = typename boost::tokenizer< T>;
   /// Type of the iterator.
   using iterator = typename BoostTokenizer::iterator;

   friend class CountingIterator< typename BoostTokenizer::iterator>;

   /// Constructor. Empty tokens are ignored.
   /// @param[in]  s          The string to split.
   /// @param[in]  separator  The separator token.
   /// @since  0.2, 04.04.2016
   TokenizerBase( const std::string& s, T separator);

   /// Default destructor is just fine.
   /// @since  0.2, 05.04.2016
   ~TokenizerBase() override = default;

   /// Returns an iterator that points to the first token.
   /// @return  Iterator that points to the first token.
   /// @since  0.2, 04.04.2016
   iterator begin();

   /// Returns an iterator that points behind the last token.
   /// @return  Iterator that points behind the last token.
   /// @since  0.2, 04.04.2016
   iterator end();

   /// Type of the counting iterator.
   using counting_iterator = CountingIterator< typename BoostTokenizer::iterator>;

   /// Returns a counting iterator that points to the first token.
   /// @return  Counting iterator that points to the first token.
   /// @since  0.2, 04.04.2016
   counting_iterator begin_counting();

   /// Returns a counting iterator that points behind the last token.
   /// @return  Counting iterator that points behind the last token.
   /// @since  0.2, 04.04.2016
   counting_iterator end_counting();

   /// Returns the number of tokens that were found when the iterating over the
   /// results is finished.
   /// @return  Number of tokens found in the string.
   /// @since  0.2, 04.04.2016
   int numTokens() const;

private:
   /// Don't copy.
   /// @since  0.2, 05.04.2016
   TokenizerBase( const TokenizerBase&) = delete;

   /// Don't assign.
   /// @since  0.2, 05.04.2016
   TokenizerBase& operator =( const TokenizerBase&) = delete;

   /// Sets the number of tokens found.
   /// @param[in]  theCount  The number of tokens that were found.
   /// @since  0.2, 04.04.2016
   void setCount( int theCount) override;

   /// Copy of the string needed to make sure that the string persists until
   /// the tokenisation process is finished, even when a a char array is
   /// directly passed as parameter.
   const std::string  mStringCopy;
   /// The tokenizer.
   BoostTokenizer     mTokenizer;
   /// The number of tokens found when iterating over the results.
   int                mNumTokens;

}; // TokenizerBase< T>


// inlined methods
// ===============


template< typename T> TokenizerBase< T>::TokenizerBase( const std::string& s,
                                                        T separator):
   ICountResult(),
   mStringCopy( s),
   mTokenizer( mStringCopy, separator),
   mNumTokens( 0)
{
} // TokenizerBase< T>::TokenizerBase


template< typename T> typename TokenizerBase< T>::iterator TokenizerBase< T>::begin()
{
   return mTokenizer.begin();
} // TokenizerBase< T>::begin


template< typename T> typename TokenizerBase< T>::iterator TokenizerBase< T>::end()
{
   return mTokenizer.end();
} // TokenizerBase< T>::end


template< typename T> typename TokenizerBase< T>::counting_iterator TokenizerBase< T>::begin_counting()
{
   counting_iterator  ci( this, mTokenizer.begin());
   return ci;
} // TokenizerBase< T>::begin_counting


template< typename T> typename TokenizerBase< T>::counting_iterator TokenizerBase< T>::end_counting()
{
   counting_iterator  ci( this, mTokenizer.end());
   return ci;
} // TokenizerBase< T>::end_counting


template< typename T> int TokenizerBase< T>::numTokens() const
{
   return mNumTokens;
} // TokenizerBase< T>::numTokens


template< typename T> void TokenizerBase< T>::setCount( int theCount)
{
   mNumTokens = theCount;
} // TokenizerBase< T>::setCount


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TOKENIZER_BASE_HPP


// =====  END OF tokenizer_base.hpp  =====

