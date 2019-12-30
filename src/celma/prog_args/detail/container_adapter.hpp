
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes
/// - celma::prog_args::detail::AdapterBase<>
/// - celma::prog_args::detail::ContainerAdapter<>


#ifndef CELMA_PROG_ARGS_DETAIL_CONTAINER_ADAPTER_HPP
#define CELMA_PROG_ARGS_DETAIL_CONTAINER_ADAPTER_HPP


#include <algorithm>
#include <deque>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>
#include "celma/common/contains.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {


// @todo  queue, forward_list


/// Base class for container adapters.
/// Provides some common methods and stores the reference to the destination.
///
/// @tparam  T  The type of the destination, container of something.
/// @since  x.y.z, 22.11.2019
template< typename T> class AdapterBase
{
public:
   /// Constructor, stores the reference to the destination.
   ///
   /// @param[in]  dest  The destination to use.
   /// @since  x.y.z, 22.11.2019
   explicit AdapterBase( T& dest):
      mDestCont( dest)
   {
   } // AdapterBase< T>::AdapterBase

   /// Returns if the container is empty.
   ///
   /// @return  \c true if the container is empty.
   /// @since  x.y.z, 22.11.2019
   bool empty() const
   {
      return mDestCont.empty();
   } // AdapterBase< T>::empty

   /// Returns the current size of the container, i.e. how many elements it
   /// contains.
   ///
   /// @return  Number of values currently stored in the container.
   /// @since  x.y.z, 22.11.2019
   size_t size() const
   {
      return mDestCont.size();
   } // AdapterBase< T>::size

protected:
   /// The reference of the destination.
   T&  mDestCont;

}; // AdapterBase< T>


/// Simple container adapter for types that are not supported.
///
/// @tparam  T
///    Type for this no container adapter is provided, e.g. std::string.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter final
{
public:
   /// Flag that can be checked if a container adapter is available, set to
   /// \c false here for all non-supported (container) types.
   static constexpr bool  HasAdapter = false;

}; // ContainerAdapter< T>


/// Container adapter for std::deque.
///
/// @tparam  T  The type of the values stored in the queue.
/// @since  x.y.z, 04.12.2019
template< typename T> class ContainerAdapter< std::deque< T>> final:
   AdapterBase< std::deque< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::deque< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 04.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::deque< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 04.12.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::deque< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 04.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::deque< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 04.12.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::deque< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 04.12.2019
   void sort()
   {
      std::sort( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::deque< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  x.y.z, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::deque< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::deque< T>>


/// Container adapter for std::list.
///
/// @tparam  T  The type of the values stored in the list.
/// @since  x.y.z, 11.12.2019
template< typename T> class ContainerAdapter< std::list< T>> final:
   AdapterBase< std::list< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::list< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 11.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::list< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 11.12.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::list< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 11.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::list< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 11.12.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::list< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 11.12.2019
   void sort()
   {
      mDestCont.sort();
   } // ContainerAdapter< std::list< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 11.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::list< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::list< T>>


/// Container adapter for std::multiset.
///
/// @tparam  T  The type of the values stored in the multi-set.
/// @since  x.y.z, 13.12.2019
template< typename T> class ContainerAdapter< std::multiset< T>> final:
   AdapterBase< std::multiset< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = true;

   /// The type of the container handled by this adapter.
   using container_type_t = std::multiset< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 13.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::multiset< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 13.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::multiset< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 13.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::multiset< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 13.12.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::multiset< T>>::contains

   /// Here: Throws, since the values in the container are already sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container are already
   ///    sorted.
   /// @since  x.y.z, 13.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for multi-sets");
   } // ContainerAdapter< std::multiset< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 13.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::multiset< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::multiset< T>>


/// Container adapter for std::priority_queue.
///
/// @tparam  T  The type of the values stored in the priority_queue.
/// @since  x.y.z, 20.12.2019
template< typename T> class ContainerAdapter< std::priority_queue< T>> final:
   AdapterBase< std::priority_queue< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = false;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = true;

   /// The type of the container handled by this adapter.
   using container_type_t = std::priority_queue< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 20.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::priority_queue< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 20.12.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::priority_queue< T>>::addValue

   /// Always throws because clearing is not supported for priority queues.
   ///
   /// @throw  std::logic_error since clearing a priority queue is not supported.
   /// @since  x.y.z, 20.12.2019
   void clear() noexcept( false)
   {
      throw std::logic_error( "clear() is not supported for priority-queues");
   } // ContainerAdapter< std::priority_queue< T>>::clear

   /// Always throws because iterating over a priority queue is not supported.
   ///
   /// @param[in]  value  Ignored here.
   /// @return  Never returns because it always throws.
   /// @throw
   ///    std::logic_error since iterating over a priority queue is
   ///    not supported.
   /// @since  x.y.z, 20.12.2019
   bool contains( const T& /* value */) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for priority-queues");
   } // ContainerAdapter< std::priority_queue< T>>::contains

   /// Always throws because sorting the values in a priority queue is not
   /// supported.
   ///
   /// @throw
   ///    std::logic_error since sorting a priority queue is not supported.
   /// @since  x.y.z, 20.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for priority-queues");
   } // ContainerAdapter< std::priority_queue< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 2012.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::priority_queue< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::priority_queue< T>>


