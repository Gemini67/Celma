
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
**    Test program for the template family celma::type< > using the Boost.Test
**    module.
**
--*/


// module to test header file include
#include "celma/common/type_name.hpp"


// OS/C lib includes
#include <cstring>


// Boost includes
#define BOOST_TEST_MODULE TypeNameTest
#include <boost/test/unit_test.hpp>


#define  BOOST_REQUIRE_EQUAL_STR( a, b) \
   BOOST_REQUIRE( ::strcmp( a, b) == 0)


/// Test for POD data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( pod_types)
{

   static_assert( celma::type< bool>::name()[0] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< bool>::name(),   "bool");

   static_assert( celma::type< char>::name()[0] == 'c');
   BOOST_REQUIRE_EQUAL_STR( celma::type< char>::name(),   "char");

   static_assert( celma::type< double>::name()[0] == 'd');
   BOOST_REQUIRE_EQUAL_STR( celma::type< double>::name(), "double");

   static_assert( celma::type< float>::name()[0] == 'f');
   BOOST_REQUIRE_EQUAL_STR( celma::type< float>::name(),  "float");

   static_assert( celma::type< int>::name()[0] == 'i');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int>::name(),    "int");

   static_assert( celma::type< long>::name()[0] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< long>::name(),   "long");

   static_assert( celma::type< short>::name()[0] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< short>::name(),  "short");

   static_assert( celma::type< unsigned char>::name()[0] == 'u');
   static_assert( celma::type< unsigned char>::name()[9] == 'c');
   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned char>::name(),  "unsigned char");

   static_assert( celma::type< unsigned long>::name()[0] == 'u');
   static_assert( celma::type< unsigned long>::name()[9] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned long>::name(),  "unsigned long");

   static_assert( celma::type< unsigned short>::name()[0] == 'u');
   static_assert( celma::type< unsigned short>::name()[9] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< unsigned short>::name(), "unsigned short");

   // just to make sure: works also with typedefs
   using my_bool = bool;
   static_assert( celma::type< my_bool>::name()[0] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< my_bool>::name(), "bool");

   static_assert( celma::type< char16_t>::name()[0] == 'c');
   static_assert( celma::type< char16_t>::name()[4] == '1');
   BOOST_REQUIRE_EQUAL_STR( celma::type< char16_t>::name(), "char16_t");

   static_assert( celma::type< char32_t>::name()[0] == 'c');
   static_assert( celma::type< char32_t>::name()[4] == '3');
   BOOST_REQUIRE_EQUAL_STR( celma::type< char32_t>::name(), "char32_t");

   static_assert( celma::type< wchar_t>::name()[0] == 'w');
   BOOST_REQUIRE_EQUAL_STR( celma::type< wchar_t>::name(),  "wchar_t");

} // pod_types



/// Test for STL data types.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types)
{

#if have_any == 1
#   ifdef experimental_any
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::any>::name(),
                          "std::experimental::any");
#   else
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::any>::name(), "std::any");
#   endif
#endif

   static_assert( celma::type< std::bitset< 128>>::name()[0] == 's');
   static_assert( celma::type< std::bitset< 128>>::name()[5] == 'b');
   static_assert( celma::type< std::bitset< 128>>::name()[12] == '1');

   BOOST_REQUIRE_EQUAL_STR( celma::type< std::bitset< 128>>::name(),
                          "std::bitset<128>");

   static_assert( celma::type< std::string>::name()[5] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::string>::name(),
                          "std::string");

   static_assert( celma::type< std::u16string>::name()[5] == 'u');
   static_assert( celma::type< std::u16string>::name()[6] == '1');
   static_assert( celma::type< std::u16string>::name()[8] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u16string>::name(),
                          "std::u16string");

   static_assert( celma::type< std::u32string>::name()[5] == 'u');
   static_assert( celma::type< std::u32string>::name()[6] == '3');
   static_assert( celma::type< std::u32string>::name()[8] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u32string>::name(),
                          "std::u32string");

   static_assert( celma::type< std::wstring>::name()[5] == 'w');
   static_assert( celma::type< std::wstring>::name()[6] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstring>::name(),
                          "std::wstring");


