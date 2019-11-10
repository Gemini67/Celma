
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
**    Test program for the module "any type base", using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/common/any_type_base.hpp"


// Boost includes
#define BOOST_TEST_MODULE AnyTypeBaseTest
#include <boost/test/unit_test.hpp>


using celma::common::AnyBase;
using celma::common::Reference;
using celma::common::TypeName;
using celma::common::TypeNameBase;
using celma::common::Value;
using celma::common::VarName;


namespace {


/// Helper super class, needed to test those base classes with a protected
/// constructor.
template< typename T> class TestTypeName: public TypeName< T, AnyBase>
{
public:
   TestTypeName():
      TypeName< T, AnyBase>()
   {
   }
   
}; // TestTypeName< T>


/// Used to test move-constructor.
template< typename T> TestTypeName< T> getTestTypeName()
{

   TestTypeName< T>  my_local_var;

   return my_local_var;
} // getTestTypeName


} // namespace



/// Test class TypeName: Stores the name of the type.
/// @since  0.13.3, 13.02.2017
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
      std::unique_ptr< AnyBase>  name_int( new TestTypeName< int>());
      auto                       name_int_base = static_cast< TypeNameBase< AnyBase>*>( name_int.get());

      BOOST_REQUIRE_EQUAL( name_int_base->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< AnyBase>  name_string( new TestTypeName< std::string>());
      auto                       name_string_base = static_cast< TypeNameBase< AnyBase>*>( name_string.get());

      BOOST_REQUIRE_EQUAL( name_string_base->getTypeName(), "std::string");
   } // end scope

   {
      std::unique_ptr< AnyBase>  name_int( new TestTypeName< int>());

      BOOST_REQUIRE_EQUAL( name_int->getTypeNameBase()->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< AnyBase>  name_string( new TestTypeName< std::string>());

      BOOST_REQUIRE_EQUAL( name_string->getTypeNameBase()->getTypeName(),
                           "std::string");
   } // end scope

} // test_type_name



/// Test class Reference: Stores a variable reference plus the name of the type.
/// @since  0.13.3, 16.02.2017
BOOST_AUTO_TEST_CASE( test_reference)
{

   {
      int                       i = 0;
      Reference< int, AnyBase>  reference_int( i);

      BOOST_REQUIRE_EQUAL( reference_int.getTypeName(), "int");
   } // end scope

   {
      std::string                       s;
      Reference< std::string, AnyBase>  reference_string( s);

      BOOST_REQUIRE_EQUAL( reference_string.getTypeName(), "std::string");
   } // end scope

   {
      int                        i = 0;
      std::unique_ptr< AnyBase>  reference_int( new Reference< int, AnyBase>( i));
      auto                       reference_int_base = static_cast< Reference< int, AnyBase>*>( reference_int.get());

      BOOST_REQUIRE_EQUAL( reference_int_base->getTypeName(), "int");
   } // end scope

   {
      std::string                s;
      std::unique_ptr< AnyBase>  reference_string( new Reference< std::string, AnyBase>( s));
      auto                       reference_string_base = static_cast< Reference< std::string, AnyBase>*>( reference_string.get());

      BOOST_REQUIRE_EQUAL( reference_string_base->getTypeName(), "std::string");
   } // end scope

   {
      int                        i = 0;
      std::unique_ptr< AnyBase>  reference_int( new Reference< int, AnyBase>( i));

      BOOST_REQUIRE_EQUAL( reference_int->getTypeNameBase()->getTypeName(),
                           "int");
   } // end scope

   {
      std::string                s;
      std::unique_ptr< AnyBase>  reference_string( new Reference< std::string, AnyBase>( s));

      BOOST_REQUIRE_EQUAL( reference_string->getTypeNameBase()->getTypeName(),
                           "std::string");
   } // end scope

} // test_reference



