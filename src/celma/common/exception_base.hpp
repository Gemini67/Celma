
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
/// See documentation of class celma::common::ExceptionBase.


#ifndef CELMA_COMMON_EXCEPTION_BASE_HPP
#define CELMA_COMMON_EXCEPTION_BASE_HPP


#include <string>
#include <stdexcept>


namespace celma { namespace common {


/// Contains some processing shared by all exception classes.<br>
/// Put here to get the stuff out of the header files.
/// @since  0.2, 07.04.2016
/// @todo  Could extract the file location from here into new class FileLocation
///        (or SourceLocation or ...). The new class could then be used here
///        and e.g. for logging.
class ExceptionBase
{
public:
   /// Constructor.
   /// @param[in]  filename  The path and file name of the source file.
   /// @param[in]  funcName  The function prototype string.
   /// @param[in]  line_nbr  The line number in the source file.
   /// @param[in]  etext     The text provided for the exception.
   /// @since  0.2, 07.04.2016
   ExceptionBase( const char* filename, const char* funcName, int line_nbr,
                  const std::string& etext);

   /// Empty, virtual destructor.
   /// @since  0.2, 07.04.2016
   virtual ~ExceptionBase();

   /// Returns the absolute path and file name as it was passed to the constructor.
   /// @return  The file path and name as passed from the __FILE__ macro.
   /// @since  0.2, 07.04.2016
   const std::string& sourceFile() const;

   /// Returns only the name of the file
   /// @return  The name of the source file (without path).
   /// @since  0.2, 07.04.2016
   const std::string sourceFilename() const;

   /// Returns the complete function prototype in string form.
   /// @return  The function prototype.
   /// @since  0.2, 07.04.2016
   const std::string& function() const;

   /// Returns only the function name.
   /// @return  The pure function name.
   /// @since  0.2, 07.04.2016
   const std::string functionName() const;

   /// Returns the exception message text.
   /// @return  The exception text.
   /// @since  0.2, 07.04.2016
   const std::string& text() const;

   /// The complete message build for this exception.
   /// @return  The complete exception message.
   /// @since  0.2, 07.04.2016
   const std::string& message() const;

   /// The line number where the exception was thrown.
   /// @return  The exception line number.
   /// @since  0.2, 07.04.2016
   int lineNbr() const;

protected:
   /// Called by the constructors to build the exception message.
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
} // end ExceptionBase::sourceFile


inline const std::string& ExceptionBase::function() const
{
   return mFunctionName;
} // end ExceptionBase::function


inline const std::string& ExceptionBase::text() const
{
   return mExceptionText;
} // end ExceptionBase::text


inline const std::string& ExceptionBase::message() const
{
   return mExceptionMsg;
} // end ExceptionBase::message


inline int ExceptionBase::lineNbr() const
{
   return mLineNbr;
} // end ExceptionBase::lineNbr


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_EXCEPTION_BASE_HPP


// =========================  END OF exception_base.hpp  =========================

