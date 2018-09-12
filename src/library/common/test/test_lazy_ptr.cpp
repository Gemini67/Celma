
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::common::lazy_ptr, using the
**    Boost.Test framework.
**
--*/


// module to test, header file include
#include "celma/common/lazy_ptr.hpp"


// Boost includes
#define BOOST_TEST_MODULE AnyTypeBaseTest
#include <boost/test/unit_test.hpp>


#include "celma/test/test_handling.hpp"


using celma::common::lazy_ptr;
using celma::test::TestHandling;


namespace {


/// Test class used to test calling the default constructor and a constructor
/// with an integer parameter.
///
/// @since  x.y.z, 07.09.2018
class TestClass
{
public:
   /// Default constructor.
   ///
   /// @since  x.y.z, 07.09.2018
   TestClass() = default;

   /// Constructor with a single integer parameter.
   ///
   /// @param[in]  value  The value to store internally.
   /// @since  x.y.z, 07.09.2018
   explicit TestClass( int value):
      mValue( value)
   {
   } // TestClass::TestClass

   /// Constructor with a single string parameter.<br>
   /// The value in string is converted to an integer and stored internally.
   ///
   /// @param[in]  value  The string with the value to store internally.
   /// @since  x.y.z, 07.09.2018
   explicit TestClass( const std::string& value):
      mValue( ::atoi( value.c_str()))
   {
   } // TestClass::TestClass

   /// Default copy constructor.
   /// @since  x.y.z, 07.09.2018
   TestClass( const TestClass&) = default;

   /// Returns the internally stored value.
   ///
   /// @return  The value currently stored internally.
   /// @since  x.y.z, 07.09.2018
   int value() const
   {
      return mValue;
   } // TestClass::value

private:
   /// The value stored for the test.
   int  mValue = -1;

}; // TestClass


/// Second test class, used to test calling a constructor with more than one
/// parameter.
///
/// @since  x.y.z, 07.09.2018
class TestClass2
{
public:
   /// Default constructor.
   ///
   /// @since  x.y.z, 07.09.2018
   TestClass2() = default;

   /// Constructor with two parameters.
   ///
   /// @param[in]  value
   ///    The integer parameter.
   /// @param[in]  name
   ///    The string parameter.
   /// @since
   ///    x.y.z, 07.09.2018
   explicit TestClass2( int value, const std::string& name):
      mValue( value),
      mName( name)
   {
   } // TestClass2::TestClass2

   /// Default copy constructor.
   ///
   /// @since  x.y.z, 07.09.2018
   TestClass2( const TestClass2&) = default;

   /// Returns the internally stored integer value.
   ///
   /// @return  The internally stored integer value.
   /// @since  x.y.z, 07.09.2018
   int value() const
   {
      return mValue;
   } // TestClass2::value

   /// Returns the internally stored string value.
   ///
   /// @return  The internally stored string value.
   /// @since  x.y.z, 07.09.2018
   const std::string& name() const
   {
      return mName;
   } // TestClass2::name

private:
   /// The integer value.
   int          mValue = -1;
   /// The string value.
   std::string  mName;

}; // TestClass2


/// Another test class, used to test calling a constructor with more than one
/// parameter (in reverse order, compared to TestClass2).
///
/// @since  x.y.z, 07.09.2018
class TestClass2r
{
public:
   /// Default constructor.
   ///
   /// @since  x.y.z, 07.09.2018
   TestClass2r() = default;

   /// Constructor with two parameters.
   ///
   /// @param[in]  name
   ///    The string parameter.
   /// @param[in]  value
   ///    The integer parameter.
   /// @since
   ///    x.y.z, 07.09.2018
   explicit TestClass2r( const std::string& name, int value):
      mName( name),
      mValue( value)
   {
   } // TestClass2r::TestClass2r

   /// Default copy constructor.
   ///
   /// @since  x.y.z, 07.09.2018
   TestClass2r( const TestClass2r&) = default;

   /// Returns the internally stored integer value.
   ///
   /// @return  The internally stored integer value.
   /// @since  x.y.z, 07.09.2018
   int value() const
   {
      return mValue;
   } // TestClass2r::value

