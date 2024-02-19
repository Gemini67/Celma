
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::EnumArray<>.


#pragma once


#include <array>


namespace celma::common {


/// Allows to use a std::array with enum values as indices.
///
/// @tparam  T
///    Type of the values to store in the array.
/// @tparam  E
///    Type of the enum that is used to access the elements of the array.
/// @tparam  N
///    Size of the array.
/// @since  1.18.0, 11.12.2018
template< typename T, typename E, std::size_t N> class EnumArray:
   public std::array< T, N>
{
public:
   // Defaulted constructors.
   EnumArray() = default;
   EnumArray( const EnumArray&) = default;
   EnumArray( EnumArray&&) = default;
   ~EnumArray() = default;

   /// Constructor that enables passing an initializer list.
   ///
   /// @tparam  X  Type(s) of the value(s) passed to the constructor.
   /// @param[in]  x  Value(s) to pass to the internal array's constructor.
   /// @since  1.18.0, 11.12.2018
   template< typename... X> EnumArray( X&&... x):
      std::array< T, N>{{ std::forward< X>( x)... }}
   {
   } // EnumArray< T, E, N>::EnumArray

   /// Assignment operator.
   ///
   /// @param[in]  ea  Other enum-array to copy the data from.
   /// @returns  This object.
   EnumArray& operator =( const EnumArray& ea)
   {
      std::array< T, N>::operator =( ea);
      return *this;
   } // EnumArray< T, E, N>::EnumArray

   /// Returns a reference of the value at the given position.
   ///
   /// @param[in]  idx
   ///    Enum value that specifies the position of the value to return.
   /// @returns  (Reference to the) Value at the given position.
   /// @since  1.18.0, 11.12.2018
   [[nodiscard]] T& operator []( const E idx)
   {
     return std::array< T, N>::operator []( static_cast< std::size_t>( idx));
   } // EnumArray< T, E, N>::operator []

   /// Returns a const reference of the value at the given position.
   ///
   /// @param[in]  idx
   ///    Enum value that specifies the position of the value to return.
   /// @returns  (Const reference to the) Value at the given position.
   /// @since  1.18.0, 11.12.2018
   [[nodiscard]] const T& operator []( const E idx) const
   {
     return std::array< T, N>::operator []( static_cast< std::size_t>( idx));
   } // EnumArray< T, E, N>::operator []

   /// Returns a reference of the value at the given position.
   ///
   /// @param[in]  idx  Position of the value to return.
   /// @returns  (Reference to the) Value at the given position.
   /// @since  1.18.0, 11.12.2018
   [[nodiscard]] T& operator []( const std::size_t idx)
   {
     return std::array< T, N>::operator []( idx);
   } // EnumArray< T, E, N>::operator []

   /// Returns a const reference of the value at the given position.
   ///
   /// @param[in]  idx  Position of the value to return.
   /// @returns  (Const reference to the) Value at the given position.
   /// @since  1.18.0, 11.12.2018
   [[nodiscard]] const T& operator []( const std::size_t idx) const
   {
     return std::array< T, N>::operator []( idx);
   } // EnumArray< T, E, N>::operator []

}; // EnumArray< T, E, N>


} // namespace celma::common


// =====  END OF enum_array.hpp  =====

