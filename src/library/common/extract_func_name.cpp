
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
/// See documentation of function celma::common::extractFuncName().


// module header file include
#include "celma/common/extract_func_name.hpp"


using std::string;


namespace celma { namespace common {



/// Extracts the function name without return type and parameters.
/// @param[out]  funcNameStripped  Returns the pure function name.
/// @param[in]   prettyFuncName    Function prototype as in the macro
///                                __PRETTY_function__.
/// @since  0.2, 07.04.2016
void extractFuncName( std::string& funcNameStripped,
                      const std::string& prettyFuncName)
{

   auto  openingBracket = prettyFuncName.find_first_of( '(');


   if ((prettyFuncName[ openingBracket + 1] == ')') &&
       (prettyFuncName[ openingBracket + 2] == '('))
   {
      openingBracket += 2;
   } // end if

   const string  beforeBracket( prettyFuncName.substr( 0, openingBracket));
   const auto    lastSpace = beforeBracket.rfind( " ") + 1;

   if (lastSpace == string::npos)
   {
      // simple functions or methods
      funcNameStripped = beforeBracket;
   } else
   {
      // operators ?
      const auto  colonColon = beforeBracket.rfind( "::");
      if (colonColon == string::npos)
      {
         funcNameStripped = beforeBracket.substr( lastSpace, string::npos);
      } else
      {
         // handle unnamed namespaces
         if (((colonColon > 9) &&
              (beforeBracket.substr( colonColon - 9, 9) == "<unnamed>")) ||
             ((colonColon > 21) &&
              (beforeBracket.substr( colonColon - 22, 22) == "(anonymous namespace)")))
         {
            funcNameStripped = beforeBracket.substr( colonColon + 2, string::npos);
         } else if (beforeBracket.substr( colonColon + 2, 8) == "operator")
         {
            // <return-type> <classname>::operator<op>()   or
            // <classname>::operator<op>()
            const auto  first_space = beforeBracket.find_first_of( ' ');
            if (first_space < colonColon)
               funcNameStripped = beforeBracket.substr( first_space + 1, string::npos);
            else
               funcNameStripped = beforeBracket;
         } else if (colonColon < lastSpace)
         {
            funcNameStripped = beforeBracket.substr( lastSpace, string::npos);
         } else
         {
            funcNameStripped = beforeBracket.substr( lastSpace, string::npos);
         } // end if
      } // end if
   } // end if

} // end common::extractFuncName



} // namespace common
} // namespace celma


// ======================  END OF extract_func_name.cpp  ======================