#if have_string_view == 1
#   ifdef experimental_string_view
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::string_view>::name(),
                            "std::experimental::string_view");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::u16string_view>::name(),
                            "std::experimental::u16string_view");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::u32string_view>::name(),
                            "std::experimental::u32string_view");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::wstring_view>::name(),
                            "std::experimental::wstring_view");
#   else
   static_assert( celma::type< std::string_view>::name()[5] == 's');
   static_assert( celma::type< std::string_view>::name()[12] == 'v');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::string_view>::name(),
                            "std::string_view");

   static_assert( celma::type< std::u16string_view>::name()[5] == 'u');
   static_assert( celma::type< std::u16string_view>::name()[6] == '1');
   static_assert( celma::type< std::u16string_view>::name()[15] == 'v');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u16string_view>::name(),
                            "std::u16string_view");

   static_assert( celma::type< std::u32string_view>::name()[5] == 'u');
   static_assert( celma::type< std::u32string_view>::name()[6] == '3');
   static_assert( celma::type< std::u32string_view>::name()[15] == 'v');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::u32string_view>::name(),
                            "std::u32string_view");

   static_assert( celma::type< std::wstring_view>::name()[5] == 'w');
   static_assert( celma::type< std::wstring_view>::name()[13] == 'v');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstring_view>::name(),
                            "std::wstring_view");
#   endif
#endif


   using int_array = std::array< int, 10>;
   using string_array = std::array< std::string, 15>;

   static_assert( celma::type< int_array>::name()[5] == 'a');
   static_assert( celma::type< int_array>::name()[11] == 'i');
   static_assert( celma::type< int_array>::name()[15] == '1');
   static_assert( celma::type< int_array>::name()[16] == '0');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_array>::name(),
                            "std::array<int,10>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_array>::name(),
                            "std::array<std::string,15>");

   static_assert( celma::type< std::deque< long>>::name()[5] == 'd');
   static_assert( celma::type< std::deque< long>>::name()[11] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::deque< long>>::name(),
                          "std::deque<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::deque< std::string>>::name(),
                          "std::deque<std::string>");

   static_assert( celma::type< std::forward_list< long>>::name()[5] == 'f');
   static_assert( celma::type< std::forward_list< long>>::name()[18] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::forward_list< long>>::name(),
                          "std::forward_list<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::forward_list< std::string>>::name(),
                          "std::forward_list<std::string>");

   static_assert( celma::type< std::list< long>>::name()[5] == 'l');
   static_assert( celma::type< std::list< long>>::name()[10] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::list< long>>::name(),
                          "std::list<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::list< std::string>>::name(),
                          "std::list<std::string>");

   static_assert( celma::type< std::multiset< long>>::name()[5] == 'm');
   static_assert( celma::type< std::multiset< long>>::name()[14] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::multiset< long>>::name(),
                          "std::multiset<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::multiset< std::string>>::name(),
                          "std::multiset<std::string>");

#if have_optional
#   ifdef experimental_optional
   static_assert( celma::type< std::experimental::optional< std::string>>::name()[5] == 'e');
   static_assert( celma::type< std::experimental::optional< std::string>>::name()[19] == 'o');
   static_assert( celma::type< std::experimental::optional< std::string>>::name()[33] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::experimental::optional< std::string>>::name(),
                          "std::experimental::optional<std::string>");
#   else
   static_assert( celma::type< std::optional< std::string>>::name()[5] == 'o');
   static_assert( celma::type< std::optional< std::string>>::name()[19] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::optional< std::string>>::name(),
                          "std::optional<std::string>");
