
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module filename::Builder, using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/log/filename/builder.hpp"


// OS/C lib includes
#include <ctime>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LogFilenameBuiderTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/filename/creator.hpp"


using celma::log::filename::Creator;
using celma::log::filename::Definition;
using celma::log::filename::Builder;


namespace {


/// Helper class to access data within the definition class.
/// @since  1.0.0, 20.10.2017
class DefinitionAccess: public Definition
{
public:
   /// Returns the size of the parts container, i.e. the number of path/filename
   /// fields in the definition.
   /// @return  Number of part fields in the container.
   /// @since  1.0.0, 20.10.2017
   size_t size() const
   {
      return mParts.size();
   } // DefinitionAccess::size
   
}; // DefinitionAccess


} // namespace



/// Test that an empty format definition results in an error.
/// @since  1.0.0, 20.10.2017
BOOST_AUTO_TEST_CASE( test_empty)
{

   DefinitionAccess  my_def;

   BOOST_REQUIRE_THROW( Builder  log_filename( my_def), std::invalid_argument);

} // test_empty



/// Test the creation of a logfile name with different parts.
/// @since  1.0.0, 20.10.2017
BOOST_AUTO_TEST_CASE( test_parts)
{

   namespace clf = celma::log::filename;

   const time_t  test_timestamp = 1508518038;


   // test only with a constant part
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << "/var/log";

      Builder      fn_builder( my_def);
      std::string  filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13, ::time( nullptr)));
      BOOST_REQUIRE_EQUAL( filename, "/var/log");
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def), filename);
   } // end scope

   // test only with a date part
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << clf::date;

      Builder      fn_builder( my_def);
      std::string  filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, "2017-10-20");
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13, test_timestamp),
         filename);
   } // end scope

   // test only with an unformatted logfile number part
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << clf::number;

      Builder      fn_builder( my_def);
      std::string  filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, "13");
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13), filename);
   } // end scope

   // test only with a logfile number part with size but no fill character
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << 4 << clf::number;

      Builder      fn_builder( my_def);
      std::string  filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, "0013");
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13), filename);
   } // end scope

   // test only with a logfile number part, with size and another fill character
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << 5 << '_' << clf::number;

      Builder      fn_builder( my_def);
      std::string  filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, "___13");
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13), filename);
   } // end scope

   // test only with an unformatted pid
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << clf::pid;

      Builder            fn_builder( my_def);
      const std::string  exp_filename = std::to_string( ::getpid());
      std::string        filename;

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, exp_filename);
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13), exp_filename);
   } // end scope

   // test only with a pid part with size but no fill character
   {
      DefinitionAccess  my_def;
      Creator           fn_def_creator( my_def);

      fn_def_creator << 5 << clf::pid;

      Builder      fn_builder( my_def);
      std::string  filename;
      char         exp_filename[ 20];

      ::sprintf( exp_filename, "%05d", ::getpid());

      BOOST_REQUIRE_NO_THROW( fn_builder.filename( filename, 13,
                                                   test_timestamp));
      BOOST_REQUIRE_EQUAL( filename, exp_filename);
      BOOST_REQUIRE_EQUAL( Builder::filename( my_def, 13), exp_filename);
   } // end scope

} // test_fields



// =====  END OF test_log_filename_builder.cpp  =====

