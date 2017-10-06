
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
**    Test program for the class detail::LogMsg, using the Boost.Test framework.
**
--*/


// include of the tested module's header file
#include "celma/common/manipulator.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ManipulatorTest
#include <boost/test/unit_test.hpp>


// project includes


using celma::common::Manipulator;


namespace {


using string_property = Manipulator< std::string>;
using int_property    = Manipulator< int>;
using name_property   = Manipulator< std::string, 1>;


/// Test helper class with one manipulator.
/// @since  x.y.z, 05.10.2017
class Test1
{
public:
   /// Constructor.
   /// @since  x.y.z, 05.10.2017
   Test1():
      mProperty()
   {
   } // Test1::Test1

   /// Stores the value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  sp  The manipulator with the value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test1& operator <<( Test1& t, const string_property& sp)
   {
      t.mProperty = sp.value();
      return t;
   } // operator <<

   /// Here we store the value from the manipulator.
   std::string  mProperty;

}; // Test1


/// Test helper class with two manipulators with different types.
/// @since  x.y.z, 05.10.2017
class Test2
{
public:
   /// Constructor.
   /// @since  x.y.z, 05.10.2017
   Test2():
      mStrProperty(),
      mIntProperty( 0)
   {
   } // Test2::Test2

   /// Stores the string value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  sp  The manipulator with the string value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test2& operator <<( Test2& t, const string_property& sp)
   {
      t.mStrProperty = sp.value();
      return t;
   } // operator <<

   /// Stores the integer value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  ip  The manipulator with the value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test2& operator <<( Test2& t, const int_property& ip)
   {
      t.mIntProperty = ip.value();
      return t;
   } // operator <<

   /// Here we store the string value from the manipulator.
   std::string  mStrProperty;
   /// Here we store the integer value from the manipulator.
   int          mIntProperty;

}; // Test2


/// Test helper class with three manipulators, two of which with the same type.
/// @since  x.y.z, 05.10.2017
class Test3
{
public:
   /// Constructor.
   /// @since  x.y.z, 05.10.2017
   Test3():
      mStrProperty(),
      mIntProperty( 0),
      mName()
   {
   } // Test3::Test3

   /// Stores the string value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  sp  The manipulator with the string value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test3& operator <<( Test3& t, const string_property& sp)
   {
      t.mStrProperty = sp.value();
      return t;
   } // operator <<

   /// Stores the integer value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  ip  The manipulator with the value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test3& operator <<( Test3& t, const int_property& ip)
   {
      t.mIntProperty = ip.value();
      return t;
   } // operator <<

   /// Stores the second string value passed through the manipulator.
   /// @param[in]  t   The object to assign the value to.
   /// @param[in]  np  The manipulator with the string value.
   /// @return  The object as passed in.
   /// @since  x.y.z, 05.10.2017
   friend Test3& operator <<( Test3& t, const name_property& np)
   {
      t.mName = np.value();
      return t;
   } // operator <<

   /// Here we store the string value from the manipulator.
   std::string  mStrProperty;
   /// Here we store the integer value from the manipulator.
   int          mIntProperty;
   /// Here we store the second string value from the manipulator.
   std::string  mName;

}; // Test3


} // namespace



/// Test a class that uses a single manipulator.
/// @since  x.y.z, 05.10.2017
BOOST_AUTO_TEST_CASE( test_one)
{

   Test1  t1;


   BOOST_REQUIRE( t1.mProperty.empty());

   t1 << string_property( "hello");

   BOOST_REQUIRE_EQUAL( t1.mProperty, "hello");

} // test_one



/// Test a class that uses two manipulators with different types.
/// @since  x.y.z, 05.10.2017
BOOST_AUTO_TEST_CASE( test_two)
{

   Test2  t2;


   BOOST_REQUIRE( t2.mStrProperty.empty());
   BOOST_REQUIRE_EQUAL( t2.mIntProperty, 0);

   t2 << string_property( "hello") << int_property( 42);

   BOOST_REQUIRE_EQUAL( t2.mStrProperty, "hello");
   BOOST_REQUIRE_EQUAL( t2.mIntProperty, 42);

} // test_two



/// Test a class that uses three manipulators, of which two use the same type.
/// @since  x.y.z, 05.10.2017
BOOST_AUTO_TEST_CASE( test_three)
{

   {
      Test3  t3;


      BOOST_REQUIRE( t3.mStrProperty.empty());
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 0);
      BOOST_REQUIRE( t3.mName.empty());

      t3 << name_property( "world") << string_property( "hello")
         << int_property( 42);

      BOOST_REQUIRE_EQUAL( t3.mStrProperty, "hello");
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 42);
      BOOST_REQUIRE_EQUAL( t3.mName, "world");
   } // end scope

   // test that order does not matter
   {
      Test3  t3;


      BOOST_REQUIRE( t3.mStrProperty.empty());
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 0);
      BOOST_REQUIRE( t3.mName.empty());

      t3 << int_property( 42) << name_property( "world")
         << string_property( "hello");

      BOOST_REQUIRE_EQUAL( t3.mStrProperty, "hello");
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 42);
      BOOST_REQUIRE_EQUAL( t3.mName, "world");
   } // end scope

   // using the same manipulator multiple times, the last occurrence should win
   {
      Test3  t3;


      BOOST_REQUIRE( t3.mStrProperty.empty());
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 0);
      BOOST_REQUIRE( t3.mName.empty());

      t3 << name_property( "name") << int_property( 13)
         << string_property( "string") << int_property( 42)
         << name_property( "world") << string_property( "hello");

      BOOST_REQUIRE_EQUAL( t3.mStrProperty, "hello");
      BOOST_REQUIRE_EQUAL( t3.mIntProperty, 42);
      BOOST_REQUIRE_EQUAL( t3.mName, "world");
   } // end scope

} // test_three



// =======================  END OF test_manipulator.cpp  =======================
