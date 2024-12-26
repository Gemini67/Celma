
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::Segment and template classes
/// - celma::container::SharedList<>
/// - celma::container::SharedMap<>
/// - celma::container::SharedMultiMap<>
/// - celma::container::SharedMultiSet<>
/// - celma::container::SharedSet<>
/// - celma::container::SharedUnorderedMap<>
/// - celma::container::SharedVector<>


#pragma once


#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/unordered_map.hpp>


namespace celma::container {


/*
   Example from www.boost.org:


   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;

   //Shared memory front-end that is able to construct objects
   //associated with a c-string. Erase previous shared memory with the name
   //to be used and create the memory segment at the specified address and initialize resources
   managed_shared_memory segment
      (create_only
      ,"MySharedMemory" //segment name
      ,65536);          //segment size in bytes

   //Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
   //so the allocator must allocate that pair.
   typedef int    KeyType;
   typedef float  MappedType;
   typedef std::pair<const int, float> ValueType;

   //Alias an STL compatible allocator of for the map.
   //This allocator will allow to place containers
   //in managed shared memory segments
   typedef allocator<ValueType, managed_shared_memory::segment_manager>
      ShmemAllocator;

   //Alias a map of ints that uses the previous STL-like allocator.
   //Note that the third parameter argument is the ordering function
   //of the map, just like with std::map, used to compare the keys.
   typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

   //Initialize the shared memory STL-compatible allocator
   ShmemAllocator alloc_inst( s.getSegmentManager());

   //Construct a shared memory map.
   //Note that the first parameter is the comparison function,
   //and the second one the allocator.
   //This the same signature as std::map's constructor taking an allocator
   MyMap *mymap =
      s.construct<MyMap>("MyMap")      //object name
                                 (std::less<int>() //first  ctor parameter
                                 ,alloc_inst);     //second ctor parameter
*/


// Class segment
// =============


/// Provides access to a shared memory segment.
/// First tries to access an existing segment, if that fails tried to open/
/// create a new segment. This way it can provide the information if the segment
/// did already exist or not.
///
/// @since  x.y.z, 31.03.2021
class Segment : public boost::interprocess::managed_shared_memory
{
public:
   /// Constructor.
   /// Tries to access an existing segment with the given name, if that fails
   /// tries to open/create a new segment.
   ///
   /// @param[in]  name
   ///    The symbolic name of the shared memory segment.
   /// @param[in]  size
   ///    The initial size of the shared memory segment. Only used if the shared
   ///    memory segment does not exist yet.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 31.03.2021
   Segment( const char* name, size_t size) noexcept( false);

