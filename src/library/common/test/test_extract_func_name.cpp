
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
**    Test program for using the function common::extractFuncName() using the
**    Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ExtractFuncNameTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/extract_func_name.hpp"


using namespace std;
using namespace celma;



static void testVoidFunc( string& funcname)
{

   common::extractFuncName( funcname, __PRETTY_FUNCTION__);

} // end testVoidFunc



static string testStringFunc()
{

   string  result;

   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return result;
} // end testStringFunc



static bool otherTestFunc( std::string& result, int param)
{

   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return param == 0;
} // end otherTestFunc



namespace {



static void testVoidFuncUnnamedNamespace( string& funcname)
{

   common::extractFuncName( funcname, __PRETTY_FUNCTION__);

} // end testVoidFuncUnnamedNamespace



static string testStringFuncUnnamedNamespace()
{

   string  result;


   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return result;
} // end testStringFuncUnnamedNamespace


bool otherTestFuncUnnamedNamespace( std::string& result, int param)
{

   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return param == 0;
} // end otherTestFuncUnnamedNamespace



} // namespace



class TestClass
{
public:
   static void staticMethod( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   TestClass( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   ~TestClass()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
      return false;
   }

   bool operator ()()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return false;
   }

   TestClass& operator +=( int)
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return *this;
   }

   operator const char* ()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return NULL;
   }

   template< typename T> void templateMethod( T&)
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
   }

   static string  mLastFuncName;

}; // TestClass


string  TestClass::mLastFuncName;


template< typename T> class TemplateTestClass
{
public:
   TemplateTestClass( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
      return false;
   }

   template< typename U> void templateMethod( U&, string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

}; // TemplateTestClass



ostream& operator <<( ostream& os, const TestClass&)
{
   common::extractFuncName( TestClass::mLastFuncName, __PRETTY_FUNCTION__);

   return os;
} // operator <<



namespace project {



static void testVoidFuncProject( string& funcname)
{

   common::extractFuncName( funcname, __PRETTY_FUNCTION__);

} // end testVoidFuncProject



static string testStringFuncProject()
{

   string  result;

   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return result;
} // end testStringFuncProject



static bool otherTestFuncProject( std::string& result, int param)
{

   common::extractFuncName( result, __PRETTY_FUNCTION__);

   return param == 0;
} // end otherTestFuncProject



class TestClassProject
{
public:
   static void staticMethod( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   TestClassProject( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   ~TestClassProject()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
      return false;
   }

   bool operator ()()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return false;
   }

   TestClassProject& operator +=( int)
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return *this;
   }

   operator const char* ()
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
      return NULL;
   }

   template< typename T> void templateMethod( T&)
   {
      common::extractFuncName( mLastFuncName, __PRETTY_FUNCTION__);
   }

   static string  mLastFuncName;

}; // TestClassProject


string  TestClassProject::mLastFuncName;


template< typename T> class TemplateTestClassProject
{
public:
   TemplateTestClassProject( string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
      return false;
   }

   template< typename U> void templateMethod( U&, string& result)
   {
      common::extractFuncName( result, __PRETTY_FUNCTION__);
   }

}; // TemplateTestClassProject



ostream& operator <<( ostream& os, const TestClassProject&)
{
   common::extractFuncName( TestClassProject::mLastFuncName, __PRETTY_FUNCTION__);

   return os;
} // end operator <<



} // namespace project



/// Test if the name of a simple function (not class) is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( simple_functions_test)
{

   string  result;


   testVoidFunc( result);
   BOOST_REQUIRE_EQUAL( result,           string( "testVoidFunc"));
   BOOST_REQUIRE_EQUAL( testStringFunc(), string( "testStringFunc"));

   testVoidFuncUnnamedNamespace( result);
   BOOST_REQUIRE_EQUAL( result,
                        string( "testVoidFuncUnnamedNamespace"));
   BOOST_REQUIRE_EQUAL( testStringFuncUnnamedNamespace(),
                        string( "testStringFuncUnnamedNamespace"));

   otherTestFunc( result, 45);
   BOOST_REQUIRE_EQUAL( result, string( "otherTestFunc"));
   otherTestFuncUnnamedNamespace( result, 45);
   BOOST_REQUIRE_EQUAL( result, string( "otherTestFuncUnnamedNamespace"));

   project::testVoidFuncProject( result);
   BOOST_REQUIRE_EQUAL( result, string( "project::testVoidFuncProject"));
   BOOST_REQUIRE_EQUAL( project::testStringFuncProject(),
                        string( "project::testStringFuncProject"));
   project::otherTestFuncProject( result, 88);
   BOOST_REQUIRE_EQUAL( result, string( "project::otherTestFuncProject"));

} // end simple_functions_test



/// Test if the name of a method is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( methods_test)
{

   string  result;


   {
      TestClass::staticMethod( result);
      BOOST_REQUIRE_EQUAL( result, string( "TestClass::staticMethod"));

      TestClass  tc( result);
      BOOST_REQUIRE_EQUAL( result, string( "TestClass::TestClass"));

      tc.method1( result);
      BOOST_REQUIRE_EQUAL( result, string( "TestClass::method1"));

      tc();
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "TestClass::operator()"));

      tc += 9;
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "TestClass::operator+="));

      static_cast< const char*>( tc);
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "TestClass::operator const char*"));

      int  my_value;
      tc.templateMethod( my_value);
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "TestClass::templateMethod"));

      // actually just a simple function, but hey
      ostringstream  oss;
      oss << tc;
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "operator<<"));
   } // end scope

   BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, string( "TestClass::~TestClass"));

} // end methods_test



/// Test if the name of a method of a class in a namespace is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( methods_namespace_test)
{

   string  result;


   {
      project::TestClassProject::staticMethod( result);
      BOOST_REQUIRE_EQUAL( result, string( "project::TestClassProject::staticMethod"));

      project::TestClassProject  tc( result);
      BOOST_REQUIRE_EQUAL( result, string( "project::TestClassProject::TestClassProject"));

      tc.method1( result);
      BOOST_REQUIRE_EQUAL( result, string( "project::TestClassProject::method1"));

      tc();
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::TestClassProject::operator()"));

      tc += 9;
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                          string( "project::TestClassProject::operator+="));

      static_cast< const char*>( tc);
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::TestClassProject::operator const char*"));

      int  my_value;
      tc.templateMethod( my_value);
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::TestClassProject::templateMethod"));

      // actually just a simple function, but hey
      ostringstream  oss;
      oss << tc;
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::operator<<"));
   } // end scope

   BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                        string( "project::TestClassProject::~TestClassProject"));
} // end methods_namespace_test



/// Test if the name of a method is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( template_class_test)
{

   string  result;


   TemplateTestClass< string>  tplObj( result);

   BOOST_REQUIRE_EQUAL( result, string( "TemplateTestClass<T>::TemplateTestClass"));

   tplObj.method1( result);
   BOOST_REQUIRE_EQUAL( result, string( "TemplateTestClass<T>::method1"));

   int  my_value;
   tplObj.templateMethod( my_value, result);
   BOOST_REQUIRE_EQUAL( result, string( "TemplateTestClass<T>::templateMethod"));

} // end template_class_test



// =========================  END OF test_extract_func_name.cpp  =========================

