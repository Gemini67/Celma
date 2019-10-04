
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
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


// C++ Standard Library includes
#include <iomanip>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LogFormatTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "celma/log/formatting/creator.hpp"


using celma::log::formatting::Creator;
using celma::log::formatting::Definition;
using celma::log::formatting::Format;
using celma::log::detail::LogMsg;


class DefinitionAccess: public Definition
{
public:
   size_t size() const
   {
      return mFields.size();
   } // size
   
};



/// Test that an empty format definition results in an empty string.
/// @since  1.0.0, 27.09.2017
BOOST_AUTO_TEST_CASE( test_empty)
{

   DefinitionAccess    my_def;
   LogMsg              msg( "filename.cpp", "test_one", __LINE__);
   std::ostringstream  oss;
   Format              log_format( my_def);


   log_format.format( oss, msg);

   BOOST_REQUIRE( oss.str().empty());

} // test_empty



/// Test the formatting of a log message with different fields.
/// @since  0.11, 07.12.2016
BOOST_AUTO_TEST_CASE( test_fields)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);

   format_creator << clf::filename;

   LogMsg              msg( "filename.cpp", "test_one", __LINE__);
   std::ostringstream  oss;

   {
      Format  log_format( my_def);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp");
   } // end scope

   format_creator << "|" << clf::func_name;

   oss.str( "");

   {
      Format  log_format( my_def);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp|test_one");
   } // end scope

} // test_fields



/// Test the left-alignment and the fixed width in formatting a log message.
/// @since  1.0.0, 26.09.2017
BOOST_AUTO_TEST_CASE( test_align_fixedwidth)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);

   format_creator << 20 << clf::left << clf::filename << ":"
                  << 6 << clf::line_nbr;

   LogMsg              msg( "filename.cpp", "test_one", 1234);
   std::ostringstream  oss;
   Format              log_format( my_def);

   log_format.format( oss, msg);

   BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp        :  1234");

} // test_align_fixedwidth



/// Test formatting the date, time and date_time fields.
/// @since  1.0.0, 26.09.2017
BOOST_AUTO_TEST_CASE( test_date_time)
{

   namespace clf = celma::log::formatting;

   // date default formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::date;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "2017-09-27");
   } // end scope

   // date custom formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::formatString( "%d") << clf::date;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "27");
   } // end scope

   // time default formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::time;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "17:17:28");
   } // end scope

   // time custom formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::formatString( "%r") << clf::time;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "05:17:28 PM");
   } // end scope

   // timestamp default formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::date_time;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "2017-09-27 17:17:28");
   } // end scope

   // timestamp custom formatting
   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      format_creator << clf::formatString( "now: %c") << clf::date_time;

      LogMsg              msg( "filename.cpp", "test_one", 1234);
      std::ostringstream  oss;
      Format              log_format( my_def);

      msg.setTimestamp( 1506525448);
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "now: Wed Sep 27 17:17:28 2017");
   } // end scope

} // test_date_time



/// Test formatting the remaining fields.
///
/// @since  1.25.0, 02.05.2019
BOOST_AUTO_TEST_CASE( pid_level)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);

   format_creator << 5 << clf::pid << "|" << clf::thread_id << "|" << clf::level
      << "|" << clf::log_class << "|" << clf::error_nbr;

   LogMsg              msg( "filename.cpp", "test_one", 1234);
   std::ostringstream  oss;
   Format              log_format( my_def);

   msg.setLevel( celma::log::LogLevel::warning);
   msg.setClass( celma::log::LogClass::application);
   msg.setErrorNumber( 13);

   log_format.format( oss, msg);

   std::ostringstream  oss_exp;
   oss_exp << std::setw( 5) << ::getpid() << "|0x" << std::hex << ::pthread_self()
      << "|Warning|Application|13";

   BOOST_REQUIRE_EQUAL( oss.str(), oss_exp.str());

} // pid_level



/// Create a log message that contains an attribute.
///
/// @since  1.15.0, 12.10.2018
BOOST_AUTO_TEST_CASE( text_with_attribute)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);

   format_creator << 20 << clf::left << clf::filename << ":"
                  << 6 << clf::line_nbr << " | "
                  << clf::attribute( "shade") << "-"
                  << clf::attribute( "color");

   LogMsg              msg( "filename.cpp", "test_one", 1234);
   std::ostringstream  oss;
   Format              log_format( my_def);

   celma::log::Logging::instance().addAttribute( "shade", "light");
   celma::log::Logging::instance().addAttribute( "color", "blue");

   log_format.format( oss, msg);

   BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp        :  1234 | light-blue");

} // text_with_attribute



/// Create a log message that contains an attribute.
///
/// @since  1.15.0, 12.10.2018
BOOST_AUTO_TEST_CASE( text_with_attribute_scoped)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);

   format_creator << 20 << clf::left << clf::filename << ":"
                  << 6 << clf::line_nbr << " | "
                  << clf::attribute( "shade") << "-"
                  << clf::attribute( "color");

   LogMsg              msg( "filename.cpp", "test_one", 1234);
   std::ostringstream  oss;
   Format              log_format( my_def);

   celma::log::Logging::instance().addAttribute( "shade", "light");
   celma::log::Logging::instance().addAttribute( "color", "blue");

   log_format.format( oss, msg);

   BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp        :  1234 | light-blue");

   {
      LOG_ATTRIBUTE( "shade", "dark");

      oss.str( "");
      log_format.format( oss, msg);

      BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp        :  1234 | dark-blue");
   } // end scope

   oss.str( "");
   log_format.format( oss, msg);

   BOOST_REQUIRE_EQUAL( oss.str(), "filename.cpp        :  1234 | light-blue");

} // text_with_attribute_scoped



// all fields


// =====  END OF test_log_format.cpp  =====

