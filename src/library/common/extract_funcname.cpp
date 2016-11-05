
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
/// See documentation of function celma::common::extractFuncname().


// module header file include
#include "celma/common/extract_funcname.hpp"


// project includes
#include "celma/common/find_sequence.hpp"


using std::string;


namespace celma { namespace common {



/// Extracts the function name without return type and parameters.
/// @param[in]  pretty_funcname  Function prototype as in the macro
///                              __PRETTY_FUNCTION__.
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
   else if ((pretty_funcname[ first_parenthesis + 1] == ')') &&
            ((first_parenthesis + 2 < pretty_funcname.length()) &&
             (pretty_funcname[ first_parenthesis + 2] == '(')))
      first_parenthesis += 2;

   // (anonymous namespace)::<funcname>
   if (pretty_funcname.substr( first_parenthesis + 1, 19) == "anonymous namespace")
   {
      auto const  first_char = first_parenthesis;
      first_parenthesis = pretty_funcname.find_first_of( '(', first_parenthesis + 20);
      return pretty_funcname.substr( first_char, first_parenthesis - first_char);
   } // end if

   auto const  operator_pos = pretty_funcname.find( "operator");
   auto const  start_search_back = (operator_pos != string::npos) ? operator_pos : first_parenthesis;
   
   // now we have the position of the parenthesis that follows the function name
   // search backwards to the first space
   auto  first_space = pretty_funcname.rfind( ' ', start_search_back) + 1;

   // e.g. Class& operator+=
   if ((pretty_funcname[ first_space] == '&') ||
       (pretty_funcname[ first_space] == '*'))
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

   // in between the space and the parenthesis we have our function name
   return pretty_funcname.substr( first_space, first_parenthesis - first_space);
} // extractFuncname



} // namespace common
} // namespace celma


// =======================  END OF extract_funcname.cpp  =======================

