
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


// module header file include
#include "celma/common/exception_base.hpp"


// C++ Standard Library includes
#include <sstream>


// project includes
#include "celma/common/extract_func_name.hpp"


using namespace std;


namespace celma { namespace common {


/// Constructor.
/// @param[in]  filename  The path and file name of the source file.
/// @param[in]  funcName  The function prototype string.
/// @param[in]  line_nbr  The line number in the source file.
/// @param[in]  etext     The text provided for the exception.
/// @since  0.2, 07.04.2016
ExceptionBase::ExceptionBase( const char* filename, const char* funcName,
                              int line_nbr, const string& etext):
   mSourceFilename( filename),
   mFunctionName( funcName),
   mLineNbr( line_nbr),
   mExceptionText( etext)
{

   buildMsg();

} // end ExceptionBase::ExceptionBase



/// Empty, virtual destructor.
/// @since  0.2, 07.04.2016
ExceptionBase::~ExceptionBase()
{
} // end ExceptionBase::~ExceptionBase



/// Returns only the name of the file
/// @return  The name of the source file (without path).
/// @since  0.2, 07.04.2016
const string ExceptionBase::sourceFilename() const
{

   const string::size_type  slashPos = mSourceFilename.find_last_of( '/');
   const string             useFilename( mSourceFilename, slashPos + 1, string::npos);

   return useFilename;
} // end ExceptionBase::sourceFilename



/// Returns only the function name.
/// @return  The pure function name.
/// @since  0.2, 07.04.2016
const string ExceptionBase::functionName() const
{

   string  justName;


   common::extractFuncName( justName, mFunctionName);

   return justName;
} // end ExceptionBase::functionName



/// Called by the constructors to build the exception message.
/// @since  0.2, 07.04.2016
void ExceptionBase::buildMsg()
{

   ostringstream  oss;


   oss << functionName() << "@" << sourceFilename() << "[" << mLineNbr << "]: "
       << mExceptionText;

   mExceptionMsg = oss.str();

} // end ExceptionBase::buildMsg



} // namespace common
} // namespace celma


// =========================  END OF exception_base.cpp  =========================

