
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::UsageParams.


// module header file include
#include "celma/prog_args/detail/usage_params.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/prog_args/handler.hpp"
#include "celma/prog_args/destination.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::string;



/// Adds an argument to the argument handler that activates printing of usage
/// with arguments with short argument key only.
/// @param[out]  handler   The argument handler to add the argument to.
/// @param[in]   arg_spec  The argument(s) on the command line for activating
///                        printing the usage with short arguments only.
/// @param[in]   desc      Optional text for the description of the argument
///                        in the usage. If not set, the default description
///                        is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 16.11.2017
detail::TypedArgBase*
   UsageParams::addArgumentUsageShort( Handler& handler,
      const string& arg_spec, const char* desc)
{

   static const string  default_desc( "Only print arguments with their short "
      "key in the usage.");


   return handler.addArgument( arg_spec,
      DEST_VAR_VALUE( mContents, Contents::shortOnly),
      (desc != nullptr) ? desc : default_desc)
      ->setPrintDefault( false);
} // UsageParams::addArgumentUsageShort



/// Adds an argument that activates printing of usage with arguments with
/// long argument key only.
/// @param[out]  handler   The argument handler to add the argument to.
/// @param[in]   arg_spec  The argument(s) on the command line for activating
///                        printing the usage with long arguments only.
/// @param[in]   desc      Optional text for the description of the argument
///                        in the usage. If not set, the default description
///                        is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 16.11.2017
detail::TypedArgBase*
   UsageParams::addArgumentUsageLong( Handler& handler,
      const string& arg_spec, const char* desc)
{

   static const string  default_desc( "Only print arguments with their long "
      "key in the usage.");


   return handler.addArgument( arg_spec,
      DEST_VAR_VALUE( mContents, Contents::longOnly),
      (desc != nullptr) ? desc : default_desc)
      ->setPrintDefault( false);
} // UsageParams:addArgumentUsageLong



/// Adds an argument that activates printing of hidden arguments in the usage.
/// @param[out]  handler   The argument handler to add the argument to.
/// @param[in]   arg_spec  The argument(s) on the command line for activating
///                        printing the hidden arguments.
/// @param[in]   desc      Optional text for the description of the argument
///                        in the usage. If not set, the default description
///                        is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 06.12.2017  (moved here from Handler)
/// @since  0.2, 10.04.2016
detail::TypedArgBase*
   UsageParams::addArgumentPrintHidden( Handler& handler,
      const string& arg_spec, const char* desc)
{

   static const string  default_desc( "Also print hidden arguments in the usage.");

   return handler.addArgument( arg_spec, DEST_VAR( mPrintHidden),
      (desc != nullptr) ? desc : default_desc);
} // UsageParams::addArgumentPrintHidden



/// Adds an argument that activates printing of deprecated arguments in the
/// usage.
/// @param[out]  handler
///    The argument handler to add the argument to.
/// @param[in]   arg_spec
///    The argument(s) on the command line for activating printing the hidden
///    arguments.
/// @param[in]   desc
///    Optional text for the description of the argument in the usage. If not
///    set, the default description is used.
/// @return
///    The object managing this argument, may be used to apply further
///    settings.
/// @since
///    1.6.0, 30.04.2018
detail::TypedArgBase* UsageParams::addArgumentPrintDeprecated( Handler& handler,
   const string& arg_spec, const char* desc)
{

   static const string  default_desc( "Also print deprecated and replaced arguments in the usage.");

   return handler.addArgument( arg_spec, DEST_VAR( mPrintDeprecated),
      (desc != nullptr) ? desc : default_desc);
} // UsageParams::addArgumentPrintDeprecated



/// Directly specifies the contents for printing the usage.
/// @param[in]  usage_contents  The contents to print in the usage.
/// @since  1.1.0, 21.11.2017
void UsageParams::setContents( Contents usage_contents)
{

   mContents = usage_contents;

} // UsageParams::setContents



/// Sets the flag 'print hidden' to print hidden arguments.
/// @since  1.1.0, 06.12.2017
void UsageParams::setPrintHidden()
{

   mPrintHidden = true;

} // UsageParams::setPrintHidden



/// Sets the flag 'print deprecated' to print deprecated arguments.
/// @since
///    1.6.0, 30.04.2018
void UsageParams::setPrintDeprecated()
{

   mPrintDeprecated = true;

} // UsageParams::setPrintDeprecated



/// Prints the value of the usage contents enum.
/// @param[in]  os  The stream to print to.
/// @param[in]  c   The enum value to print.
/// @return  The stream as given in \a os.
/// @since  1.1.0, 26.10.2017
std::ostream& operator <<( std::ostream& os, UsageParams::Contents c)
{

   switch (c)
   {
   case UsageParams::Contents::all:        os << "all";         break;
   case UsageParams::Contents::shortOnly:  os << "short only";  break;
   case UsageParams::Contents::longOnly:   os << "long only";   break;
   } // end switch

   return os << " (" << static_cast< int>( c) << ")";
} // operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF usage_params.cpp  =====