#   endif
#endif

   static_assert( celma::type< std::priority_queue< long>>::name()[5] == 'p');
   static_assert( celma::type< std::priority_queue< long>>::name()[20] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::priority_queue< long>>::name(),
                          "std::priority_queue<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::priority_queue< std::string>>::name(),
                          "std::priority_queue<std::string>");

   static_assert( celma::type< std::queue< long>>::name()[5] == 'q');
   static_assert( celma::type< std::queue< long>>::name()[11] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::queue< long>>::name(),
                          "std::queue<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::queue< std::string>>::name(),
                          "std::queue<std::string>");

   static_assert( celma::type< std::set< long>>::name()[5] == 's');
   static_assert( celma::type< std::set< long>>::name()[9] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< long>>::name(),
                          "std::set<long>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< std::string>>::name(),
                          "std::set<std::string>");

   static_assert( celma::type< std::stack< long>>::name()[5] == 's');
   static_assert( celma::type< std::stack< long>>::name()[11] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stack< int>>::name(),
                          "std::stack<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stack< std::string>>::name(),
                          "std::stack<std::string>");

   static_assert( celma::type< std::unordered_multiset< long>>::name()[5] == 'u');
   static_assert( celma::type< std::unordered_multiset< long>>::name()[24] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_multiset< int>>::name(),
                          "std::unordered_multiset<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_multiset< std::string>>::name(),
                          "std::unordered_multiset<std::string>");

   static_assert( celma::type< std::unordered_set< long>>::name()[5] == 'u');
   static_assert( celma::type< std::unordered_set< long>>::name()[19] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_set< int>>::name(),
                          "std::unordered_set<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unordered_set< std::string>>::name(),
                          "std::unordered_set<std::string>");

   static_assert( celma::type< std::valarray< uint64_t>>::name()[5] == 'v');
   static_assert( celma::type< std::valarray< uint64_t>>::name()[14] == 'u');
   static_assert( celma::type< std::valarray< uint64_t>>::name()[23] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::valarray< uint64_t>>::name(),
                          "std::valarray<unsigned long>");

   static_assert( celma::type< std::vector< int>>::name()[5] == 'v');
   static_assert( celma::type< std::vector< int>>::name()[12] == 'i');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::vector< int>>::name(),
                          "std::vector<int>");
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::vector< std::string>>::name(),
                          "std::vector<std::string>");

} // stl_types



/// Test for STL data types with more than one template parameter.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( stl_types_key_value)
{

   using int_string_map = std::map< int, std::string>;
   static_assert( celma::type< int_string_map>::name()[5] == 'm');
   static_assert( celma::type< int_string_map>::name()[9] == 'i');
   static_assert( celma::type< int_string_map>::name()[18] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_map>::name(),
                            "std::map<int,std::string>");

   using string_long_multimap = std::multimap< std::string, long>;
   static_assert( celma::type< string_long_multimap>::name()[5] == 'm');
   static_assert( celma::type< string_long_multimap>::name()[19] == 's');
   static_assert( celma::type< string_long_multimap>::name()[26] == 'l');
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_long_multimap>::name(),
                            "std::multimap<std::string,long>");

   using string_string_pair = std::pair< std::string, std::string>;
   static_assert( celma::type< string_string_pair>::name()[5] == 'p');
   static_assert( celma::type< string_string_pair>::name()[15] == 's');
   static_assert( celma::type< string_string_pair>::name()[27] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_string_pair>::name(),
                            "std::pair<std::string,std::string>");

   using int_string_tuple = std::tuple< int, std::string>;
   // static_assert( celma::type< int_string_tuple>::name()[5] == 't');
   // static_assert( celma::type< int_string_tuple>::name()[11] == 'i');
   // static_assert( celma::type< int_string_tuple>::name()[20] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_tuple>::name(),
                            "std::tuple<int,std::string>");

   using int_string_int_tuple = std::tuple< int, std::string, int>;
   // static_assert( celma::type< int_string_tuple>::name()[5] == 't');
   // static_assert( celma::type< int_string_tuple>::name()[11] == 'i');
   // static_assert( celma::type< int_string_tuple>::name()[20] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_int_tuple>::name(),
                            "std::tuple<int,std::string,int>");

   using int_string_unordered_multimap = std::unordered_multimap< int, std::string>;
   static_assert( celma::type< int_string_unordered_multimap>::name()[5] == 'u');
   static_assert( celma::type< int_string_unordered_multimap>::name()[15] == 'm');
   static_assert( celma::type< int_string_unordered_multimap>::name()[24] == 'i');
   static_assert( celma::type< int_string_unordered_multimap>::name()[33] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< int_string_unordered_multimap>::name(),
                          "std::unordered_multimap<int,std::string>");

   using string_int_unordered_map = std::unordered_map< std::string, int>;
   static_assert( celma::type< string_int_unordered_map>::name()[5] == 'u');
   static_assert( celma::type< string_int_unordered_map>::name()[15] == 'm');
   static_assert( celma::type< string_int_unordered_map>::name()[24] == 's');
   static_assert( celma::type< string_int_unordered_map>::name()[31] == 'i');
   BOOST_REQUIRE_EQUAL_STR( celma::type< string_int_unordered_map>::name(),
                          "std::unordered_map<std::string,int>");

} // stl_types_key_value



