
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
/// See documentation of class celma::prog_args::detail::ArgumentKey.


#ifndef CELMA_PROG_ARGS_DETAIL_ARGUMENT_KEY_HPP
#define CELMA_PROG_ARGS_DETAIL_ARGUMENT_KEY_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Stores and compares the short and/or long argument specifier of an
/// argument.<br>
/// This class does not provide an assignment operator to assign a new argument
/// specification string. If this is needed, assign a temporary object.
/// @since  0.2, 06.04.2016
class ArgumentKey
{
public:
   /// Constructor, splits the specified string into short and/or long specifier
   /// and checks for all kind of format errors, content errors etc.<br>
   /// Dashes are silently ignored.
   /// @param[in]  arg_spec  The string with the argument specifiers.
   /// @since  0.2, 06.04.2016
   explicit ArgumentKey( const std::string& arg_spec);

   /// Default copy constructor is just fine.
   /// @since  0.2, 06.04.2016
   ArgumentKey( const ArgumentKey&) = default;

   /// Default assignment operator is just fine.
   /// @since  0.2, 06.04.2016
   ArgumentKey& operator =( const ArgumentKey&) = default;

   /// Compares two argument keys if the short or long specifier are the same.
   /// Mismatches are not detected by this function.
   /// @param[in]  other  The other key object to compare against.
   /// @return  \c true if the short or the long specifier are identical.
   /// @since  0.2, 06.04.2016
   bool operator ==( const ArgumentKey& other) const;

   /// Checks if there is a mismatch: Short specifier matches but long don't or
   /// vice versa.
   /// @param[in]  other  The other key object to compare against.
   /// @return  \c true if a mismatch was detected.
   /// @since  0.2, 06.04.2016
   bool mismatch( const ArgumentKey& other) const;

   /// Returns the key in string format.
   /// @return  The key of this object in string format.
   /// @since  0.2, 06.04.2016
   std::string str() const;

   /// Prints the short and/or the long specifier of the key.<br>
   /// The string is created from the data extracted in the constructor, i.e. it
   /// may differ to this original string regarding the order of the arguments.
   /// @param[out]  os  The stream to write into.
   /// @param[in]   ak  The key object to print the data of.
   /// @return  The stream as passed in.
   /// @since  0.2, 06.04.2016
   friend std::ostream& operator <<( std::ostream& os, const ArgumentKey& ak);

private:
   /// The short specifier, \0 if not set.
   char         mChar;
   /// The long specifier, empty if not set.
   std::string  mWord;

}; // ArgumentKey


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_KEY_HPP


// =========================  END OF argument_key.hpp  =========================

