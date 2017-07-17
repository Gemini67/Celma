
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module formatting::Format, using the Boost.Test
**    framework.
**
--*/


// include of the tested module's header file
#include "celma/log/formatting/format.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFormatTest
#include <boost/test/unit_test.hpp>


using celma::log::formatting::Format;


class DefinitionAccess: public celma::log::formatting::Definition
{
public:
   size_t size() const
   {
      return mFields.size();
   } // size
   
};



/// 
/// @since  0.11, 07.12.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   DefinitionAccess  my_def;
   Format            log_format( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

} // end test_one



// =======================  END OF test_log_format.cpp  =======================
