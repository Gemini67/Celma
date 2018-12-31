
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::format::AutoSprintf.


#ifndef CELMA_FORMAT_AUTO_SPRINTF_HPP
#define CELMA_FORMAT_AUTO_SPRINTF_HPP


#include <cstdarg>
#include <string>


namespace celma { namespace format {


/// Helper class for using vasprintf() and make sure that the buffer is always
/// deallocated again.
///
/// @since  0.2, 08.04.2016
class AutoSprintf
{
public:
   /// Constructor.
   ///
   /// @param[in]  format  The format string.
   /// @param[in]  ...     Additional parameters for the string formatting.
   /// @throw  CelmaRuntimeError when the string formatting failed.
   /// @since  0.2, 08.04.2016
   AutoSprintf( const char* format, ...) noexcept( false);

   /// Constructor for passing a pre-processed argument list.<br>
   /// Make sure that the format string is a std::string object to make sure
   /// this constructor is called.
   ///
   /// @param[in]  format  The format string as std::string object.
   /// @param[in]  ap      Additional parameters for the string formatting.
   /// @throw  SixRuntimeError when the string formatting failed.
   /// @since  0.7, 08.11.2016
   AutoSprintf( const std::string& format, va_list ap) noexcept( false);

   /// Don't copy.
   /// @since  0.2, 08.04.2016
   AutoSprintf( const AutoSprintf&) = delete;

   /// Don't move.
   /// @since  1.19.0, 25.12.2018
   AutoSprintf( AutoSprintf&&) = delete;

   /// Destructor, ensures that the buffer is free'd again.
   ///
   /// @since  0.2, 08.04.2016
   ~AutoSprintf();

   /// Don't assign.
   /// @since  0.2, 08.04.2016
   AutoSprintf& operator =( const AutoSprintf&) = delete;

   /// Don't move-assign.
   /// @since  1.19.0, 25.12.2018
   AutoSprintf& operator =( AutoSprintf&&) = delete;

   /// Returns the formatted string.
   ///
   /// @return  The formatted string.
   /// @since  0.2, 08.04.2016
   operator const char*() const;

   /// Returns the formatted string.
   ///
   /// @return  The formatted string.
   /// @since  0.2, 08.04.2016
   const char* c_str() const;

   /// Returns the length of the formatted string.
   ///
   /// @return  The length of the string.
   /// @since  0.2, 08.04.2016
   operator int() const;

   /// Returns the length of the formatted string.
   ///
   /// @return  The length of the string.
   /// @since  0.2, 08.04.2016
   int length() const;

private:
   /// Pointer to the dynamically allocated string buffer.
   char*  mpString;
   /// The length of the string in the buffer.
   int    mLength;

}; // AutoSprintf


// inlined methods
// ===============


inline AutoSprintf::operator const char*() const
{
   return mpString;
} // AutoSprintf::operator const char*


inline const char* AutoSprintf::c_str() const
{
   return mpString;
} // AutoSprintf::c_str


inline AutoSprintf::operator int() const
{
   return mLength;
} // AutoSprintf::operator int


inline int AutoSprintf::length() const
{
   return mLength;
} // AutoSprintf::length


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_AUTO_SPRINTF_HPP


// =====  END OF auto_sprintf.hpp  =====

