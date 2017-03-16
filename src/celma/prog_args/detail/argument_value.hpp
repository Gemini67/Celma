
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::ArgumentValue.


#ifndef CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP
#define CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP


#include "celma/common/any_type_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Used by the class ValueHandler to store a destination variable of a specific
/// type.<br>
/// Not much code is actually needed here, since everything is done by
/// common::Value<> already.
/// @tparam  T  The type of the variable to store.
/// @since  0.14.0, 09.02.2017
template< typename T> class ArgumentValue:
   public common::Value< T, common::AnyBase>
{

   using common::Value< T, common::AnyBase>::mValue;

public:
   /// Default destructor is just fine.
   ~ArgumentValue() = default;

   /// Returns the value.
   /// @return  The value stored internally.
   /// @since  0.14.0, 09.02.2017
   T& operator ()();

}; // ArgumentValue< T>


// inlined methods
// ===============


template< typename T> T& ArgumentValue< T>::operator ()()
{
   return mValue;
} // ArgumentValue< T>::operator ()


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP


// ========================  END OF argument_value.hpp  ========================

