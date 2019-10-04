
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for some types provided by the STL.


#ifndef CELMA_TYPE_NAME_STL_HPP
#define CELMA_TYPE_NAME_STL_HPP


#include <cstring>
#include <array>
#include <bitset>
#include <complex>
#include <deque>
#include <forward_list>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <ratio>
#include <set>
#include <stack>
#include <string>
#include <system_error>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "celma/common/constexpr_string_concat.hpp"
#include "celma/common/constexpr_string_from.hpp"
#include "celma/common/detail/provide_simple_type_name.hpp"
#include "celma/common/detail/provide_template_type_name.hpp"
#include "celma/common/detail/type_name.hpp"

#ifdef __has_include
#   if __has_include(<any>)
#      include <any>
#      define have_any 1
#   elif __has_include(<experimental/any>)
#      include <experimental/any>
#      define have_any 1
#      define experimental_any
#   else
#      define have_any 0
#   endif
#   if __has_include(<optional>)
#      include <optional>
#      define have_optional 1
#   elif __has_include(<experimental/optional>)
#      include <experimental/optional>
#      define have_optional 1
#      define experimental_optional
#   else
#      define have_optional 0
#   endif
#   if __has_include(<string_view>)
#      include <string_view>
#      define have_string_view 1
#   elif __has_include(<experimental/string_view>)
#      include <experimental/string_view>
#      define have_string_view 1
#      define experimental_string_view
#   else
#      define have_string_view 0
#   endif
#endif   // has_include


namespace celma {


#if have_any
#   ifdef experimental_any
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::any);
#   else
PROVIDE_SIMPLE_TYPE_NAME( std::any);
#   endif
#endif


/// Specialisation for type 'std::nullptr_t'.
PROVIDE_SIMPLE_TYPE_NAME( std::nullptr_t);
/// Specialisation for type 'std::thread'.
PROVIDE_SIMPLE_TYPE_NAME( std::thread);

/// Specialisation for type 'std::error_category'.
PROVIDE_SIMPLE_TYPE_NAME( std::error_category);
/// Specialisation for type 'std::error_code'.
PROVIDE_SIMPLE_TYPE_NAME( std::error_code);
/// Specialisation for type 'std::error_condition'.
PROVIDE_SIMPLE_TYPE_NAME( std::error_condition);
/// Specialisation for type 'std::system_error'.
PROVIDE_SIMPLE_TYPE_NAME( std::system_error);

/// Specialisation for type 'std::string'.
PROVIDE_SIMPLE_TYPE_NAME( std::string);
/// Specialisation for type 'std::u16string'.
PROVIDE_SIMPLE_TYPE_NAME( std::u16string);
/// Specialisation for type 'std::u32string'.
PROVIDE_SIMPLE_TYPE_NAME( std::u32string);
/// Specialisation for type 'std::wstring'.
PROVIDE_SIMPLE_TYPE_NAME( std::wstring);


#if have_string_view == 1
#   ifdef experimental_string_view
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::u16string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::u32string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::wstring_view);
#   else
PROVIDE_SIMPLE_TYPE_NAME( std::string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::u16string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::u32string_view);
PROVIDE_SIMPLE_TYPE_NAME( std::wstring_view);
#   endif
#endif


/// Specialisation for type 'std::array<>'.
///
/// @tparam  T  The type of the data stored in the array.
/// @tparam  N  The number of values stored in the array.
/// @since  1.12.0, 14.09.2018  (now fully constexpr)
/// @since  0.10, 25.12.2016
template< typename T, std::size_t N> class type< std::array< T, N>>
{
public:
   /// Returns the name of the type.
   ///
   /// @return  'std::array<type,n>'.
   /// @since  0.10, 25.12.2016
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< std::array< T>>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( "std::array<", type< T>::mName, ",",
         common::string_from< std::size_t, N>::value, ">");

}; // type< std::array< T, N>>


/// Specialisation for type 'std::bitset<>'.
/// @tparam  N  The number of values stored in the bitset.
/// @since  1.12.0, 14.09.2018  (now fully constexpr)
/// @since  0.1, 15.03.2016
template< std::size_t N> class type< std::bitset< N>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::bitset< <number> >' (without the spaces).
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< std::bitset< T>>::name

   /// Used to store the name of the type persistently.<br>
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( "std::bitset<",
         common::string_from< std::size_t, N>::value, ">");

}; // type< std::bitset< T>>


/// Specialisation for type 'std::ratio<>'.
///
/// @tparam  N  The numerator of the ratio.
/// @tparam  D  The denominator of the ratio.
/// @since  1.16.0, 03.10.2018
template< intmax_t N, intmax_t D> class type< std::ratio< N, D>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::ratio< <numerator>, <denominator> >' (without the spaces).
   /// @since  1.16.0, 03.10.2018
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< std::ratio< N, D>>::name

   /// Used to store the name of the type persistently.<br>
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( "std::ratio<",
         common::string_from< std::intmax_t, N>::value, ",",
         common::string_from< std::intmax_t, D>::value, ">");

}; // type< std::ratio< N, D>>


PROVIDE_TEMPLATE_TYPE_NAME( std::complex);
PROVIDE_TEMPLATE_TYPE_NAME( std::deque);
PROVIDE_TEMPLATE_TYPE_NAME( std::forward_list);
PROVIDE_TEMPLATE_TYPE_NAME( std::list);
PROVIDE_TEMPLATE_TYPE_NAME( std::multiset);
PROVIDE_TEMPLATE_TYPE_NAME( std::numeric_limits);
PROVIDE_TEMPLATE_TYPE_NAME( std::priority_queue);
PROVIDE_TEMPLATE_TYPE_NAME( std::queue);
PROVIDE_TEMPLATE_TYPE_NAME( std::set);
PROVIDE_TEMPLATE_TYPE_NAME( std::stack);
PROVIDE_TEMPLATE_TYPE_NAME( std::unordered_multiset);
PROVIDE_TEMPLATE_TYPE_NAME( std::unordered_set);
PROVIDE_TEMPLATE_TYPE_NAME( std::valarray);
PROVIDE_TEMPLATE_TYPE_NAME( std::vector);


#if have_optional == 1
#   ifdef experimental_optional
PROVIDE_TEMPLATE_TYPE_NAME( std::experimental::optional);
#   else
PROVIDE_TEMPLATE_TYPE_NAME( std::optional);
#   endif
#endif


/// Macro to create the specialisation of type<> for an STL container.
/// @param  c  The type of the container to create the specialisation for.
/// @since  1.12.0, 14.09.2018  (now fully constexpr)
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( c) \
   template< typename K, typename V> class type< c< K, V>> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         return &mName[ 0]; \
      } \
      static constexpr auto const  mName = \
         common::string_concat( # c, "<", type< K>::mName, ",", \
            type< V>::mName, ">"); \
   }


PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::map);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::multimap);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::pair);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::unordered_map);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::unordered_multimap);


} // namespace celma


#endif   // CELMA_TYPE_NAME_STL_HPP


// =====  END OF type_name_stl.hpp  =====

