
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
/// See documentation of template function celma::common::transformCall().


#pragma once


#include <type_traits>
#include "celma/common/value_result.hpp"


namespace celma::common {


/// Use this template to turn the call of a function, that returns error
/// information through an error_code out parameter, into those of a function
/// that returns error information or the success value in the return value.<br>
/// Example:
/// - size_t file_size( std::error_code& error);
/// - ValueResult< size_t> file_size();
/// .
/// @tparam  F  Type of the function to call.
/// @param[in]  func  Function to call with an error_code out parameter.
/// @return  A ValueResult object that contains the return value from a
///          successful call, or the error information.
/// @since 0.10, 01.12.2016
template< typename F> [[nodiscard]] decltype( auto) transformCall( F func) 
{

   std::error_code  error;
   auto             result = func( error);


   if (error)
      return ValueResult< decltype( result)>( error);

   return ValueResult< decltype( result)>( result);
} // transformCall


} // namespace celma::common


// =====  END OF transform_call.hpp  =====

