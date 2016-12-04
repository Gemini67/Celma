
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
/// See documentation of template class celma::common::ValueResult.


#ifndef CELMA_COMMON_VALUE_RESULT_HPP
#define CELMA_COMMON_VALUE_RESULT_HPP


#include <string>
#include <system_error>


namespace celma { namespace common {


/// Use this template to solve the following dilemma:
/// - You want to implement a function that returns a value.
/// - But the function can also fail, so you need to either:
///   - throw an exception
///   - add an out-parameter in which you can return the error information, or
///   - return the success/failure information from the function, and pass
///     the value to return in the success case by out-parameter.
/// - Sometimes it also possible to return all in one return value, e.g. values
///   below zero are error codes, above zero are success values.
/// .
/// By using this template you can return the success/error information plus the
/// return value in one return parameter, without the need for additional
/// out-parameters.<br>
/// The object can be checked in boolean expressions to determine if an error
/// was returned or a value, afterwards the error information or the value can
/// be retrieved from the object.
/// @tparam  T  The type of the value that is returned when the function was
///             successful.
/// @since 0.10, 01.12.2016
template< typename T> class ValueResult
{
public:
   /// Constructor for the success case. Stores the value to return.
   /// @param[in]  success_result  The value to return.
   /// @since 0.10, 01.12.2016
   explicit ValueResult( const T& success_result);

   /// Constructor for the error/failure case. Stores the error information to
   /// return.
   /// @param[in]  error  The error information to return.
   /// @since 0.10, 01.12.2016
   explicit ValueResult( const std::error_code& error);

   /// Default copy constructor.
   ValueResult( const ValueResult&) = default;

   /// Default destructor.
   ~ValueResult() = default;

   /// Returns if the object contains a value from a successful call, or error
   /// information.<br>
   /// Be aware that this operator uses the inverse logic as the bool operator
   /// of the std::error_code class.
   /// @return  \c true if the function was successful and the object contains
   ///          the return value.
   /// @since 0.10, 01.12.2016
   operator bool() const;

   /// Returns the value returned by a successful function call.<br>
   /// If the function failed, i.e. this object actually contains the error 
   /// information, the value returned here will be a default-initialised object
   /// of type \c T.
   /// @return  The success value as provided when the object was created.
   /// @since 0.10, 01.12.2016
   const T& value() const;

   /// Returns the error information as set by a failed function call.<br>
   /// If the function was successful, i.e. this object actually contains the
   /// success value, the value returned here will a default-initialised error
   /// object.
   /// @return  The error information as provided by the failed function call
   ///          when the object was created.
   /// @since 0.10, 01.12.2016
   const std::error_code& getError() const;

private:
   // Theoretically, these two values could be handled in a union, but the
   // error object is also used to determine the error/success case, so we
   // always need both.

   /// The object that stores the error information.
   const std::error_code  mErrorCode;
   /// The return value in the success case.
   const T                mReturnValue;

}; // ValueResult< T>


// inlined methods
// ===============


template< typename T> ValueResult< T>::ValueResult( const T& success_result):
   mErrorCode(),
   mReturnValue( success_result)
{
} // ValueResult< T>::ValueResult


template< typename T>
   ValueResult< T>::ValueResult( const std::error_code& error):
      mErrorCode( error),
      mReturnValue()
{
} // ValueResult< T>::ValueResult


template< typename T> ValueResult< T>::operator bool() const
{
   return !static_cast< bool>( mErrorCode);
} // ValueResult< T>::operator bool


template< typename T> const T& ValueResult< T>::value() const
{
   return mReturnValue;
} // ValueResult< T>::value


template< typename T> const std::error_code& ValueResult< T>::getError() const
{
   return mErrorCode;
} // ValueResult< T>::getError


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_VALUE_RESULT_HPP


// =========================  END OF value_result.hpp  =========================

