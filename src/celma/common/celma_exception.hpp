
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::CelmaException.


#ifndef CELMA_COMMON_CELMA_EXCEPTION_HPP
#define CELMA_COMMON_CELMA_EXCEPTION_HPP


#include <cstdarg>
#include <cstdio>
#include <memory>
#include <string>
#include <stdexcept>
#include "celma/common/exception_base.hpp"


namespace celma { namespace common {


/// Extension of the standard exception classes: Provides more information
/// about the location where the exception was thrown.
///
/// @tparam  BE  The Base Exception class to use (e.g. runtime_error,
///              logic_error etc.)
/// @since  0.2, 07.04.2016
template< typename BE> class CelmaException: public BE, public ExceptionBase
{
public:
   /// Constructor.<br>
   /// Use the macros below which provide the values for the location parameters.
   /// @param[in]  filename  The full path and file name of the source file.
   /// @param[in]  funcName  The name of the function where the error occurred.
   /// @param[in]  line_nbr  The line number in the function/file where the
   ///                       exception was thrown.
   /// @param[in]  etext     The text to pass with the exception.
   /// @since  0.2, 07.04.2016
   CelmaException( const char* filename, const char* funcName, int line_nbr,
                   const std::string& etext);

   /// Constructor that allows to build the text with a printf()-like format
   /// string and parameters.<br>
   /// Use the macros below which provide the values for the location parameters.
   /// @param[in]  filename  The full path and file name of the source file.
   /// @param[in]  funcName  The name of the function where the error occurred.
   /// @param[in]  line_nbr  The line number in the function/file where the
   ///                       exception was thrown.
   /// @param[in]  fmt       The format string for the exception.
   /// @param[in]  ...       Additional parameters for the text.
   /// @since  0.2, 07.04.2016
   CelmaException( const char* filename, const char* funcName, int line_nbr,
                   const char* fmt, ...);

   /// Use this when an exception was caught and will be thrown again. Using
   /// this constructor gives a sequence of the locations in the source code
   /// where the exception was thrown, caught and thrown again.
   /// @param[in]  filename  The full path and file name of the source file.
   /// @param[in]  funcName  The name of the function where the error occurred.
   /// @param[in]  line_nbr  The line number in the function/file where the
   ///                       exception was thrown.
   /// @param[in]  parent    The exception that was caught.
   /// @since  0.2, 07.04.2016
   CelmaException( const char* filename, const char* funcName, int line_nbr,
                   const ExceptionBase& parent);

   /// Copy-constructor, may be used to change the (std) exception type.
   /// @tparam  U  The base-type of the other exception.
   /// @param[in]  other  The other exception to copy the data from.
   /// @since  0.2, 07.04.2016
   template< typename U> CelmaException( const CelmaException< U>& other);

   /// Copy-constructor.
   /// @param[in]  other  The other exception to copy the data from.
   /// @since  0.11, 16.01.2017
   CelmaException( const CelmaException& other);

   /// Empty, virtual destructor.
   /// @since  0.2, 07.04.2016
   ~CelmaException() noexcept override;

   /// Returns the error text with the location information.
   /// @return  The error information in the format
   ///          '\<funcname\>\@\<filename<>[\<linenbr<>]: \<text\>'.
   /// @since  0.2, 07.04.2016
   const char* what() const noexcept override;

   // copy-assignment not allowed, but move-assignment is
   CelmaException& operator =( const CelmaException&) = delete;
   CelmaException& operator =( CelmaException&&) = default;

private:
   /// If called with a parent, contains a copy-created object with the data of
   /// the parent exception.
   std::unique_ptr< ExceptionBase>  mpParent;

}; // CelmaException< BE>


// inlined methods
// ===============


template< typename BE>
   CelmaException< BE>::CelmaException( const char* filename, const char* funcName,
                                        int line_nbr, const std::string& etext):
      BE( ""),
      ExceptionBase( filename, funcName, line_nbr, etext),
      mpParent()
{
} // CelmaException< BE>::CelmaException


template< typename BE>
   CelmaException< BE>::CelmaException( const char* filename, const char* funcName,
                                        int line_nbr, const char* fmt, ...):
      BE( ""),
      ExceptionBase( filename, funcName, line_nbr, ""),
      mpParent()
{
   char     etext[ 1024];
   va_list  args;

   va_start( args, fmt);
   ::vsnprintf( etext, sizeof( etext) - 1, fmt, args);
   va_end( args);

   mExceptionText = etext;
   buildMsg();
} // CelmaException< BE>::CelmaException


template< typename BE>
   CelmaException< BE>::CelmaException( const char* filename, const char* funcName,
                                        int line_nbr, const ExceptionBase& parent):
      BE( ""),
      ExceptionBase( filename, funcName, line_nbr, ""),
      mpParent( new ExceptionBase( parent))
{
   mExceptionText.assign( "\n   previous exception: ").append( parent.message());
   buildMsg();
} // CelmaException< BE>::CelmaException


template< typename BE>
   template< typename U> CelmaException< BE>::CelmaException( const CelmaException< U>& other):
      BE( ""),
      ExceptionBase( other),
      mpParent()
{
   if (other.mpParent.get() != nullptr)
      mpParent.reset( new ExceptionBase( *other.mpParent.get()));
} // CelmaException< BE>::CelmaException


template< typename BE>
   CelmaException< BE>::CelmaException( const CelmaException& other):
      BE( ""),
      ExceptionBase( other),
      mpParent()
{
   if (other.mpParent.get() != nullptr)
      mpParent.reset( new ExceptionBase( *other.mpParent.get()));
} // CelmaException< BE>::CelmaException


template< typename BE> CelmaException< BE>::~CelmaException() noexcept
{
} // CelmaException< BE>::~CelmaException


template< typename BE> const char* CelmaException< BE>::what() const noexcept
{
   return mExceptionMsg.c_str();
} // CelmaException< BE>::what


/// Convenience: Typedef for the 'Celma logic error'.
using CelmaLogicError = CelmaException< std::logic_error>;
/// Convenience: Typedef for the 'Celma runtime error'.
using CelmaRuntimeError = CelmaException< std::runtime_error>;


} // namespace common
} // namespace celma


/// Macro to easily throw a 'Celma logic error' with the standard information
/// already set.<br>
/// @param  t  The text to add to the exception.
/// @since  0.2, 07.04.2016
#define  CELMA_LogicError( t) \
   celma::common::CelmaLogicError( __FILE__, __PRETTY_FUNCTION__, __LINE__, t)

/// Macro to easily throw a 'Celma runtime error' with the standard information
/// already set.<br>
/// @param  t  The text to add to the exception.
/// @since  0.2, 07.04.2016
#define  CELMA_RuntimeError( t) \
   celma::common::CelmaRuntimeError( __FILE__, __PRETTY_FUNCTION__, __LINE__, t)


#endif   // CELMA_COMMON_CELMA_EXCEPTION_HPP


// =====  END OF celma_exception.hpp  =====