   /// Returns if the shared memory segment was created by this object, or if it
   /// did exist already.
   ///
   /// @return  \c true if the shared memory segment was created by this object.
   /// @since  x.y.z, 31.03.2021
   bool wasCreated() const;

private:
   /// Set to \c true if the shared memory segment is created by this object.
   bool  mWasCreated = false;

}; // Segment


// inlined methods
// ===============


inline bool Segment::wasCreated() const
{
   return mWasCreated;
} // Segment::wasCreated


// Class SharedList
// ================


/// Template to easily create a list in shared memory.
/// Mostly it defines the required types and creates the list in the
/// constructor.<br>
/// After creation, use the operators to get the list object and use its methods.
///
/// @tparam  T  Type of the entries of the list.
/// @since  x.y.z, 06.04.2021
template< typename T> class SharedList
{
public:
   /// Type of the allocator to use for list entries.
   using allocator_type = boost::interprocess::allocator< T,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the list.
   using list_t = boost::interprocess::list< T, allocator_type>;

   /// Constructor.
   /// Accesses or creates the list with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the list in.
   /// @param[in]  list_name
   ///    Symbolic name of the list.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 06.04.2021
   SharedList( Segment& s, const char* list_name) noexcept( false)
   {
      mpSharedList = s.find_or_construct< list_t>( list_name)( s.get_segment_manager());
   } // SharedList< T>::SharedList

   /// Returns a const pointer to the list in shared memory.
   ///
   /// @return  Const pointer to the list.
   /// @since  x.y.z, 06.04.2021
   const list_t* operator ->() const
   {
      return mpSharedList;
   } // SharedList< T>::operator ->

   /// Returns a pointer to the list in shared memory.
   ///
   /// @return  Pointer to the list.
   /// @since  x.y.z, 06.04.2021
   list_t* operator ->()
   {
      return mpSharedList;
   } // SharedList< T>::operator ->

   /// Returns a const reference to the list in shared memory.
   ///
   /// @return  Const reference to the list.
   /// @since  x.y.z, 06.04.2021
   const list_t& operator *() const
   {
      return *mpSharedList;
   } // SharedList< T>::operator *

   /// Returns a reference to the list in shared memory.
   ///
   /// @return  Reference to the list.
   /// @since  x.y.z, 06.04.2021
   list_t& operator *()
   {
      return *mpSharedList;
   } // SharedList< T>::operator *

private:
   /// Pointer to the list in shared memory.
   list_t*  mpSharedList = nullptr;

}; // SharedList< T>


// Class SharedMap
// ===============


/// Template to easily create a map in shared memory.
/// Mostly it defines the required types and creates the map in the
/// constructor.<br>
/// After creation, use the operators to get the map object and use its methods.
///
/// @tparam  K  Type of the key of the map.
/// @tparam  V  Type of the values stored in the map.
/// @tparam  C  Comparator to use for comparing keys.
/// @since  x.y.z, 31.03.2021
template< typename K, typename V, typename C = std::less< K>> class SharedMap
{
public:
   /// Value type of the map: const key and values.
   using value_type = std::pair< const K, V>;
   /// Type of the allocator to use for map entries.
   using allocator_type = boost::interprocess::allocator< value_type,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the map.
   using map_t = boost::interprocess::map< K, V, C, allocator_type>;

   /// Constructor.
   /// Accesses or creates the map with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the map in.
   /// @param[in]  map_name
   ///    Symbolic name of the map.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 31.03.2021
   SharedMap( Segment& s, const char* map_name) noexcept( false)
   {
      mpSharedMap = s.find_or_construct< map_t>( map_name)( C(), s.get_segment_manager());
   } // SharedMap< K, V, C>::SharedMap

   /// Returns a const pointer to the map in shared memory.
   ///
   /// @return  Const pointer to the map.
   /// @since  x.y.z, 01.04.2021
   const map_t* operator ->() const
   {
      return mpSharedMap;
   } // SharedMap< K, V, C>::operator ->

   /// Returns a pointer to the map in shared memory.
   ///
   /// @return  Pointer to the map.
   /// @since  x.y.z, 01.04.2021
   map_t* operator ->()
   {
      return mpSharedMap;
   } // SharedMap< K, V, C>::operator ->

   /// Returns a const reference to the map in shared memory.
   ///
   /// @return  Const reference to the map.
   /// @since  x.y.z, 01.04.2021
   const map_t& operator *() const
   {
      return *mpSharedMap;
   } // SharedMap< K, V, C>::operator *

   /// Returns a reference to the map in shared memory.
   ///
   /// @return  Reference to the map.
   /// @since  x.y.z, 01.04.2021
   map_t& operator *()
   {
      return *mpSharedMap;
   } // SharedMap< K, V, C>::operator *

private:
   /// Pointer to the map in shared memory.
   map_t*  mpSharedMap = nullptr;

}; // SharedMap< K, V, C>


// Class SharedMultiMap
// ====================


/// Template to easily create a multi-map in shared memory.
/// Mostly it defines the required types and creates the multi-map in the
/// constructor.<br>
/// After creation, use the operators to get the multi-map object and use its
/// methods.
///
/// @tparam  K  Type of the key of the multi-map.
/// @tparam  V  Type of the values stored in the multi-map.
/// @tparam  C  Comparator to use for comparing keys.
/// @since  x.y.z, 07.04.2021
template< typename K, typename V, typename C = std::less< K>>
   class SharedMultiMap
{
public:
   /// Value type of the multi-map: const key and values.
   using value_type = std::pair< const K, V>;
   /// Type of the allocator to use for multi-map entries.
   using allocator_type = boost::interprocess::allocator< value_type,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the multi-map.
   using multimap_t = boost::interprocess::multimap< K, V, C, allocator_type>;

