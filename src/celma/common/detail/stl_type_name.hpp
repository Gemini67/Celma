
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
#include <boost/lexical_cast.hpp>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include "celma/common/detail/type_name.hpp"


namespace celma {


/// Specialisation for type 'std::string'.
/// @since  0.1, 15.03.2016
template<> class type< std::string>
{
public:
   /// Returns the name of the type.
   /// @return  'std::string'.
   /// @since  0.1, 15.03.2016
   static constexpr const char* name()
   {
      return "std::string";
   } // end type< std::string>::name

}; // type< std::string>


/// Specialisation for type 'std::bitset<>'.
/// @tparam  N  The number of values stored in the bitset.
/// @since  0.1, 15.03.2016
template< std::size_t N> class type< std::bitset< N> >
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
         ::strcpy( &mName[ 12], boost::lexical_cast< std::string>( N).c_str());
         ::strcat( mName, ">");
      } // end if
      return mName;
   } // end type< std::bitset< T> >::name

private:
   /// Used to store the name of the type persistently.
   static char  mName[ 128];

}; // type< std::bitset< T> >

template< std::size_t N> char  type< std::bitset< N> >::mName[ 128] = { 0 };


/// Macro to create the specialisation of type<> for an STL container.
/// @param  c  The type of the container to create the specialisation for.
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_TEMPLATE_TYPE_NAME( c) \
   template< typename T> class type< c< T> > \
   { \
   public: \
      static constexpr const char* name() \
      { \
         if (mName[ 0] == 0) \
         { \
            ::strcpy( mName, # c); \
            ::strcat( mName, "<"); \
            ::strcat( mName, type< T>::name()); \
            ::strcat( mName, ">"); \
         } \
         return mName; \
      } \
   private: \
      static char  mName[ 128]; \
   }; \
   template< typename T> char  type< c< T> >::mName[ 128] = { 0 }


PROVIDE_TEMPLATE_TYPE_NAME( std::deque);
PROVIDE_TEMPLATE_TYPE_NAME( std::list);
PROVIDE_TEMPLATE_TYPE_NAME( std::multiset);
PROVIDE_TEMPLATE_TYPE_NAME( std::priority_queue);
PROVIDE_TEMPLATE_TYPE_NAME( std::queue);
PROVIDE_TEMPLATE_TYPE_NAME( std::set);
PROVIDE_TEMPLATE_TYPE_NAME( std::stack);
PROVIDE_TEMPLATE_TYPE_NAME( std::vector);


/// Macro to create the specialisation of type<> for an STL container.
/// @param  c  The type of the container to create the specialisation for.
/// @since  0.1, 15.03.2016  (macro-isation of multiple template specialisations).
#define  PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( c) \
   template< typename K, typename V> class type< c< K, V> > \
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
   template< typename K, typename V> char  type< c< K, V> >::mName[ 128] = { 0 }


PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::map);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::multimap);
PROVIDE_KEY_VALUE_TEMPLATE_TYPE_NAME( std::pair);


} // namespace celma


#endif   // CELMA_STL_TYPE_NAME_HPP


// ========================  END OF stl_type_name.hpp  ========================

