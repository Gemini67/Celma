
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module celma::appl::GenerationFileCreator, using the
**    Boost.Test framework.
**
--*/


// include of the tested module's header file
#include "celma/appl/generation_file_creator.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFormatTest
#include <boost/test/unit_test.hpp>



BOOST_TEST_DONT_PRINT_LOG_VALUE(celma::appl::GenerationFileDefinition::ElementTypes);


using celma::appl::GenerationFileCreator;
using celma::appl::GenerationFileDefinition;
using celma::appl::customProperty;
using celma::appl::date_time;
using celma::appl::env;
using celma::appl::file_nbr;
using celma::appl::fill_char;
using celma::appl::project_path;
using celma::appl::sep;
using celma::appl::width;


class DefinitionAccess: public GenerationFileDefinition
{
public:
   size_t size() const
   {
      return mFields.size();
   } // DefinitionAccess::size

   const Field& operator []( size_t idx) const
   {
      return mFields[ idx];
   } // DefinitionAccess::operator []
      
};



/// 
/// @since  1.0.0, 07.12.2016
BOOST_AUTO_TEST_CASE( test_two)
{

   DefinitionAccess       my_def;
   GenerationFileCreator  creator( my_def);


   creator << project_path << "/log/my.log";

   BOOST_REQUIRE_EQUAL( my_def.size(), 2);

   BOOST_REQUIRE_EQUAL( my_def[ 0].mType,
                        GenerationFileDefinition::ElementTypes::projectPath);

   BOOST_REQUIRE_EQUAL( my_def[ 1].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 1].mParamInfo, "/log/my.log");

} // end test_two



/// 
/// @since  1.0.0, 07.12.2016
BOOST_AUTO_TEST_CASE( test_two_sep)
{

   DefinitionAccess       my_def;
   GenerationFileCreator  creator( my_def);


   creator << project_path << sep << "/log/my.log";

   BOOST_REQUIRE_EQUAL( my_def.size(), 3);

   BOOST_REQUIRE_EQUAL( my_def[ 0].mType,
                        GenerationFileDefinition::ElementTypes::projectPath);

   BOOST_REQUIRE_EQUAL( my_def[ 1].mType,
                        GenerationFileDefinition::ElementTypes::separator);

   BOOST_REQUIRE_EQUAL( my_def[ 2].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 2].mParamInfo, "/log/my.log");

} // end test_two_sep



/// 
/// @since  x.y, 31.01.2017
BOOST_AUTO_TEST_CASE( test_all)
{

   DefinitionAccess       my_def;
   GenerationFileCreator  creator( my_def);


   creator << project_path << sep << env( "LOG") << sep << "/my_"
           << date_time( "%X") << "_" << width( 3) << fill_char( '0')
           << file_nbr << "-" << customProperty( "LOG_TYPE") << ".log";

   BOOST_REQUIRE_EQUAL( my_def.size(), 11);

   BOOST_REQUIRE_EQUAL( my_def[ 0].mType,
                        GenerationFileDefinition::ElementTypes::projectPath);

   BOOST_REQUIRE_EQUAL( my_def[ 1].mType,
                        GenerationFileDefinition::ElementTypes::separator);

   BOOST_REQUIRE_EQUAL( my_def[ 2].mType,
                        GenerationFileDefinition::ElementTypes::env);
   BOOST_REQUIRE_EQUAL( my_def[ 2].mParamInfo, "LOG");

   BOOST_REQUIRE_EQUAL( my_def[ 3].mType,
                        GenerationFileDefinition::ElementTypes::separator);

   BOOST_REQUIRE_EQUAL( my_def[ 4].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 4].mParamInfo, "/my_");

   BOOST_REQUIRE_EQUAL( my_def[ 5].mType,
                        GenerationFileDefinition::ElementTypes::dateTime);
   BOOST_REQUIRE_EQUAL( my_def[ 5].mParamInfo, "%X");

   BOOST_REQUIRE_EQUAL( my_def[ 6].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 6].mParamInfo, "_");

   BOOST_REQUIRE_EQUAL( my_def[ 7].mType,
                        GenerationFileDefinition::ElementTypes::fileNbr);
   BOOST_REQUIRE_EQUAL( my_def[ 7].mFixedWidth, 3);
   BOOST_REQUIRE_EQUAL( my_def[ 7].mFillChar, '0');

   BOOST_REQUIRE_EQUAL( my_def[ 8].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 8].mParamInfo, "-");

   BOOST_REQUIRE_EQUAL( my_def[ 9].mType,
                        GenerationFileDefinition::ElementTypes::customProperty);
   BOOST_REQUIRE_EQUAL( my_def[ 9].mParamInfo, "LOG_TYPE");

   BOOST_REQUIRE_EQUAL( my_def[ 10].mType,
                        GenerationFileDefinition::ElementTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def[ 10].mParamInfo, ".log");

} // end test_all



// =====  END OF test_generation_file_creator.cpp  =====