/// Test for the data types provided by the iostreams sublibrary.
/// @since  0.10, 21.12.2016
BOOST_AUTO_TEST_CASE( test_iostream_types)
{

   static_assert( celma::type< std::filebuf>::name()[5] == 'f');
   static_assert( celma::type< std::filebuf>::name()[9] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::filebuf>::name(),
                            "std::filebuf");

   static_assert( celma::type< std::fstream>::name()[5] == 'f');
   static_assert( celma::type< std::fstream>::name()[6] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::fstream>::name(),
                            "std::fstream");

   static_assert( celma::type< std::ifstream>::name()[5] == 'i');
   static_assert( celma::type< std::ifstream>::name()[6] == 'f');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ifstream>::name(),
                            "std::ifstream");

   static_assert( celma::type< std::ios>::name()[5] == 'i');
   static_assert( celma::type< std::ios>::name()[6] == 'o');
   static_assert( celma::type< std::ios>::name()[7] == 's');
   static_assert( celma::type< std::ios>::name()[8] == '\0');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ios>::name(),
                            "std::ios");

   static_assert( celma::type< std::iostream>::name()[5] == 'i');
   static_assert( celma::type< std::iostream>::name()[6] == 'o');
   static_assert( celma::type< std::iostream>::name()[7] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::iostream>::name(),
                            "std::iostream");

   static_assert( celma::type< std::istream>::name()[5] == 'i');
   static_assert( celma::type< std::istream>::name()[6] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::istream>::name(),
                            "std::istream");

   static_assert( celma::type< std::ofstream>::name()[5] == 'o');
   static_assert( celma::type< std::ofstream>::name()[6] == 'f');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ofstream>::name(),
                            "std::ofstream");

   static_assert( celma::type< std::ostream>::name()[5] == 'o');
   static_assert( celma::type< std::ostream>::name()[6] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ostream>::name(),
                            "std::ostream");

   static_assert( celma::type< std::streambuf>::name()[5] == 's');
   static_assert( celma::type< std::streambuf>::name()[11] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::streambuf>::name(),
                            "std::streambuf");

   static_assert( celma::type< std::stringbuf>::name()[5] == 's');
   static_assert( celma::type< std::stringbuf>::name()[11] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stringbuf>::name(),
                            "std::stringbuf");

   static_assert( celma::type< std::wfilebuf>::name()[5] == 'w');
   static_assert( celma::type< std::wfilebuf>::name()[6] == 'f');
   static_assert( celma::type< std::wfilebuf>::name()[10] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wfilebuf>::name(),
                            "std::wfilebuf");

   static_assert( celma::type< std::wfstream>::name()[5] == 'w');
   static_assert( celma::type< std::wfstream>::name()[6] == 'f');
   static_assert( celma::type< std::wfstream>::name()[7] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wfstream>::name(),
                            "std::wfstream");

   static_assert( celma::type< std::wifstream>::name()[5] == 'w');
   static_assert( celma::type< std::wifstream>::name()[6] == 'i');
   static_assert( celma::type< std::wifstream>::name()[7] == 'f');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wifstream>::name(),
                            "std::wifstream");

   static_assert( celma::type< std::wios>::name()[5] == 'w');
   static_assert( celma::type< std::wios>::name()[6] == 'i');
   static_assert( celma::type< std::wios>::name()[7] == 'o');
   static_assert( celma::type< std::wios>::name()[8] == 's');
   static_assert( celma::type< std::wios>::name()[9] == '\0');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wios>::name(),
                            "std::wios");

   static_assert( celma::type< std::wiostream>::name()[5] == 'w');
   static_assert( celma::type< std::wiostream>::name()[6] == 'i');
   static_assert( celma::type< std::wiostream>::name()[7] == 'o');
   static_assert( celma::type< std::wiostream>::name()[8] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wiostream>::name(),
                            "std::wiostream");

   static_assert( celma::type< std::wistream>::name()[5] == 'w');
   static_assert( celma::type< std::wistream>::name()[6] == 'i');
   static_assert( celma::type< std::wistream>::name()[7] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wistream>::name(),
                            "std::wistream");

   static_assert( celma::type< std::wofstream>::name()[5] == 'w');
   static_assert( celma::type< std::wofstream>::name()[6] == 'o');
   static_assert( celma::type< std::wofstream>::name()[7] == 'f');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wofstream>::name(),
                            "std::wofstream");

   static_assert( celma::type< std::wostream>::name()[5] == 'w');
   static_assert( celma::type< std::wostream>::name()[6] == 'o');
   static_assert( celma::type< std::wostream>::name()[7] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wostream>::name(),
                            "std::wostream");

   static_assert( celma::type< std::wstreambuf>::name()[5] == 'w');
   static_assert( celma::type< std::wstreambuf>::name()[6] == 's');
   static_assert( celma::type< std::wstreambuf>::name()[12] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstreambuf>::name(),
                            "std::wstreambuf");

   static_assert( celma::type< std::wstringbuf>::name()[5] == 'w');
   static_assert( celma::type< std::wstringbuf>::name()[6] == 's');
   static_assert( celma::type< std::wstringbuf>::name()[12] == 'b');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstringbuf>::name(),
                            "std::wstringbuf");

   static_assert( celma::type< std::istringstream>::name()[5] == 'i');
   static_assert( celma::type< std::istringstream>::name()[6] == 's');
   static_assert( celma::type< std::istringstream>::name()[12] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::istringstream>::name(),
                            "std::istringstream");

   static_assert( celma::type< std::ostringstream>::name()[5] == 'o');
   static_assert( celma::type< std::ostringstream>::name()[6] == 's');
   static_assert( celma::type< std::ostringstream>::name()[12] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::ostringstream>::name(),
                            "std::ostringstream");

   static_assert( celma::type< std::stringstream>::name()[5] == 's');
   static_assert( celma::type< std::stringstream>::name()[11] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::stringstream>::name(),
                            "std::stringstream");

   static_assert( celma::type< std::wistringstream>::name()[5] == 'w');
   static_assert( celma::type< std::wistringstream>::name()[6] == 'i');
   static_assert( celma::type< std::wistringstream>::name()[7] == 's');
   static_assert( celma::type< std::wistringstream>::name()[13] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wistringstream>::name(),
                            "std::wistringstream");

   static_assert( celma::type< std::wostringstream>::name()[5] == 'w');
   static_assert( celma::type< std::wostringstream>::name()[6] == 'o');
   static_assert( celma::type< std::wostringstream>::name()[7] == 's');
   static_assert( celma::type< std::wostringstream>::name()[13] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wostringstream>::name(),
                            "std::wostringstream");

   static_assert( celma::type< std::wstringstream>::name()[5] == 'w');
   static_assert( celma::type< std::wstringstream>::name()[6] == 's');
   static_assert( celma::type< std::wstringstream>::name()[12] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::wstringstream>::name(),
                            "std::wstringstream");

} // test_iostream_types



