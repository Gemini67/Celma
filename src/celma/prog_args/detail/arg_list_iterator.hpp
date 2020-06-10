
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
/// See documentation of class celma::prog_args::detail::ArgListIterator.


#ifndef CELMA_PROG_ARGS_DETAIL_ARG_LIST_ITERATOR_HPP
#define CELMA_PROG_ARGS_DETAIL_ARG_LIST_ITERATOR_HPP


#include <cstring>
#include <string>
#include <iterator>
#include <stdexcept>
#include "celma/common/pre_postfix.hpp"
#include "celma/common/reset_at_exit.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Iterator for a list of program arguments.<br>
/// The class does not know about mandatory or optional arguments, expected
/// arguments etc. It just parses the list of arguments and creates a normalised
/// sequence of argument parts: Single character arguments (e.g. -v or -vts),
/// word arguments (e.g. --verbose) and values (e.g. from -file mytest.txt,
/// --file mytest.txt or --file=mytest.txt).<br>
/// Use this class to iterate over the arguments and there implement checks
/// like mandatory arguments, value for argument etc.
/// @tparam  T  The type of the class where the argument list is stored.
/// @tparam  E  Storage type for the argument list elements.
/// @since  0.2, 09.04.2016
template< typename T, typename E> class ArgListIterator:
   public std::iterator< std::forward_iterator_tag, void*>
{
public:
   /// Constructor.
   /// @param[in]  src    The object that provides access to the argument list.
   /// @param[in]  asEnd  Set this flag when this iterator object should
   ///                    reference the end element.
   /// @since  0.2, 09.04.2016
   explicit ArgListIterator( const T& src, bool asEnd = false);

   ArgListIterator( const ArgListIterator&) = default;
   ~ArgListIterator() = default;
   ArgListIterator& operator =( const ArgListIterator&) = default;

   /// Equality comparison.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if the two objects reference the same base object
   ///          (type \c T) and point to the same element (position).
   /// @since  0.2, 09.04.2016
   bool operator ==( const ArgListIterator& other) const;

   /// Not-equal comparison.
   /// @param[in]  other  The other object to compare against.
   /// @return  Returns \c true if the two objects reference different base
   ///          objects or point to different elements.
   /// @since  0.2, 09.04.2016
   bool operator !=( const ArgListIterator& other) const;

   /// Call this function when, starting from the current argument/position,
   /// the remaining part of the argument may be treated as the value for the
   /// previous (i.e., at the moment still current) argument.
   /// @since  0.2, 09.04.2016
   void remArgStrAsVal();

   /// Returns the remaining arguments/values from the argument list as string,
   /// like they were entered on the command line.
   /// @param[in]  include_myself  If set, the current argument is also included
   ///                             in the result string.
   /// @return  The remaining arguments as string.
   /// @since  0.14.2, 12.05.2017
   std::string argsAsString( bool include_myself = true) const;

   /// Prefix increment operator.
   /// @return  This object.
   /// @since  0.2, 09.04.2016
   ArgListIterator& operator ++( std::prefix);

   /// Postfix increment operator.
   /// @return  Object that points the previous element.
   /// @since  0.2, 09.04.2016
   ArgListIterator operator ++( std::postfix);

   /// Dereference operator.
   /// @return  Pointer to the data element.
   /// @since  0.2, 09.04.2016
   const E* operator ->() const;

   /// Indirection operator.
   /// @return  Reference of the internal data element.
   /// @since  0.2, 09.04.2016
   const E& operator *() const;

private:
   /// Returns if the specified character is a special command line control
   /// character.
   /// @param[in]  argChar  The character to check.
   /// @return  \c true if the character is a special control character.
   /// @since  0.2, 09.04.2016
   static bool isCtrlChar( char argChar);

   /// Determines the next argument.
   /// @since  0.2, 09.04.2016
   void determineNextArg();

   /// Returns if the current argument was used alone, i.e. character argument
   /// may not have been combined with another.
   /// @return  \c true if this character argument was not combined with
   ///          another character argument, and for all other argument types.
   /// @since 0.14.2, 12.05.2017
   bool isSingleArg() const noexcept( false);

   /// The base object that provides access to the argument list.
   const T*  mpSource;
   /// Number of arguments.
   int       mArgC;
   /// List of arguments strings.
   char**    mpArgV;
   /// Current index of this iterator object.
   int       mArgIndex;
   /// Position of the single character arguments within the current argument
   /// string.
   size_t    mArgCharPos;
   /// Stores the current element data for external access.
   E         mCurrElement;
   /// Length of the current argument string.
   size_t    mCurrArgStringLen;
   /// Set when the token '--' was found in the argument list: Accept dashed
   /// values as simple values.
   bool      mAcceptDashedValue;

   /// Internal flag, set when a long argument followed by an equal sign and a
   /// value is found (--\<long_arg\>=\<value\>).<br>
   /// In this case, the argument is returned and this flag set so that the
   /// next call of the iterator returns the value.
   bool      mNextIsValue;
   /// If set, the operator++ may treat the remaining part of the current
   /// argument string as value.
   bool      mRemainingArgumentStringAsValue;

}; // ArgListIterator< T, E>


