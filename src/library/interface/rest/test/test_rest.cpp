
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test headerfile include
#include "celma/interface/rest/rest.hpp"


// Boost includes
#define BOOST_TEST_MODULE RestTest
#include <boost/test/unit_test.hpp>



/// 
/// @since  x.y.z, 01.05.2023
BOOST_AUTO_TEST_CASE( rest)
{


   BOOST_REQUIRE_NO_THROW( celma::interface::rest::rest());

} // no_arguments



// =====  END OF test_rest.cpp  =====

