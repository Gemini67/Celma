
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "value formatting" in the module Handler,
**    using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HandlerFormatTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/detail/i_format.hpp"
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;


namespace {


/// Helper class: An additional formatter.
///
/// @since  1.32.0, 19.08.2019
class RemoveDigitFormatter final : public celma::prog_args::detail::IFormat
{
public:
   /// Default constructor.
   ///
   /// @since  1.32.0, 19.08.2019
   RemoveDigitFormatter():
      IFormat( "remove-digit")
   {
   } // RemoveDigitFormatter::RemoveDigitFormatter

   /// Empty, default destructor.
   ///
   /// @since  1.32.0, 19.08.2019
   ~RemoveDigitFormatter() override = default;

   /// The formatting function: Remove all digits from the string.
   ///
   /// @param[in,out]  val  The string to format.
   /// @since  1.32.0, 19.08.2019
   void formatValue( std::string& val) const override
   {
      auto  i = val.begin();
      while (i != val.end())
      {
         if (std::isdigit( *i))
         {
            i = val.erase( i);
         } else
         {
            ++i;
         } // end if
      }
   } // RemoveDigitFormatter::formatValue

}; // RemoveDigitFormatter


/// Helper function to use the formatting class easily with addFormat().
///
/// @return  A new object of the formatting class RemoveDigitFormatter.
/// @since  1.32.0, 19.08.2019
celma::prog_args::detail::IFormat* noDigit()
{
   return new RemoveDigitFormatter();
} // noDigit


} // namespace



/// Verify that errors regarding formats are caught.
///
/// @since  1.23.1, 15.04.2019
BOOST_AUTO_TEST_CASE( errors)
{

   // ensure that calling addFormat() with a NULL object pointer throws
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
         ->addFormat( nullptr), std::logic_error);
   } // end scope

   // ensure that calling addFormat() with a NULL object pointer throws
   {
      Handler  ah( 0);
      int      dummy = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( dummy), "int")
         ->addFormat( nullptr), std::invalid_argument);
   } // end scope

   // ensure that calling addFormat() on a wrong type throws
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
         ->addFormat( celma::prog_args::uppercase()), std::logic_error);
   } // end scope

   // ensure that calling addFormat() with an empty format pattern throws
   {
      Handler      ah( 0);
      std::string  dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( dummy), "string")
         ->addFormat( celma::prog_args::anycase( "")), std::invalid_argument);
   } // end scope

   // ensure that calling addFormatPos() on a wrong type throws
   {
      Handler      ah( 0);
      std::string  my_string;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( my_string), "string")
         ->addFormatPos( 1, celma::prog_args::uppercase()), std::logic_error);
   } // end scope

} // errors



/// Check formatting to upper- and lowercase.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( format_case)
{

   std::optional< std::string>  name;


   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addFormat( celma::prog_args::uppercase());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n process1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   name.reset();

   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addFormat( celma::prog_args::lowercase());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n PROceSS1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "process1");
   } // end scope

   // test with a string directly
   {
      Handler      ah( 0);
      std::string  my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::uppercase());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a PROceSS1"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "PROCESS1");
   } // end scope

} // format_case



/// Check any-case formatting.
///
/// @since  1.23.0, 11.04.2019
BOOST_AUTO_TEST_CASE( format_anycase)
{

   // must throw when the format string is empty
   {
      Handler      ah( 0);
      std::string  my_string;

      BOOST_REQUIRE_THROW( ah.addArgument( "a", DEST_VAR( my_string),
         "another string")->addFormat( celma::prog_args::anycase( "")),
         std::invalid_argument);
   } // end scope

   // test special anycase formatting
   {
      Handler      ah( 0);
      std::string  my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUlllll"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a bigSmAlL"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGsmall");
   } // end scope

   // format string longer than input string
   {
      Handler      ah( 0);
      std::string  my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUlllll"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a bigS"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGs");
   } // end scope

   // format string shorter than input string
   {
      Handler      ah( 0);
      std::string  my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUl"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a bigSmAlL"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGsmAlL");
   } // end scope

} // format_anycase



/// Check formatting by a function.
///
/// @since  1.47.0, 21.11.2021
BOOST_AUTO_TEST_CASE( format_function)
{

   auto formatter = []( std::string& val)
   {
      int  i_value = std::atoi( val.c_str());
      if (val.back() == 'k')  i_value *= 1024;
      if (val.back() == 'M')  i_value *= 1024 * 1024;
      val = std::to_string( i_value);
   };

   {
      Handler  ah( 0);
      int      buffer_size = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( buffer_size),
         "buffer size")->addFormat( celma::prog_args::formatFunction(
            formatter, "apply size suffix")));

      evalArgumentString( ah, "-b 900");
      BOOST_REQUIRE_EQUAL( buffer_size, 900);
   } // end scope

   {
      Handler  ah( 0);
      int      buffer_size = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( buffer_size),
         "buffer size")->addFormat( celma::prog_args::formatFunction(
            formatter, "apply size suffix")));

      evalArgumentString( ah, "-b 900k");
      BOOST_REQUIRE_EQUAL( buffer_size, 921'600);
   } // end scope

   {
      Handler  ah( 0);
      int      buffer_size = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( buffer_size),
         "buffer size")->addFormat( celma::prog_args::formatFunction(
            formatter, "apply size suffix")));

      evalArgumentString( ah, "-b 900M");
      BOOST_REQUIRE_EQUAL( buffer_size, 943'718'400);
   } // end scope

} // format_function



/// Add multiple formatters.
///
/// @since  1.32.0, 19.08.2019
BOOST_AUTO_TEST_CASE( multiple_formatters)
{

   {
      Handler      ah( 0);
      std::string  my_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( my_string),
         "another string")->addFormat( celma::prog_args::lowercase())
         ->addFormat( noDigit()));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a Hello123World"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "helloworld");
   } // end if

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfListArgVar);
      std::string         my_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( my_string),
         "another string")->addFormat( celma::prog_args::lowercase())
         ->addFormat( noDigit()));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
         "-a Hello123World --list-arg-vars"));

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-a' value type 'std::string', destination 'my_string', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, 2 formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-a' value type 'std::string', destination 'my_string', value = \"helloworld\".\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, 2 formats.\n"
         "\n"));
   } // end scope

   // test argument help
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::string         my_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( my_string),
         "another string")->addFormat( celma::prog_args::lowercase())
         ->addFormat( noDigit()));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a AND4now "
         "--help-arg-full a"));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "andnow");

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-a', usage:\n"
         "   another string\n"
         "Properties:\n"
         "   destination variable name:  my_string\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     -\n"
         "   check original value:       false\n"
         "   formats:                    all: lowercase, remove-digit\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // multiple_formatters



// =====  END OF test_argh_format_c.cpp  =====

