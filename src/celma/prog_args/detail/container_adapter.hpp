
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
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
#include <forward_list>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>
#include "celma/common/contains.hpp"
#include "celma/common/has_intersection.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Base class for container adapters.
/// Provides some common methods and stores the reference to the destination.
///
/// @tparam  T  The type of the destination, container of something.
/// @since  1.34.0, 22.11.2019
template< typename T> class AdapterBase
{
public:
   /// Constructor, stores the reference to the destination.
   ///
   /// @param[in]  dest  The destination to use.
   /// @since  1.34.0, 22.11.2019
   explicit AdapterBase( T& dest):
      mDestCont( dest)
   {
   } // AdapterBase< T>::AdapterBase

   // default copy-/move-construction is fine
   AdapterBase( const AdapterBase&) = default;
   AdapterBase( AdapterBase&&) = default;

   // empty, virtual default destructor
   virtual ~AdapterBase() = default;

   /// Returns if the container is empty.
   ///
   /// @return  \c true if the container is empty.
   /// @since  1.34.0, 22.11.2019
   bool empty() const
   {
      return mDestCont.empty();
   } // AdapterBase< T>::empty

   /// Returns the current size of the container, i.e. how many elements it
   /// contains.
   ///
   /// @return  Number of values currently stored in the container.
   /// @since  1.34.0, 22.11.2019
   size_t size() const
   {
      return mDestCont.size();
   } // AdapterBase< T>::size

   // assignment is not allowed
   AdapterBase& operator =( const AdapterBase&) = delete;
   AdapterBase& operator =( AdapterBase&&) = delete;

protected:
   /// The reference of the destination.
   T&  mDestCont;

}; // AdapterBase< T>


