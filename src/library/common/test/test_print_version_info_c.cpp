
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the function celma::common::printVersionInfo().
**
--*/


// module to test headerfile include
#include "celma/common/print_version_info.hpp"


// OS/C lib includes
#include <cstdlib>



/// The main function.
/// No, really.<br>
/// Prints the version of the library to \c stdout.
///
/// @since  x.y.z, 13.11.2019
int main()
{

   celma::common::printVersionInfo();

   ::exit( EXIT_SUCCESS);
} // main



// =====  END OF test_print_version_info_c.cpp  =====

