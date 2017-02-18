
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
/// See documentation of class celma::prog_args::detail::@@@.


#ifndef CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP
#define CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP


#include "celma/common/type_name.hpp"
#include "celma/prog_args/detail/value_storage.hpp"


namespace celma { namespace prog_args { namespace detail {


/// @since  x.y.z, 09.02.2017
template< typename T> class ArgumentValue: public ValueStorage
{
public:
   ArgumentValue();

   T& operator ()();

private:
   T  mValue;

};


template< typename T> ArgumentValue< T>::ArgumentValue():
   ValueStorage( type< T>::name()),
   mValue()
{
} // 


template< typename T> T& ArgumentValue< T>::operator ()()
{
   return mValue;
} // 


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_VALUE_HPP


// ========================  END OF argument_value.hpp  ========================

