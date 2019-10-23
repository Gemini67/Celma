
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
/// See documentation of class celma::prog_args::detail::ArgListElement.


#ifndef CELMA_PROG_ARGS_DETAIL_ARG_LIST_ELEMENT_HPP
#define CELMA_PROG_ARGS_DETAIL_ARG_LIST_ELEMENT_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Stores the properties of the next argument from the list:
/// - mArgIndex contains the number of the argument string in which this
///   argument was found
/// - if it is a value, #mElementType is set to #etValue
/// - the value is stored in #mValue
/// - if it is a single character argument, #mElementType is set to
///   #etSingleCharArg, and the argument character is stored in #mArgChar<br>
///   #mArgCharPos then contains the position of the argument character in the
///   argument string
/// - if it is a long argument, #mElementType is set to #etStringArg, and the
///   argument name is stored in #mArgString
///
/// @since  0.2, 09.04.2016
class ArgListElement
{
public:
   /// Element types to be found/identified in an argument list:
   enum class ElementType
   {
     singleCharArg,   //!< Single character argument.
     stringArg,       //!< String/long argument.
     value,           //!< Value (after argument or positional).
     control,         //!< Control character.
     invalid          //!< Initialisation value.
   }; // ElementType

   /// Returns the name/description of the given element type.
   ///
   /// @param[in]  et  The type of the element to return the name of.
   /// @return  The name of the element.
   /// @since  1.23.1, 16.04.2019
   static const char* typeName( ElementType et);

   /// Default constructor.
   ///
   /// @since  0.2, 09.04.2016
   ArgListElement() = default;

   /// Default copy constructor is fine.
   ///
   /// @since  0.2, 09.04.2016
   ArgListElement( const ArgListElement&) = default;

   /// Default destructor is fine.
   ///
   /// @since  0.2, 09.04.2016
   ~ArgListElement() = default;

   /// Stores the data of a single argument character.
   ///
   /// @param[in]  argi     The argument string index.
   /// @param[in]  argp     The position of the argument character in the string.
   /// @param[in]  argChar  The argument character.
   /// @since  0.2, 09.04.2016
   void setArgChar( int argi, int argp, char argChar);

   /// Stores the data of a long argument.
   ///
   /// @param[in]  argi     The argument string index.
   /// @param[in]  argName  The long argument.
   /// @since  0.2, 09.04.2016
   void setArgString( int argi, const std::string& argName);

   /// Stores a value.
   ///
   /// @param[in]  argi   The argument string index.
   /// @param[in]  value  The value (== the argument string).
   /// @since  0.2, 09.04.2016
   void setValue( int argi, const std::string& value);

   /// Stores the data of a control character.
   ///
   /// @param[in]  argi      The argument string index.
   /// @param[in]  argp      The position of the control character in the string.
   /// @param[in]  ctrlChar  The control character.
   /// @since  0.2, 09.04.2016
   void setControl( int argi, int argp, char ctrlChar);

   /// Prints the name and value of the given element type.
   ///
   /// @param[in]  os
   ///    The stream to print to.
   /// @param[in]  et
   ///    The element type to print.
   /// @return
   ///    The stream as passed in.
   /// @since
   ///    1.23.1, 16.04.2019
   friend std::ostream& operator <<( std::ostream& os,
      ArgListElement::ElementType et);

   /// Prints the contents of an argument list element.
   ///
   /// @param[out]  os   The stream to write to.
   /// @param[in]   ale  The object to dump the data of.
   /// @return  The stream.
   /// @since  0.2, 09.04.2016
   friend std::ostream& operator <<( std::ostream& os,
      const ArgListElement& ale);

   /// The index of the argument string in the list in which the current
   /// argument was found.
   int          mArgIndex = -1;
   /// For single argument characters: The position of the character.
   int          mArgCharPos = -1;
   /// The type of this element.
   ElementType  mElementType = ElementType::invalid;
   /// The single argument character.
   char         mArgChar = '-';
   /// The long argument string.
   std::string  mArgString;
   /// The value.
   std::string  mValue;

}; // ArgListElement


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARG_LIST_ELEMENT_HPP


// =====  END OF arg_list_element.hpp  =====