/// Test class Value: Stores a value plus the name of the type.
/// @since  0.13.3, 16.02.2017
BOOST_AUTO_TEST_CASE( test_value)
{

   {
      Value< int, AnyBase>  value_int;

      BOOST_REQUIRE_EQUAL( value_int.getTypeName(), "int");
   } // end scope

   {
      Value< std::string, AnyBase>  value_string;

      BOOST_REQUIRE_EQUAL( value_string.getTypeName(), "std::string");
   } // end scope

   {
      std::unique_ptr< AnyBase>  value_int( new Value< int, AnyBase>());
      auto                       value_int_base = static_cast< Value< int, AnyBase>*>( value_int.get());

      BOOST_REQUIRE_EQUAL( value_int_base->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< AnyBase>  value_string( new Value< std::string, AnyBase>());
      auto                       value_string_base = static_cast< Value< std::string, AnyBase>*>( value_string.get());

      BOOST_REQUIRE_EQUAL( value_string_base->getTypeName(), "std::string");
   } // end scope

   {
      std::unique_ptr< AnyBase>  value_int( new Value< int, AnyBase>());

      BOOST_REQUIRE_EQUAL( value_int->getTypeNameBase()->getTypeName(), "int");
   } // end scope

   {
      std::unique_ptr< AnyBase>  value_string( new Value< std::string, AnyBase>());

      BOOST_REQUIRE_EQUAL( value_string->getTypeNameBase()->getTypeName(),
                           "std::string");
   } // end scope

} // test_value



/// Test class Reference: Stores a variable reference plus the name of the type.
/// @since  0.13.3, 16.02.2017
BOOST_AUTO_TEST_CASE( test_var_name)
{

   {
      int                     i = 0;
      VarName< int, AnyBase>  var_name_int( VAR_NAME( i));

      BOOST_REQUIRE_EQUAL( var_name_int.getTypeName(), "int");
      BOOST_REQUIRE_EQUAL( var_name_int.getVarName(), "i");
   } // end scope

   {
      std::string                     s;
      VarName< std::string, AnyBase>  var_name_string( VAR_NAME( s));

      BOOST_REQUIRE_EQUAL( var_name_string.getTypeName(), "std::string");
      BOOST_REQUIRE_EQUAL( var_name_string.getVarName(), "s");
   } // end scope

   {
      int                        i = 0;
      std::unique_ptr< AnyBase>  var_name_int( new VarName< int, AnyBase>( VAR_NAME( i)));
      auto                       var_name_int_base = static_cast< VarName< int, AnyBase>*>( var_name_int.get());

      BOOST_REQUIRE_EQUAL( var_name_int_base->getTypeName(), "int");
      BOOST_REQUIRE_EQUAL( var_name_int_base->getVarName(), "i");
   } // end scope

   {
      std::string                s;
      std::unique_ptr< AnyBase>  var_name_string( new VarName< std::string, AnyBase>( VAR_NAME( s)));
      auto                       var_name_string_base = static_cast< VarName< std::string, AnyBase>*>( var_name_string.get());

      BOOST_REQUIRE_EQUAL( var_name_string_base->getTypeName(), "std::string");
      BOOST_REQUIRE_EQUAL( var_name_string_base->getVarName(), "s");
   } // end scope

   {
      int                        i = 0;
      std::unique_ptr< AnyBase>  var_name_int( new VarName< int, AnyBase>( VAR_NAME( i)));

      BOOST_REQUIRE_EQUAL( var_name_int->getTypeNameBase()->getTypeName(), "int");
   } // end scope

   {
      std::string                s;
      std::unique_ptr< AnyBase>  var_name_string( new VarName< std::string, AnyBase>( VAR_NAME( s)));

      BOOST_REQUIRE_EQUAL( var_name_string->getTypeNameBase()->getTypeName(),
                           "std::string");
   } // end scope

} // test_var_name



/// Test copying and moving the helper classes.
/// @since  0.13.3, 16.02.2017
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



// =====  END OF test_any_type_base.cpp  =====

