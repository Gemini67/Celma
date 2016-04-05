
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
/// See documentation of class celma::common::ArgString2Array.


// module header file include
#include "celma/common/arg_string_2_array.hpp"


// UNIX/C lib includes
#include <unistd.h>
#include <cstring>


// C++ Standard Library includes
#include <string>
#include <vector>


using namespace std;


namespace celma { namespace common {


namespace {


/// Container type used to store the arguments: vector of strings.
typedef vector< string>  StringVec;


// functions prototypes
void splitString( StringVec& arguments, const string& argstring);
void copyArguments( int& argc, char* argv[], const StringVec& arguments);


} // namespace


/// Constructor, splits the string into separate arguments.<br>
/// The file name is automatically set in the first string in the array, even
/// if the argument string does not contain the program name.<br>
/// So, if you want to create an argument string that contains only a free
/// argument (not preceeded by an argument with one or two dashes), you need
/// to set a program name before it.
/// @param[in]  argstring  The argument string to split.
/// @param[in]  progname   Optional program name to set. If not set,
///                        'programname' is set as mpArgv[ 0].
/// @since  0.2, 05.0.4.2016
ArgString2Array::ArgString2Array( const string& argstring, const char* progname):
   mArgc( -1),
   mpArgv( nullptr)
{

   StringVec  arguments;


   splitString( arguments, argstring);

   mpArgv = new char*[ arguments.size() + 2];
   if (progname == nullptr)
   {
      mpArgv[ 0] = new char[ 12];
      ::strcpy( mpArgv[ 0], "programname");
   } else
   {
      mpArgv[ 0] = new char[ ::strlen( progname) + 1];
      ::strcpy( mpArgv[ 0], progname);
   } // end if

   mArgc = 1;
   copyArguments( mArgc, mpArgv, arguments);

} // end ArgString2Array::ArgString2Array



/// Constructor, splits the string into separate arguments.<br>
/// The program file name must be first word/argument in the string,
/// otherwise you should use the constructor with two parameters.
/// @param[in]  cmdLine  The argument string to split.
/// @since  0.2, 05.0.4.2016
ArgString2Array::ArgString2Array( const string& cmdLine):
   mArgc( -1),
   mpArgv( nullptr)
{

   StringVec  arguments;


   splitString( arguments, cmdLine);

   mpArgv = new char*[ arguments.size() + 1];

   mArgc = 0;
   copyArguments( mArgc, mpArgv, arguments);

} // end ArgString2Array::ArgString2Array



/// Destructor, frees dynamically allocated memory.
/// @since  0.2, 05.0.4.2016
ArgString2Array::~ArgString2Array()
{

   for (int i = 0; i < mArgc; ++i)
      delete [] mpArgv[ i];

   delete [] mpArgv;

} // end ArgString2Array::~ArgString2Array



namespace {



/// Splits the complete argument string into list of arguments.
/// @param[out]  arguments  Returns the arguments as separate strings.
/// @param[in]   argstring  The complete argument argument string.
/// @since  0.2, 05.0.4.2016
void splitString( StringVec& arguments, const string& argstring)
{

   string  currWord;
   char    usedQuoteChar = '-';
   bool    inQuote = false;
   bool    gotBackslash = false;


   // priority for parsing:
   // - backslashes: had a backslash before or a new backslash?
   // - in a quoted string?
   // - new quote, single or double?
   // - space
   // - all the rest
   for (auto next_char : argstring)
   {
      if (gotBackslash)
      {
         currWord.append( 1, next_char);
         gotBackslash = false;
      } else if (next_char == '\\')
      {
         gotBackslash = true;
      } else if (inQuote)
      {
         if (next_char == usedQuoteChar)
         {
            usedQuoteChar = '-';
            inQuote = false;
         } else
         {
            currWord.append( 1, next_char);
         } // end if
      } else if ((next_char == '\'') || (next_char == '"'))
      {
         inQuote = true;
         usedQuoteChar = next_char;
      } else if (next_char == ' ')
      {
         arguments.push_back( currWord);
         currWord.clear();
      } else
      {
         currWord.append( 1, next_char);
      } // end if
   } // end for

   if (currWord.length() > 0)
      arguments.push_back( currWord);

} // end splitString



/// Copies all the arguments (and values) from the vector into the array of
/// argument string.
/// @param[in,out]  argc       Number of arguments already stored in \a argv,
///                            at the end returns the number of arguments
///                            finally in \a argv.
/// @param[out]     argv       List of arguments/values.
/// @param[in]      arguments  The separated list of arguments and values to
///                            store in \a argv.
/// @since  0.2, 05.04.2016
void copyArguments( int& argc, char* argv[], const StringVec& arguments)
{

   for (auto const& next_arg : arguments)
   {
      argv[ argc] = new char[ next_arg.length() + 1];
      ::strcpy( argv[ argc], next_arg.c_str());
      ++argc;
   } // end for

   argv[ argc] = nullptr;

} // end copyArguments



} // namespace


} // namespace common
} // namespace celma


// =========================  END OF arg_string_2_array.cpp  =========================

