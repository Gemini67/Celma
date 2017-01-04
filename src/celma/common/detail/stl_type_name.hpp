
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for some types provided by the STL.


#ifndef CELMA_STL_TYPE_NAME_HPP
#define CELMA_STL_TYPE_NAME_HPP


#include <cstring>
#include <array>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "celma/common/constexpr_string_concat.hpp"
#include "celma/common/constexpr_string_from.hpp"
#include "celma/common/detail/provide_simple_type_name.hpp"
#include "celma/common/detail/provide_template_type_name.hpp"
#include "celma/common/detail/type_name.hpp"

#ifdef __has_include
/*
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
*/
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


/*
#if have_any
#   ifdef experimental_any
PROVIDE_SIMPLE_TYPE_NAME( std::experimental::any);
#   else
PROVIDE_SIMPLE_TYPE_NAME( std::any);
#   endif
#endif
*/


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
/// @tparam  T  The type of the data stored in the array.
/// @tparam  N  The number of values stored in the array.
/// @since  0.10, 25.12.2016
template< typename T, std::size_t N> class type< std::array< T, N>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::array<type,n>'.
   /// @since  0.10, 25.12.2016
   static constexpr const char* name()
   {
      if (mName[ 0] == 0)
      {
         ::memcpy( mName, "std::array<", 11);
         ::strcat( &mName[ 11], type< T>::name());
         ::strcat( mName, ",");
         ::strcat( mName, common::string_from< std::size_t, N>::value);
         ::strcat( mName, ">");
      } // end if
      return mName;
   } // end type< std::array< T>>::name

private:
   /// Used to store the name of the type persistently.
   static char  mName[ 128];

}; // type< std::array< T, N>>

template< typename T, std::size_t N> char  type< std::array< T, N>>::mName[ 128] = { 0 };


#if 1


/// Specialisation for type 'std::bitset<>'.
/// @tparam  N  The number of values stored in the bitset.
/// @since  0.1, 15.03.2016
template< std::size_t N> class type< std::bitset< N>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::bitset<n>'.
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      if (mName[ 0] == 0)
      {
         ::memcpy( mName, "std::bitset<", 12);
         ::strcpy( &mName[ 12], common::string_from< std::size_t, N>::value);
         ::strcat( mName, ">");
      } // end if
      return mName;
   } // end type< std::bitset< T>>::name

private:
   /// Used to store the name of the type persistently.
   static char  mName[ 128];

}; // type< std::bitset< T>>

template< std::size_t N> char  type< std::bitset< N>>::mName[ 128] = { 0 };


#else


/// Specialisation for type 'std::bitset<>'.
/// @tparam  N  The number of values stored in the bitset.
/// @since  0.1, 15.03.2016
template< std::size_t N> class type< std::bitset< N>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::bitset<n>'.
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // end type< std::bitset< T>>::name

private:
   /// Used to store the name of the type persistently.
   static constexpr auto const  mName =
      common::string_concat( "std::bitset<",
                             common::string_from< std::size_t, N>::value, ">");

}; // type< std::bitset< T>>


template< std::size_t N> constexpr auto const  type< std::bitset< N>>::mName;


#endif


PROVIDE_TEMPLATE_TYPE_NAME( std::deque);
PROVIDE_TEMPLATE_TYPE_NAME( std::forward_list);
PROVIDE_TEMPLATE_TYPE_NAME( std::list);
PROVIDE_TEMPLATE_TYPE_NAME( std::multiset);
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
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( c) \
   template< typename K, typename V> class type< c< K, V>> \
   { \
   public: \
      static constexpr const char* name() \
      { \
         if (mName[ 0] == 0) \
         { \
            ::strcpy( mName, # c); \
            ::strcat( mName, "<"); \
            ::strcat( mName, type< K>::name()); \
            ::strcat( mName, ","); \
            ::strcat( mName, type< V>::name()); \
            ::strcat( mName, ">"); \
         } \
         return mName; \
      } \
   private: \
      static char  mName[ 128]; \
   }; \
   template< typename K, typename V> char  type< c< K, V>>::mName[ 128] = { 0 }


PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::map);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::multimap);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::pair);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::unordered_map);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::unordered_multimap);


} // namespace celma


#endif   // CELMA_STL_TYPE_NAME_HPP


// ========================  END OF stl_type_name.hpp  ========================