/// Simple container adapter for types that are not supported.
///
/// @tparam  T
///    Type for this no container adapter is provided, e.g. std::string.
/// @since  1.34.0, 22.11.2019
template< typename T> class ContainerAdapter final
{
public:
   /// Flag that can be checked if a container adapter is available, set to
   /// \c false here for all non-supported (container) types.
   static constexpr bool  HasAdapter = false;

   // should never have to create an object of this type
   ContainerAdapter() = delete;
   ContainerAdapter( const ContainerAdapter&) = delete;
   ContainerAdapter( ContainerAdapter&&) = delete;
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< T>


/// Container adapter for std::deque.
///
/// @tparam  T  The type of the values stored in the queue.
/// @since  1.34.0, 04.12.2019
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
   /// @since  1.34.0, 04.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::deque< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 04.12.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::deque< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 04.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::deque< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 04.12.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::deque< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  1.34.0, 04.12.2019
   void sort()
   {
      std::sort( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::deque< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::deque< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  1.34.0, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::deque< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::deque< T>>


/// Container adapter for std::forward_list.
///
/// @tparam  T  The type of the values stored in the forward-list.
/// @since  1.34.0, 30.12.2019
template< typename T> class ContainerAdapter< std::forward_list< T>> final:
   AdapterBase< std::forward_list< T>>
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
   static constexpr bool  IsSortable = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, sorts the values automatically.
   static constexpr bool  IsSorted = false;

   /// The type of the container handled by this adapter.
   using container_type_t = std::forward_list< T>;
   /// The type of the values stored in the container.
   using value_type_t = T;
   /// Of course we use the variable from the base class.
   using AdapterBase< container_type_t>::mDestCont;

   /// Constructor.
   ///
   /// @param[in]  dest  The destination container.
   /// @since  1.34.0, 30.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::forward_list< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 30.12.2019
   void addValue( const T& value)
   {
      mDestCont.push_front( value);
   } // ContainerAdapter< std::forward_list< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 30.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::forward_list< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 30.12.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::forward_list< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  1.34.0, 30.12.2019
   void sort()
   {
      mDestCont.sort();
   } // ContainerAdapter< std::forward_list< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::forward_list< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  1.34.0, 30.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::deque< T>>::toString

   /// Returns the current size of the container, i.e. how many elements it
   /// contains.
   ///
   /// @return  Number of values currently stored in the container.
   /// @since  1.34.0, 22.11.2019
   size_t size() const
   {
      return std::distance( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::forward_list< T>>::size

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::forward_list< T>>


/// Container adapter for std::list.
///
/// @tparam  T  The type of the values stored in the list.
/// @since  1.34.0, 11.12.2019
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
   /// @since  1.34.0, 11.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::list< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 11.12.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::list< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 11.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::list< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 11.12.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::list< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  1.34.0, 11.12.2019
   void sort()
   {
      mDestCont.sort();
   } // ContainerAdapter< std::list< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::list< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 11.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::list< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::list< T>>


/// Container adapter for std::multiset.
///
/// @tparam  T  The type of the values stored in the multi-set.
/// @since  1.34.0, 13.12.2019
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
   /// @since  1.34.0, 13.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::multiset< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 13.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::multiset< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 13.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::multiset< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 13.12.2019
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
   /// @since  1.34.0, 13.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for multi-sets");
   } // ContainerAdapter< std::multiset< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::multiset< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 13.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::multiset< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::multiset< T>>


/// Container adapter for std::priority_queue.
///
/// @tparam  T  The type of the values stored in the priority_queue.
/// @since  1.34.0, 20.12.2019
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
   /// @since  1.34.0, 20.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::priority_queue< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 20.12.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::priority_queue< T>>::addValue

   /// Clears the priority queue by popping off all entries.
   ///
   /// @since  1.34.0, 20.12.2019
   void clear()
   {
      while (!mDestCont.empty())
      {
         mDestCont.pop();
      } // end while
   } // ContainerAdapter< std::priority_queue< T>>::clear

   /// Always throws because iterating over a priority queue is not supported.
   ///
   /// @param[in]  value  Ignored here.
   /// @return  Never returns because it always throws.
   /// @throw
   ///    std::logic_error since iterating over a priority queue is
   ///    not supported.
   /// @since  1.34.0, 20.12.2019
   bool contains( const T& /* value */) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for priority-queues");
   } // ContainerAdapter< std::priority_queue< T>>::contains

   /// Always throws because sorting the values in a priority queue is not
   /// supported.
   ///
   /// @throw
   ///    std::logic_error since sorting a priority queue is not supported.
   /// @since  1.34.0, 20.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for priority-queues");
   } // ContainerAdapter< std::priority_queue< T>>::sort

   /// Always throws.
   ///
   /// @param[in]  Ignored.
   /// @return  Never, always throws.
   /// @throw  std::logic_error since this container does not support iterators.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& /* other */) const
      noexcept( false)
   {
      throw std::logic_error( "hasIntersection() is not supported for priority "
         "queues");
   } // ContainerAdapter< std::priority_queue< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 2012.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::priority_queue< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::priority_queue< T>>


/// Container adapter for std::queue.
///
/// @tparam  T  The type of the values stored in the queue.
/// @since  1.34.0, 29.12.2019
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
   /// @since  1.34.0, 29.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::queue< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 29.12.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::queue< T>>::addValue

   /// Clears the queue by popping off all entries.
   ///
   /// @since  1.34.0, 29.12.2019
   void clear()
   {
      while (!mDestCont.empty())
      {
         mDestCont.pop();
      } // end while
   } // ContainerAdapter< std::queue< T>>::clear

   /// Always throws because iterating over a queue is not possible.
   ///
   /// @param[in]  value  Ignored here.
   /// @return  Never returns, always throws.
   /// @throw  std::logic_error since iterating over a queue is not possible.
   /// @since  1.34.0, 29.12.2019
   bool contains( const T& /* value */) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::contains

   /// Always throws because sorting is not supported for queues.
   ///
   /// @throw  std::logic_error since sorting a queue is not possible.
   /// @since  1.34.0, 29.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::sort

   /// Always throws.
   ///
   /// @param[in]  Ignored.
   /// @return  Never, always throws.
   /// @throw  std::logic_error since this container does not support iterators.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& /* other */) const
      noexcept( false)
   {
      throw std::logic_error( "hasIntersection() is not supported for queues");
   } // ContainerAdapter< std::queue< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  1.34.0, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::queue< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::queue< T>>


/// Container adapter for std::set.
///
/// @tparam  T  The type of the values stored in the set.
/// @since  1.34.0, 22.11.2019
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
   /// @since  1.34.0, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::set< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::set< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 22.11.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::set< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 25.11.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::set< T>>::contains

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::set< T>>::hasIntersection

   /// Here: Throws, since the values in the container are already sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container are already
   ///    sorted.
   /// @since  1.34.0, 22.11.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not necessary for sets");
   } // ContainerAdapter< std::set< T>>::sort

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::set< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::set< T>>


/// Container adapter for std::stack.
///
/// @tparam  T  The type of the values stored in the stack.
/// @since  1.34.0, 22.11.2019
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
   /// @since  1.34.0, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< std::stack< T>>( dest)
   {
   } // ContainerAdapter< std::stack< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.push( value);
   } // ContainerAdapter< std::stack< T>>::addValue

   /// Clears the stack by popping off all entries.
   ///
   /// @since  1.34.0, 22.11.2019
   void clear()
   {
      while (!mDestCont.empty())
      {
         mDestCont.pop();
      } // end while
   } // ContainerAdapter< std::stack< T>>::clear

   /// Here: Throws since stacks are not searchable.
   /// Check #HasIterators before calling this function.
   /// 
   /// @param[in]  Ignored.
   /// @throw
   ///    std::logic_error since stacks are not searchable, i.e. they do not
   ///    provide iterators.
   /// @since  1.34.0, 25.11.2019
   bool contains( const T&) const noexcept( false)
   {
      throw std::logic_error( "contains() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::contains

   /// Here: Throws since stacks cannot be sorted.
   /// Check #IsSortable before calling this function.
   ///
   /// @throw  std::logic_error since stacks cannot be sorted.
   /// @since  1.34.0, 22.11.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::sort

   /// Always throws.
   ///
   /// @param[in]  Ignored.
   /// @return  Never, always throws.
   /// @throw  std::logic_error since this container does not support iterators.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& /* other */) const
      noexcept( false)
   {
      throw std::logic_error( "hasIntersection() is not supported for stacks");
   } // ContainerAdapter< std::stack< T>>::hasIntersection

   /// Returns a string with the values from the container.
   /// This is possible for stacks only because the values from the container
   /// are copied into a new stack for printing.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont);
   } // ContainerAdapter< std::stack< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::stack< T>>


/// Container adapter for std::unordered_multiset.
///
/// @tparam  T  The type of the values stored in the unordered multi-set.
/// @since  1.34.0, 17.12.2019
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
   /// @since  1.34.0, 17.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::unordered_multiset< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 17.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::unordered_multiset< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 17.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::unordered_multiset< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 17.12.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::unordered_multiset< T>>::contains

   /// Here: Throws, since the values in the container cannot be sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container cannot be sorted.
   /// @since  1.34.0, 17.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for unordered multi-sets");
   } // ContainerAdapter< std::unordered_multiset< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::unordered_multiset< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  1.34.0, 17.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::unordered_multiset< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::unordered_multiset< T>>


