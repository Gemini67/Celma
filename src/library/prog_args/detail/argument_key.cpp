
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
/// See documentation of class celma::prog_args::detail::ArgumentKey.


// module header file include
#include "celma/prog_args/detail/argument_key.hpp"


// C++ Standard Library includes
#include <ostream>
#include <sstream>
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {


namespace {



/// Removes at most two leading dashes from the string.
/// @param[in]  arg_spec  The string with a single argument specification.
/// @return  The string without leading dashes.
/// @since  0.2, 06.04.2016
string remove_dashes( string arg_spec)
{

   if (arg_spec[ 0] == '-')
      arg_spec.erase( 0, 1);
   if (arg_spec[ 0] == '-')
      arg_spec.erase( 0, 1);

   if (arg_spec[ 0] == '-')
      throw invalid_argument( "too many leading dashes in argument specification");

   return arg_spec;
} // end remove_dashes



} // namespace



/// Constructor, splits the specified string into short and/or long specifier
/// and checks for all kind of format errors, content errors etc.<br>
/// Dashes are silently ignored.
/// @param[in]  arg_spec  The string with the argument specifiers.
/// @since  0.2, 06.04.2016
ArgumentKey::ArgumentKey( const std::string& arg_spec):
   mChar( '\0'),
   mWord()
{

   if (arg_spec.length() == 0)
      throw invalid_argument( "argument specification may not be empty");
   if (arg_spec == ",")
      throw invalid_argument( "',' is not a valid argument specification");
   if (arg_spec.find( ' ') != string::npos)
      throw invalid_argument( "argument specification may not contain space(s)");

   const string::size_type  comma_pos = arg_spec.find( ',');

   if (comma_pos == string::npos)
   {
      const int  ignore_leading_dashes = static_cast< int>( arg_spec[ 0] == '-') +
                                         static_cast< int>( arg_spec[ 1] == '-');

      if (arg_spec[ ignore_leading_dashes] == '-')
         throw invalid_argument( "too many leading dashes in argument specification");

      // only one type of argument specification given
      if (arg_spec.length() - ignore_leading_dashes == 1)
         mChar = arg_spec[ ignore_leading_dashes];
      else
         mWord = arg_spec.substr( ignore_leading_dashes);
   } else
   {
      if (arg_spec.find( ',', comma_pos + 1) != string::npos)
         throw invalid_argument( "too many commas, only one allowed");

      const string  sub_begin( remove_dashes( arg_spec.substr( 0, comma_pos)));
      const string  sub_end(   remove_dashes( arg_spec.substr( comma_pos + 1)));

      if (sub_begin == sub_end)
         throw invalid_argument( "short and long argument may not be identical");
      if ((sub_begin.length() == 0) || (sub_end.length() == 0))
         throw invalid_argument( "second argument missing");
      if ((sub_begin.length() == 1) && (sub_end.length() == 1))
         throw invalid_argument( "two short arguments are not allowed");

      if (sub_begin.length() == 1)
      {
         mChar = sub_begin[ 0];
         mWord = sub_end;
      } else if (sub_end.length() == 1)
      {
         mChar = sub_end[ 0];
         mWord = sub_begin;
      } else
      {
         throw invalid_argument( "two long arguments are not allowed");
      } // end if
   } // end if

} // end ArgumentKey::ArgumentKey



/// Compares two argument keys if the short or long specifier are the same.
/// Mismatches are not detected by this function.
/// @param[in]  other  The other key object to compare against.
/// @return  \c true if the short or the long specifier are identical.
/// @since  0.2, 06.04.2016
bool ArgumentKey::operator ==( const ArgumentKey& other) const
{

   if ((mChar != '\0') && (other.mChar != '\0'))
      return mChar == other.mChar;

   if (!mWord.empty() && !other.mWord.empty())
      return mWord == other.mWord;

   // actually we could not really veryify if it is the same argument ...
   return false;
} // end ArgumentKey::operator ==



/// Checks if there is a mismatch: Short specifier matches but long don't or
/// vice versa.
/// @param[in]  other  The other key object to compare against.
/// @return  \c true if a mismatch was detected.
/// @since  0.2, 06.04.2016
bool ArgumentKey::mismatch( const ArgumentKey& other) const
{

   // two argument keys mismatch if either the short or long key match and the
   // other doesn't

   // both short and long argument specifiers must be set in both keys
   if ((mChar != '\0') && (other.mChar != '\0') &&
       !mWord.empty() && !other.mWord.empty())
   {
      return ((mChar == other.mChar) && (mWord != other.mWord)) ||
             ((mWord == other.mWord) && (mChar != other.mChar));
   } // end if

   return false;
} // end ArgumentKey::mismatch



/// Returns the key in string format.
/// @return  The key of this object in string format.
/// @since  0.2, 06.04.2016
string ArgumentKey::str() const
{

   ostringstream  oss;


   oss << *this;
   return oss.str();
} // end ArgumentKey::str



/// Prints the short and/or the long specifier of the key.<br>
/// The string is created from the data extracted in the constructor, i.e. it
/// may differ to this original string regarding the order of the arguments.
/// @param[out]  os  The stream to write into.
/// @param[in]   ak  The key object to print the data of.
/// @return  The stream as passed in.
/// @since  1.1, 09.03.2016
ostream& operator <<( ostream& os, const ArgumentKey& ak)
{

   if (ak.mChar != '\0')
   {
      os << ak.mChar;
      if (ak.mWord.length() > 0)
         os << "," << ak.mWord;
   } else
   {
      os << ak.mWord;
   } // end if

   return os;
} // end operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF argument_key.cpp  =========================

