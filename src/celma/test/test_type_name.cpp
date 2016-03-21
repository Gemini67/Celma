
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
**    Test program for the template family celma::type< > using the Boost.Test
**    module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// Boost includes
#define BOOST_TEST_MODULE TypeNameTest
#include <boost/test/unit_test.hpp>
#include <utility>


// project includes
#include "celma/type_name.hpp"



/// Test for POD data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( pod_types)
{

   BOOST_REQUIRE( strcmp( celma::type< bool>::name(),   "bool")   == 0);
   BOOST_REQUIRE( strcmp( celma::type< char>::name(),   "char")   == 0);
   BOOST_REQUIRE( strcmp( celma::type< double>::name(), "double") == 0);
   BOOST_REQUIRE( strcmp( celma::type< float>::name(),  "float")  == 0);
   BOOST_REQUIRE( strcmp( celma::type< int>::name(),    "int")    == 0);
   BOOST_REQUIRE( strcmp( celma::type< long>::name(),   "long")   == 0);
   BOOST_REQUIRE( strcmp( celma::type< short>::name(),  "short")  == 0);

   BOOST_REQUIRE( strcmp( celma::type< unsigned char>::name(),  "unsigned char")  == 0);
   BOOST_REQUIRE( strcmp( celma::type< unsigned long>::name(),  "unsigned long")  == 0);
   BOOST_REQUIRE( strcmp( celma::type< unsigned short>::name(), "unsigned short") == 0);

   // just to make sure: works also with typedefs
   typedef bool  my_bool;
   BOOST_REQUIRE( strcmp( celma::type< my_bool>::name(), "bool") == 0);

} // end pod_types



/// Test for STL data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types)
{

   BOOST_REQUIRE( strcmp( celma::type< std::bitset< 128> >::name(),
                          "std::bitset<128>") == 0);
   BOOST_REQUIRE( strcmp( celma::type< std::string>::name(),
                          "std::string") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::list< long> >::name(),
                          "std::list<long>") == 0);
   BOOST_REQUIRE( strcmp( celma::type< std::list< std::string> >::name(),
                          "std::list<std::string>") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::set< long> >::name(),
                          "std::set<long>") == 0);
   BOOST_REQUIRE( strcmp( celma::type< std::set< std::string> >::name(),
                          "std::set<std::string>") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::vector< int> >::name(),
                          "std::vector<int>") == 0);
   BOOST_REQUIRE( strcmp( celma::type< std::vector< std::string> >::name(),
                          "std::vector<std::string>") == 0);

} // end stl_types



/// Test for STL data types with more than one template parameter.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types_key_value)
{

   BOOST_REQUIRE( strcmp( celma::type< std::map< int, std::string> >::name(),
                          "std::map<int,std::string>") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::multimap< std::string, long> >::name(),
                          "std::multimap<std::string,long>") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::pair< std::string, std::string> >::name(),
                          "std::pair<std::string,std::string>") == 0);

} // end stl_types_key_value



/// User defined class for which we won't provide the name.
/// @since  0.1, 15.03.2016
class UnknownUserDefinedType
{
}; // UnknownUserDefinedType



/// Test for unknown user defined type.
/// @since  1.0, 28.07.2015
BOOST_AUTO_TEST_CASE( unknown_user_defined_type)
{

   BOOST_REQUIRE( strcmp( celma::type< UnknownUserDefinedType>::name(),
                          "unknown") == 0);

} // end unknown_user_defined_type



/// User defined class for which we provide the name.
/// @since  0.1, 15.03.2016
class UserDefinedType
{
}; // UserDefinedType



namespace celma {



/// Specialisation for type 'UserDefinedType'.
/// @since  0.1, 15.03.2016
template<> class type<  UserDefinedType>
{
public:
   /// Returns the name of the type.
   /// @return  'UserDefinedType'.
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      return "UserDefinedType";
   } // end celma::type< UserDefinedType>::name

}; // type<  UserDefinedType>



} // namespace celma



/// Test for user defined type.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( user_defined_type)
{

   BOOST_REQUIRE( strcmp( celma::type< UserDefinedType>::name(),
                          "UserDefinedType") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::vector< UserDefinedType> >::name(),
                          "std::vector<UserDefinedType>") == 0);

} // end user_defined_type



/// User defined class for which we provide the name with the macro.
/// @since  0.1, 15.03.2016
class UserDefinedTypeMacro
{
}; // UserDefinedTypeMacro



namespace celma {



PROVIDE_SIMPLE_TYPE_NAME( UserDefinedTypeMacro);



} // namespace celma



/// Test for user defined type.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( user_defined_type_macro)
{

   BOOST_REQUIRE( strcmp( celma::type< UserDefinedTypeMacro>::name(),
                          "UserDefinedTypeMacro") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::list< UserDefinedTypeMacro> >::name(),
                          "std::list<UserDefinedTypeMacro>") == 0);

} // end user_defined_type_macro



/// User defined enum.
/// @since  0.1, 15.03.2016
enum EnumType
{
};



namespace celma {



PROVIDE_SIMPLE_TYPE_NAME( EnumType);



} // namespace celma



/// Test for user defined enum.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( user_defined_enum)
{

   BOOST_REQUIRE( strcmp( celma::type< EnumType>::name(), "EnumType") == 0);

   BOOST_REQUIRE( strcmp( celma::type< std::set< EnumType> >::name(),
                          "std::set<EnumType>") == 0);

} // end user_defined_enum



// =========================  END OF test_type_name.cpp  =========================


