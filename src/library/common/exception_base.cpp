
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


// module headerfile include
#include "celma/common/exception_base.hpp"


// C++ Standard Library includes
#include <sstream>


// project includes
#include "celma/common/extract_funcname.hpp"


namespace celma::common {



/// Constructor.
///
/// @param[in]  filename  Path and file name of the source file.
/// @param[in]  funcName  Function prototype string.
/// @param[in]  line_nbr  Line number in the source file.
/// @param[in]  etext     Text provided for the exception.
/// @since  0.2, 07.04.2016
ExceptionBase::ExceptionBase( const char* filename, const char* funcName,
                              const int line_nbr, const std::string& etext):
   mSourceFilename( filename),
   mFunctionName( funcName),
   mLineNbr( line_nbr),
   mExceptionText( etext)
{

   buildMsg();

} // ExceptionBase::ExceptionBase



/// Returns only the name of the file.
///
/// @returns  Name of the source file (without path).
/// @since  0.2, 07.04.2016
const std::string ExceptionBase::sourceFilename() const
{

   auto const         slashPos = mSourceFilename.find_last_of( '/');
   const std::string  useFilename( mSourceFilename, slashPos + 1,
      std::string::npos);

   return useFilename;
} // ExceptionBase::sourceFilename



/// Returns only the function name.
///
/// @returns  Pure function name.
/// @since  0.2, 07.04.2016
const std::string ExceptionBase::functionName() const
{

   return extractFuncname( mFunctionName);
} // ExceptionBase::functionName



/// Called by the constructors to build the exception message.
///
/// @since  0.2, 07.04.2016
void ExceptionBase::buildMsg()
{

   std::ostringstream  oss;


   oss << functionName() << "@" << sourceFilename() << "[" << mLineNbr << "]: "
       << mExceptionText;

   mExceptionMsg = oss.str();

} // ExceptionBase::buildMsg



} // namespace celma::common


// =====  END OF exception_base.cpp  =====