   /// Returns the internally stored string value.
   ///
   /// @return  The internally stored string value.
   /// @since  x.y.z, 07.09.2018
   const std::string& name() const
   {
      return mName;
   } // TestClass2r::name

private:
   /// The string value.
   std::string  mName;
   /// The integer value.
   int          mValue = -1;

}; // TestClass2r


/// Test class that verifies that its parameters were copied (or moved), not
/// passed by reference.
///
/// @since  x.y.z, 07.09.2018
class TestClassCopy
{
public:
   /// Constructor.<br>
   /// Verifies that the parameters were copied or moved.
   ///
   /// @param[in]  th1
   ///    The first parameter to check.
   /// @param[in]  th2
   ///    The second parameter to check.
   /// @throw
   ///    runtime_error when at least one of the two parameters was not copied.
   /// @since
   ///    x.y.z, 07.09.2018
   TestClassCopy( const TestHandling& th1, const TestHandling& th2)
   {
      if (!th1.copyCtorCalled() && !th1.moveCtorCalled())
         throw std::runtime_error( "parameter 1 was not copied/moved!");
      if (!th2.copyCtorCalled() && !th2.moveCtorCalled())
         throw std::runtime_error( "parameter 2 was not copied/moved!");
   } // TestClassCopy::TestClassCopy

}; // TestClassCopy


#if 0


lazy_ptr< TestClassCopy>&& create_lp()
{

   TestHandling              th1;
   TestHandling              th2;
   lazy_ptr< TestClassCopy>  lpCopy( th1, th2);

   BOOST_REQUIRE( lpCopy.get());

   return std::move( lpCopy);
} // create_lp


#endif


} // namespace



/// Tests lazy construction of an object with none or one parameter.
///
/// @since  x.y.z, 07.09.2018
BOOST_AUTO_TEST_CASE( none_or_one)
{

   {
      lazy_ptr< int>  lpInt( 42);

      BOOST_REQUIRE( !lpInt);
      BOOST_REQUIRE( lpInt.release() == nullptr);

      BOOST_REQUIRE( lpInt.get() != nullptr);
      BOOST_REQUIRE_EQUAL( *lpInt.get(), 42);
      BOOST_REQUIRE( lpInt);
   } // end scope

   // test using default constructor
   {
      lazy_ptr< TestClass>  lp_test_class;

      BOOST_REQUIRE( !lp_test_class);

      BOOST_REQUIRE( lp_test_class.get() != nullptr);
      BOOST_REQUIRE_EQUAL( lp_test_class.get()->value(), -1);
      BOOST_REQUIRE( lp_test_class);
   } // end scope

   // test using integer constructor
   {
      lazy_ptr< TestClass>  lp_test_class( 42);

      BOOST_REQUIRE( !lp_test_class);

      BOOST_REQUIRE( lp_test_class.get() != nullptr);
      BOOST_REQUIRE_EQUAL( lp_test_class.get()->value(), 42);
      BOOST_REQUIRE( lp_test_class);
   } // end scope

   // test with scalar whose value is changed after the lazy_ptr is created, but
   // before the object is created
   // since the value should have been copied, the object should contain the
   // originally passed value
   {
      int                   my_int = 42;
      lazy_ptr< TestClass>  lp_test_class( my_int);

      my_int = 4711;

      BOOST_REQUIRE( !lp_test_class);

      BOOST_REQUIRE( lp_test_class.get() != nullptr);
      BOOST_REQUIRE_EQUAL( lp_test_class.get()->value(), 42);
      BOOST_REQUIRE( lp_test_class);
   } // end scope

   // test using dynamically created integer constructor
   // works because the single parameter constructor copies the value
   {
      int*                  my_int = new int( 42);
      lazy_ptr< TestClass>  lp_test_class( *my_int);
      delete  my_int;

      BOOST_REQUIRE( !lp_test_class);

      BOOST_REQUIRE( lp_test_class.get() != nullptr);
      BOOST_REQUIRE_EQUAL( lp_test_class.get()->value(), 42);
      BOOST_REQUIRE( lp_test_class);
   } // end scope

   // test using string constructor
   {
      lazy_ptr< TestClass>  lp_test_class( "4711");

      BOOST_REQUIRE( !lp_test_class);

      BOOST_REQUIRE( lp_test_class.get() != nullptr);
      BOOST_REQUIRE_EQUAL( lp_test_class.get()->value(), 4711);
      BOOST_REQUIRE_EQUAL( lp_test_class->value(), 4711);
      BOOST_REQUIRE( lp_test_class);
   } // end scope

} // none_or_one



