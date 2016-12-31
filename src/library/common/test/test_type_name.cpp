
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
#include "celma/common/type_name.hpp"


#define  BOOST_REQUIRE_EQUAL_STR( a, b) \
   BOOST_REQUIRE( ::strcmp( a, b) == 0)


/// Test for POD data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( pod_types)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< bool>::name(),   "bool");
   BOOST_REQUIRE_EQUAL_STR( celma::type< char>::name(),   "char");
   BOOST_REQUIRE_EQUAL_STR( celma::type< double>::name(), "double");
   BOOST_REQUIRE_EQUAL_STR( celma::type< float>::name(),  "float");
   BOOST_REQUIRE_EQUAL_STR( celma::type< int>::name(),    "int");
   BOOST_REQUIRE_EQUAL_STR( celma::type< long>::name(),   "long");
   BOOST_REQUIRE_EQUAL_STR( celma::type< short>::name(),  "short");

   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned char>::name(),  "unsigned char");
   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned long>::name(),  "unsigned long");
   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned short>::name(), "unsigned short");

   // just to make sure: works also with typedefs
   typedef bool  my_bool;
   BOOST_REQUIRE_EQUAL_STR( celma::type< my_bool>::name(), "bool");

   BOOST_REQUIRE_EQUAL_STR( celma::type< char16_t>::name(), "char16_t");
   BOOST_REQUIRE_EQUAL_STR( celma::type< char32_t>::name(), "char32_t");
   BOOST_REQUIRE_EQUAL_STR( celma::type< wchar_t>::name(),  "wchar_t");

} // pod_types



/// Test for STL data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::bitset< 128>>::name(),
                          "std::bitset<128>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::string>::name(),
                          "std::string");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u16string>::name(),
                          "std::u16string");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u32string>::name(),
                          "std::u32string");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstring>::name(),
                          "std::wstring");

/*
#if have_any
#   ifdef experimental_any
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::any>::name(),
                          "std::experimental::any");
#   else
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::any>::name(), "std::any");
#   endif
#endif
*/

   typedef std::array< int, 10>          int_array;
   typedef std::array< std::string, 15>  string_array;
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_array>::name(),
                            "std::array<int,10>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_array>::name(),
                            "std::array<std::string,15>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::deque< long>>::name(),
                          "std::deque<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::deque< std::string>>::name(),
                          "std::deque<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::forward_list< long>>::name(),
                          "std::forward_list<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::forward_list< std::string>>::name(),
                          "std::forward_list<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::list< long>>::name(),
                          "std::list<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::list< std::string>>::name(),
                          "std::list<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::multiset< long>>::name(),
                          "std::multiset<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::multiset< std::string>>::name(),
                          "std::multiset<std::string>");

#if have_optional
#   ifdef experimental_optional
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::optional< std::string>>::name(),
                          "std::experimental::optional<std::string>");
#   else
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::optional< std::string>>::name(),
                          "std::optional<std::string>");
#   endif
#endif

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::priority_queue< long>>::name(),
                          "std::priority_queue<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::priority_queue< std::string>>::name(),
                          "std::priority_queue<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::queue< long>>::name(),
                          "std::queue<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::queue< std::string>>::name(),
                          "std::queue<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< long>>::name(),
                          "std::set<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< std::string>>::name(),
                          "std::set<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stack< int>>::name(),
                          "std::stack<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stack< std::string>>::name(),
                          "std::stack<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_multiset< int>>::name(),
                          "std::unordered_multiset<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_multiset< std::string>>::name(),
                          "std::unordered_multiset<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_set< int>>::name(),
                          "std::unordered_set<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_set< std::string>>::name(),
                          "std::unordered_set<std::string>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::valarray< uint64_t>>::name(),
                          "std::valarray<unsigned long>");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::vector< int>>::name(),
                          "std::vector<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::vector< std::string>>::name(),
                          "std::vector<std::string>");

} // stl_types



