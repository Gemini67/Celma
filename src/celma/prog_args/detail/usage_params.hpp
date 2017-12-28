
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::UsageParams.


#ifndef CELMA_PROG_ARGS_DETAIL_USAGE_PARAMS_HPP
#define CELMA_PROG_ARGS_DETAIL_USAGE_PARAMS_HPP


#include <iosfwd>
#include <memory>
#include <string>


namespace celma { namespace prog_args {


class Handler;


namespace detail {


class TypedArgBase;


/// Stores the parameters for printing the usage.
/// @since  x.y.z, 21.11.2017
class UsageParams
{
public:
   /// List of possible settings for printing the usage:
   enum class Contents
   {
      all,         //!< Default: Display all arguments with their short and/or
                   //!< long argument keys.
      shortOnly,   //!< Display only those arguments with a short key.
      longOnly     //!< Display only those arguments with a long key.
   }; // UsageContents

   UsageParams() = default;
   ~UsageParams() = default;

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
   /// @since  x.y.z, 16.11.2017
   detail::TypedArgBase* addArgumentUsageShort( Handler& handler,
      const std::string& arg_spec, const char* desc = nullptr);

   /// Adds an argument that activates printing of usage with arguments with
   /// long argument key only.
   /// @param[out]  handler   The argument handler to add the argument to.
   /// @param[in]   arg_spec  The argument(s) on the command line for activating
   ///                        printing the usage with long arguments only.
   /// @param[in]  desc       Optional text for the description of the argument
   ///                        in the usage. If not set, the default description
   ///                        is used.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  x.y.z, 16.11.2017
   detail::TypedArgBase* addArgumentUsageLong( Handler& handler,
      const std::string& arg_spec, const char* desc = nullptr);

   /// Adds an argument that activates printing of hidden arguments in the usage.
   /// @param[out]  handler   The argument handler to add the argument to.
   /// @param[in]   arg_spec  The argument(s) on the command line for activating
   ///                        printing the hidden arguments.
   /// @param[in]  desc       Optional text for the description of the argument
   ///                        in the usage. If not set, the default description
   ///                        is used.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  x.y.z, 06.12.2017  (moved here from Handler)
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentPrintHidden( Handler& handler,
         const std::string& arg_spec, const char* desc = nullptr);

   /// Directly specifies the contents for printing the usage.
   /// @param[in]  usage_contents  The contents to print n the usage.
   /// @since  x.y.z, 21.11.2017
   void setContents( Contents usage_contents);

   /// Returns the specified contents for printing the usage
   /// @return  The contents to print in the usage.
   /// @since  x.y.z, 21.11.2017
   Contents contents() const;

   /// Sets the flag 'print hidden' to print hidden arguments.
   /// @since  x.y.z, 06.12.2017
   void setPrintHidden();

   /// Returns if hidden arguments should be printed.
   /// @return  \c true if hidden arguments should be printed too.
   /// @since  x.y.z, 06.12.2017
   bool printHidden() const;

private:
   /// Defines the contents of the usage.
   Contents  mContents = Contents::all;
   /// Specifies if hidden arguments should be printed.
   bool      mPrintHidden = false;

}; // UsageParams


/// Same usage parameters should be used for all handlers, sub-group handlers
/// groups. So, we use a shared object everywhere.
using shared_usage_params_t = std::shared_ptr< UsageParams>;


// inlined methods
// ===============


inline UsageParams::Contents UsageParams::contents() const
{
   return mContents;
} // UsageParams::contents


inline bool UsageParams::printHidden() const
{
   return mPrintHidden;
} // UsageParams::printHidden


// standalone functions
// ====================


/// Prints the value of the usage contents enum.
/// @param[in]  os  The stream to print to.
/// @param[in]  c   The enum value to print.
/// @return  The stream as given in \a os.
/// @since  x.y.z, 26.10.2017
std::ostream& operator <<( std::ostream& os, UsageParams::Contents c);


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_USAGE_PARAMS_HPP


// =========================  END OF usage_params.hpp  =========================

