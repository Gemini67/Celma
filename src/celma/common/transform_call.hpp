
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
/// See documentation of template function celma::common::transformCall().


#ifndef CELMA_COMMON_TRANSFORM_CALL_HPP
#define CELMA_COMMON_TRANSFORM_CALL_HPP


#include <type_traits>
#include "celma/common/value_result.hpp"


namespace celma { namespace common {


/// Use this template to turn the call of a function, that returns error
/// information through an error_code out parameter, into those of a function
/// that returns error information or the success value in the return value.<br>
/// Example:
/// - size_t file_size( std::error_code& error);
/// - ValueResult< size_t> file_size();
/// .
/// @tparam  F  The type of the function to call.
/// @param[in]  func  The function to call with an error_code out parameter.
/// @return  A ValueResult object that contains the return value from a
///          successful call, or the error information.
/// @since 0.10, 01.12.2016
template< typename F> decltype( auto) transformCall( F func) 
{

   std::error_code  error;
   auto             result = func( error);


   if (error)
      return ValueResult< decltype( result)>( error);

   return ValueResult< decltype( result)>( result);
} // transformCall


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TRANSFORM_CALL_HPP


// ========================  END OF transform_call.hpp  ========================
