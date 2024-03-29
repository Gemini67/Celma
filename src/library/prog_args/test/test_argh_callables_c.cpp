
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for arguments resulting in a function/method call in the
**    module celma::prog_args::Handler, using the Boost.Test module.
**
--*/


/// @todo: Mandatory free values


// module to test, headerfile include
#include "celma/prog_args.hpp"


// STL includes
#include <sstream>
#include <stdexcept>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCallablesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/multi_setter.hpp"
#include "celma/prog_args/argument_error.hpp"
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;
using std::string;


namespace {


/// Global variable used for the argument function handler check.
bool    gotCalled = false;
string  gotVal;


/// This function should be called when the corresponding argument is set on
/// the command line.
/// @since  0.2, 10.04.2016
void handlerFun( bool)
{

   gotCalled = true;

} // handlerFun


/// This function should be called when the corresponding argument is set on
/// the command line.
/// @param[in]  v  The value.
/// @since  0.2, 10.04.2016
void handlerFunValue( const string& v, bool)
{

   if (v.empty())
      throw celma::prog_args::argument_error( "handlerFunValue() always expects"
         " a value!");

   gotVal = v;

} // handlerFunValue


/// Helper class to test the argument handler feature with a class method.
/// @since  0.2, 10.04.2016
class TestArgFunc : private boost::noncopyable
{
public:
   TestArgFunc():
      mBoolValue( false)
   {
   } // TestArgFunc::TestArgFunc

   void handlerFunc( const string& s, bool)
   {
      if (s.empty())
         throw celma::prog_args::argument_error( "handlerFunc() always expects "
            "a value!");

      mValue = s;
   } // TestArgFunc::handlerFunc

   /// 
   /// @throw  Exception .
   /// @since  0.2, 10.04.2016
   void resetValue()
   {
      mValue.clear();
   } // TestArgFunc::resetValue

   /// Called when a value was passed to the argument.
   /// @param[in]  optValue  The value from the command line.
   /// @since  0.2, 10.04.2016
   void boolFunc( const string& optValue, bool)
   {
      if (!optValue.empty())
         throw celma::prog_args::argument_error( "TestArgFunc::boolFunc() must "
            "not be called with a value!");

      mBoolValue = true;
   } // TestArgFunc::boolFunc

   const string& value() const
   {
      return mValue;
   } // TestArgFunc::value

   bool boolValue() const
   {
      return mBoolValue;
   } // TestArgFunc::boolValue

private:
   string  mValue;
   bool    mBoolValue;

}; // TestArgFunc


/// Helper class to test a method that accepts no values.
///
/// @since  1.25.0, 30.04.2019
class NoValueTest
{
public:
   NoValueTest() = default;

   /// Called when the argument was used on the command line.
   ///
   /// @since  1.25.0, 30.04.2019
   void assign( bool)
   {
      ++mNumCalls;
   } // NoValueTest::assign

   /// Returns how many times the assign() method was called.
   ///
   /// @return  Number of times that assign() was called.
   /// @since  1.25.0, 30.04.2019
   int numCalls() const
   {
      return mNumCalls;
   } // MultiValueTest::numCalls

private:
   /// Counter for the calls of assign().
   int  mNumCalls = 0;

}; // NoValueTest


/// Helper class to test a method that accepts multiple values.
///
/// @since  1.25.0, 30.04.2019
class MultiValueTest
{
public:
   MultiValueTest() = default;

   /// Called with the value(s) from the command line.
   ///
   /// @param[in]  Value from the command line, real value is ignored.
   /// @since  1.25.0, 30.04.2019
   void assign( const std::string&, bool)
   {
      ++mNumValues;
   } // MultiValueTest::assign

   /// Returns how many times the assign() method was called.
   ///
   /// @return  Number of times that assign() was called.
   /// @since  1.25.0, 30.04.2019
   int numValues() const
   {
      return mNumValues;
   } // MultiValueTest::numValues

private:
   /// Counter for the calls of assign().
   int  mNumValues = 0;

}; // MultiValueTest


} // namespace



