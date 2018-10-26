
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the function common::extractFuncname() using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/common/extract_funcname.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ExtractFuncnameTest
#include <boost/test/unit_test.hpp>


using std::ostream;
using std::ostringstream;
using std::string;
using celma::common::extractFuncname;


static void testVoidFunc( string& funcname)
{

   funcname = extractFuncname( __PRETTY_FUNCTION__);

} // testVoidFunc


static string testStringFunc()
{

   return extractFuncname( __PRETTY_FUNCTION__);
} // testStringFunc


static bool otherTestFunc( string& result, int param)
{

   result = extractFuncname( __PRETTY_FUNCTION__);

   return param == 0;
} // otherTestFunc


namespace {


static void testVoidFuncUnnamedNamespace( string& funcname)
{

   funcname = extractFuncname( __PRETTY_FUNCTION__);

} // testVoidFuncUnnamedNamespace


static string testStringFuncUnnamedNamespace()
{

   return extractFuncname( __PRETTY_FUNCTION__);
} // testStringFuncUnnamedNamespace


bool otherTestFuncUnnamedNamespace( string& result, int param)
{

   result = extractFuncname( __PRETTY_FUNCTION__);

   return param == 0;
} // otherTestFuncUnnamedNamespace


void* ptrReturningFunction( string& funcname)
{
   funcname = extractFuncname( __PRETTY_FUNCTION__);
   return nullptr;
} // ptrReturningFunction


auto funcPtrReturningFunction( string& funcname)
{
   funcname = extractFuncname( __PRETTY_FUNCTION__);
   return ptrReturningFunction;
} // funcPtrReturningFunction


} // namespace



class TestClass
{
public:
   static void staticMethod( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   TestClass( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   ~TestClass()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   bool operator ()()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   TestClass& operator +=( int)
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return *this;
   }

   operator const char* ()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return nullptr;
   }

   template< typename T> void templateMethod( T&)
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
   }

   const TestClass& me() const
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return *this;
   }

   static string  mLastFuncName;

}; // TestClass


string  TestClass::mLastFuncName;


template< typename T> class TemplateTestClass
{
public:
   TemplateTestClass( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   template< typename U> void templateMethod( U&, string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

}; // TemplateTestClass



ostream& operator <<( ostream& os, const TestClass&)
{
   TestClass::mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);

   return os;
} // operator <<



namespace project {



static void testVoidFuncProject( string& funcname)
{

   funcname = extractFuncname( __PRETTY_FUNCTION__);

} // testVoidFuncProject



static string testStringFuncProject()
{

   return extractFuncname( __PRETTY_FUNCTION__);
} // testStringFuncProject



static bool otherTestFuncProject( string& result, int param)
{

   result = extractFuncname( __PRETTY_FUNCTION__);

   return param == 0;
} // otherTestFuncProject



class TestClassProject
{
public:
   static void staticMethod( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   TestClassProject( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   ~TestClassProject()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   bool operator ()()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   TestClassProject& operator +=( int)
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return *this;
   }

   operator const char* ()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return NULL;
   }

   template< typename T> void templateMethod( T&)
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
   }

   TestClassProject& operator ++()
   {
      mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);
      return *this;
   }
   
   static string  mLastFuncName;

}; // TestClassProject


string  TestClassProject::mLastFuncName;


template< typename T> class TemplateTestClassProject
{
public:
   TemplateTestClassProject( string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

   bool method1( string& result) const
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
      return false;
   }

   template< typename U> void templateMethod( U&, string& result)
   {
      result = extractFuncname( __PRETTY_FUNCTION__);
   }

}; // TemplateTestClassProject



ostream& operator <<( ostream& os, const TestClassProject&)
{
   TestClassProject::mLastFuncName = extractFuncname( __PRETTY_FUNCTION__);

   return os;
} // operator <<



} // namespace project



/// Test if the name of a simple function (not class) is returned correctly.
///
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( simple_functions_test)
{

   string  result;


   testVoidFunc( result);
   BOOST_REQUIRE_EQUAL( result, "testVoidFunc");
   BOOST_REQUIRE_EQUAL( testStringFunc(), "testStringFunc");

   testVoidFuncUnnamedNamespace( result);
   BOOST_REQUIRE_EQUAL( result, "testVoidFuncUnnamedNamespace");

   BOOST_REQUIRE_EQUAL( testStringFuncUnnamedNamespace(),
      "testStringFuncUnnamedNamespace");

   otherTestFunc( result, 45);
   BOOST_REQUIRE_EQUAL( result, "otherTestFunc");
   otherTestFuncUnnamedNamespace( result, 45);
   BOOST_REQUIRE_EQUAL( result, "otherTestFuncUnnamedNamespace");

   ptrReturningFunction( result);
   BOOST_REQUIRE_EQUAL( result, "ptrReturningFunction");
   
   funcPtrReturningFunction( result);
   BOOST_REQUIRE_EQUAL( result, "funcPtrReturningFunction");

   project::testVoidFuncProject( result);
   BOOST_REQUIRE_EQUAL( result, "project::testVoidFuncProject");
   BOOST_REQUIRE_EQUAL( project::testStringFuncProject(),
                        "project::testStringFuncProject");
   project::otherTestFuncProject( result, 88);
   BOOST_REQUIRE_EQUAL( result, "project::otherTestFuncProject");

} // simple_functions_test



