
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template function celma::common::tuple_length.


#pragma once


#include <functional>
#include <tuple>


namespace celma::common {


/// When this function is called, we know the number of elements in the tuple
/// which we were looking for: \a I.
///
/// @tparam  I
///    Tuple element index, here: Number of elements in the tuple.
/// @tparam  Tp
///    Template parameter pack, not really used here.
/// @param[in]
///    The tuple object, not used here.
/// @return
///    The number of elements in the tuple.
/// @since
///    0.10, 27.09.2016
template< std::size_t I = 0, typename... Tp>
   inline typename std::enable_if< I == sizeof...( Tp), std::size_t>::type
      tuple_length( const std::tuple< Tp...>&)
{
   return I;
} // tuple_length
 

/// Simply call this function with the tuple as parameter. It will recursively
/// call itself until \a I matches the number of elements in the tuple.
///
/// @tparam  I
///    Tuple element index.
/// @tparam  Tp
///    Template parameter pack, not really used here.
/// @param[in]
///    The tuple object to determine the length of.
/// @return
///    The number of elements in the tuple.
/// @since
///    0.10, 27.09.2016
template< std::size_t I = 0, typename... Tp>
   inline typename std::enable_if< I < sizeof...( Tp), std::size_t>::type
      tuple_length( const std::tuple< Tp...>& t)
{
   return tuple_length< I + 1, Tp...>( t);
} // tuple_length


} // namespace celma::common


// =====  END OF tuple_length.hpp  =====