// inlined methods
// ===============


template< typename T, typename E>
   ArgListIterator< T, E>::ArgListIterator( const T& src, bool asEnd):
      mpSource( &src),
      mArgC( mpSource->argCount()),
      mpArgV( mpSource->argVector()),
      mArgIndex( -1),
      mArgCharPos( -1),
      mCurrElement(),
      mCurrArgStringLen( 0L),
      mAcceptDashedValue( false),
      mNextIsValue( false),
      mRemainingArgumentStringAsValue( false)
{

   if (asEnd || (mArgC == 1))
   {
      mArgIndex   = mArgC + 1;
      mArgCharPos = ::strlen( mpArgV[ mArgC - 1]) + 1;
   } else
   {
      mArgIndex         = 1;
      mArgCharPos       = 1;
      mCurrArgStringLen = ::strlen( mpArgV[ mArgIndex]);

      if (mpArgV[ mArgIndex][ 0] == '-')
      {
         if (mCurrArgStringLen == 1)
            throw std::runtime_error( "single dash in argument list");

         determineNextArg();
      } else
      {
         mCurrElement.setValue( mArgIndex, mpArgV[ mArgIndex]);
         ++mArgIndex;
         mArgCharPos = 0;
      } // end if
   } // end if

} // ArgListIterator< T, E>::ArgListIterator


template< typename T, typename E>
   bool ArgListIterator< T, E>::operator ==( const ArgListIterator& other) const
{
   return (mpSource == other.mpSource) && (mArgIndex == other.mArgIndex)
          && (mArgCharPos == other.mArgCharPos);
} // ArgListIterator< T, E>::operator ==


template< typename T, typename E>
   bool ArgListIterator< T, E>::operator !=( const ArgListIterator& other) const
{
   return !(*this == other);
} // ArgListIterator< T, E>::operator !=


template< typename T, typename E> void ArgListIterator< T, E>::remArgStrAsVal()
{
   mRemainingArgumentStringAsValue = true;
} // ArgListIterator< T, E>::remArgStrAsVal


template< typename T, typename E>
   std::string ArgListIterator< T, E>::argsAsString( bool include_myself) const
{
   if (!include_myself && !isSingleArg())
      throw std::runtime_error( "cannot build remaining arguments string "
                                "when included argument is not single argument");

   int          argi = include_myself ? mCurrElement.mArgIndex : mArgIndex;
   std::string  remaining( mpArgV[ argi++]);

   for (; argi < mArgC; ++argi)
   {
      remaining.append( " ").append( mpArgV[ argi]);
   } // end for

   return remaining;
} // ArgListIterator< T, E>::argsAsString


