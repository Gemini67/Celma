
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
**    Test program for arguments resulting in a function/method call in the
**    module prog_args::Handler, using the Boost.Test module.
**
--*/


/// @todo: Mandatory free values


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE prog_args::HandlerTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"
#include "celma/common/multi_setter.hpp"
#include "celma/prog_args/handler.hpp"


using namespace std;
using namespace celma;


// module definitions

/// Global variable used for the argument function handler check.
static bool    gotCalled = false;
static string  gotVal;



/// This function should be called when the corresponding argument is set on
/// the command line.
/// @since  0.2, 10.04.2016
static void handlerFun()
{

   gotCalled = true;

} // end handlerFun



/// This function should be called when the corresponding argument is set on
/// the command line.
/// @param[in]  v  The value.
/// @since  0.2, 10.04.2016
static void handlerFunValue( const string& v)
{

   if (v.empty())
      throw invalid_argument( "handlerFun() always expects a value!");

   gotVal = v;

} // end handlerFunValue



/// Test function for an optional argument that results in a function call.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( function_check)
{

   // function that does not accept a value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION( handlerFun), "Function"));

      common::ArgString2Array  as2a( "-f", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( gotCalled);
   } // end scope

   gotCalled = false;

   // function that does not accept a value, value is (unexpected) free value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION( handlerFun), "Function"));

      common::ArgString2Array  as2a( "-f hello", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   gotCalled = false;

   // function that does expect a value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function"));

      common::ArgString2Array  as2a( "-f", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   // function that does expect a value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function"));

      common::ArgString2Array  as2a( "-f hello", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "hello");
   } // end scope

   // function with value mode optional, actually expects a value (without value)
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-f", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   gotVal.clear();

   // function with value mode optional, actually expects a value (with value)
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-f v1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "v1");
   } // end scope

   gotVal.clear();

   // function with value mode optional, actually expects a value (with value)
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-fv1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "v1");
   } // end scope

   gotVal.clear();

} // end function_check



/// Test function for a mandatory argument that results in a function call.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mandatory_function_check)
{

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   gotVal.clear();

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "-f", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   gotVal.clear();

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "-f v1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "v1");
   } // end scope

   gotVal.clear();

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "--fun", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   gotVal.clear();

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "--fun v2", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "v2");
   } // end scope

   gotVal.clear();

   {
      prog_args::Handler   ah( 0);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,fun", DEST_FUNCTION_VALUE( handlerFunValue), "Function")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional)
                                            ->setIsMandatory());

      common::ArgString2Array  as2a( "--fun=v3", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "v3");
   } // end scope

} // end mandatory_function_check



/// Helper class to test the argument handler feature with a class method.
/// @since  0.2, 10.04.2016
class TestArgFunc : private boost::noncopyable
{
public:
   TestArgFunc():
      mBoolValue( false)
   {
   } // end TestArgFunc::TestArgFunc

   void handlerFunc( const string& s)
   {
      if (s.empty())
         throw invalid_argument( "TestArgFunc::handlerFunc() always expects a value!");

      mValue = s;
   } // end TestArgFunc::handlerFunc

   /// 
   /// @throw  Exception .
   /// @since  0.2, 10.04.2016
   void resetValue()
   {
      mValue.clear();
   } // end TestArgFunc::resetValue

   /// 
   /// @param[in]  optValue  .
   /// @since  0.2, 10.04.2016
   void boolFunc( const string& optValue)
   {
      if (!optValue.empty())
         throw invalid_argument( "TestArgFunc::boolFunc() must not be called with a value!");

      mBoolValue = true;
   } // end TestArgFunc::boolFunc

   void resetBool()
   {
      mBoolValue = false;
   } // end TestArgFunc::resetBool

   const string& value() const
   {
      return mValue;
   } // end TestArgFunc::value

   bool boolValue() const
   {
      return mBoolValue;
   } // end TestArgFunc::boolValue

private:
   string  mValue;
   bool    mBoolValue;

}; // TestArgFunc



/// Test function for an optional argument that results in a method call of a
/// method that requires a value.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( value_method_check)
{

   TestArgFunc  myTestObj;


   // value mode unknown
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method"));

      common::ArgString2Array  as2a( "-m", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, but no value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-m", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-m v1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-mv1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   myTestObj.resetValue();

   // value mode unknown
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method"));

      common::ArgString2Array  as2a( "--method", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, but no value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--method", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--method v1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

   myTestObj.resetValue();

   // value mode optional, value
   {
      prog_args::Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,method", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--method=v1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "v1");
   } // end scope

} // end value_method_check



/// Test function for an optional argument that results in a method call of a
/// method that doesn't accept values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( bool_method_check)
{

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool", DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-b", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.boolValue(), true);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool", DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "-m true", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool", DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--bool", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.boolValue(), true);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool", DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--bool true", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b,bool", DEST_METHOD_VALUE( TestArgFunc, boolFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmOptional));

      common::ArgString2Array  as2a( "--bool=true", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), invalid_argument);
   } // end scope

} // end bool_method_check



/// Check setting two values on two variables using the template MultiSetter2.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( multi_setter2_check)
{

   prog_args::Handler  ah( 0);
   int              var1;
   string           var2;

   typedef  common::MultiSetter2< int, string>  my_setter;
   my_setter  ms( DEST_VAR( var1), DEST_VAR( var2), "hello world");


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,multi",
                                           DEST_METHOD_VALUE( my_setter, assign, ms),
                                           "multi-setter2"));

   common::ArgString2Array  as2a( "-m 42", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( var1, 42);
   BOOST_REQUIRE_EQUAL( var2, "hello world");

} // end multi_setter2_check



/// Check setting two values on three variables using the template MultiSetter3.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( multi_setter3_check)
{

   prog_args::Handler  ah( 0);
   string           string_var1;
   int              int_var2;
   string           string_var3;

   typedef  common::MultiSetter3< string, int, string>  my_setter;
   my_setter  ms( DEST_VAR( string_var1),
                  DEST_VAR( int_var2), 42,
                  DEST_VAR( string_var3), "hello world");


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m,multi",
                                           DEST_METHOD_VALUE( my_setter, assign, ms),
                                           "multi-setter3"));

   common::ArgString2Array  as2a( "-m now", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( string_var1, "now");
   BOOST_REQUIRE_EQUAL( int_var2, 42);
   BOOST_REQUIRE_EQUAL( string_var3, "hello world");

} // end multi_setter3_check



/// Check specifying a callable for a free value.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( free_value)
{

   {
      prog_args::Handler  ah( 0);

      ah.addArgument( "", DEST_FUNCTION_VALUE( handlerFunValue), "Function");

      common::ArgString2Array  as2a( "hello", nullptr);

      gotVal.clear();
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( gotVal, "hello");
   } // end scope

   {
      prog_args::Handler  ah( 0);
      TestArgFunc      myTestObj;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "", DEST_METHOD_VALUE( TestArgFunc, handlerFunc, myTestObj), "Method")
                                            ->setValueMode( prog_args::detail::TypedArgBase::vmRequired));

      common::ArgString2Array  as2a( "again", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( myTestObj.value(), "again");
   } // end scope

} // end free_value



// =========================  END OF test_argh_callables.cpp  =========================
