
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


// module header file include
#include "celma/prog_args/detail/argument_desc.hpp"


// STL includes
#include <iomanip>
#include <iostream>


// project includes
#include "celma/format/text_block.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {


/// Constructor.
/// @since  0.2, 10.04.2016
ArgumentDesc::ArgumentDesc():
   mIndention( IndentLength, ' '),
   mArguments(),
   mMaxArgLen( 0),
   mCaptionMandatory( "Mandatory arguments:"),
   mCaptionOptional( "Optional arguments:"),
   mLineLength( DefaultLineLength),
   mPrintHidden( false)
{
} // end ArgumentDesc::ArgumentDesc



/// Adds an argument.
/// @param[in]  argSpec  The string with the arguments (character, long
///                      format).
/// @param[in]  argDesc  The string with the description.
/// @param[in]  argObj   Pointer to the object that handles this argument.
/// @since  0.2, 10.04.2016
void ArgumentDesc::addArgument( const string& argSpec, const string& argDesc,
                                TypedArgBase* argObj)
{

   string             argSpecDashed( argSpec);
   string::size_type  pos = argSpecDashed.find_first_of( ',');


   if (pos == string::npos)
   {
      // no comma: short or long?
      if (argSpecDashed.length() == 1)  argSpecDashed.insert( 0, "-");
      else                              argSpecDashed.insert( 0, "--");
   } else
   {
      // with comma: short and long
      argSpecDashed.insert( pos + 1, "--");
      argSpecDashed.insert( 0,       "-");
   } // end if

   if (argSpecDashed.length() > mMaxArgLen)
      mMaxArgLen = argSpecDashed.length();

   ArgDesc  ad( argSpecDashed, argDesc, argObj);

   mArguments.push_back( ad);

} // end ArgumentDesc::addArgument



/// Can be used to modify the captions (titel) written before the
/// mandatory and/or optional arguments.<br>
/// If any of those points is NULL, the corresponding value is not changed.
/// @param[in]  mandatory  Sets the caption for the mandatory arguments.<br>
///                        Default value: 'Mandatory arguments:'.
/// @param[in]  optional   Sets the caption for the optional arguments.<br>
///                        Default value: 'Optional arguments:'.
/// @since  0.2, 10.04.2016
void ArgumentDesc::setCaption( const char* mandatory, const char* optional)
{

   if (mandatory != nullptr)
      mCaptionMandatory.assign( mandatory);

   if (optional != nullptr)
      mCaptionOptional.assign( optional);

} // end ArgumentDesc::setCaption



/// Specifies the line length to use when printing the usage.
/// @param[in]  useLen  The new line length to use.<br>
///                     The value must be in the range 60 <= useLen < 240.
/// @since  0.2, 10.04.2016
void ArgumentDesc::setLineLength( int useLen)
{

   if ((useLen < 60) || (useLen >= 240))
      throw runtime_error( "Line length must be in the range 60..240");

   mLineLength = useLen;

} // end ArgumentDesc::setLineLength



/// Prints the contents of the storage to the specified stream.
/// @param[out]  os  the stream to write to.
/// @since  0.2, 10.04.2016
void ArgumentDesc::print( ostream& os) const
{

   bool  printIsMandatory = true;
   int   printed[ 2] = { 0, 0};


   for (int printLoop = 0; printLoop < 2; ++printLoop)
   {
      if (mMaxArgLen < MaxNameLength)
      {
         format::TextBlock  tb( 2 * IndentLength + mMaxArgLen, mLineLength, false);

         printArguments( tb, printIsMandatory, printed, true, os);
      } else
      {
         format::TextBlock  tb( 2 * IndentLength, mLineLength, true);

         printArguments( tb, printIsMandatory, printed, false, os);
      } // end if

      printIsMandatory = !printIsMandatory;
   } // end for

} // end ArgumentDesc::print



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
void ArgumentDesc::printArguments( format::TextBlock& tb, bool printIsMandatory,
                                   int* printed, bool sameLine, ostream& os) const
{

   for (size_t i = 0; i < mArguments.size(); ++i)
   {
      if (!mArguments[ i].doPrint( printIsMandatory, mPrintHidden))
         continue;   // for

      if (printed[ printIsMandatory] == 0)
      {
         if (printIsMandatory)
         {
            os << mCaptionMandatory << endl;
         } else
         {
            if (printed[ true] > 0)
               os << endl;
            os << mCaptionOptional << endl;
         } // end if
      } // end if

      if (sameLine)
         os << mIndention << setw( mMaxArgLen) << left
            << mArguments[ i].mArgSpec << mIndention;
      else
         os << mIndention << left << mArguments[ i].mArgSpec << endl;

      // if the destination variable contains the default value for an optional
      // argument, add this to the usage
      if ((mArguments[ i].mpArgObj != nullptr) &&
          !mArguments[ i].mpArgObj->isMandatory() &&
          mArguments[ i].mpArgObj->printDefault())
      {
         string  descCopy( mArguments[ i].mDescription);
         descCopy.append( "\nDefault value: ");
         mArguments[ i].mpArgObj->defaultValue( descCopy);
         tb.format( os, descCopy);
      } else
      {
         tb.format( os, mArguments[ i].mDescription);
      } // end if
      os  << endl;

      ++printed[ printIsMandatory];
   } // end for

} // end ArgumentDesc::printArguments



/// Prints the contents of the storage to the specified stream.
/// @param[out]  os  the stream to write to.
/// @param[in]   ad  The object to dump the contents of the storage of.
/// @return  The stream as passed as parameter.
/// @since  0.2, 10.04.2016
ostream& operator <<( ostream& os, const ArgumentDesc& ad)
{

   ad.print( os);

   return os;
} // end operator <<



/// Returns if this entry should be printed in the usage now.
/// @param[in]  printIsMandatory  Specifies if only mandatory (\c true)
///                               parameters should be printed or all.
/// @param[in]  printHidden       Specifies if hidden parameters should be
///                               printed or not.
/// @return  \c true if mandatory parameters are requested and this
///          parameter is mandatory, or if non-mandatory (optional)
///          parameters are requested and this parameter is not mandatory,
///          and when hidden parameters may be printed or this parameter is
///          is not hidden.
/// @since  0.2, 10.04.2016
bool ArgumentDesc::ArgDesc::doPrint( bool printIsMandatory, bool printHidden) const
{
   return ((printIsMandatory  && (mpArgObj != nullptr) && mpArgObj->isMandatory()) ||
           (!printIsMandatory && ((mpArgObj == nullptr) || !mpArgObj->isMandatory()))) &&
          (printHidden || (mpArgObj == nullptr) || !mpArgObj->isHidden());
} // end ArgumentDesc::ArgDesc::doPrint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF argument_desc.cpp  =========================

