
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for the types provided by the iostream
/// sub-library of the STL.


#ifndef CELMA_IOSTREAM_TYPE_NAME_HPP
#define CELMA_IOSTREAM_TYPE_NAME_HPP


#include "celma/common/detail/provide_simple_type_name.hpp"


namespace celma {


/// Provides the name of the type 'std::filebuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::filebuf);
/// Provides the name of the type 'std::fstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::fstream);
/// Provides the name of the type 'std::ifstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::ifstream);
/// Provides the name of the type 'std::ios'.
PROVIDE_SIMPLE_TYPE_NAME( std::ios);
/// Provides the name of the type 'std::iostream'.
PROVIDE_SIMPLE_TYPE_NAME( std::iostream);
/// Provides the name of the type 'std::istream'.
PROVIDE_SIMPLE_TYPE_NAME( std::istream);
/// Provides the name of the type 'std::ofstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::ofstream);
/// Provides the name of the type 'std::ostream'.
PROVIDE_SIMPLE_TYPE_NAME( std::ostream);
/// Provides the name of the type 'std::streambuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::streambuf);
/// Provides the name of the type 'std::stringbuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::stringbuf);

/// Provides the name of the type 'std::wfilebuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::wfilebuf);
/// Provides the name of the type 'std::wfstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wfstream);
/// Provides the name of the type 'std::wifstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wifstream);
/// Provides the name of the type 'std::wios'.
PROVIDE_SIMPLE_TYPE_NAME( std::wios);
/// Provides the name of the type 'std::wiostream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wiostream);
/// Provides the name of the type 'std::wistream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wistream);
/// Provides the name of the type 'std::wofstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wofstream);
/// Provides the name of the type 'std::wostream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wostream);
/// Provides the name of the type 'std::wstreambuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::wstreambuf);
/// Provides the name of the type 'std::wstringbuf'.
PROVIDE_SIMPLE_TYPE_NAME( std::wstringbuf);

/// Provides the name of the type 'std::istringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::istringstream);
/// Provides the name of the type 'std::ostringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::ostringstream);
/// Provides the name of the type 'std::stringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::stringstream);
/// Provides the name of the type 'std::wistringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wistringstream);
/// Provides the name of the type 'std::wostringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wostringstream);
/// Provides the name of the type 'std::wstringstream'.
PROVIDE_SIMPLE_TYPE_NAME( std::wstringstream);


} // namespace celma


#endif   // CELMA_IOSTREAM_TYPE_NAME_HPP


// ======================  END OF iostream_type_name.hpp  ======================

