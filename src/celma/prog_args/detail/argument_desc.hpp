
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
/// See documentation of class celma::prog_args::detail::ArgumentDesc.


#ifndef CELMA_PROG_ARGS_DETAIL_ARGUMENT_DESC_HPP
#define CELMA_PROG_ARGS_DETAIL_ARGUMENT_DESC_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include "celma/format/text_block_fwd.hpp"


namespace celma { namespace prog_args { namespace detail {


class TypedArgBase;


/// Provides storage for all arguments (specifyer plus description).<br>
/// This is used to print the usage.
/// @since  0.2, 10.04.2016
class ArgumentDesc
{
public:
   /// For the formatting of the usage output: Maximum length of a parameter
   /// specification (short and/or long parameter) to print on one line with
   /// the argument description, if longer then the specification and
   /// description are written on separate lines.
   static const unsigned int  MaxNameLength = 40;
   /// Default line length for printing the usage.
   static const unsigned int  DefaultLineLength = 80;
   /// Number of spaces to use for indention on the usage.
   static const unsigned int  IndentLength = 3;

   /// Constructor.
   /// @since  0.2, 10.04.2016
   ArgumentDesc();

   /// Adds an argument.
   /// @param[in]  argSpec  The string with the arguments (character, long
   ///                      format).
   /// @param[in]  argDesc  The string with the description.
   /// @param[in]  argObj   Pointer to the object that handles this argument.
   /// @since  0.2, 10.04.2016
   void addArgument( const std::string& argSpec, const std::string& argDesc,
                     TypedArgBase* argObj = nullptr);

   /// Makes sure that the argument specification length (in #mMaxArgLen) is at
   /// least \a minLen characters.
   /// @param[in]  minLen  Minimum number of characters to set as arg spec len.
   /// @since  0.2, 10.04.2016
   void setMinArgLen( size_t minLen);

   /// Returns the argument specification length as stored in #mMaxArgLen.
   /// @return  The maximum argument specification length to use for formatting
   ///          the output.
   /// @since  0.2, 10.04.2016
   size_t maxArgLen() const;

   /// Can be used to modify the captions (titel) written before the
   /// mandatory and/or optional arguments.<br>
   /// If any of those points is NULL, the corresponding value is not changed.
   /// @param[in]  mandatory  Sets the caption for the mandatory arguments.<br>
   ///                        Default value: 'Mandatory arguments:'.
   /// @param[in]  optional   Sets the caption for the optional arguments.<br>
   ///                        Default value: 'Optional arguments:'.
   /// @since  0.2, 10.04.2016
   void setCaption( const char* mandatory, const char* optional);

   /// Specifies the line length to use when printing the usage.
   /// @param[in]  useLen  The new line length to use.<br>
   ///                     The value must be in the range 60 <= useLen < 240.
   /// @since  0.2, 10.04.2016
   void setLineLength( int useLen);

   /// Specifies if hidden arguments should be printed or not.
   /// @param[in]  do_print  \c true = print hidden arguments.
   /// @since  0.2, 10.04.2016
   void setPrintHidden( bool do_print);

   /// Prints the contents of the storage to the specified stream.
   /// @param[out]  os  the stream to write to.
   /// @param[in]   ad  The object to dump the contents of the storage of.
   /// @return  The stream as passed as parameter.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const ArgumentDesc& ad);

private:
   /// Internal class, used to store the information for one argument.
   /// @since  0.2, 10.04.2016
   class ArgDesc
   {
   public:
      /// Constructor.
      /// @param[in]  argSpec  The string with the arguments (character, long format).
      /// @param[in]  argDesc  The string with the description.
      /// @param[in]  argObj   Pointer to the object that handles this argument.
      /// @since  0.2, 10.04.2016
      ArgDesc( const std::string& argSpec, const std::string& argDesc,
               TypedArgBase* argObj):
         mArgSpec( argSpec),
         mDescription( argDesc),
         mpArgObj( argObj)
      {
      } // end ArgumentDesc::ArgDesc::ArgDesc

      ArgDesc( const ArgDesc&) = default;
      ArgDesc& operator =( const ArgDesc&) = default;

      /// Returns if this entry should be printed in the usage now.
      /// @param[in]  printIsMandatory  Specifies if only mandatory (\c true)
      ///                               parameters should be printed or all.
      /// @param[in]  printHidden       Specifies if hidden parameters should be
      ///                               printed or not.
      /// @return  \c true if mandatory parameters are requested and this
      ///          parameter is mandatory, or if non-mandatory (optional)
      ///          parameters are requested and this parameter is not mandatory,
      ///          and when hidden parameters may be printed or this parameter
      ///          is not hidden.
      /// @since  0.2, 10.04.2016
      bool doPrint( bool printIsMandatory, bool printHidden) const;

      /// The argument specification (character and/or long format).
      std::string    mArgSpec;
      /// The description of the argument.
      std::string    mDescription;
      /// Pointer to the object that handles this argument.
      TypedArgBase*  mpArgObj;

   }; // ArgumentDesc::ArgDesc

   /// Used to store the arguments.
   typedef std::vector< ArgDesc>  ArgDescCont;

   /// Prints the contents of the storage to the specified stream.
   /// @param[out]  os  the stream to write to.
   /// @since  0.2, 10.04.2016
   void print( std::ostream& os) const;

   /// Finally prints the arguments.
   /// @param[in]   tb                The object used to format the description
   ///                                of the parameters.
   /// @param[in]   printIsMandatory  Specifies if the mandatory (\c true) or
   ///                                non-mandatory (\c false) parameters should
   ///                                be printed now.
   /// @param[in]   printed           Pointer to the array with the counters for
   ///                                the number of parameters printed.
   /// @param[in]   sameLine          \c true if the parameter name and its
   ///                                description should be printed on the same
   ///                                line, \c false otherwise (printed on two
   ///                                lines).
   /// @param[out]  os                The stream to write to.
   /// @since  0.2, 10.04.2016
   void printArguments( format::TextBlock& tb, bool printIsMandatory, int* printed,
                        bool sameLine, std::ostream& os) const;

   /// The string with the spaces to use for indention.
   const std::string  mIndention;
   /// All defined arguments.
   ArgDescCont        mArguments;
   /// The length of the longest argument specification (used to format the
   /// output).
   size_t             mMaxArgLen;
   /// The caption to print before mandatory arguments.
   std::string        mCaptionMandatory;
   /// The caption to print before optional arguments.
   std::string        mCaptionOptional;
   /// The line length used when printing the usage.
   int                mLineLength;
   /// Specifies if hidden arguments should be printed or not.
   bool               mPrintHidden;

}; // ArgumentDesc


// inlined methods
// ===============


inline void ArgumentDesc::setMinArgLen( size_t minLen)
{
   if (minLen > mMaxArgLen)
      mMaxArgLen = minLen;
} // end ArgumentDesc::setMinArgLen


inline size_t ArgumentDesc::maxArgLen() const
{
   return mMaxArgLen;
} // end ArgumentDesc::maxArgLen


inline void ArgumentDesc::setPrintHidden( bool do_print)
{
   mPrintHidden = do_print;
} // end ArgumentDesc::setPrintHidden


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_DESC_HPP


// =========================  END OF argument_desc.hpp  =========================

