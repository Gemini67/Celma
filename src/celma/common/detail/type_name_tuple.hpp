
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
/// Adds partial template specialisations for the std::tuple type provided
/// by the STL.


#ifndef CELMA_TYPE_NAME_TUPLE_HPP
#define CELMA_TYPE_NAME_TUPLE_HPP


#include <cstring>
#include <functional>
#include <tuple>
#include "celma/common/tuple_at_index.hpp"
#include "celma/common/tuple_length.hpp"
#include "celma/common/detail/type_name.hpp"
#include "celma/common/detail/type_name_pod.hpp"


namespace celma {


namespace {


/// Helper class to append the name of the type of the next element of the tuple
/// to the destination string.
/// @since  0.10, 25.12.2016
class TypeHandler
{
public:
   /// Constructor.
   /// @param[in]  dest  Pointer to the string to append the element type name
   ///                   to.
   /// @since  0.10, 25.12.2016
   constexpr TypeHandler( char* dest):
      mpDest( dest)
   {
   } // TypeHandler::TypeHandler

   /// Called by common::tuple_at_index() for the next element of the tuple.
   /// @tparam  U  The type of the next element in the tuple.
   /// @param[in]  The next element of the tuple, value not needed.
   /// @since  0.10, 25.12.2016
   template< typename U> void operator()( U&)
   {
      ::strcat( mpDest, type< U>::name());
   } // TypeHandler::operator ()

private:
   /// Pointer to the string to append the type name to.
   char*   mpDest;

}; // TypeHandler


} // namespace


/// Specialisation for type 'std::tuple<>'.
/// @tparam  T  The types of the elements stored in the tuple.
/// @since  0.10, 25.12.2016
template< typename... T> class type< std::tuple< T...>>
{
public:
   /// Returns the name of the type.
   /// @return  'std::tuple<types...>'.
   /// @since  0.10, 25.12.2016
   static constexpr const char* name()
   {
      if (mName[ 0] == 0)
      {
         std::tuple< T...>  tmp;
         ::memcpy( mName, "std::tuple<", 11);
         for (size_t i = 0; i < common::tuple_length( tmp); ++i)
         {
            if (i > 0)
               ::strcat( mName, ",");

            TypeHandler  th( mName);
            common::tuple_at_index( i, tmp, th);
         } // end for
         ::strcat( mName, ">");
      } // end if
      return mName;
   } // end type< std::tuple< T...>>::name

private:
   /// Used to store the name of the type persistently.
   static char  mName[ 256];

}; // type< std::tuple< T...>>


template< typename... T> char  type< std::tuple< T...>>::mName[ 256] = { 0 };


} // namespace celma


#endif   // CELMA_TYPE_NAME_TUPLE_HPP


// =====  END OF type_name_tuple.hpp  =====