/// Test lazy object creation with a class that takes two parameters on the
/// constructor.
///
/// @since  x.y.z, 07.09.2018
BOOST_AUTO_TEST_CASE( two_parameters)
{

   {
      lazy_ptr< TestClass2>  lpC2;

      BOOST_REQUIRE( !lpC2);

      BOOST_REQUIRE( lpC2.get() != nullptr);
      BOOST_REQUIRE( lpC2);
      BOOST_REQUIRE_EQUAL( lpC2.get()->value(), -1);
      BOOST_REQUIRE_EQUAL( lpC2->value(), -1);
      BOOST_REQUIRE( lpC2.get()->name().empty());
      BOOST_REQUIRE( lpC2->name().empty());
   } // end scope

   {
      lazy_ptr< TestClass2>  lpC2( 42, "hugentobler");

      BOOST_REQUIRE( !lpC2);

      BOOST_REQUIRE( lpC2.get() != nullptr);
      BOOST_REQUIRE( lpC2);
      BOOST_REQUIRE_EQUAL( lpC2.get()->value(), 42);
      BOOST_REQUIRE_EQUAL( lpC2->value(), 42);
      BOOST_REQUIRE( !lpC2.get()->name().empty());
      BOOST_REQUIRE_EQUAL( lpC2.get()->name(), "hugentobler");
      BOOST_REQUIRE_EQUAL( lpC2->name(), "hugentobler");
   } // end scope

} // two_parameters



/// Test with a class that takes also two parameters for the constructor, but in
/// reverse order than in the previous example.
///
/// @since  x.y.z, 07.09.2018
BOOST_AUTO_TEST_CASE( two_parameters_reversed)
{

   int                     int_val = 42;
   lazy_ptr< TestClass2r>  lpC2( "hugentobler", int_val);


   BOOST_REQUIRE( !lpC2);

   BOOST_REQUIRE( lpC2.get() != nullptr);
   BOOST_REQUIRE( lpC2);
   BOOST_REQUIRE_EQUAL( lpC2.get()->value(), 42);
   BOOST_REQUIRE_EQUAL( lpC2->value(), 42);
   BOOST_REQUIRE( !lpC2.get()->name().empty());
   BOOST_REQUIRE_EQUAL( lpC2.get()->name(), "hugentobler");
   BOOST_REQUIRE_EQUAL( lpC2->name(), "hugentobler");

} // two_parameters_reversed



/// Verify that the parameters are really copied in(to) the lambda.
///
/// @since  x.y.z, 07.09.2018
BOOST_AUTO_TEST_CASE( parameter_copy)
{

   TestHandling              th1;
   TestHandling              th2;
   lazy_ptr< TestClassCopy>  lpCopy( th1, th2);


   BOOST_REQUIRE( !lpCopy);

   // object is created now
   // check if parameters were copied happens inside the constructor
   BOOST_REQUIRE_NO_THROW( lpCopy.get());

} // parameter_copy



// disabled until the problem with the move constructor is solved
#if 0



/// Verify that the contents of the lazy_ptr<> object are moved correctly.
///
/// @since  x.y.z, 12.09.2018
BOOST_AUTO_TEST_CASE( move_members)
{

   lazy_ptr< TestClassCopy>  lp_moved_from( create_lp());


   BOOST_REQUIRE( lp_moved_from);

   BOOST_REQUIRE_NO_THROW( lp_moved_from.get());

} // move_members



#endif



/// Verify that the release operation works correctly.
///
/// @since  x.y.z, 11.09.2018
BOOST_AUTO_TEST_CASE( correctly_released)
{

   bool           dtor_called = false;
   TestHandling*  ptr = nullptr;


   {
      lazy_ptr< TestHandling>  lpTH;

      BOOST_REQUIRE( lpTH.get() != nullptr);

      lpTH->setDtorFlag( dtor_called);
      ptr = lpTH.release();

      BOOST_REQUIRE( !dtor_called);
   } // end scope

   BOOST_REQUIRE( !dtor_called);
   delete ptr;

} // correctly_released



/// Verify that the reset operation works correctly.
///
/// @since  x.y.z, 12.09.2018
BOOST_AUTO_TEST_CASE( correctly_reset)
{

   lazy_ptr< TestHandling>  lpTH;
   bool                     dtor_called = false;


   BOOST_REQUIRE( lpTH.get() != nullptr);

   lpTH->setDtorFlag( dtor_called);
   lpTH.reset();

   BOOST_REQUIRE( dtor_called);

} // correctly_reset



// =====  END OF test_any_type_base.cpp  =====

