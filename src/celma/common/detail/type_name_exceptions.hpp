
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for the exception classes.


#ifndef CELMA_TYPE_NAME_EXCEPTIONS_HPP
#define CELMA_TYPE_NAME_EXCEPTIONS_HPP


#include <stdexcept>
#include "celma/common/detail/provide_simple_type_name.hpp"


namespace celma {


/// Provides the name of the type 'std::exception'.
PROVIDE_SIMPLE_TYPE_NAME( std::exception);

/// Provides the name of the type 'std::domain_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::domain_error);
/// Provides the name of the type 'std::invalid_argument'.
PROVIDE_SIMPLE_TYPE_NAME( std::invalid_argument);
/// Provides the name of the type 'std::length_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::length_error);
/// Provides the name of the type 'std::logic_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::logic_error);
/// Provides the name of the type 'std::out_of_range'.
PROVIDE_SIMPLE_TYPE_NAME( std::out_of_range);
/// Provides the name of the type 'std::overflow_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::overflow_error);
/// Provides the name of the type 'std::range_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::range_error);
/// Provides the name of the type 'std::runtime_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::runtime_error);
/// Provides the name of the type 'std::underflow_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::underflow_error);


} // namespace celma


#endif   // CELMA_TYPE_NAME_EXCEPTIONS_HPP


// =====  END OF type_name_exceptions.hpp  =====

