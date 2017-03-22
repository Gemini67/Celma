
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
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
#include "celma/appl/generation_file_creator.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFormatTest
#include <boost/test/unit_test.hpp>


using celma::appl::GenerationFileCreator;
using celma::appl::customProperty;
using celma::appl::date_time;
using celma::appl::env;
using celma::appl::file_nbr;
using celma::appl::fill_char;
using celma::appl::project_path;
using celma::appl::sep;
using celma::appl::width;


class DefinitionAccess: public celma::appl::GenerationFileDefinition
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

   DefinitionAccess       my_def;
   GenerationFileCreator  creator( my_def);


   creator << project_path << "/log/my.log";

   BOOST_REQUIRE_EQUAL( my_def.size(), 2);

} // end test_one



/// 
/// @since  x.y, 31.01.2017
BOOST_AUTO_TEST_CASE( test_all)
{

   DefinitionAccess       my_def;
   GenerationFileCreator  creator( my_def);


   creator << project_path << sep << env( "LOG") << sep << "/my_"
           /* << date_time( "%X") << "_" */ << width( 3) << fill_char( '0')
           << file_nbr << "-" << customProperty( "LOG_TYPE") << ".log";

   BOOST_REQUIRE_EQUAL( my_def.size(), 9);

} // end test_all



// =================  END OF test_generation_file_creator.cpp  =================