/// Container adapter for std::queue.
///
/// @tparam  T  The type of the values stored in the queue.
/// @since  x.y.z, 29.12.2019
template< typename T> class ContainerAdapter< std::queue< T>> final:
   AdapterBase< std::queue< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = false;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::queue< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 29.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::queue< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 29.12.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::queue< T>>::addValue

   /// Always throws because clearing is not supported for queues.
   ///
   /// @throw  std::logic_error since clearing is not supported for queues.
   /// @since  x.y.z, 29.12.2019
   void clear() noexcept( false)
   {
      throw std::logic_error( "clear() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::clear

   /// Always throws because iterating over a queue is not possible.
   ///
   /// @param[in]  value  Ignored here.
   /// @return  Never returns, always throws.
   /// @throw  std::logic_error since iterating over a queue is not possible.
   /// @since  x.y.z, 29.12.2019
   bool contains( const T& /* value */) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::contains

   /// Always throws because sorting is not supported for queues.
   ///
   /// @throw  std::logic_error since sorting a queue is not possible.
   /// @since  x.y.z, 29.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  x.y.z, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::queue< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::queue< T>>


/// Container adapter for std::set.
///
/// @tparam  T  The type of the values stored in the set.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter< std::set< T>> final:
   AdapterBase< std::set< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = true;

   /// The type of the container handled by this adapter.
   using container_type_t = std::set< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::set< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::set< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 22.11.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::set< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 25.11.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::set< T>>::contains

   /// Here: Throws, since the values in the container are already sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container are already
   ///    sorted.
   /// @since  x.y.z, 22.11.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for sets");
   } // ContainerAdapter< std::set< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::set< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::set< T>>


/// Container adapter for std::stack.
///
/// @tparam  T  The type of the values stored in the stack.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter< std::stack< T>> final:
   AdapterBase< std::stack< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = false;
   /// Flag for (compile-time) check if positional formatters should be allowed,
   /// i.e. the values stored in the container keep their order.
   static constexpr bool  AllowsPositionFormat = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::stack< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< std::stack< T>>( dest)
   {
   } // ContainerAdapter< std::stack< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::stack< T>>::addValue

   /// Here: Throws since stacks do not support clearing.
   /// Check #IsClearable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since stacks do not provide a method for clearing.
   /// @since  x.y.z, 22.11.2019
   void clear() noexcept( false)
   {
      throw std::logic_error( "clear() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::clear

   /// Here: Throws since stacks are not searchable.
   /// Check #HasIterators before calling this function.
   /// 
   /// @param[in]  Ignored.
   /// @throw
   ///    std::logic_error since stacks are not searchable, i.e. they do not
   ///    provide iterators.
   /// @since  x.y.z, 25.11.2019
   bool contains( const T&) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::contains

   /// Here: Throws since stacks cannot be sorted.
   /// Check #IsSortable before calling this function.
   ///
   /// @throw  std::logic_error since stacks cannot be sorted.
   /// @since  x.y.z, 22.11.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::sort

   /// Returns a string with the values from the container.
   /// This is possible for stacks only because the values from the container
   /// are copied into a new stack for printing.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::stack< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::stack< T>>


/// Container adapter for std::unordered_multiset.
///
/// @tparam  T  The type of the values stored in the unordered multi-set.
/// @since  x.y.z, 17.12.2019
template< typename T> class ContainerAdapter< std::unordered_multiset< T>> final:
   AdapterBase< std::unordered_multiset< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::unordered_multiset< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 17.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::unordered_multiset< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 17.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::unordered_multiset< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 17.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::unordered_multiset< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 17.12.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::unordered_multiset< T>>::contains

   /// Here: Throws, since the values in the container cannot be sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container cannot be sorted.
   /// @since  x.y.z, 17.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for unordered multi-sets");
   } // ContainerAdapter< std::unordered_multiset< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  x.y.z, 17.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::unordered_multiset< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::unordered_multiset< T>>


/// Container adapter for std::unordered_set.
///
/// @tparam  T  The type of the values stored in the unordered set.
/// @since  x.y.z, 04.12.2019
template< typename T> class ContainerAdapter< std::unordered_set< T>> final:
   AdapterBase< std::unordered_set< T>>
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
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::unordered_set< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 04.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::unordered_set< T>>::ContainerAdapter

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 04.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::unordered_set< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 04.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::unordered_set< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 04.12.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::unordered_set< T>>::contains

   /// Here: Throws, since the values in the container cannot be sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container cannot be sorted.
   /// @since  x.y.z, 04.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for unordered sets");
   } // ContainerAdapter< std::unordered_set< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  x.y.z, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::unordered_set< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::unordered_set< T>>


/// Container adapter for std::vector.
///
/// @tparam  T  The type of the values stored in the vector.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter< std::vector< T>> final:
   AdapterBase< std::vector< T>>
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
   static constexpr bool  AllowsPositionFormat = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports clearing its contents.
   static constexpr bool  IsClearable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, is sortable.
   static constexpr bool  IsSortable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::vector< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  x.y.z, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::vector< T>>::ContainerAdapter

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  x.y.z, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::vector< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  x.y.z, 22.11.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::vector< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  x.y.z, 25.11.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::vector< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  x.y.z, 22.11.2019
   void sort()
   {
      std::sort( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::vector< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  x.y.z, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::vector< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

}; // ContainerAdapter< std::vector< T>>


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONTAINER_ADAPTER_HPP


// =====  END OF container_adapter.hpp  =====

