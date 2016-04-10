
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
/// See documentation of classes celma::common::ClearVector,
/// celma::common::ClearContainer and celma::common::ClearMap.


#ifndef CELMA_COMMON_CLEAR_CONTAINER_HPP
#define CELMA_COMMON_CLEAR_CONTAINER_HPP


#include <cstddef>


namespace celma { namespace common {


/// Clear a vector which contains pointers: Delete all objects and the clear the
/// vector.
/// @since  0.2, 10.04.2016
class Vector
{
public:
   /// Clears a vector.
   /// @tparam  V  The type of the vector to clear.
   /// @param[in]  vec  The vector to clear.
   /// @since  0.2, 10.04.2016
   template< typename V> static void clear( V& vec)
   {
      for (size_t i = 0; i < vec.size(); ++i)
      {
         delete vec[ i];
      } // end for
      vec.clear();
   } // end Vector::clear

}; // Vector


/// Clear a container that provides an iterator, holds single (key) values (not
/// key/value pairs) and contains pointers: Delete all objects and the clear the
/// container.<br>
/// Use for list, deque, set etc.
/// @since  0.2, 10.04.2016
class Container
{
public:
   /// Clears a container.
   /// @tparam  C  The type of the container to clear.
   /// @param[in]  cont  The container to clear.
   /// @since  0.2, 10.04.2016
   template< typename C> static void clear( C& cont)
   {
      // in C++11x, this could be
      // std::for_each( cont.begin(), cont.end(),
      //                [&]( typename C::value_type& pv) { delete pv; }
      //              );
      // but then, in C++11x we would use a unique_ptr<>, so ...
      for (typename C::iterator it = cont.begin(); it != cont.end(); ++it)
      {
         delete *it;
      } // end for
      cont.clear();
   } // Container::clear

}; // Container


/// Clear a container with separate key/value pairs that contains pointers:
/// Delete all objects and the clear the container.<br>
/// Use for map, multimap etc.
/// @since  0.2, 10.04.2016
class Map
{
public:
   /// Clears a key/value pair container.
   /// @param[in]  map2c  The container to clear.
   /// @since  0.2, 10.04.2016
   template< typename M> static void clear( M& map2c)
   {
      for (typename M::iterator it = map2c.begin(); it != map2c.end(); ++it)
      {
         delete it->second;
      } // end for
      map2c.clear();
   } // end Map::clear

}; // Map


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CLEAR_CONTAINER_HPP


// =========================  END OF clear_container.hpp  =========================

