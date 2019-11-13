
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
/// See documentation of function celma::common::extractFuncname().


// module header file include
#include "celma/common/extract_funcname.hpp"


// project includes
#include "celma/common/find_sequence.hpp"

#include <iostream>

using std::string;


namespace celma { namespace common {



/// Extracts the function name without return type and parameters.
///
/// @param[in]  pretty_funcname  Function prototype as in the macro
///                              \c __PRETTY_FUNCTION__.
/// @since  0.6, 04.11.2016  (interface changed, simplified algorithm)
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
            && ((first_parenthesis + 2 < pretty_funcname.length())
                && (pretty_funcname[ first_parenthesis + 2] == '(')))
      first_parenthesis += 2;

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

   auto const  operator_pos = pretty_funcname.find( "operator");
   auto const  start_search_back = (operator_pos != string::npos) ? operator_pos : first_parenthesis;
   
   // now we have the position of the parenthesis that follows the function name
   // search backwards to the first space
   auto  first_space = pretty_funcname.rfind( ' ', start_search_back) + 1;

   // the following block for handling of special return values and/or templates
   // seems not to be needed (anymore)
#if NOT_NEEDED
   // e.g. Class& operator+=
   if ((pretty_funcname[ first_space] == '&')
       || (pretty_funcname[ first_space] == '*'))
      ++first_space;

   // template class
   if (pretty_funcname[ first_space] == '>')
   {
      auto  first_less_iter = find_sequence_start( std::begin( pretty_funcname) + first_space,
                                                   std::begin( pretty_funcname), '<');
      auto  first_less = first_less_iter - std::begin( pretty_funcname);

      first_space = (first_less > 0) ? pretty_funcname.rfind( ' ', first_less) : first_less;
      if (first_space == string::npos)
         first_space = 0;
      else
         ++first_space;
      
      return pretty_funcname.substr( first_space, first_parenthesis - first_space);
   } // end if
#endif

   // in between the space and the parenthesis we have our function name
   return pretty_funcname.substr( first_space, first_parenthesis - first_space);
} // extractFuncname



} // namespace common
} // namespace celma


// =====  END OF extract_funcname.cpp  =====

