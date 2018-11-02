
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


namespace celma {


namespace detail {


/// Special case for single or last type of a tuple.<br>
/// Returns the name of the single type.
///
/// @tparam  T  The type to return the name of.
/// @return  The name of the given type, using the corresponding type<> template.
/// @since  x.y.z, 01.11.2018
template< class T> constexpr const auto tuple_type_names()
{
   return type< T>::mName;
} // tuple_type_names


/// Returns the concatenated names of all the types passed in here.<br>
/// Special case of single/last type is handled in template above.<br>
/// This function handles the cases of 2, 3, ... etc. types, since \a Tp can be
/// empty.<br>
/// Here we actually create the string for the name of the first type, then call
/// tuple_type_names<> again with the remaining types (must be at least 1:
/// \a T1).
///
/// @tparam  T0
///    The first type to create the name string for.
/// @tparam  T1
///    The second type name, will be handled in the next function call.
/// @tparam  Tp
///    List of the remaining types, may be empty.
/// @return  The string with the comma separated list of all type names.
/// @since  x.y.z, 01.11.2018
template< typename T0, typename T1, typename... Tp>
   constexpr const auto tuple_type_names()
{
   return common::string_concat( type< T0>::mName, ",", tuple_type_names< T1, Tp...>());
} // tuple_type_names


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
      return &mName[ 0];
   } // end type< std::tuple< T...>>::name

   /// Used to store the name of the type persistently.
   static constexpr auto const  mName =
      common::string_concat( "std::tuple<",
         detail::tuple_type_names< T...>(), ">");

}; // type< std::tuple< T...>>


} // namespace celma


#endif   // CELMA_TYPE_NAME_TUPLE_HPP


// =====  END OF type_name_tuple.hpp  =====