/// Test for STL data types with more than one template parameter.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types_key_value)
{

   typedef std::map< int, std::string>  int_string_map;
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_map>::name(),
                            "std::map<int,std::string>");

   typedef std::multimap< std::string, long>  string_long_multimap;
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_long_multimap>::name(),
                            "std::multimap<std::string,long>");

   typedef std::pair< std::string, std::string>  string_string_pair;
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_string_pair>::name(),
                            "std::pair<std::string,std::string>");

   typedef std::tuple< int, std::string>  int_string_tuple;
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_tuple>::name(),
                            "std::tuple<int,std::string>");

   typedef std::unordered_multimap< int, std::string>  int_string_unordered_multimap;
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_unordered_multimap>::name(),
                          "std::unordered_multimap<int,std::string>");

   typedef std::unordered_map< std::string, int>  string_int_unordered_map;
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_int_unordered_map>::name(),
                          "std::unordered_map<std::string,int>");

} // stl_types_key_value



/// Test for the data types provided by the iostreams sublibrary.
/// @since  0.10, 21.12.2016
BOOST_AUTO_TEST_CASE( test_iostream_types)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::filebuf>::name(),
                            "std::filebuf");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::fstream>::name(),
                            "std::fstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ifstream>::name(),
                            "std::ifstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ios>::name(),
                            "std::ios");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::iostream>::name(),
                            "std::iostream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::istream>::name(),
                            "std::istream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ofstream>::name(),
                            "std::ofstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ostream>::name(),
                            "std::ostream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::streambuf>::name(),
                            "std::streambuf");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stringbuf>::name(),
                            "std::stringbuf");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wfilebuf>::name(),
                            "std::wfilebuf");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wfstream>::name(),
                            "std::wfstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wifstream>::name(),
                            "std::wifstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wios>::name(),
                            "std::wios");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wiostream>::name(),
                            "std::wiostream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wistream>::name(),
                            "std::wistream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wostream>::name(),
                            "std::wostream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wofstream>::name(),
                            "std::wofstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstreambuf>::name(),
                            "std::wstreambuf");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstringbuf>::name(),
                            "std::wstringbuf");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::istringstream>::name(),
                            "std::istringstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ostringstream>::name(),
                            "std::ostringstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stringstream>::name(),
                            "std::stringstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wistringstream>::name(),
                            "std::wistringstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wostringstream>::name(),
                            "std::wostringstream");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstringstream>::name(),
                            "std::wstringstream");

} // test_iostream_types



/// Test getting the names of types within a smart pointer.
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( test_smart_pointers)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unique_ptr< std::string>>::name(),
                            "std::unique_ptr<std::string>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::shared_ptr< double>>::name(),
                            "std::shared_ptr<double>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::weak_ptr< int>>::name(),
                            "std::weak_ptr<int>");

} // test_smart_pointers



/// User defined class for which we won't provide the name.
/// @since  0.1, 15.03.2016
class UnknownUserDefinedType
{
}; // UnknownUserDefinedType



/// Test for unknown user defined type.
/// @since  1.0, 28.07.2015
BOOST_AUTO_TEST_CASE( unknown_user_defined_type)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< UnknownUserDefinedType>::name(),
                            "unknown");

} // unknown_user_defined_type



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
   } // celma::type< UserDefinedType>::name

}; // type<  UserDefinedType>



} // namespace celma



/// Test for user defined type.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( user_defined_type)
{

   BOOST_REQUIRE_EQUAL_STR( celma::type< UserDefinedType>::name(),
                            "UserDefinedType");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::vector< UserDefinedType>>::name(),
                            "std::vector<UserDefinedType>");

} // user_defined_type



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

   BOOST_REQUIRE_EQUAL_STR( celma::type< UserDefinedTypeMacro>::name(),
                            "UserDefinedTypeMacro");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::list< UserDefinedTypeMacro>>::name(),
                            "std::list<UserDefinedTypeMacro>");

} // user_defined_type_macro



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

   BOOST_REQUIRE_EQUAL_STR( celma::type< EnumType>::name(), "EnumType");

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< EnumType>>::name(),
                            "std::set<EnumType>");

} // user_defined_enum



// ========================  END OF test_type_name.cpp  ========================

