
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
/// See documentation of class celma::format::AutoSprintf.


#ifndef CELMA_FORMAT_AUTO_SPRINTF_HPP
#define CELMA_FORMAT_AUTO_SPRINTF_HPP


namespace celma { namespace format {


/// Helper class for using vasprintf() and make sure that the buffer is always
/// deallocated again.
/// @since  0.2, 08.04.2016
class AutoSprintf
{
public:
   /// Constructor.
   /// @param[in]  format  The format string.
   /// @param[in]  ...     Additional parameters for the string formatting.
   /// @throw  CelmaRuntimeError when the string formatting failed.
   /// @since  0.2, 08.04.2016
   AutoSprintf( const char* format, ...);

   /// Destructor, ensures that the buffer is free'd again.
   /// @since  0.2, 08.04.2016
   ~AutoSprintf();

   /// Returns the formatted string.
   /// @return  The formatted string.
   /// @since  0.2, 08.04.2016
   operator const char*() const;

   /// Returns the formatted string.
   /// @return  The formatted string.
   /// @since  0.2, 08.04.2016
   const char* c_str() const;

   /// Returns the length of the formatted string.
   /// @return  The length of the string.
   /// @since  0.2, 08.04.2016
   operator int() const;

   /// Returns the length of the formatted string.
   /// @return  The length of the string.
   /// @since  0.2, 08.04.2016
   int length() const;

private:
   /// Don't copy.
   /// @since  0.2, 08.04.2016
   AutoSprintf( const AutoSprintf&) = delete;

   /// Don't assign.
   /// @since  0.2, 08.04.2016
   AutoSprintf& operator =( const AutoSprintf&) = delete;

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
} // end AutoSprintf::operator const char*


inline const char* AutoSprintf::c_str() const
{
   return mpString;
} // end AutoSprintf::c_str


inline AutoSprintf::operator int() const
{
   return mLength;
} // end AutoSprintf::operator int


inline int AutoSprintf::length() const
{
   return mLength;
} // end AutoSprintf::length


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_AUTO_SPRINTF_HPP


// =========================  END OF auto_sprintf.hpp  =========================

