
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for the std::tuple type provided
/// by the STL.


#ifndef CELMA_DETAIL_TYPE_NAME_STL_STORE_HPP
#define CELMA_DETAIL_TYPE_NAME_STL_STORE_HPP


#include <tuple>
#include <variant>


namespace celma { namespace detail {


/// Special case for single or last type of a type list.<br>
/// Returns the name of the single type.
///
/// @tparam  T  The type to return the name of.
/// @return  The name of the given type, using the corresponding type<> template.
/// @since  1.16.0, 01.11.2018
template< class T> constexpr auto typeNameList()
{
   return type< T>::mName;
} // typeNameList


/// Returns the comma separated list of all names of the types passed in here.<br>
/// Special case of single/last type is handled in template above.<br>
/// This function handles the cases of 2, 3, ... etc. types, since \a Tp can be
/// empty.<br>
/// Here we actually create the string for the name of the first type, then call
/// typeNameList<> again with the remaining types (must be at least 1: \a T1).
///
/// @tparam  T0
///    The first type to create the name string for.
/// @tparam  T1
///    The second type name, will be handled in the next function call.
/// @tparam  Tp
///    List of the remaining types, may be empty.
/// @return  The string with the comma separated list of all type names.
/// @since  1.16.0, 01.11.2018
template< typename T0, typename T1, typename... Tp>
   constexpr auto typeNameList()
{
   return common::string_concat( type< T0>::mName, ",", typeNameList< T1, Tp...>());
} // typeNameList


} // namespace detail


/// Specialisation for type 'std::tuple<>'.
///
/// @tparam  T  The types of the elements stored in the tuple.
/// @since  0.10, 25.12.2016
template< typename... T> class type< std::tuple< T...>>
{
public:
   /// Returns the name of the tuple type.
   ///
   /// @return  'std::tuple<types...>'.
   /// @since  0.10, 25.12.2016
   static constexpr const char* name()
   {
      return mName.data();
   } // end type< std::tuple< T...>>::name

   /// Used to store the name of the type persistently.
   static constexpr auto const  mName =
      common::string_concat( "std::tuple<", detail::typeNameList< T...>(), ">");

}; // type< std::tuple< T...>>


/// Specialisation for type 'std::variant<>'.
///
/// @tparam  T  The types of the elements stored in the variant.
/// @since  1.16.0, 02.11.2018
template< typename... T> class type< std::variant< T...>>
{
public:
   /// Returns the name of the variant type.
   ///
   /// @return  'std::variant<types...>'.
   /// @since  1.16.0, 02.11.2018
   static constexpr const char* name()
   {
      return mName.data();
   } // end type< std::variant< T...>>::name

   /// Used to store the name of the type persistently.
   static constexpr auto const  mName =
      common::string_concat( "std::variant<", detail::typeNameList< T...>(),
         ">");

}; // type< std::variant< T...>>


} // namespace celma


#endif   // CELMA_DETAIL_TYPE_NAME_STL_STORE_HPP


// =====  END OF type_name_stl_store.hpp  =====