   /// Constructor.
   /// Accesses or creates the multi-map with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the multi-map in.
   /// @param[in]  map_name
   ///    Symbolic name of the multi-map.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 07.04.2021
   SharedMultiMap( Segment& s, const char* map_name) noexcept( false)
   {
      mpSharedMultiMap = s.find_or_construct< multimap_t>( map_name)( C(),
         s.get_segment_manager());
   } // SharedMultiMap< K, V, C>::SharedMultiMap

   /// Returns a const pointer to the multi-map in shared memory.
   ///
   /// @return  Const pointer to the multi-map.
   /// @since  x.y.z, 07.04.2021
   const multimap_t* operator ->() const
   {
      return mpSharedMultiMap;
   } // SharedMultiMap< K, V, C>::operator ->

   /// Returns a pointer to the multi-map in shared memory.
   ///
   /// @return  Pointer to the multi-map.
   /// @since  x.y.z, 07.04.2021
   multimap_t* operator ->()
   {
      return mpSharedMultiMap;
   } // SharedMultiMap< K, V, C>::operator ->

   /// Returns a const reference to the multi-map in shared memory.
   ///
   /// @return  Const reference to the multi-map.
   /// @since  x.y.z, 07.04.2021
   const multimap_t& operator *() const
   {
      return *mpSharedMultiMap;
   } // SharedMultiMap< K, V, C>::operator *