/// Test getting the names of types within a smart pointer.
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( test_smart_pointers)
{

   using  unique_string_t = std::unique_ptr< std::string>;
   static_assert( celma::type< unique_string_t>::name()[5] == 'u');
   static_assert( celma::type< unique_string_t>::name()[21] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::unique_ptr< std::string>>::name(),
                            "std::unique_ptr<std::string>");

   using  shared_double_t = std::shared_ptr< double>;
   static_assert( celma::type< shared_double_t>::name()[5] == 's');
   static_assert( celma::type< shared_double_t>::name()[16] == 'd');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::shared_ptr< double>>::name(),
                            "std::shared_ptr<double>");

   using  weak_int = std::weak_ptr< int>;
   static_assert( celma::type< weak_int>::name()[5] == 'w');
   static_assert( celma::type< weak_int>::name()[14] == 'i');
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

   static constexpr char const  mName[] = "UserDefinedType";

}; // type< UserDefinedType>



} // namespace celma



/// Test for user defined type.
/// @since  0.1, 15.03.2016
BOOST_AUTO_TEST_CASE( user_defined_type)
{

   static_assert( celma::type< UserDefinedType>::name()[0] == 'U');
   BOOST_REQUIRE_EQUAL_STR( celma::type< UserDefinedType>::name(),
                            "UserDefinedType");

   static_assert( celma::type< std::vector< UserDefinedType>>::name()[5] == 'v');
   static_assert( celma::type< std::vector< UserDefinedType>>::name()[12] == 'U');
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

   static_assert( celma::type< UserDefinedTypeMacro>::name()[0] == 'U');
   static_assert( celma::type< UserDefinedTypeMacro>::name()[15] == 'M');
   BOOST_REQUIRE_EQUAL_STR( celma::type< UserDefinedTypeMacro>::name(),
                            "UserDefinedTypeMacro");

   static_assert( celma::type< std::list< UserDefinedTypeMacro>>::name()[5] == 'l');
   static_assert( celma::type< std::list< UserDefinedTypeMacro>>::name()[10] == 'U');
   static_assert( celma::type< std::list< UserDefinedTypeMacro>>::name()[25] == 'M');
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

   static_assert( celma::type< EnumType>::name()[0] == 'E');
   BOOST_REQUIRE_EQUAL_STR( celma::type< EnumType>::name(), "EnumType");

   static_assert( celma::type< std::set< EnumType>>::name()[5] == 's');
   static_assert( celma::type< std::set< EnumType>>::name()[9] == 'E');
   BOOST_REQUIRE_EQUAL_STR( celma::type< std::set< EnumType>>::name(),
                            "std::set<EnumType>");

} // user_defined_enum



