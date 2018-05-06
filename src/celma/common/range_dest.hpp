
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of templates celma::common::RangeDest.


#ifndef CELMA_COMMON_RANGE_DEST_HPP
#define CELMA_COMMON_RANGE_DEST_HPP


#include <bitset>
#include <set>


namespace celma { namespace common {


/// Helper class to store value(s) in a container. Partial template
/// specialisation is used to provide the same interface for all standard
/// containers.<br>
/// Default type for all containers that support push_back().
/// @tparam  T  The type of the values stored in the container.
/// @tparam  C  The type of the container.
/// @since  0.2, 07.04.2016
template< typename T, typename C> class RangeDest
{
public:
   /// Constructor.
   /// @param[in]  dest  The container to store the values in.
   /// @since  0.2, 07.04.2016
   RangeDest( C& dest):
      mDestination( dest)
   {
   } // RangeDest< T, C>::RangeDest

   /// Stores/Sets a value in the container.
   /// @param[in]  v  The value to store in the container.
   /// @since  0.2, 07.04.2016
   void set( const T& v)
   {
      mDestination.push_back( v);
   } // RangeDest< T, C>::set

   /// Returns if the destination container is empty (no value set/stored).
   /// @return  \c true if the destination container is empty.
   /// @since  0.2, 07.04.2016
   bool empty() const
   {
      return mDestination.empty();
   } // RangeDest< T, C>::empty

private:
   /// The container to store the values in.
   C&  mDestination;
   
}; // RangeDest< T, C>::


/// Partial template specialisation for destination containers type std::bitset<>.
/// @tparam  S  The size of the bitset.
/// @since  0.2, 07.04.2016
template< size_t S> class RangeDest< size_t, std::bitset< S> >
{
public:
   /// The container type.
   typedef std::bitset< S>  dest_type;

   /// Constructor.
   /// @param[in]  dest  The bitset to set the flags on.
   /// @since  0.2, 07.04.2016
   RangeDest( dest_type& dest):
      mDestination( dest)
   {
   } // RangeDest< size_t, std::bitset< S> >::RangeDest

   /// Sets a flag in the bitset.
   /// @param[in]  v  The index of the flag to set.
   /// @since  0.2, 07.04.2016
   void set( const size_t& v)
   {
      mDestination.set( v);
   } // RangeDest< size_t, std::bitset< S> >:set

   /// Returns if destination bitset is empty (no value set).
   /// @return  \c true if no value is set in the destination bitset.
   /// @since  0.2, 07.04.2016
   bool empty() const
   {
      return mDestination.none();
   } // RangeDest< T, C>::empty

private:
   /// The bitset to set the flags on.
   dest_type&  mDestination;

}; // RangeDest< size_t, std::bitset< S> >


/// Partial template specialisation for destination container type std::set<>.
/// @tparam  T  The type of the values to store in the set.
/// @since  0.2, 07.04.2016
template< typename T> class RangeDest< T, std::set< T> >
{
public:
   /// The container type.
   typedef std::set< T>  dest_type;

   /// Constructor.
   /// @param[in]  dest  The set to store the values in.
   /// @since  0.2, 07.04.2016
   RangeDest( dest_type& dest):
      mDestination( dest)
   {
   } // RangeDest< T, std::set< T> >::RangeDest

   /// Stores/Sets a value in the set.
   /// @param[in]  v  The value to store in the set.
   /// @since  0.2, 07.04.2016
   void set( const T& v)
   {
      mDestination.insert( v);
   } // RangeDest< T, std::set< T> >::set

   /// Returns if the destination set is empty (no value stored).
   /// @return  \c true if the destination set is empty.
   /// @since  0.2, 07.04.2016
   bool empty() const
   {
      return mDestination.empty();
   } // RangeDest< T, C>::empty

private:
   /// The set to store the values in.
   dest_type&  mDestination;

}; // RangeDest< T, std::set< T> >


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RANGE_DEST_HPP


// =====  END OF range_dest.hpp  =====