   /// Returns a reference to the multi-map in shared memory.
   ///
   /// @return  Reference to the multi-map.
   /// @since  x.y.z, 07.04.2021
   multimap_t& operator *()
   {
      return *mpSharedMultiMap;
   } // SharedMultiMap< K, V, C>::operator *

private:
   /// Pointer to the multi-map in shared memory.
   multimap_t*  mpSharedMultiMap = nullptr;

}; // SharedMultiMap< K, V, C>


// Class SharedMultiSet
// ====================


/// Template to easily create a multi-set in shared memory.
/// Mostly it defines the required types and creates the multi-set in the
/// constructor.<br>
/// After creation, use the operators to get the multi-set object and use its
/// methods.
///
/// @tparam  T  Type of the entries of the multi-set.
/// @tparam  C  Comparator to use for comparing entries.
/// @since  x.y.z, 07.04.2021
template< typename T, typename C = std::less< T>> class SharedMultiSet
{
public:
   /// Type of the allocator to use for multi-set entries.
   using allocator_type = boost::interprocess::allocator< T,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the multi-set.
   using multiset_t = boost::interprocess::multiset< T, C, allocator_type>;

   /// Constructor.
   /// Accesses or creates the multi-set with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the multi-set in.
   /// @param[in]  set_name
   ///    Symbolic name of the multi-set.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 07.04.2021
   SharedMultiSet( Segment& s, const char* set_name) noexcept( false)
   {
      mpSharedMultiSet = s.find_or_construct< multiset_t>( set_name)( C(), s.get_segment_manager());
   } // SharedMultiSet< T, C>::SharedMultiSet

   /// Returns a const pointer to the multi-set in shared memory.
   ///
   /// @return  Const pointer to the multi-set.
   /// @since  x.y.z, 07.04.2021
   const multiset_t* operator ->() const
   {
      return mpSharedMultiSet;
   } // SharedMultiSet< T, C>::operator ->

   /// Returns a pointer to the multi-set in shared memory.
   ///
   /// @return  Pointer to the multi-set.
   /// @since  x.y.z, 07.04.2021
   multiset_t* operator ->()
   {
      return mpSharedMultiSet;
   } // SharedMultiSet< T, C>::operator ->

   /// Returns a const reference to the multi-set in shared memory.
   ///
   /// @return  Const reference to the multi-set.
   /// @since  x.y.z, 07.04.2021
   const multiset_t& operator *() const
   {
      return *mpSharedMultiSet;
   } // SharedMultiSet< T, C>::operator *

   /// Returns a reference to the multi-set in shared memory.
   ///
   /// @return  Reference to the multi-set.
   /// @since  x.y.z, 07.04.2021
   multiset_t& operator *()
   {
      return *mpSharedMultiSet;
   } // SharedMultiSet< T, C>::operator *

private:
   /// Pointer to the multi-set in shared memory.
   multiset_t*  mpSharedMultiSet = nullptr;

}; // SharedMultiSet< T, C>


// Class SharedSet
// ===============


/// Template to easily create a set in shared memory.
/// Mostly it defines the required types and creates the set in the
/// constructor.<br>
/// After creation, use the operators to get the set object and use its methods.
///
/// @tparam  T  Type of the entries of the set.
/// @tparam  C  Comparator to use for comparing entries.
/// @since  x.y.z, 06.04.2021
template< typename T, typename C = std::less< T>> class SharedSet
{
public:
   /// Type of the allocator to use for set entries.
   using allocator_type = boost::interprocess::allocator< T,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the set.
   using set_t = boost::interprocess::set< T, C, allocator_type>;

   /// Constructor.
   /// Accesses or creates the set with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the set in.
   /// @param[in]  set_name
   ///    Symbolic name of the set.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 06.04.2021
   SharedSet( Segment& s, const char* set_name) noexcept( false)
   {
      mpSharedSet = s.find_or_construct< set_t>( set_name)( C(), s.get_segment_manager());
   } // SharedSet< T, C>::SharedSet

   /// Returns a const pointer to the set in shared memory.
   ///
   /// @return  Const pointer to the set.
   /// @since  x.y.z, 06.04.2021
   const set_t* operator ->() const
   {
      return mpSharedSet;
   } // SharedSet< T, C>::operator ->

   /// Returns a pointer to the set in shared memory.
   ///
   /// @return  Pointer to the set.
   /// @since  x.y.z, 06.04.2021
   set_t* operator ->()
   {
      return mpSharedSet;
   } // SharedSet< T, C>::operator ->

   /// Returns a const reference to the set in shared memory.
   ///
   /// @return  Const reference to the set.
   /// @since  x.y.z, 06.04.2021
   const set_t& operator *() const
   {
      return *mpSharedSet;
   } // SharedSet< T, C>::operator *

   /// Returns a reference to the set in shared memory.
   ///
   /// @return  Reference to the set.
   /// @since  x.y.z, 06.04.2021
   set_t& operator *()
   {
      return *mpSharedSet;
   } // SharedSet< T, C>::operator *

private:
   /// Pointer to the set in shared memory.
   set_t*  mpSharedSet = nullptr;

}; // SharedSet< T, C>


// Class SharedUnorderedMap
// ========================


/// Template to easily create an unordered map in shared memory.
/// Mostly it defines the required types and creates the unordered map in the
/// constructor.<br>
/// After creation, use the operators to get the unordered map object and use
/// its methods.
///
/// @tparam  K  Type of the key of the map.
/// @tparam  V  Type of the values stored in the map.
/// @tparam  C  Comparator to use for comparing keys.
/// @since  x.y.z, 01.04.2021
template< typename K, typename V, typename H = boost::hash< K>,
          typename E = std::equal_to< K>>
   class SharedUnorderedMap
{
public:
   /// Value type of the unordered map: const key and values.
   using value_type = std::pair< const K, V>;
   /// Type of the allocator to use for map entries.
   using allocator_type = boost::interprocess::allocator< value_type,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the unordered map.
   using map_t = boost::unordered_map< K, V, H, E, allocator_type>;

   /// Constructor.
   /// Accesses or creates the unordered map with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the map in.
   /// @param[in]  map_name
   ///    Symbolic name of the map.
   /// @param[in]  bucket_count
   ///    Initial value for the bucket count.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 01.04.2021
   SharedUnorderedMap( Segment& s, const char* map_name, int bucket_count)
   {
      mpSharedMap = s.find_or_construct< map_t>( map_name)( bucket_count,
        H(), E(), s.get_allocator< value_type>());
   } // SharedUnorderedMap< K, V, H, E>::SharedUnorderedMap

