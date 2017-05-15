
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ArgListElement.


// module header file include
#include "celma/prog_args/detail/arg_list_element.hpp"


// C++ Standard Library includes
#include <iostream>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @since  0.2, 09.04.2016
ArgListElement::ArgListElement():
   mArgIndex( -1),
   mArgCharPos( -1),
   mElementType( ElementType::invalid),
   mArgChar( '-'),
   mArgString(),
   mValue()
{
} // ArgListElement::ArgListElement



/// Stores the data of a single argument character.
/// @param[in]  argi     The argument string index.
/// @param[in]  argp     The position of the argument character in the string.
/// @param[in]  argChar  The argument character.
/// @since  0.2, 09.04.2016
void ArgListElement::setArgChar( int argi, int argp, char argChar)
{

   mArgIndex    = argi;
   mArgCharPos  = argp;
   mElementType = ElementType::singleCharArg;
   mArgChar     = argChar;

   mArgString.clear();
   mValue.clear();

} // ArgListElement::setArgChar



/// Stores the data of a long argument.
/// @param[in]  argi     The argument string index.
/// @param[in]  argName  The long argument.
/// @since  0.2, 09.04.2016
void ArgListElement::setArgString( int argi, const string& argName)
{

   mArgIndex    = argi;
   mArgCharPos  = -1;
   mElementType = ElementType::stringArg;
   mArgChar     = '-';
   mArgString   = argName;

   mValue.clear();

} // ArgListElement::setArgString



/// Stores a value.
/// @param[in]  argi   The argument string index.
/// @param[in]  value  The value (== the argument string).
/// @since  0.2, 09.04.2016
void ArgListElement::setValue( int argi, const string& value)
{

   mArgIndex    = argi;
   mArgCharPos  = -1;
   mElementType = ElementType::value;
   mArgChar     = '-';
   mValue       = value;

   mArgString.clear();

} // ArgListElement::setValue



/// Stores the data of a control character.
/// @param[in]  argi      The argument string index.
/// @param[in]  argp      The position of the control character in the string.
/// @param[in]  ctrlChar  The control character.
/// @since  0.2, 09.04.2016
void ArgListElement::setControl( int argi, int argp, char ctrlChar)
{

   mArgIndex    = argi;
   mArgCharPos  = argp;
   mElementType = ElementType::control;
   mArgChar     = ctrlChar;

   mArgString.clear();
   mValue.clear();

} // ArgListElement::setControl



/// Prints the contents of an argument list element.
/// @param[out]  os   The stream to write to.
/// @param[in]   ale  The object to dump the data of.
/// @return  The stream.
/// @since  0.2, 09.04.2016
ostream& operator <<( ostream& os, const ArgListElement& ale)
{

   os << "argument index     = " << ale.mArgIndex << endl;

   if (ale.mElementType == ArgListElement::ElementType::value)
   {
      os << "free value         = " << ale.mValue << endl;
   } else if (ale.mElementType == ArgListElement::ElementType::singleCharArg)
   {
      os << "character position = " << ale.mArgCharPos << endl
         << "argument character = " << ale.mArgChar << endl;
   } else if (ale.mElementType == ArgListElement::ElementType::control)
   {
      os << "ctrl char position = " << ale.mArgCharPos << endl
         << "control character  = " << ale.mArgChar << endl;
   } else if (ale.mElementType == ArgListElement::ElementType::stringArg)
   {
      os << "argument string    = " << ale.mArgString << endl;
   } else
   {
      os << "invalid argument list element" << endl;
   } // end if

   return os;
} // operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// =======================  END OF arg_list_element.cpp  =======================

