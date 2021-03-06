
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::EnumArray<>.


#ifndef CELMA_COMMON_ENUM_ARRAY_HPP
#define CELMA_COMMON_ENUM_ARRAY_HPP


#include <array>


namespace celma { namespace common {


/// Allows to use a std::array with enum values as indices.
///
/// @tparam  T
///    The type of the values to store in the array.
/// @tparam  E
///    The type of the enum that is used to access the elements of the array.
/// @tparam  N
///    The size of the array.
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
   /// @tparam  X  The type(s) of the value(s) passed to the constructor.
   /// @param[in]  x  The value(s) to pass to the internal array's constructor.
   /// @since  1.18.0, 11.12.2018
   template< typename... X> EnumArray( X&&... x):
      std::array< T, N>{{ std::forward< X>( x)... }}
   {
   } // EnumArray< T, E, N>::EnumArray

   /// Assignment operator.
   ///
   /// @param[in]  ea  The other enum-array to copy the data from.
   /// @return  This object.
   EnumArray& operator =( const EnumArray& ea)
   {
      std::array< T, N>::operator =( ea);
      return *this;
   } // EnumArray< T, E, N>::EnumArray

   /// Returns a reference of the value at the given position.
   ///
   /// @param[in]  idx
   ///    The enum value that specifies the position of the value to return.
   /// @return  The (reference to the) value at the given position.
   /// @since  1.18.0, 11.12.2018
   T& operator []( E idx)
   {
     return std::array< T, N>::operator []( static_cast< std::size_t>( idx));
   } // EnumArray< T, E, N>::operator []

   /// Returns a const reference of the value at the given position.
   ///
   /// @param[in]  idx
   ///    The enum value that specifies the position of the value to return.
   /// @return  The (const reference to the) value at the given position.
   /// @since  1.18.0, 11.12.2018
   const T& operator []( E idx) const
   {
     return std::array< T, N>::operator []( static_cast< std::size_t>( idx));
   } // EnumArray< T, E, N>::operator []

   /// Returns a reference of the value at the given position.
   ///
   /// @param[in]  idx  The position of the value to return.
   /// @return  The (reference to the) value at the given position.
   /// @since  1.18.0, 11.12.2018
   T& operator []( std::size_t idx)
   {
     return std::array< T, N>::operator []( idx);
   } // EnumArray< T, E, N>::operator []

   /// Returns a const reference of the value at the given position.
   ///
   /// @param[in]  idx  The position of the value to return.
   /// @return  The (const reference to the) value at the given position.
   /// @since  1.18.0, 11.12.2018
   const T& operator []( std::size_t idx) const
   {
     return std::array< T, N>::operator []( idx);
   } // EnumArray< T, E, N>::operator []

}; // EnumArray< T, E, N>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_ENUM_ARRAY_HPP


// =====  END OF enum_array.hpp  =====

