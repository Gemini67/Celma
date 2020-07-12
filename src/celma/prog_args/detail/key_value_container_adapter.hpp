
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes
/// - celma::prog_args::detail::KeyValueContainerAdapter<>
/// - celma::prog_args::detail::KeyValueContainerAdapter< std::map>
/// - celma::prog_args::detail::KeyValueContainerAdapter< std::multimap>
/// - celma::prog_args::detail::KeyValueContainerAdapter< std::unordered_map>
/// - celma::prog_args::detail::KeyValueContainerAdapter< std::unordered_multimap>


#pragma once


#include <algorithm>
#include <map>
#include <unordered_map>
#include "celma/common/contains.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/container_adapter.hpp"


namespace celma::prog_args::detail {


/// Simple container adapter for types that are not supported.
///
/// @tparam  T
///    Type for this no container adapter is provided, e.g. std::string.
/// @since  x.y.z, 09.02.2020
template< typename T> class KeyValueContainerAdapter final
{
public:
   /// Flag that can be checked if a container adapter is available, set to
   /// \c false here for all non-supported (container) types.
   static constexpr bool  HasAdapter = false;

   // should never have to create an object of this type
   KeyValueContainerAdapter() = delete;
   KeyValueContainerAdapter( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter( KeyValueContainerAdapter&&) = delete;
   KeyValueContainerAdapter& operator =( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter& operator =( KeyValueContainerAdapter&&) = delete;

}; // KeyValueContainerAdapter< T>


/// Container adapter for std::map.
///
/// @tparam  K
///    The type of the keys used by the map.
/// @tparam  V
///    The type of the values stored in the map.
/// @since  x.y.z, 07.01.2020
template< typename K, typename V>
   class KeyValueContainerAdapter< std::map< K, V>> final:
      AdapterBase< std::map< K, V>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = true;

   /// The type of the container handled by this adapter.
   using container_type_t = std::map< K, V>;
   /// The type of the keys of the container.
   using key_type_t   = K;
   /// The type of the values stored in the container.
   using value_type_t = V;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 07.01.2020
   explicit KeyValueContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // KeyValueContainerAdapter< std::map< K, V>>::KeyValueContainerAdapter

   // default copy- or move-construction is okay
   KeyValueContainerAdapter( const KeyValueContainerAdapter&) = default;
   KeyValueContainerAdapter( KeyValueContainerAdapter&&) = default;

   // default destructor is fine
   ~KeyValueContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  key    The key of the value to store.
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 07.01.2020
   void addValue( const K& key, const V& value)
   {
      mDestCont.insert( { key, value});
   } // KeyValueContainerAdapter< std::map< K, V>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 07.01.2020
   void clear()
   {
      mDestCont.clear();
   } // KeyValueContainerAdapter< std::map< K, V>>::clear

   /// Returns if the container contains the given key.
   ///
   /// @param[in]  key  The key to search in the container.
   /// @return  \c true if the key was found.
   /// @since  x.y.z, 07.01.2020
   bool contains( const K& key) const
   {
      return common::contains( mDestCont, key);
   } // KeyValueContainerAdapter< std::map< K, V>>::contains

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  x.y.z, 16.02.2020
   bool hasIntersection( const KeyValueContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // KeyValueContainerAdapter< std::map< K, V>>::hasIntersection

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 07.01.2020
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for maps");
   } // KeyValueContainerAdapter< std::map< K, V>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 07.01.2020
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // KeyValueContainerAdapter< std::map< K, V>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignments are not allowed
   KeyValueContainerAdapter&
      operator =( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter& operator =( KeyValueContainerAdapter&&) = delete;

}; // KeyValueContainerAdapter< std::map< K, V>>


/// Container adapter for std::multimap.
///
/// @tparam  K
///    The type of the keys used by the multi-map.
/// @tparam  V
///    The type of the values stored in the multi-map.
/// @since  x.y.z, 15.03.2020
template< typename K, typename V>
   class KeyValueContainerAdapter< std::multimap< K, V>> final:
      AdapterBase< std::multimap< K, V>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = true;

   /// The type of the container handled by this adapter.
   using container_type_t = std::multimap< K, V>;
   /// The type of the keys of the container.
   using key_type_t   = K;
   /// The type of the values stored in the container.
   using value_type_t = V;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 15.03.2020
   explicit KeyValueContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // KeyValueContainerAdapter< std::multimap< K, V>>::KeyValueContainerAdapter

   // default copy- or move-construction is okay
   KeyValueContainerAdapter( const KeyValueContainerAdapter&) = default;
   KeyValueContainerAdapter( KeyValueContainerAdapter&&) = default;

   // default destructor is fine
   ~KeyValueContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  key    The key of the value to store.
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 15.03.2020
   void addValue( const K& key, const V& value)
   {
      mDestCont.insert( { key, value});
   } // KeyValueContainerAdapter< std::multimap< K, V>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 15.03.2020
   void clear()
   {
      mDestCont.clear();
   } // KeyValueContainerAdapter< std::multimap< K, V>>::clear

   /// Returns if the container contains the given key.
   ///
   /// @param[in]  key  The key to search in the container.
   /// @return  \c true if the key was found.
   /// @since  x.y.z, 15.03.2020
   bool contains( const K& key) const
   {
      return common::contains( mDestCont, key);
   } // KeyValueContainerAdapter< std::multimap< K, V>>::contains

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  x.y.z, 15.03.2020
   bool hasIntersection( const KeyValueContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // KeyValueContainerAdapter< std::multimap< K, V>>::hasIntersection

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 15.03.2020
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for multi-maps");
   } // KeyValueContainerAdapter< std::multimap< K, V>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 15.03.2020
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // KeyValueContainerAdapter< std::multimap< K, V>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignments are not allowed
   KeyValueContainerAdapter&
      operator =( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter& operator =( KeyValueContainerAdapter&&) = delete;

}; // KeyValueContainerAdapter< std::multimap< K, V>>


/// Container adapter for std::unordered_map.
///
/// @tparam  K
///    The type of the keys used by the unordered map.
/// @tparam  V
///    The type of the values stored in the unordered map.
/// @since  x.y.z, 15.03.2020
template< typename K, typename V>
   class KeyValueContainerAdapter< std::unordered_map< K, V>> final:
      AdapterBase< std::unordered_map< K, V>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::unordered_map< K, V>;
   /// The type of the keys of the container.
   using key_type_t   = K;
   /// The type of the values stored in the container.
   using value_type_t = V;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 15.03.2020
   explicit KeyValueContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::KeyValueContainerAdapter

   // default copy- or move-construction is okay
   KeyValueContainerAdapter( const KeyValueContainerAdapter&) = default;
   KeyValueContainerAdapter( KeyValueContainerAdapter&&) = default;

   // default destructor is fine
   ~KeyValueContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  key    The key of the value to store.
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 15.03.2020
   void addValue( const K& key, const V& value)
   {
      mDestCont.insert( { key, value});
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 15.03.2020
   void clear()
   {
      mDestCont.clear();
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::clear

   /// Returns if the container contains the given key.
   ///
   /// @param[in]  key  The key to search in the container.
   /// @return  \c true if the key was found.
   /// @since  x.y.z, 15.03.2020
   bool contains( const K& key) const
   {
      return common::contains( mDestCont, key);
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::contains

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  x.y.z, 15.03.2020
   bool hasIntersection( const KeyValueContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::hasIntersection

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 15.03.2020
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not possible for unordered maps");
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 15.03.2020
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // KeyValueContainerAdapter< std::unordered_map< K, V>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignments are not allowed
   KeyValueContainerAdapter&
      operator =( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter& operator =( KeyValueContainerAdapter&&) = delete;

}; // KeyValueContainerAdapter< std::unordered_map< K, V>>


/// Container adapter for std::unordered_multimap.
///
/// @tparam  K
///    The type of the keys used by the unordered multi-map.
/// @tparam  V
///    The type of the values stored in the unordered multi-map.
/// @since  x.y.z, 15.03.2020
template< typename K, typename V>
   class KeyValueContainerAdapter< std::unordered_multimap< K, V>> final:
      AdapterBase< std::unordered_multimap< K, V>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::unordered_multimap< K, V>;
   /// The type of the keys of the container.
   using key_type_t   = K;
   /// The type of the values stored in the container.
   using value_type_t = V;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 15.03.2020
   explicit KeyValueContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::KeyValueContainerAdapter

   // default copy- or move-construction is okay
   KeyValueContainerAdapter( const KeyValueContainerAdapter&) = default;
   KeyValueContainerAdapter( KeyValueContainerAdapter&&) = default;

   // default destructor is fine
   ~KeyValueContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  key    The key of the value to store.
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 15.03.2020
   void addValue( const K& key, const V& value)
   {
      mDestCont.insert( { key, value});
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 15.03.2020
   void clear()
   {
      mDestCont.clear();
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::clear

   /// Returns if the container contains the given key.
   ///
   /// @param[in]  key  The key to search in the container.
   /// @return  \c true if the key was found.
   /// @since  x.y.z, 15.03.2020
   bool contains( const K& key) const
   {
      return common::contains( mDestCont, key);
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::contains

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  x.y.z, 15.03.2020
   bool hasIntersection( const KeyValueContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::hasIntersection

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 15.03.2020
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not possible for unordered maps");
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 15.03.2020
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // KeyValueContainerAdapter< std::unordered_multimap< K, V>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignments are not allowed
   KeyValueContainerAdapter&
      operator =( const KeyValueContainerAdapter&) = delete;
   KeyValueContainerAdapter& operator =( KeyValueContainerAdapter&&) = delete;

}; // KeyValueContainerAdapter< std::unordered_multimap< K, V>>


} // namespace celma::prog_args::detail


// =====  END OF key_value_container_adapter.hpp  =====

