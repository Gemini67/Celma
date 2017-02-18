
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test, header file include
#include "celma/common/any_type_base.hpp"


// Boost includes
#define BOOST_TEST_MODULE AnyTypeBaseTest
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::Reference;
using celma::common::TypeName;
using celma::common::TypeNameBase;
using celma::common::Value;
using celma::common::VarName;


class SimpleBase
{
public:
   ~SimpleBase() = default;

}; // SimpleBase


template< typename T> class TestTypeName: public TypeName< T, SimpleBase>
{
public:
   TestTypeName():
      TypeName< T, SimpleBase>()
   {
   }
   
};


template< typename T> TestTypeName< T> getTestTypeName()
{

   TestTypeName< T>  my_local_var;

   return my_local_var;
} // 



/// Test class TypeName: Stores the name of the type.
/// @since  x.y.z, 13.02.2017
BOOST_AUTO_TEST_CASE( test_type_name)
{

   {
      TestTypeName< int>  name_int;

      BOOST_REQUIRE_EQUAL( name_int.getTypeName(), "int");
   } // end scope

   {
      TestTypeName< std::string>  name_string;

      BOOST_REQUIRE_EQUAL( name_string.getTypeName(), "std::string");
   } // end scope

   {
      std::unique_ptr< SimpleBase>  name_int( new TestTypeName< int>());
      auto                          name_int_base = static_cast< TypeNameBase< SimpleBase>*>( name_int.get());

      BOOST_REQUIRE_EQUAL( name_int_base->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< SimpleBase>  name_string( new TestTypeName< std::string>());
      auto                          name_string_base = static_cast< TypeNameBase< SimpleBase>*>( name_string.get());

      BOOST_REQUIRE_EQUAL( name_string_base->getTypeName(), "std::string");
   } // end scope

} // test_type_name



/// Test class Reference: Stores a variable reference plus the name of the type.
/// @since  x.y.z, 16.02.2017
BOOST_AUTO_TEST_CASE( test_reference)
{

   {
      int                          i = 0;
      Reference< int, SimpleBase>  reference_int( i);

      BOOST_REQUIRE_EQUAL( reference_int.getTypeName(), "int");
   } // end scope

   {
      std::string                          s;
      Reference< std::string, SimpleBase>  reference_string( s);

      BOOST_REQUIRE_EQUAL( reference_string.getTypeName(), "std::string");
   } // end scope

   {
      int                           i = 0;
      std::unique_ptr< SimpleBase>  reference_int( new Reference< int, SimpleBase>( i));
      auto                          reference_int_base = static_cast< Reference< int, SimpleBase>*>( reference_int.get());

      BOOST_REQUIRE_EQUAL( reference_int_base->getTypeName(), "int");
   } // end scope

   {
      std::string                   s;
      std::unique_ptr< SimpleBase>  reference_string( new Reference< std::string, SimpleBase>( s));
      auto                          reference_string_base = static_cast< Reference< std::string, SimpleBase>*>( reference_string.get());

      BOOST_REQUIRE_EQUAL( reference_string_base->getTypeName(), "std::string");
   } // end scope

} // test_reference



/// Test class Value: Stores a value plus the name of the type.
/// @since  x.y.z, 16.02.2017
BOOST_AUTO_TEST_CASE( test_value)
{

   {
      Value< int, SimpleBase>  value_int;

      BOOST_REQUIRE_EQUAL( value_int.getTypeName(), "int");
   } // end scope

   {
      Value< std::string, SimpleBase>  value_string;

      BOOST_REQUIRE_EQUAL( value_string.getTypeName(), "std::string");
   } // end scope

   {
      std::unique_ptr< SimpleBase>  value_int( new Value< int, SimpleBase>());
      auto                          value_int_base = static_cast< Value< int, SimpleBase>*>( value_int.get());

      BOOST_REQUIRE_EQUAL( value_int_base->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< SimpleBase>  value_string( new Value< std::string, SimpleBase>());
      auto                          value_string_base = static_cast< Value< std::string, SimpleBase>*>( value_string.get());

      BOOST_REQUIRE_EQUAL( value_string_base->getTypeName(), "std::string");
   } // end scope

} // test_value



/// Test class Reference: Stores a variable reference plus the name of the type.
/// @since  x.y.z, 16.02.2017
BOOST_AUTO_TEST_CASE( test_var_name)
{

   {
      int                        i = 0;
      VarName< int, SimpleBase>  var_name_int( VAR_NAME( i));

      BOOST_REQUIRE_EQUAL( var_name_int.getTypeName(), "int");
      BOOST_REQUIRE_EQUAL( var_name_int.getVarName(), "i");
   } // end scope

   {
      std::string                        s;
      VarName< std::string, SimpleBase>  var_name_string( VAR_NAME( s));

      BOOST_REQUIRE_EQUAL( var_name_string.getTypeName(), "std::string");
      BOOST_REQUIRE_EQUAL( var_name_string.getVarName(), "s");
   } // end scope

   {
      int                           i = 0;
      std::unique_ptr< SimpleBase>  var_name_int( new VarName< int, SimpleBase>( VAR_NAME( i)));
      auto                          var_name_int_base = static_cast< VarName< int, SimpleBase>*>( var_name_int.get());

      BOOST_REQUIRE_EQUAL( var_name_int_base->getTypeName(), "int");
      BOOST_REQUIRE_EQUAL( var_name_int_base->getVarName(), "i");
   } // end scope

   {
      std::string                   s;
      std::unique_ptr< SimpleBase>  var_name_string( new VarName< std::string, SimpleBase>( VAR_NAME( s)));
      auto                          var_name_string_base = static_cast< VarName< std::string, SimpleBase>*>( var_name_string.get());

      BOOST_REQUIRE_EQUAL( var_name_string_base->getTypeName(), "std::string");
      BOOST_REQUIRE_EQUAL( var_name_string_base->getVarName(), "s");
   } // end scope

} // test_var_name



/// Test copying and moving the helper classes.
/// @since  x.y.z, 16.02.2017
BOOST_AUTO_TEST_CASE( test_copy_move)
{

   {
      TestTypeName< int>  name_int;
      auto                name_int_copy( name_int);

      BOOST_REQUIRE_EQUAL( name_int.getTypeName(), name_int_copy.getTypeName());
   } // end scope

   {
      TestTypeName< int>  name_int( getTestTypeName< int>());

      BOOST_REQUIRE_EQUAL( name_int.getTypeName(), "int");
   } // end scope

} // test_copy_move



// ======================  END OF test_any_type_base.cpp  ======================

