
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
/// @since  0.14.0, 16.03.2017  (added methods to check/return the character and
///                             string argument)
/// @since  0.2, 06.04.2016
class ArgumentKey
{
public:
   /// Constructor, splits the specified string into short and/or long specifier
   /// and checks for all kind of format errors, content errors etc.<br>
   /// Dashes are silently ignored.
   /// @param[in]  arg_spec  The string with the argument specifiers.
   /// @since  0.2, 06.04.2016
   explicit ArgumentKey( const std::string& arg_spec) noexcept( false);

   /// Constructor, takes a single character as argument key.
   /// @param[in]  char_arg  The argument character.
   /// @since  x.y.z, 17.07.2017
   explicit ArgumentKey( char char_arg) noexcept;

   ArgumentKey( const ArgumentKey&) = default;
   ArgumentKey( ArgumentKey&&) = default;

   ArgumentKey& operator =( const ArgumentKey&) = default;
   ArgumentKey& operator =( ArgumentKey&&) = default;

   /// Compares two argument keys if the short or long specifier are the same.
   /// Mismatches are not detected by this function.
   /// @param[in]  other  The other key object to compare against.
   /// @return  \c true if the short or the long specifier are identical.
   /// @since  0.2, 06.04.2016
   bool operator ==( const ArgumentKey& other) const;

   /// Less comparison operator, needed in order to use an argument key object
   /// as key in a sorted STL container.
   /// @param[in]  other  The other key object to compare against.
   /// @return  \c true if this is less than \a other.
   /// @since  0.14.0, 09.02.2017
   bool operator <( const ArgumentKey& other) const;

   /// Checks if there is a mismatch: Short specifier matches but long don't or
   /// vice versa.
   /// @param[in]  other  The other key object to compare against.
   /// @return  \c true if a mismatch was detected.
   /// @since  0.2, 06.04.2016
   bool mismatch( const ArgumentKey& other) const;

   /// Returns if the character argument is set.
   /// @return \c true if the character argument is set.
   /// @since  0.14.0, 16.03.2017
   bool hasCharArg() const;

   /// Returns if the string argument is set.
   /// @return \c true if the string argument is set.
   /// @since  0.14.0, 16.03.2017
   bool hasStringArg() const;

   /// Returns the character argument.
   /// @return  The value of the character argument key.
   /// @since  0.14.0, 16.03.2017
   char argChar() const;

   /// Returns the string argument.
   /// @return  The value of the string argument key.
   /// @since  0.14.0, 16.03.2017
   const std::string& argString() const;

   /// 
   /// @param[in]  other  .
   /// @return  .
   /// @since  x.y.z, 12.07.2017
   bool startsWith( const ArgumentKey& other) const;

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


// inlined methods
// ===============


inline bool ArgumentKey::hasCharArg() const
{
   return mChar != '\0';
} // ArgumentKey::hasCharArg


inline bool ArgumentKey::hasStringArg() const
{
   return !mWord.empty();
} // ArgumentKey::hasStringArg


inline char ArgumentKey::argChar() const
{
   return mChar;
} // ArgumentKey::argChar


inline const std::string& ArgumentKey::argString() const
{
   return mWord;
} // ArgumentKey::argString


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_KEY_HPP


// =========================  END OF argument_key.hpp  =========================

