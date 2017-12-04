
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
/// See documentation of class celma::prog_args::detail::ArgumentDesc.


// module header file include
#include "celma/prog_args/detail/argument_desc.hpp"


// STL includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


// project includes
#include "celma/format/text_block.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::string;



/// Constructor.
/// @param[in]  usage_params  The object that contains the parameters for
///                           printing the usage.
/// @since  x.y.z, 21.11.2017  (added paramater arg_desc_params)
/// @since  0.2, 10.04.2016
ArgumentDesc::ArgumentDesc( shared_usage_params_t& usage_params):
   mpUsageParams( usage_params),
   mIndention( IndentLength, ' '),
   mArguments(),
   mCaptionMandatory( "Mandatory arguments:"),
   mCaptionOptional( "Optional arguments:")
{
} // ArgumentDesc::ArgumentDesc



/// Adds an argument.
/// @param[in]  arg_desc  The string with the description.
/// @param[in]  arg_obj   Pointer to the object that handles this argument.
/// @since  x.y.z, 17.11.2017  (removed key parameter, object may not be NULL
///         anymore)
/// @since  0.2, 10.04.2016
void ArgumentDesc::addArgument( const string& arg_desc, TypedArgBase* arg_obj)
{

   assert( arg_obj != nullptr);

   mArguments.push_back( ArgDesc( arg_desc, arg_obj));

} // ArgumentDesc::addArgument



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

} // ArgumentDesc::setCaption



/// Specifies the line length to use when printing the usage.
/// @param[in]  useLen  The new line length to use.<br>
///                     The value must be in the range 60 <= useLen < 240.
/// @since  0.2, 10.04.2016
void ArgumentDesc::setLineLength( int useLen)
{

   if ((useLen < 60) || (useLen >= 240))
      throw std::runtime_error( "Line length must be in the range 60..240");

   mLineLength = useLen;

} // ArgumentDesc::setLineLength



/// Prints the contents of the storage to the specified stream.
/// @param[out]  os  the stream to write to.
/// @since  0.2, 10.04.2016
void ArgumentDesc::print( std::ostream& os) const
{

   size_t  max_length = 0;


   for (auto const& arg_desc : mArguments)
   {
      if (!arg_desc.doPrint( true, mPrintHidden, mpUsageParams->contents())
          && !arg_desc.doPrint( false, mPrintHidden, mpUsageParams->contents()))
         continue;  // for

      max_length = std::max( max_length, arg_desc.key( mpUsageParams->contents()).length());
   } // end for

   bool  printIsMandatory = true;
   int   printed[ 2] = { 0, 0};

   for (int printLoop = 0; printLoop < 2; ++printLoop)
   {
      if (max_length < MaxNameLength)
      {
         format::TextBlock  tb( 2 * IndentLength + max_length, mLineLength, false);

         printArguments( os, tb, printIsMandatory, printed, true, max_length);
      } else
      {
         format::TextBlock  tb( 2 * IndentLength, mLineLength, true);

         printArguments( os, tb, printIsMandatory, printed, false, max_length);
      } // end if

      printIsMandatory = !printIsMandatory;
   } // end for

} // ArgumentDesc::print



/// Finally prints the arguments.
/// @param[out]  os                The stream to write to.
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
/// @param[in]   max_length        The maximum length of all arguments.
/// @since  0.2, 10.04.2016
void ArgumentDesc::printArguments( std::ostream& os, format::TextBlock& tb,
   bool printIsMandatory, int* printed, bool sameLine, int max_length) const
{

   using std::endl;

   for (size_t i = 0; i < mArguments.size(); ++i)
   {
      if (!mArguments[ i].doPrint( printIsMandatory, mPrintHidden,
          mpUsageParams->contents()))
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
         os << mIndention << std::setw( max_length) << std::left
            << mArguments[ i].key( mpUsageParams->contents()) << mIndention;
      else
         os << mIndention << std::left
            << mArguments[ i].key( mpUsageParams->contents())
            << endl;

      // if the destination variable contains the default value for an optional
      // argument, add this to the usage
      auto  descCopy( mArguments[ i].mDescription);
      if (!mArguments[ i].mpArgObj->isMandatory()
          && mArguments[ i].mpArgObj->printDefault())
      {
         descCopy.append( "\nDefault value: ");
         mArguments[ i].mpArgObj->defaultValue(descCopy);
      } // end if
      if (mArguments[ i].mpArgObj->hasCheck())
      {
         descCopy.append( "\nCheck: ")
            .append( mArguments[ i].mpArgObj->checkStr());
      } // end if
      if (mArguments[ i].mpArgObj->hasConstraint())
      {
         descCopy.append( "\nConstraint: ")
            .append( mArguments[ i].mpArgObj->constraintStr());
      } // end if

      tb.format( os, descCopy);
      os  << endl;

      ++printed[ printIsMandatory];
   } // end for

} // ArgumentDesc::printArguments



/// Prints the contents of the storage to the specified stream.
/// @param[out]  os  the stream to write to.
/// @param[in]   ad  The object to dump the contents of the storage of.
/// @return  The stream as passed as parameter.
/// @since  0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, const ArgumentDesc& ad)
{

   ad.print( os);

   return os;
} // operator <<



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
bool ArgumentDesc::ArgDesc::doPrint( bool printIsMandatory, bool printHidden,
   UsageParams::Contents usage_contents) const
{

   return (printIsMandatory == mpArgObj->isMandatory())
          && (printHidden || !mpArgObj->isHidden())
          && ((usage_contents == UsageParams::Contents::all)
              || ((usage_contents == UsageParams::Contents::shortOnly)
                  && mpArgObj->key().hasCharArg())
              || ((usage_contents == UsageParams::Contents::longOnly)
                  && mpArgObj->key().hasStringArg()));
} // ArgumentDesc::ArgDesc::doPrint



/// Returns the key string of the argument with the specified contents.
/// @param[in]  usage_contents  Contents of the key string to return.
/// @return  The key string with the given contents.
/// @since  x.y.z, 20.11.2017
string ArgumentDesc::ArgDesc::key( UsageParams::Contents usage_contents) const
{

   if (usage_contents == UsageParams::Contents::all)
   {
      std::ostringstream  os;
      os << format::toString( mpArgObj->key());
      return os.str();
   } // end if

   if (usage_contents == UsageParams::Contents::shortOnly)
   {
      string  result( "-");
      result.append( 1, mpArgObj->key().argChar());
      return result;
   } // end if

   string  result( "--");
   result.append( mpArgObj->key().argString());
   return result;
} // ArgumentDesc::ArgDesc::key



} // namespace detail
} // namespace prog_args
} // namespace celma


// ========================  END OF argument_desc.cpp  ========================