/// Check that errors are handler properly.
///
/// @since  1.25.0, 30.04.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function with value")
         ->setValueMode( Handler::ValueMode::none), std::invalid_argument);
   } // end scope

   // pass a value to a method that does not accept values
   {
      Handler      ah( 0);
      NoValueTest  nvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_METHOD( NoValueTest, assign, nvt), "Method without value"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v juhu"),
         std::invalid_argument);
   } // end scope

   // pass no value to a method that does require values
   {
      Handler         ah( 0);
      MultiValueTest  mvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_METHOD_VALUE( MultiValueTest, assign, mvt), "Method with value"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f"),
         celma::prog_args::argument_error);
   } // end scope

} // errors



/// Test function for an optional argument that results in a function call.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( function_check)
{

   // function that does not accept a value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION( handlerFun), "Function"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
      BOOST_REQUIRE( gotCalled);
   } // end scope

   gotCalled = false;

   // function that does not accept a value, value is (unexpected) free value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION( handlerFun), "Function"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f hello"),
         std::invalid_argument);
   } // end scope

   gotCalled = false;

   // function that does expect a value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f"),
         celma::prog_args::argument_error);
   } // end scope

   // function that does expect a value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f hello"));
      BOOST_REQUIRE_EQUAL( gotVal, "hello");
   } // end scope

   // function with value mode optional, actually expects a value (without value)
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f"),
         celma::prog_args::argument_error);
   } // end scope

   gotVal.clear();

   // function with value mode optional, actually expects a value (with value)
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f v1"));
      BOOST_REQUIRE_EQUAL( gotVal, "v1");
   } // end scope

   gotVal.clear();

} // function_check



/// Test function for a mandatory argument that results in a function call.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mandatory_function_check)
{

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, ""), std::runtime_error);
   } // end scope

   gotVal.clear();

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f"),
         celma::prog_args::argument_error);
   } // end scope

   gotVal.clear();

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f v1"));
      BOOST_REQUIRE_EQUAL( gotVal, "v1");
   } // end scope

   gotVal.clear();

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--fun"),
         celma::prog_args::argument_error);
   } // end scope

   gotVal.clear();

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--fun v2"));
      BOOST_REQUIRE_EQUAL( gotVal, "v2");
   } // end scope

   gotVal.clear();

   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun",
         DEST_FUNCTION_VALUE( handlerFunValue), "Function")
         ->setValueMode( Handler::ValueMode::optional)->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--fun=v3"));
      BOOST_REQUIRE_EQUAL( gotVal, "v3");
   } // end scope

} // mandatory_function_check



/// Test function for an optional argument that results in a method call of a
/// method that requires a value.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( value_method_check)
{

   TestArgFunc  myTestObj;


   // value mode unknown
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method"));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m"),
         celma::prog_args::argument_error);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, but no value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m"),
                           celma::prog_args::argument_error);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m v1"));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   myTestObj.resetValue();

   // value mode unknown
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method"));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "--method"),
                           celma::prog_args::argument_error);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, but no value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "--method"),
         celma::prog_args::argument_error);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--method v1"));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      Handler  ah( 0);
      
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--method=v1"));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   // check list arg vars feature
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfListArgVar);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--method=v1 --list-arg-var"));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-m,--method' calls function/method 'TestArgFunc::handlerFunc'.\n"
         "   value 'optional' (1), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

} // value_method_check



/// Test function for an optional argument that results in a method call of a
/// method that doesn't accept values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( bool_method_check)
{

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool",
         DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b"));
      BOOST_REQUIRE_EQUAL( myTestObj.boolValue(), true);
   } // end scope

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool",
         DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m true"),
                           std::invalid_argument);
   } // end scope

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool",
         DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--bool"));
      BOOST_REQUIRE_EQUAL( myTestObj.boolValue(), true);
   } // end scope

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool",
         DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--bool true"),
                           celma::prog_args::argument_error);
   } // end scope

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool",
         DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--bool=true"),
                           celma::prog_args::argument_error);
   } // end scope

} // bool_method_check



/// Check setting two values on two variables using the template MultiSetter2.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( multi_setter2_check)
{

   Handler  ah( 0);
   int      var1;
   string   var2;

   using my_setter = celma::common::MultiSetter2< int, string>;
   my_setter  ms( DEST_MULTI_SETTER2( var1, var2, "hello world"));


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,multi",
      DEST_METHOD_VALUE( my_setter, assign, ms), "multi-setter2"));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 42"));
   BOOST_REQUIRE_EQUAL( var1, 42);
   BOOST_REQUIRE_EQUAL( var2, "hello world");

} // multi_setter2_check



