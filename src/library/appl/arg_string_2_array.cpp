
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
/// See documentation of class celma::appl::ArgString2Array.


// module headerfile include
#include "celma/appl/arg_string_2_array.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstring>


// C++ Standard Library includes
#include <vector>


namespace celma::appl {


namespace {


/// Container type used to store the arguments: vector of strings.
using StringVec = std::vector< std::string>;


// functions prototypes
void splitString( StringVec& arguments, const std::string& argstring);
void copyArguments( int& argc, char* argv[], const StringVec& arguments);


} // namespace


/// Constructor, splits the string into separate arguments.<br>
/// The file name is automatically set in the first string in the array, even
/// if the argument string does not contain the program name.<br>
/// So, if you want to create an argument string that contains only a free
/// argument (not preceeded by an argument with one or two dashes), you need
/// to set a program name before it.
///
/// @param[in]  argstring
///    The argument string to split.
/// @param[in]  progname
///    Optional program name to set. If not set, 'programname' is set
///    as mpArgV[ 0].
/// @since  0.2, 05.0.4.2016
ArgString2Array::ArgString2Array( const std::string& argstring,
   const char* progname)
{

   StringVec  arguments;


   splitString( arguments, argstring);

   mpArgV = new char*[ arguments.size() + 2];
   if (progname == nullptr)
   {
      mpArgV[ 0] = new char[ 12];
      ::strcpy( mpArgV[ 0], "programname");
   } else
   {
      mpArgV[ 0] = new char[ ::strlen( progname) + 1];
      ::strcpy( mpArgV[ 0], progname);
   } // end if

   mArgC = 1;
   copyArguments( mArgC, mpArgV, arguments);

} // ArgString2Array::ArgString2Array



/// Constructor, splits the string into separate arguments.<br>
/// The program file name must be first word/argument in the string,
/// otherwise you should use the constructor with two parameters.
///
/// @param[in]  cmdLine  The argument string to split.
/// @since  0.2, 05.0.4.2016
ArgString2Array::ArgString2Array( const std::string& cmdLine)
{

   StringVec  arguments;


   splitString( arguments, cmdLine);

   mpArgV = new char*[ arguments.size() + 1];

   mArgC = 0;
   copyArguments( mArgC, mpArgV, arguments);

} // ArgString2Array::ArgString2Array



/// Destructor, frees dynamically allocated memory.
/// @since  0.2, 05.0.4.2016
ArgString2Array::~ArgString2Array()
{

   for (int i = 0; i < mArgC; ++i)
      delete [] mpArgV[ i];

   delete [] mpArgV;

} // ArgString2Array::~ArgString2Array



/// Move constructor.
///
/// @param[in]  other
///    The other object to move the data from.
/// @since  1.27.0, 29.05.2019
ArgString2Array::ArgString2Array( ArgString2Array&& other):
   mArgC( other.mArgC),
   mpArgV( other.mpArgV)
{

   other.mpArgV = nullptr;
   other.mArgC  = -1;

} // ArgString2Array::ArgString2Array



/// Returns an \c ArgString2Array object with the arguments from the given
/// command line.
///
/// @param[in]  cmd_line
///    The arguments from the command line to split into an argument array.
/// @return  ArgString2Array object with the argument arrays.
/// @since  1.27.0, 29.05.2019
ArgString2Array make_arg_array( const std::string& cmd_line)
{

   return ArgString2Array( cmd_line);
} // make_arg_array


/// Returns an \c ArgString2Array object with the arguments from the given
/// command line.
///
/// @param[in]  cmd_line
///    The arguments from the command line to split into an argument array.
/// @param[in]prog_name
///    The (path and) name of the program file.
/// @return  ArgString2Array object with the argument arrays.
/// @since  1.27.0, 29.05.2019
ArgString2Array make_arg_array( const std::string& cmd_line,
   const char* prog_name)
{

   return ArgString2Array( cmd_line, prog_name);
} // make_arg_array



namespace {



/// Splits the complete argument string into list of arguments.
///
/// @param[out]  arguments
///    Returns the arguments as separate strings.
/// @param[in]   argstring
///    The complete argument argument string.
/// @since  0.2, 05.0.4.2016
void splitString( StringVec& arguments, const std::string& argstring)
{

   std::string  currWord;
   char         usedQuoteChar = '-';
   bool         inQuote = false;
   bool         gotBackslash = false;


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
         if (!currWord.empty())
         {
            arguments.push_back( currWord);
            currWord.clear();
         } // end if
      } else
      {
         currWord.append( 1, next_char);
      } // end if
   } // end for

   if (currWord.length() > 0)
      arguments.push_back( currWord);

} // splitString



/// Copies all the arguments (and values) from the vector into the array of
/// argument string.
///
/// @param[in,out]  argc
///    Number of arguments already stored in \a argv, at the end returns the
///    number of arguments finally in \a argv.
/// @param[out]     argv
///    List of arguments/values.
/// @param[in]      arguments
///    The separated list of arguments and values to store in \a argv.
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

} // copyArguments



} // namespace


} // namespace celma::appl


// =====  END OF arg_string_2_array.cpp  =====