   /// Returns a const pointer to the unordered map in shared memory.
   ///
   /// @return  Const pointer to the unordered map.
   /// @since  x.y.z, 01.04.2021
   const map_t* operator ->() const
   {
      return mpSharedMap;
   } // SharedUnorderedMap< K, V, H, E>::operator ->

   /// Returns a pointer to the unordered map in shared memory.
   ///
   /// @return  Pointer to the unordered map.
   /// @since  x.y.z, 01.04.2021
   map_t* operator ->()
   {
      return mpSharedMap;
   } // SharedUnorderedMap< K, V, H, E>::operator ->

   /// Returns a const reference to the unordered map in shared memory.
   ///
   /// @return  Const reference to the unordered map.
   /// @since  x.y.z, 01.04.2021
   const map_t& operator *() const
   {
      return *mpSharedMap;
   } // SharedUnorderedMap< K, V, H, E>::operator *

   /// Returns a reference to the unordered map in shared memory.
   ///
   /// @return  Reference to the unordered map.
   /// @since  x.y.z, 01.04.2021
   map_t& operator *()
   {
      return *mpSharedMap;
   } // SharedUnorderedMap< K, V, H, E>::operator *

private:
   /// Pointer to the unordered map in shared memory.
   map_t*  mpSharedMap = nullptr;

}; // SharedUnorderedMap< K, V, H, E>


// Class SharedVector
// ==================


/// Template to easily create a vector in shared memory.
/// Mostly it defines the required types and creates the vector in the
/// constructor.<br>
/// After creation, use the operators to get the vector object and use its
/// methods.
///
/// @tparam  T  Type of the values stored in the vector.
/// @since  x.y.z, 06.04.2021
template< typename T> class SharedVector
{
public:
   /// Type of the allocator to use for vector entries.
   using allocator_type = boost::interprocess::allocator< T,
                             boost::interprocess::managed_shared_memory::segment_manager>;
   /// The actual type of the map.
   using vector_t = boost::interprocess::vector< T, allocator_type>;

   /// Constructor.
   /// Accesses or creates the vector with the given name.
   ///
   /// @param[in]  s
   ///    Shared memory segment to create the vector in.
   /// @param[in]  vec_name
   ///    Symbolic name of the vector.
   /// @throws  boost::interprocess::bad_alloc if memory allocation failed.
   /// @since  x.y.z, 06.04.2021
   SharedVector( Segment& s, const char* vec_name) noexcept( false)
   {
      mpSharedVector = s.find_or_construct< vector_t>( vec_name)( s.get_segment_manager());
   } // SharedVector< T>::SharedVector

   /// Returns a const pointer to the vector in shared memory.
   ///
   /// @return  Const pointer to the vector.
   /// @since  x.y.z, 01.04.2021
   const vector_t* operator ->() const
   {
      return mpSharedVector;
   } // SharedVector< T>::operator ->

   /// Returns a pointer to the vector in shared memory.
   ///
   /// @return  Pointer to the vector.
   /// @since  x.y.z, 01.04.2021
   vector_t* operator ->()
   {
      return mpSharedVector;
   } // SharedVector< T>::operator ->

   /// Returns a const reference to the vector in shared memory.
   ///
   /// @return  Const reference to the vector.
   /// @since  x.y.z, 01.04.2021
   const vector_t& operator *() const
   {
      return *mpSharedVector;
   } // SharedVector< T>::operator *

   /// Returns a reference to the vector in shared memory.
   ///
   /// @return  Reference to the vector.
   /// @since  x.y.z, 01.04.2021
   vector_t& operator *()
   {
      return *mpSharedVector;
   } // SharedVector< T>::operator *

private:
   /// Pointer to the vector in shared memory.
   vector_t*  mpSharedVector = nullptr;

}; // SharedVector< T>


} // namespace celma::container


// =====  END OF shared_container.hpp  =====

