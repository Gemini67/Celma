
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::ExceptionBase.


#pragma once


#include <string>
#include <stdexcept>


namespace celma::common {


/// Contains some processing shared by all exception classes.<br>
/// Put here to get the stuff out of the header files.
///
/// @since  0.2, 07.04.2016
/// @todo  Could extract the file location from here into new class FileLocation
///        (or SourceLocation or ...). The new class could then be used here
///        and e.g. for logging.
class ExceptionBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  filename  Path and file name of the source file.
   /// @param[in]  funcName  Function prototype string.
   /// @param[in]  line_nbr  Line number in the source file.
   /// @param[in]  etext     Text provided for the exception.
   /// @since  0.2, 07.04.2016
   ExceptionBase( const char* filename, const char* funcName, int line_nbr,
                  const std::string& etext);

   /// Empty, virtual destructor.
   ///
   /// @since  0.2, 07.04.2016
   virtual ~ExceptionBase() = default;

   /// Returns the absolute path and file name as it was passed to the constructor.
   ///
   /// @returns  File path and name as passed from the __FILE__ macro.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& sourceFile() const;

   /// Returns only the name of the file.
   ///
   /// @returns  Name of the source file (without path).
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string sourceFilename() const;

   /// Returns the complete function prototype in string form.
   ///
   /// @returns  Function prototype.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& function() const;

   /// Returns only the function name.
   ///
   /// @returns  Pure function name.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string functionName() const;

   /// Returns the exception message text.
   ///
   /// @returns  Exception text.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& text() const;

   /// The complete message build for this exception.
   ///
   /// @returns  Complete exception message.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] const std::string& message() const;

   /// The line number where the exception was thrown.
   ///
   /// @returns  Exception line number.
   /// @since  0.2, 07.04.2016
   [[nodiscard]] int lineNbr() const;

protected:
   /// Called by the constructors to build the exception message.
   ///
   /// @since  0.2, 07.04.2016
   void buildMsg();

   /// The complete path and file name of the source file.
   const std::string  mSourceFilename;
   /// The complete function prototype in string form.
   const std::string  mFunctionName;
   /// The line number.
   const int          mLineNbr;

   /// The text passed for this exception.
   std::string  mExceptionText;
   /// The complete exception message.
   std::string  mExceptionMsg;

}; // ExceptionBase


// inlined methods
// ===============


inline const std::string& ExceptionBase::sourceFile() const
{
   return mSourceFilename;
} // ExceptionBase::sourceFile


inline const std::string& ExceptionBase::function() const
{
   return mFunctionName;
} // ExceptionBase::function


inline const std::string& ExceptionBase::text() const
{
   return mExceptionText;
} // ExceptionBase::text


inline const std::string& ExceptionBase::message() const
{
   return mExceptionMsg;
} // ExceptionBase::message


inline int ExceptionBase::lineNbr() const
{
   return mLineNbr;
} // ExceptionBase::lineNbr


} // namespace celma::common


// =====  END OF exception_base.hpp  =====

