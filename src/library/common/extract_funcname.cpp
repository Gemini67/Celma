
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
/// See documentation of function celma::common::extractFuncname().


// module header file include
#include "celma/common/extract_funcname.hpp"


// project includes
#include "celma/common/find_sequence.hpp"

#include <iostream>

using std::string;


namespace celma { namespace common {



/// Extracts the function/method name without return type or parameters.
///
/// @param[in]  pretty_funcname
///    Function prototype as in the macro \c __PRETTY_FUNCTION__.
/// @since  1.36.0, 12.04.2020
///    (adapted to work with clang++ too)
/// @since  0.6, 04.11.2016
///    (interface changed, simplified algorithm)
/// @since  0.2, 07.04.2016
string extractFuncname( const string& pretty_funcname)
{

   auto  first_parenthesis = pretty_funcname.find_first_of( '(');

   // function/method that returns a pointer to a function starts
   // with '<type> (* <funcname>(...'
   // so, if we have '(*', search for the next parenthesis
   if (pretty_funcname[ first_parenthesis + 1] == '*')
      first_parenthesis = pretty_funcname.find_first_of( '(', first_parenthesis + 1);

   // operator()(....
   else if ((pretty_funcname[ first_parenthesis + 1] == ')')
            && (first_parenthesis + 2 < pretty_funcname.length())
            && (pretty_funcname[ first_parenthesis + 2] == '('))
      first_parenthesis += 2;

#ifdef __clang__
   // (anonymous namespace)::<funcname>
   if (pretty_funcname.substr( first_parenthesis + 1, 19) == "anonymous namespace")
   {
      auto const  first_char = first_parenthesis + 23;
      first_parenthesis = pretty_funcname.find_first_of( '(', first_char);
      return pretty_funcname.substr( first_char, first_parenthesis - first_char);
   } // end if
#else
   // {anonymous namespace}::<funcname>(
   // or {anonymous}::<funcname>(
   auto const curly_brace_before_paren = pretty_funcname.find_first_of( '{');
   if ((curly_brace_before_paren != string::npos)
       && (curly_brace_before_paren < first_parenthesis))
   {
      auto const end_curly_brace = pretty_funcname.find_first_of( '}',
         curly_brace_before_paren);
      return pretty_funcname.substr( end_curly_brace + 3,
         first_parenthesis - end_curly_brace - 3);
   } // end if

#endif

   auto const  operator_pos = pretty_funcname.find( "operator");
   auto const  template_start_pos = pretty_funcname.find( "<");
   auto const  start_search_back = (operator_pos != string::npos)
     ? operator_pos
     : (template_start_pos != string::npos) ? template_start_pos
       : first_parenthesis;
   
   // now we have the position of the parenthesis that follows the function name
   // search backwards to the first space
   auto  first_space = pretty_funcname.rfind( ' ', start_search_back) + 1;

#ifdef __clang__
   // used for clang ...
   if ((pretty_funcname[ first_space] == '&')
       || (pretty_funcname[ first_space] == '*'))
      ++first_space;
#endif

   // in between the space and the parenthesis we have our function name
   return pretty_funcname.substr( first_space, first_parenthesis - first_space);
} // extractFuncname



} // namespace common
} // namespace celma


// =====  END OF extract_funcname.cpp  =====

