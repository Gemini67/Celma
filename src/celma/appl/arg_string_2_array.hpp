
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
/// See documentation of class celma::appl::ArgString2Array.


#ifndef CELMA_APPL_ARG_STRING_2_ARRAY_HPP
#define CELMA_APPL_ARG_STRING_2_ARRAY_HPP


#include <string>


namespace celma { namespace appl {


/// Helper class to convert an argument string (e.g. '-n PROC1 -v -d /tmp') into
/// an array of string pointers with the separate arguments.<br>
/// Afterwards, the string array can be passed to a function that expects
/// parameters in the same format as a main() function.<br>
/// This function does similar processing regarding multi-word strings: Quotes
/// are removed, but the text within the quotes is passed as one value.
///
/// @since  1.11.0, 16.08.2018  (renamed member variables)
/// @since  0.2, 05.04.2016
class ArgString2Array
{
public:
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
   ArgString2Array( const std::string& argstring, const char* progname);

   /// Constructor, splits the string into separate arguments.<br>
   /// The program file name must be first word/argument in the string,
   /// otherwise you should use the constructor with two parameters.
   ///
   /// @param[in]  cmdLine  The argument string to split.
   /// @since  0.2, 05.0.4.2016
   explicit ArgString2Array( const std::string& cmdLine);

   /// Destructor, frees dynamically allocated memory.
   /// @since  0.2, 05.0.4.2016
   ~ArgString2Array();

   /// Don't copy.
   /// @since  0.2, 05.0.4.2016
   ArgString2Array( const ArgString2Array&) = delete;

   /// Move constructor.
   ///
   /// @param[in]  other
   ///    The other object to move the data from.
   /// @since  x.y.z, 29.05.2019
   ArgString2Array( ArgString2Array&& other);

   /// The number of arguments in the string array.
   int     mArgC = -1;
   /// The string array with the separated arguments.<br>
   /// The first argument (mpArgV[ 0]) contains the program name.
   char**  mpArgV = nullptr;

}; // ArgString2Array


/// Returns an \c ArgString2Array object with the arguments from the given
/// command line.
///
/// @param[in]  cmd_line
///    The arguments from the command line to split into an argument array.
/// @return  ArgString2Array object with the argument arrays.
/// @since  x.y.z, 29.05.2019
ArgString2Array make_arg_array( const std::string& cmd_line);


/// Returns an \c ArgString2Array object with the arguments from the given
/// command line.
///
/// @param[in]  cmd_line
///    The arguments from the command line to split into an argument array.
/// @param[in]prog_name
///    The (path and) name of the program file.
/// @return  ArgString2Array object with the argument arrays.
/// @since  x.y.z, 29.05.2019
ArgString2Array make_arg_array( const std::string& cmd_line,
   const char* prog_name);


} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_ARG_STRING_2_ARRAY_HPP


// =====  END OF arg_string_2_array.hpp  =====