/// Container adapter for std::unordered_set.
///
/// @tparam  T  The type of the values stored in the unordered set.
/// @since  1.34.0, 04.12.2019
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
   /// @since  1.34.0, 04.12.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::unordered_set< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 04.12.2019
   void addValue( const T& value)
   {
      mDestCont.insert( value);
   } // ContainerAdapter< std::unordered_set< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 04.12.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::unordered_set< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 04.12.2019
   bool contains( const T& value) const
   {
      return mDestCont.find( value) != mDestCont.end();
   } // ContainerAdapter< std::unordered_set< T>>::contains

   /// Here: Throws, since the values in the container cannot be sorted.
   /// Check #IsSorted and/or #IsSortable before calling this function.
   ///
   /// @throw
   ///    std::logic_error since the values in this container cannot be sorted.
   /// @since  1.34.0, 04.12.2019
   void sort() noexcept( false)
   {
      throw std::logic_error( "sort() is not supported for unordered sets");
   } // ContainerAdapter< std::unordered_set< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::unordered_set< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the (unsorted) values from the container.
   /// @since  1.34.0, 04.12.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::unordered_set< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::unordered_set< T>>


/// Container adapter for std::vector.
///
/// @tparam  T  The type of the values stored in the vector.
/// @since  1.34.0, 22.11.2019
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
   /// @since  1.34.0, 22.11.2019
   explicit ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::vector< T>>::ContainerAdapter

   // default copy-/move-construction is fine
   ContainerAdapter( const ContainerAdapter&) = default;
   ContainerAdapter( ContainerAdapter&&) = default;

   // default destructor is fine
   ~ContainerAdapter() override = default;

   /// Stores a value in the destination container.
   ///
   /// @param[in]  value  The value to store.
   /// @since  1.34.0, 22.11.2019
   void addValue( const T& value)
   {
      mDestCont.push_back( value);
   } // ContainerAdapter< std::vector< T>>::addValue

   /// Clears the destination container.
   ///
   /// @since  1.34.0, 22.11.2019
   void clear()
   {
      mDestCont.clear();
   } // ContainerAdapter< std::vector< T>>::clear

   /// Returns if the container contains the given value.
   ///
   /// @param[in]  value  The value to search in the container.
   /// @return  \c true if the value was found.
   /// @since  1.34.0, 25.11.2019
   bool contains( const T& value) const
   {
      return common::contains( mDestCont, value);
   } // ContainerAdapter< std::vector< T>>::contains

   /// Sorts the values in the container.
   ///
   /// @since  1.34.0, 22.11.2019
   void sort()
   {
      std::sort( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::vector< T>>::sort

   /// Returns if the data in this and the other container intersect.
   ///
   /// @param[in]  other
   ///    The other object with the container/data to compare. against.
   /// @return
   ///    \c true if the data in this and the other object/containers intersect,
   ///    i.e. at least one value exists in both.
   /// @since  1.34.1, 14.01.2020
   bool hasIntersection( const ContainerAdapter& other) const
   {
      return common::hasIntersection( mDestCont, other.mDestCont);
   } // ContainerAdapter< std::vector< T>>::hasIntersection

   /// Returns a string with the values from the container.
   ///
   /// @return  String with the values from the container.
   /// @since  1.34.0, 22.11.2019
   std::string toString() const
   {
      return format::toString( mDestCont.begin(), mDestCont.end());
   } // ContainerAdapter< std::vector< T>>::toString

   /// Method empty() is used from te base class.
   using AdapterBase< container_type_t>::empty;
   /// Method size() is used from the base class.
   using AdapterBase< container_type_t>::size;

   // assignment is not allowed
   ContainerAdapter& operator =( const ContainerAdapter&) = delete;
   ContainerAdapter& operator =( ContainerAdapter&&) = delete;

}; // ContainerAdapter< std::vector< T>>


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONTAINER_ADAPTER_HPP


// =====  END OF container_adapter.hpp  =====