/// Test if the name of a method is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( methods_test)
{

   string  result;


   {
      TestClass::staticMethod( result);
      BOOST_REQUIRE_EQUAL( result, "TestClass::staticMethod");

      TestClass  tc( result);
      BOOST_REQUIRE_EQUAL( result, "TestClass::TestClass");

      tc.method1( result);
      BOOST_REQUIRE_EQUAL( result, "TestClass::method1");

      tc();
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "TestClass::operator()");

      tc += 9;
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "TestClass::operator+=");

      static_cast< const char*>( tc);
      BOOST_REQUIRE( (TestClass::mLastFuncName == "TestClass::operator const char *") ||
                     (TestClass::mLastFuncName == "TestClass::operator const char*"));

      int  my_value;
      tc.templateMethod( my_value);
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "TestClass::templateMethod");

      auto x = tc.me();
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "TestClass::me");

      // actually just a simple function, but hey
      ostringstream  oss;
      oss << tc;
      BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "operator<<");
   } // end scope

   BOOST_REQUIRE_EQUAL( TestClass::mLastFuncName, "TestClass::~TestClass");

} // methods_test



/// Test if the name of a method of a class in a namespace is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( methods_namespace_test)
{

   string  result;


   {
      project::TestClassProject::staticMethod( result);
      BOOST_REQUIRE_EQUAL( result, "project::TestClassProject::staticMethod");

      project::TestClassProject  tc( result);
      BOOST_REQUIRE_EQUAL( result, "project::TestClassProject::TestClassProject");

      tc.method1( result);
      BOOST_REQUIRE_EQUAL( result, "project::TestClassProject::method1");

      tc();
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::TestClassProject::operator()"));

      tc += 9;
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                          string( "project::TestClassProject::operator+="));

      static_cast< const char*>( tc);
      BOOST_REQUIRE( (project::TestClassProject::mLastFuncName ==
                      string( "project::TestClassProject::operator const char *")) ||
                     (project::TestClassProject::mLastFuncName ==
                      string( "project::TestClassProject::operator const char*")));

      int  my_value;
      tc.templateMethod( my_value);
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           string( "project::TestClassProject::templateMethod"));

      ++tc;
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           "project::TestClassProject::operator++");

      // actually just a simple function, but hey
      ostringstream  oss;
      oss << tc;
      BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                           "project::operator<<");
   } // end scope

   BOOST_REQUIRE_EQUAL( project::TestClassProject::mLastFuncName,
                        "project::TestClassProject::~TestClassProject");
} // methods_namespace_test



/// Test if the name of a method is returned correctly.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( template_class_test)
{

   string  result;


   {
      TemplateTestClass< uint32_t>  tplObj( result);

      BOOST_REQUIRE( (result == "TemplateTestClass<uint32_t>::TemplateTestClass") ||
                     (result == "TemplateTestClass<T>::TemplateTestClass"));

      tplObj.method1( result);
      BOOST_REQUIRE( (result == "TemplateTestClass<uint32_t>::method1") ||
                     (result == "TemplateTestClass<T>::method1"));

      int  my_value;
      tplObj.templateMethod( my_value, result);
      BOOST_REQUIRE( (result == "TemplateTestClass<uint32_t>::templateMethod") ||
                     (result == "TemplateTestClass<T>::templateMethod"));
   } // end scope

   {
      TemplateTestClass< string>  tplObj( result);

      BOOST_REQUIRE( (result == "TemplateTestClass<std::__cxx11::basic_string<char> >::TemplateTestClass") ||
                     (result == "TemplateTestClass<T>::TemplateTestClass"));

      tplObj.method1( result);
      BOOST_REQUIRE( (result == "TemplateTestClass<std::__cxx11::basic_string<char> >::method1") ||
                     (result == "TemplateTestClass<T>::method1"));

      int  my_value;
      tplObj.templateMethod( my_value, result);
      BOOST_REQUIRE( (result == "TemplateTestClass<std::__cxx11::basic_string<char> >::templateMethod") ||
                     (result == "TemplateTestClass<T>::templateMethod"));
   } // end scope

} // template_class_test



// =====  END OF test_extract_funcname.cpp  =====