/// Test printing the type name of variable.
/// @since  0.11, 07.01.2017
BOOST_AUTO_TEST_CASE( test_type_from_variable)
{

   std::string  my_string;

   static_assert( celma::type< decltype( my_string)>::name()[5] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< decltype( my_string)>::name(),
                            "std::string");


   std::map< int, std::string>  my_map;

   BOOST_REQUIRE_EQUAL_STR( celma::type< decltype( my_map)>::name(),
                            "std::map<int,std::string>");

} // test_type_from_variable



/// Check the names of nested STL container types.
/// @since  1.12.0, 24.09.2018
BOOST_AUTO_TEST_CASE( nested_containers)
{

   using  map_of_vector_t = std::map< std::string, std::vector< int>>;

   static_assert( celma::type< map_of_vector_t>::name()[ 5] == 'm');
   static_assert( celma::type< map_of_vector_t>::name()[ 14] == 's');
   BOOST_REQUIRE_EQUAL_STR( celma::type< map_of_vector_t>::name(),
                            "std::map<std::string,std::vector<int>>");

   using  vector_of_sets_t = std::vector< std::set< int>>;

   static_assert( celma::type< vector_of_sets_t>::name()[  5] == 'v');
   static_assert( celma::type< vector_of_sets_t>::name()[ 18] == 'e');
   BOOST_REQUIRE_EQUAL_STR( celma::type< vector_of_sets_t>::name(),
                            "std::vector<std::set<int>>");

} // nested_containers



// =====  END OF test_type_name.cpp  =====

