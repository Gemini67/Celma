
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
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "celma/common/contains.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {


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
   AdapterBase( T& dest):
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
template< typename T> class ContainerAdapter
{
public:
   /// Flag that can be checked if a container adapter is available, set to
   /// \c false here for all non-supported (container) types.
   static constexpr bool  HasAdapter = false;

}; // ContainerAdapter< T>


/// Container adapter for std::set.
///
/// @tparam  T  The type of the values stored in the set.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter< std::set< T>>:
   AdapterBase< std::set< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, allows duplicates.
   static constexpr bool  AllowsDuplicates = false;
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
   ContainerAdapter( container_type_t& dest):
      AdapterBase< container_type_t>( dest)
   {
   } // ContainerAdapter< std::set< T>>::ContainerAdapter

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
template< typename T> class ContainerAdapter< std::stack< T>>:
   AdapterBase< std::stack< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = false;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, allows duplicates.
   static constexpr bool  AllowsDuplicates = true;
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
   ContainerAdapter( container_type_t& dest):
      AdapterBase< std::stack< T>>( dest)
   {
   } // ContainerAdapter< std::stack< T>>::ContainerAdapter

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


/// Container adapter for std::vector.
///
/// @tparam  T  The type of the values stored in the vector.
/// @since  x.y.z, 22.11.2019
template< typename T> class ContainerAdapter< std::vector< T>>:
   AdapterBase< std::vector< T>>
{
public:
   /// Flag for compile-time check if a container adapter exists for this type
   /// (obviously).
   static constexpr bool  HasAdapter = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, supports iterators.
   static constexpr bool  HasIterators = true;
   /// Flag for (compile-time) check if the container type, wrapped in this
   /// adapter, allows duplicates.
   static constexpr bool  AllowsDuplicates = true;
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
   ContainerAdapter( container_type_t& dest):
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