/// Check setting two values on three variables using the template MultiSetter3.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( multi_setter3_check)
{

   Handler  ah( 0);
   string   string_var1;
   int      int_var2;
   string   string_var3;

   using my_setter = celma::common::MultiSetter3< string, int, string>;
   my_setter  ms( DEST_MULTI_SETTER3( string_var1, int_var2, 42,
                                      string_var3, "hello world"));


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,multi",
      DEST_METHOD_VALUE( my_setter, assign, ms), "multi-setter3"));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m now"));
   BOOST_REQUIRE_EQUAL( string_var1, "now");
   BOOST_REQUIRE_EQUAL( int_var2, 42);
   BOOST_REQUIRE_EQUAL( string_var3, "hello world");

} // multi_setter3_check



/// Check specifying a callable for a free value.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( free_value)
{

   {
      Handler  ah( 0);

      ah.addArgument( "-", DEST_FUNCTION_VALUE( handlerFunValue), "Function");

      gotVal.clear();
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "hello"));
      BOOST_REQUIRE_EQUAL( gotVal, "hello");
   } // end scope

   {
      Handler      ah( 0);
      TestArgFunc  myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-",
         DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
         ->setValueMode( Handler::ValueMode::required));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "again"));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "again");
   } // end scope

} // free_value



/// Test passing multiple values to the same callable.
///
/// @since  1.25.0, 30.04.2019
BOOST_AUTO_TEST_CASE( multi_values)
{

   {
      Handler         ah( 0);
      MultiValueTest  mvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_METHOD_VALUE( MultiValueTest, assign, mvt),
         "Method that can be called multiple times")->setCardinality( nullptr));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 1 -v 2 -v 3"));
      BOOST_REQUIRE_EQUAL( mvt.numValues(), 3);
   } // end scope

   {
      Handler         ah( 0);
      MultiValueTest  mvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_METHOD_VALUE( MultiValueTest, assign, mvt),
         "Method that can be called multiple times")->setCardinality( nullptr)
         ->setTakesMultiValue());

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 1 2 3"));
      BOOST_REQUIRE_EQUAL( mvt.numValues(), 3);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      MultiValueTest      mvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_METHOD_VALUE( MultiValueTest, assign, mvt),
         "Method that can be called multiple times")->setCardinality( nullptr)
         ->setTakesMultiValue());

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg v"));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-v', usage:\n"
         "   Method that can be called multiple times\n"
         "Properties:\n"
         "   destination variable name:  MultiValueTest::assign\n"
         "   destination variable type:  callable-value\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                none\n"
         "   checks:                     -\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      true\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // multi_values



/// Check using a method that does not accept values.
///
/// @since  1.25.0, 30.04.2019
BOOST_AUTO_TEST_CASE( no_value_method)
{

   {
      Handler      ah( 0);
      NoValueTest  nvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_METHOD( NoValueTest, assign, nvt), "Method for flag"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
      BOOST_REQUIRE_EQUAL( nvt.numCalls(), 1);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      NoValueTest         nvt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_METHOD( NoValueTest, assign, nvt), "Method for flag"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg f"));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-f', usage:\n"
         "   Method for flag\n"
         "Properties:\n"
         "   destination variable name:  NoValueTest::assign\n"
         "   destination variable type:  callable\n"
         "   is mandatory:               false\n"
         "   value mode:                 'none' (0)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     -\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // no_value_method



/// Check using a lambda that is executed when the argument is used.
///
/// @since  1.46.1, 19.08.2021
BOOST_AUTO_TEST_CASE( lambda)
{

   // lambda without a value
   {
      Handler  ah( 0);
      int      v = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_LAMBDA( [&v]( bool) -> void { v = 42; }), "lambda"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
      BOOST_REQUIRE_EQUAL( v, 42);
   } // end scope

   // lambda with a value
   {
      Handler  ah( 0);
      int      v = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_LAMBDA_VALUE( [&v]( const std::string& val, bool) -> void
            {
               v = std::stoi( val);
            }), "lambda"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 42"));
      BOOST_REQUIRE_EQUAL( v, 42);
   } // end scope

} // lambda



// =====  END OF test_argh_callables_c.cpp  =====

