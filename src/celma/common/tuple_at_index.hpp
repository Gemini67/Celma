
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template function celma::common::tuple_at_index.


#ifndef CELMA_COMMON_TUPLE_AT_INDEX_HPP
#define CELMA_COMMON_TUPLE_AT_INDEX_HPP


#include <functional>
#include <stdexcept>
#include <tuple>


namespace celma { namespace common {


/// kudos to Victor Laskin
/// found here: http://stackoverflow.com/questions/8194227/how-to-get-the-i-th-element-from-an-stdtuple-when-i-isnt-know-at-compile-time


/// Special version of tuple_at_index() that is used when the specified element
/// index is greater than the number of elements in the tuple.
template< std::size_t I = 0, typename FuncT, typename... Tp>
   inline typename std::enable_if< sizeof...( Tp) < I, void>::type
      tuple_at_index( int, std::tuple< Tp...>&, FuncT) noexcept( false)
{
   throw std::range_error( "index exceeds number of elements in tuple");
} // tuple_at_index


/// Special version of tuple_at_index() that is used to handle the end of the
/// iteration.
template< std::size_t I = 0, typename FuncT, typename... Tp>
   inline typename std::enable_if< I == sizeof...( Tp), void>::type
      tuple_at_index( int index, std::tuple< Tp...>&, FuncT) noexcept( false)
{
   if (index >= 0)
      throw std::range_error( "index exceeds number of elements in tuple");
} // tuple_at_index
 

/// Access the nth value of a tuple, when n is only known at runtime.
/// @tparam  I      The current element number of the tuple to investigate.
/// @tparam  FuncT  The type of the functor to call when the requested element
///                 is found.
/// @tparam  Tp     The template parameter pack, i.e. the tuple.
/// @param[in]  index  The number of the element in the tuple to search for.<br>
///                    The first element has number 0.
/// @param[in]  t      The tuple.
/// @param[in]  f      The functor to call.
/// @return  The (reference of) the element at the specified position, when found.
/// @since  0.5, 27.09.2016
template< std::size_t I = 0, typename FuncT, typename... Tp>
   inline typename std::enable_if< I < sizeof...( Tp), void>::type
      tuple_at_index( int index, std::tuple< Tp...>& t, FuncT f) noexcept( false)
{
   if (index == 0)
      f( std::get< I>( t));
   tuple_at_index< I + 1, FuncT, Tp...>( index - 1, t, f);
} // tuple_at_index


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TUPLE_AT_INDEX_HPP


// ========================  END OF tuple_at_index.hpp  ========================