template< typename T, typename E>
   ArgListIterator< T, E>& ArgListIterator< T, E>::operator ++( std::prefix)
{
   const common::ResetAtExit< bool>  rae( mRemainingArgumentStringAsValue, false);

   if (mArgIndex >= mArgC)
   {
      // reached the end
      *this = ArgListIterator( *mpSource, true);
   } else if (mNextIsValue
              || (mRemainingArgumentStringAsValue && (mArgCharPos > 0)))
   {
      // reached the end of the argument string in the previous call,
      // and determined already that this must be a value (no dash in front)
      // or
      // within argument string: previous character was a single-character
      // argument that (may) accept values
      // treat the remaining argument string as value
      mCurrElement.setValue( mArgIndex, &mpArgV[ mArgIndex][ mArgCharPos]);
      ++mArgIndex;
      mArgCharPos  = 0;
      mNextIsValue = false;
   } else
   {
      mCurrArgStringLen = ::strlen( mpArgV[ mArgIndex]);
      if (mArgCharPos == 0)
      {
         if ((mCurrArgStringLen == 1) && isCtrlChar( mpArgV[ mArgIndex][ 0]))
         {
            mCurrElement.setControl( mArgIndex, 0, mpArgV[ mArgIndex][ 0]);
            ++mArgIndex;
            return *this;
         } // end if
         if ((mpArgV[ mArgIndex][ 0] != '-') || mAcceptDashedValue)
         {
            mCurrElement.setValue( mArgIndex, mpArgV[ mArgIndex]);
            ++mArgIndex;
            return *this;
         } // end if
         if (mCurrArgStringLen == 1)
            throw std::runtime_error( "single dash in argument list");
         mArgCharPos = 1;
      } // end if

      determineNextArg();
   } // end if

   return *this;
} // ArgListIterator< T, E>::operator ++


template< typename T, typename E>
   ArgListIterator< T, E> ArgListIterator< T, E>::operator ++( std::postfix)
{
   ArgListIterator  prev( *this);
   operator ++();
   return prev;
} // ArgListIterator< T, E>::operator ++


template< typename T, typename E>
   const E* ArgListIterator< T, E>::operator ->() const
{
   return &mCurrElement;
} // ArgListIterator< T, E>::operator ->


template< typename T, typename E>
   const E& ArgListIterator< T, E>::operator *() const
{
   return mCurrElement;
} // ArgListIterator< T, E>::operator *


template< typename T, typename E>
   void ArgListIterator< T, E>::determineNextArg()
{

   if (mpArgV[ mArgIndex][ mArgCharPos] == '-')
   {
      // double dash: long argument
      if (mArgCharPos + 1 == mCurrArgStringLen)
      {
         mAcceptDashedValue = true;
         ++mArgIndex;
         mArgCharPos = 0;
         operator ++();
         return;
      } // end if

      // two dashes followed by long name
      std::string  argName( &mpArgV[ mArgIndex][ mArgCharPos + 1]);
      const auto   equalPos = argName.find_first_of( '=');
      if (equalPos == std::string::npos)
      {
         mCurrElement.setArgString( mArgIndex, argName);
         ++mArgIndex;
         mArgCharPos = 0;
      } else
      {
         // long argument with =
         argName.erase( equalPos);
         mCurrElement.setArgString( mArgIndex, argName);
         mArgCharPos += equalPos + 2;
         mNextIsValue = true;
      } // end if
   } else if (mCurrArgStringLen == mArgCharPos + 1)
   {
      // one dash -> next is argument character
      mCurrElement.setArgChar( mArgIndex, mArgCharPos,
                               mpArgV[ mArgIndex][ mArgCharPos]);
      ++mArgIndex;
      mArgCharPos = 0;
   } else
   {
      // format: -<char>[<char>]
      mCurrElement.setArgChar( mArgIndex, mArgCharPos,
                               mpArgV[ mArgIndex][ mArgCharPos]);
      ++mArgCharPos;
   } // end if

} // ArgListIterator< T, E>::determineNextArg


template< typename T, typename E>
   bool ArgListIterator< T, E>::isCtrlChar( char argChar)
{
   return (argChar == '(') || (argChar == ')') || (argChar == '!');
} // ArgListIterator< T, E>::isCtrlChar


template< typename T, typename E>
   bool ArgListIterator< T, E>::isSingleArg() const noexcept( false)
{

   return (mCurrElement.mElementType == E::Type::singleCharArg)
      && (mCurrElement.mArgCharPos == 1)
      && (mpArgV[ mCurrElement.mArgIndex][ 2] == '\0');
} // ArgListIterator< T, E>::isSingleArg

   
} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARG_LIST_ITERATOR_HPP


// =====  END OF arg_list_iterator.hpp  =====

