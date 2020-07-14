
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::containers::btree.


#ifndef CELMA_CONTAINER_BTREE_HPP
#define CELMA_CONTAINER_BTREE_HPP


#include <cassert>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <istream>
#include <memory>
#include <ostream>
#include "celma/common/pre_postfix.hpp"


namespace celma::container {


// $Id: btree.h 128 2011-05-18 07:23:35Z tb $ -*- fill-column: 79 -*-
/** \file btree.h
 * Contains the main B+ tree implementation template class btree.
 */

/*
 * STX B+ Tree Template Classes v0.8.6
 * Copyright (C) 2008-2011 Timo Bingmann
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


// Debugging Macros

#ifdef BTREE_DEBUG

#include <iostream>

/// Print out debug information to std::cout if BTREE_DEBUG is defined.
#define BTREE_PRINT(x)          do { if (debug) (std::cout << x); } while (0)

/// Assertion only if BTREE_DEBUG is defined. This is not used in verify().
#define BTREE_ASSERT(x)         do { assert(x); } while (0)

#else

/// Print out debug information to std::cout if BTREE_DEBUG is defined.
#define BTREE_PRINT(x)          do { } while (0)

/// Assertion only if BTREE_DEBUG is defined. This is not used in verify().
#define BTREE_ASSERT(x)         do { } while (0)

#endif

/// The maximum of a and b. Used in some compile-time formulas.
#define BTREE_MAX(a,b)          ((a) < (b) ? (b) : (a))

#ifndef BTREE_FRIENDS
/// The macro BTREE_FRIENDS can be used by outside class to access the B+
/// tree internals. This was added for wxBTreeDemo to be able to draw the
/// tree.
#define BTREE_FRIENDS           friend class btree_friend;

#endif


/// Generates default traits for a B+ tree used as a set. It estimates leaf and
/// inner node sizes by assuming a cache line size of 256 bytes.
template< typename _Key> struct btree_default_set_traits
{
   /// If true, the tree will self verify it's invariants after each insert()
   /// or erase(). The header must have been compiled with BTREE_DEBUG defined.
   static constexpr bool  selfverify = false;

   /// If true, the tree will print out debug information and a tree dump
   /// during insert() or erase() operation. The header must have been
   /// compiled with BTREE_DEBUG defined and key_type must be std::ostream
   /// printable.
   static constexpr bool  debug = false;

   /// Number of slots in each leaf of the tree. Estimated so that each node
   /// has a size of about 256 bytes.
   static constexpr int   leafslots = BTREE_MAX( 8, 256 / sizeof( _Key));

   /// Number of slots in each inner node of the tree. Estimated so that each
   /// node has a size of about 256 bytes.
   static constexpr int   innerslots = BTREE_MAX( 8, 256 /
      (sizeof( _Key) + sizeof( void*)));
}; // btree_default_set_traits

/// Generates default traits for a B+ tree used as a map. It estimates leaf and
/// inner node sizes by assuming a cache line size of 256 bytes.
template< typename _Key, typename _Data> struct btree_default_map_traits
{
   /// If true, the tree will self verify it's invariants after each insert()
   /// or erase(). The header must have been compiled with BTREE_DEBUG defined.
   static constexpr bool  selfverify = false;

   /// If true, the tree will print out debug information and a tree dump
   /// during insert() or erase() operation. The header must have been
   /// compiled with BTREE_DEBUG defined and key_type must be std::ostream
   /// printable.
   static constexpr bool  debug = false;

   /// Number of slots in each leaf of the tree. Estimated so that each node
   /// has a size of about 256 bytes.
   static constexpr int   leafslots = BTREE_MAX( 8, 256 /
      (sizeof( _Key) + sizeof( _Data)));

   /// Number of slots in each inner node of the tree. Estimated so that each
   /// node has a size of about 256 bytes.
   static constexpr int   innerslots = BTREE_MAX( 8, 256 /
      (sizeof( _Key) + sizeof( void*)));
}; // btree_default_map_traits

/// Basic class implementing a base B+ tree data structure in memory.
///
/// The base implementation of a memory B+ tree. It is based on the
/// implementation in Cormen's Introduction into Algorithms, Jan Jannink's paper
/// and other algorithm resources. Almost all STL-required function calls are
/// implemented. The asymptotic time requirements of the STL are not always
/// fulfilled in theory, however in practice this B+ tree performs better than a
/// red-black tree by using more memory. The insertion function splits the nodes
/// on the recursion unroll. Erase is largely based on Jannink's ideas.
///
/// This class is specialized into btree_set, btree_multiset, btree_map and
/// btree_multimap using default template parameters and facade functions.
template< typename _Key, typename _Data,
          typename _Value = std::pair<_Key, _Data>,
          typename _Compare = std::less<_Key>,
          typename _Traits = btree_default_map_traits<_Key, _Data>,
          bool _Duplicates = false,
          typename _Alloc = std::allocator<_Value> >
class btree
{
public:
   // Template Parameter Types

   /// First template parameter: The key type of the B+ tree. This is stored
   /// in inner nodes and leaves
   using key_type = _Key;

   /// Second template parameter: The data type associated with each
   /// key. Stored in the B+ tree's leaves
   using data_type = _Data;

   /// Third template parameter: Composition pair of key and data types, this
   /// is required by the STL standard. The B+ tree does not store key and
   /// data together. If value_type == key_type then the B+ tree implements a
   /// set.
   using value_type = _Value;

   /// Fourth template parameter: Key comparison function object
   using key_compare = _Compare;

   /// Fifth template parameter: Traits object used to define more parameters
   /// of the B+ tree
   using traits = _Traits;

   /// Sixth template parameter: Allow duplicate keys in the B+ tree. Used to
   /// implement multiset and multimap.
   static constexpr bool  AllowDuplicates = _Duplicates;

   /// Seventh template parameter: STL allocator for tree nodes
   using allocator_type = _Alloc;

   // The macro BTREE_FRIENDS can be used by outside class to access the B+
   // tree internals. This was added for wxBTreeDemo to be able to draw the
   // tree.
   BTREE_FRIENDS

public:
   // Constructed Types

   /// Typedef of our own type
   using btree_self = btree< key_type, data_type, value_type, key_compare,
                             traits, AllowDuplicates, allocator_type>;

   /// Size type used to count keys
   using size_type = size_t;

   /// The pair of key_type and data_type, this may be different from value_type.
   using pair_type = std::pair< key_type, data_type>;

public:
   // Static Constant Options and Values of the B+ Tree

   /// Base B+ tree parameter: The number of ky/data slots in each leaf
   static constexpr unsigned short  LeafSlotMax =  traits::leafslots;

   /// Base B+ tree parameter: The number of key slots in each inner node,
   /// this can differ from slots in each leaf.
   static constexpr unsigned short  InnerSlotMax =  traits::innerslots;

   /// Computed B+ tree parameter: The minimum number of key/data slots used
   /// in a leaf. If fewer slots are used, the leaf will be merged or slots
   /// shifted from it's siblings.
   static constexpr unsigned short  MinLeafSlots = LeafSlotMax / 2;

   /// Computed B+ tree parameter: The minimum number of key slots used
   /// in an inner node. If fewer slots are used, the inner node will be
   /// merged or slots shifted from it's siblings.
   static constexpr unsigned short  MinInnerSlots = InnerSlotMax / 2;

   /// Debug parameter: Enables expensive and thorough checking of the B+ tree
   /// invariants after each insert/erase operation.
   static constexpr bool            SelfVerify = traits::selfverify;

   /// Debug parameter: Prints out lots of debug information about how the
   /// algorithms change the tree. Requires the header file to be compiled
   /// with BTREE_DEBUG and the key type must be std::ostream printable.
   static constexpr bool            Debug = traits::debug;

private:
   // Node Classes for In-Memory Nodes

   /// The header structure of each node in-memory. This structure is extended
   /// by InnerNode or leaf_node.
   class Node
   {
   public:
      /// Delayed initialisation of constructed node
      void initialize( const unsigned short l)
      {
         mLevel = l;
         mSlotUse = 0;
      }

      /// True if this is a leaf node
      bool isleafnode() const
      {
         return mLevel == 0;
      }

      /// Level in the b-tree, if level == 0 -> leaf node
      unsigned short  mLevel;

      /// Number of key mSlotUse use, so number of valid children or data
      /// pointers
      unsigned short  mSlotUse;

   }; // Node

   /// Extended structure of a inner node in-memory. Contains only keys and no
   /// data items.
   class InnerNode: public Node
   {
   public:
      /// Set variables to initial values
      void initialize( const unsigned short l)
      {
         Node::initialize( l);
      }

      /// True if the node's slots are full
      bool isfull() const
      {
         return Node::mSlotUse == InnerSlotMax;
      }

      /// True if few used entries, less than half full
      bool isfew() const
      {
         return Node::mSlotUse <= MinInnerSlots;
      }

      /// True if node has too few entries
      bool isunderflow() const
      {
         return Node::mSlotUse < MinInnerSlots;
      }

      /// Define an related allocator for the InnerNode structs.
      using alloc_type = typename _Alloc::template rebind< InnerNode>::other;

      /// Keys of children or data pointers
      key_type  mSlotKey[ InnerSlotMax];

      /// Pointers to children
      Node*     mChildId[ InnerSlotMax + 1];

   }; // InnerNode

   /// Extended structure of a leaf node in memory. Contains pairs of keys and
   /// data items. Key and data slots are kept in separate arrays, because the
   /// key array is traversed very often compared to accessing the data items.
   class LeafNode: public Node
   {
   public:
      /// Define an related allocator for the leaf_node structs.
      using alloc_type = typename _Alloc::template rebind< LeafNode>::other;

      /// Double linked list pointers to traverse the leaves
      LeafNode*   mpPrevLeaf;

      /// Double linked list pointers to traverse the leaves
      LeafNode*   mpNextLeaf;

      /// Keys of children or data pointers
      key_type    mSlotKey[ LeafSlotMax];

      /// Array of data
      data_type   mSlotData[ LeafSlotMax];

      /// Set variables to initial values
      void initialize()
      {
         Node::initialize( 0);
         mpPrevLeaf = mpNextLeaf = nullptr;
      }

      /// True if the node's slots are full
      bool isfull() const
      {
         return Node::mSlotUse == LeafSlotMax;
      }

      /// True if few used entries, less than half full
      bool isfew() const
      {
         return Node::mSlotUse <= MinLeafSlots;
      }

      /// True if node has too few entries
      bool isunderflow() const
      {
         return Node::mSlotUse < MinLeafSlots;
      }
   }; // LeafNode

private:
   // Template Magic to Convert a pair or key/data types to a value_type

   /// For sets the second pair_type is an empty struct, so the value_type
   /// should only be the first.
   template <typename value_type, typename pair_type>
      struct btree_pair_to_value
   {
      /// Convert a fake pair type to just the first component
      value_type operator ()( pair_type& p) const
      {
         return p.first;
      }
      /// Convert a fake pair type to just the first component
      value_type operator ()( const pair_type& p) const
      {
         return p.first;
      }
   }; // btree_pair_to_value

   /// For maps value_type is the same as the pair_type
   template< typename value_type>
      struct btree_pair_to_value< value_type, value_type>
   {
      /// Identity "convert" a real pair type to just the first component
      value_type operator ()( pair_type& p) const
      {
         return p;
      }
      /// Identity "convert" a real pair type to just the first component
      value_type operator ()( const pair_type& p) const
      {
         return p;
      }
   }; // btree_pair_to_value

   /// Using template specialization select the correct converter used by the
   /// iterators
   using pair_to_value_type = btree_pair_to_value< value_type, pair_type>;

public:
   // Iterators and Reverse Iterators

   class iterator;
   class const_iterator;
   class reverse_iterator;
   class const_reverse_iterator;

   /// STL-like iterator object for B+ tree items. The iterator points to a
   /// specific slot number in a leaf.
   class iterator
   {
   public:
      // Types

      /// The key type of the btree. Returned by key().
      using key_type = typename btree::key_type;

      /// The data type of the btree. Returned by data().
      using data_type = typename btree::data_type;

      /// The value type of the btree. Returned by operator*().
      using value_type = typename btree::value_type;

      /// The pair type of the btree.
      using pair_type = typename btree::pair_type;

      /// Reference to the value_type. STL required.
      using reference = value_type&;

      /// Pointer to the value_type. STL required.
      using pointer = value_type*;

      /// STL-magic iterator category
      using iterator_category = std::bidirectional_iterator_tag;

      /// STL-magic
      using difference_type = ptrdiff_t;

      /// Our own type
      using self = iterator;

   private:
      /// Friendly to the const_iterator, so it may access the two data items
      /// directly.
      friend class const_iterator;

      /// Also friendly to the reverse_iterator, so it may access the two data
      /// items directly.
      friend class reverse_iterator;

      /// Also friendly to the const_reverse_iterator, so it may access the two
      /// data items directly.
      friend class const_reverse_iterator;

      /// Also friendly to the base btree class, because erase_iter() needs
      /// to read the currnode and currslot values directly.
      friend class btree< key_type, data_type, value_type, key_compare, traits,
         AllowDuplicates>;

      // Members

      /// The currently referenced leaf node of the tree
      typename btree::LeafNode*  mpCurrentNode = nullptr;

      /// Current key/data slot referenced
      unsigned short             mCurrentSlot = 0;

      /// Evil! A temporary value_type to STL-correctly deliver operator* and
      /// operator->
      mutable value_type         mTemporaryValue;

      // The macro BTREE_FRIENDS can be used by outside class to access the B+
      // tree internals. This was added for wxBTreeDemo to be able to draw the
      // tree.
      BTREE_FRIENDS

   public:
      // Methods

      /// Default-Constructor of a mutable iterator
      iterator() = default;

      /// Initializing-Constructor of a mutable iterator
      iterator( typename btree::LeafNode* l, unsigned short s)
          : mpCurrentNode( l), mCurrentSlot( s)
      { }

      /// Copy-constructor from a reverse iterator
      iterator( const reverse_iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Dereference the iterator, this is not a value_type& because key and
      /// value are not stored together
      reference operator *() const
      {
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot],
                       mpCurrentNode->mSlotData[ mCurrentSlot]));
         return mTemporaryValue;
      }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      pointer operator ->() const
      {
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot],
                       mpCurrentNode->mSlotData[ mCurrentSlot]));
         return &mTemporaryValue;
      }

      /// Key of the current slot
      const key_type& key() const
      {
         return mpCurrentNode->mSlotKey[ mCurrentSlot];
      }

      /// Writable reference to the current data object
      data_type& data() const
      {
         return mpCurrentNode->mSlotData[ mCurrentSlot];
      }

      /// Prefix++ advance the iterator to the next slot
      self& operator ++( std::prefix)
      {
         if (mCurrentSlot + 1 < mpCurrentNode->mSlotUse)
         {
            ++mCurrentSlot;
         } else if (mpCurrentNode->mpNextLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpNextLeaf;
            mCurrentSlot = 0;
         } else
         {
            // this is end()
            mCurrentSlot = mpCurrentNode->mSlotUse;
         }

         return *this;
      }

      /// Postfix++ advance the iterator to the next slot
      self operator ++( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator ++();  // rely on the prefix ++ operator
         return tmp;
      }

      /// Prefix-- backstep the iterator to the last slot
      self& operator --( std::prefix)
      {
         if (mCurrentSlot > 0)
         {
            --mCurrentSlot;
         } else if (mpCurrentNode->mpPrevLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpPrevLeaf;
            mCurrentSlot = mpCurrentNode->mSlotUse - 1;
         } else
         {
            // this is begin()
            mCurrentSlot = 0;
         }

         return *this;
      }

      /// Postfix-- backstep the iterator to the last slot
      self operator --( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator --();  // rely on the prefix -- operator
         return tmp;
      }

      /// Equality of iterators
      bool operator ==( const self& x) const
      {
         return (x.mpCurrentNode == mpCurrentNode)
                && (x.mCurrentSlot == mCurrentSlot);
      }

      /// Inequality of iterators
      bool operator !=( const self& x) const
      {
         return (x.mpCurrentNode != mpCurrentNode)
                || (x.mCurrentSlot != mCurrentSlot);
      }
   }; // iterator

   /// STL-like read-only iterator object for B+ tree items. The iterator
   /// points to a specific slot number in a leaf.
   class const_iterator
   {
   public:
      // Types

      /// The key type of the btree. Returned by key().
      using key_type = typename btree::key_type;

      /// The data type of the btree. Returned by data().
      using data_type = typename btree::data_type;

      /// The value type of the btree. Returned by operator*().
      using value_type = typename btree::value_type;

      /// The pair type of the btree.
      using pair_type = typename btree::pair_type;

      /// Reference to the value_type. STL required.
      using reference = const value_type&;

      /// Pointer to the value_type. STL required.
      using pointer = const value_type*;

      /// STL-magic iterator category
      using iterator_category = std::bidirectional_iterator_tag;

      /// STL-magic
      using difference_type = ptrdiff_t;

      /// Our own type
      using self = const_iterator;

   private:
      // Members

      /// The currently referenced leaf node of the tree
      const typename btree::LeafNode*  mpCurrentNode = nullptr;

      /// Current key/data slot referenced
      unsigned short                   mCurrentSlot = 0;

      /// Friendly to the reverse_const_iterator, so it may access the two data items directly
      friend class const_reverse_iterator;

      /// Evil! A temporary value_type to STL-correctly deliver operator* and
      /// operator->
      mutable value_type               mTemporaryValue;

      // The macro BTREE_FRIENDS can be used by outside class to access the B+
      // tree internals. This was added for wxBTreeDemo to be able to draw the
      // tree.
      BTREE_FRIENDS

   public:
      // Methods

      /// Default-Constructor of a const iterator
      const_iterator() = default;

      /// Initializing-Constructor of a const iterator
      const_iterator( const typename btree::LeafNode* l,
         unsigned short s)
          : mpCurrentNode( l), mCurrentSlot( s)
      { }

      /// Copy-constructor from a mutable iterator
      const_iterator( const iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Copy-constructor from a mutable reverse iterator
      const_iterator( const reverse_iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Copy-constructor from a const reverse iterator
      const_iterator( const const_reverse_iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      reference operator *() const
      {
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot],
                       mpCurrentNode->mSlotData[ mCurrentSlot]));
         return mTemporaryValue;
      }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      pointer operator ->() const
      {
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot],
                       mpCurrentNode->mSlotData[ mCurrentSlot]));
         return &mTemporaryValue;
      }

      /// Key of the current slot
      const key_type& key() const
      {
         return mpCurrentNode->mSlotKey[ mCurrentSlot];
      }

      /// Read-only reference to the current data object
      const data_type& data() const
      {
         return mpCurrentNode->mSlotData[ mCurrentSlot];
      }

      /// Prefix++ advance the iterator to the next slot
      self& operator ++( std::prefix)
      {
         if (mCurrentSlot + 1 < mpCurrentNode->mSlotUse)
         {
            ++mCurrentSlot;
         } else if (mpCurrentNode->mpNextLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpNextLeaf;
            mCurrentSlot = 0;
         } else
         {
            // this is end()
            mCurrentSlot = mpCurrentNode->mSlotUse;
         }

         return *this;
      }

      /// Postfix++ advance the iterator to the next slot
      self operator ++( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator ++();  // rely on the prefix ++ operator
         return tmp;
      }

      /// Prefix-- backstep the iterator to the last slot
      self& operator --( std::prefix)
      {
         if (mCurrentSlot > 0)
         {
            --mCurrentSlot;
         } else if (mpCurrentNode->mpPrevLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpPrevLeaf;
            mCurrentSlot = mpCurrentNode->mSlotUse - 1;
         } else
         {
            // this is begin()
            mCurrentSlot = 0;
         }

         return *this;
      }

      /// Postfix-- backstep the iterator to the last slot
      self operator --( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator --();  // rely on the prefix -- operator
         return tmp;
      }

      /// Equality of iterators
      bool operator ==( const self& x) const
      {
         return (x.mpCurrentNode == mpCurrentNode)
                && (x.mCurrentSlot == mCurrentSlot);
      }

      /// Inequality of iterators
      bool operator !=( const self& x) const
      {
         return (x.mpCurrentNode != mpCurrentNode)
                || (x.mCurrentSlot != mCurrentSlot);
      }
   }; // const_iterator

   /// STL-like mutable reverse iterator object for B+ tree items. The
   /// iterator points to a specific slot number in a leaf.
   class reverse_iterator
   {
   public:
      // Types

      /// The key type of the btree. Returned by key().
      using key_type = typename btree::key_type;

      /// The data type of the btree. Returned by data().
      using data_type = typename btree::data_type;

      /// The value type of the btree. Returned by operator*().
      using value_type = typename btree::value_type;

      /// The pair type of the btree.
      using pair_type = typename btree::pair_type;

      /// Reference to the value_type. STL required.
      using reference = value_type&;

      /// Pointer to the value_type. STL required.
      using pointer = value_type*;

      /// STL-magic iterator category
      using iterator_category = std::bidirectional_iterator_tag;

      /// STL-magic
      using difference_type = ptrdiff_t;

      /// Our own type
      using self = reverse_iterator;

   private:
      // Members

      /// The currently referenced leaf node of the tree
      typename btree::LeafNode*  mpCurrentNode = nullptr;

      /// One slot past the current key/data slot referenced.
      unsigned short             mCurrentSlot = 0;

      /// Friendly to the const_iterator, so it may access the two data items directly
      friend class iterator;

      /// Also friendly to the const_iterator, so it may access the two data items directly
      friend class const_iterator;

      /// Also friendly to the const_iterator, so it may access the two data items directly
      friend class const_reverse_iterator;

      /// Evil! A temporary value_type to STL-correctly deliver operator* and
      /// operator->
      mutable value_type          mTemporaryValue;

      // The macro BTREE_FRIENDS can be used by outside class to access the B+
      // tree internals. This was added for wxBTreeDemo to be able to draw the
      // tree.
      BTREE_FRIENDS

   public:
      // Methods

      /// Default-Constructor of a reverse iterator
      reverse_iterator() = default;

      /// Initializing-Constructor of a mutable reverse iterator
      reverse_iterator( typename btree::LeafNode* l, unsigned short s)
          : mpCurrentNode( l), mCurrentSlot( s)
      { }

      /// Copy-constructor from a mutable iterator
      reverse_iterator( const iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Dereference the iterator, this is not a value_type& because key and
      /// value are not stored together
      reference operator *() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot - 1],
                       mpCurrentNode->mSlotData[ mCurrentSlot - 1]));
         return mTemporaryValue;
      }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      pointer operator ->() const
      {
         BTREE_ASSERT(mCurrentSlot > 0);
         mTemporaryValue = 
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot - 1],
                       mpCurrentNode->mSlotData[ mCurrentSlot - 1]);
         return &mTemporaryValue;
      }

      /// Key of the current slot
      const key_type& key() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         return mpCurrentNode->mSlotKey[ mCurrentSlot - 1];
      }

      /// Writable reference to the current data object
      data_type& data() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         return mpCurrentNode->mSlotData[ mCurrentSlot - 1];
      }

      /// Prefix++ advance the iterator to the next slot
      self& operator ++( std::prefix)
      {
         if (mCurrentSlot > 1)
         {
            --mCurrentSlot;
         } else if (mpCurrentNode->mpPrevLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpPrevLeaf;
            mCurrentSlot = mpCurrentNode->mSlotUse;
         } else
         {
            // this is begin() == rend()
            mCurrentSlot = 0;
         }

         return *this;
      }

      /// Postfix++ advance the iterator to the next slot
      self operator ++( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator ++();  // rely on the prefix ++ operator
         return tmp;
      }

      /// Prefix-- backstep the iterator to the last slot
      self& operator --( std::prefix)
      {
         if (mCurrentSlot < mpCurrentNode->mSlotUse)
         {
            ++mCurrentSlot;
         } else if (mpCurrentNode->mpNextLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpNextLeaf;
            mCurrentSlot = 1;
         } else
         {
            // this is end() == rbegin()
            mCurrentSlot = mpCurrentNode->mSlotUse;
         }

         return *this;
      }

      /// Postfix-- backstep the iterator to the last slot
      self operator --( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator --();  // rely on the prefix -- operator
         return tmp;
      }

      /// Equality of iterators
      bool operator==(const self& x) const
      {
         return (x.mpCurrentNode == mpCurrentNode)
                && (x.mCurrentSlot == mCurrentSlot);
      }

      /// Inequality of iterators
      bool operator!=(const self& x) const
      {
         return (x.mpCurrentNode != mpCurrentNode)
                || (x.mCurrentSlot != mCurrentSlot);
      }
   }; // reverse_iterator

   /// STL-like read-only reverse iterator object for B+ tree items. The
   /// iterator points to a specific slot number in a leaf.
   class const_reverse_iterator
   {
   public:
      // Types

      /// The key type of the btree. Returned by key().
      using key_type = typename btree::key_type;

      /// The data type of the btree. Returned by data().
      using data_type = typename btree::data_type;

      /// The value type of the btree. Returned by operator*().
      using value_type = typename btree::value_type;

      /// The pair type of the btree.
      using pair_type = typename btree::pair_type;

      /// Reference to the value_type. STL required.
      using reference = const value_type&;

      /// Pointer to the value_type. STL required.
      using pointer = const value_type*;

      /// STL-magic iterator category
      using iterator_category = std::bidirectional_iterator_tag;

      /// STL-magic
      using difference_type = ptrdiff_t;

      /// Our own type
      using self = const_reverse_iterator;

   private:
      // Members

      /// The currently referenced leaf node of the tree
      const typename btree::LeafNode*  mpCurrentNode = nullptr;

      /// One slot past the current key/data slot referenced.
      unsigned short                   mCurrentSlot = 0;

      /// Friendly to the const_iterator, so it may access the two data items directly.
      friend class reverse_iterator;

      /// Evil! A temporary value_type to STL-correctly deliver operator* and
      /// operator->
      mutable value_type               mTemporaryValue;

      // The macro BTREE_FRIENDS can be used by outside class to access the B+
      // tree internals. This was added for wxBTreeDemo to be able to draw the
      // tree.
      BTREE_FRIENDS

   public:
      // Methods

      /// Default-Constructor of a const reverse iterator
      const_reverse_iterator() = default;

      /// Initializing-Constructor of a const reverse iterator
      const_reverse_iterator( const typename btree::LeafNode* l,
         unsigned short s)
          : mpCurrentNode( l), mCurrentSlot( s)
      { }

      /// Copy-constructor from a mutable iterator
      const_reverse_iterator( const iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Copy-constructor from a const iterator
      const_reverse_iterator( const const_iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Copy-constructor from a mutable reverse iterator
      const_reverse_iterator( const reverse_iterator& it)
          : mpCurrentNode( it.mpCurrentNode), mCurrentSlot( it.mCurrentSlot)
      { }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      reference operator *() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot - 1],
                       mpCurrentNode->mSlotData[ mCurrentSlot - 1]));
         return mTemporaryValue;
      }

      /// Dereference the iterator. Do not use this if possible, use key()
      /// and data() instead. The B+ tree does not stored key and data
      /// together.
      pointer operator ->() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         mTemporaryValue = pair_to_value_type()(
            pair_type( mpCurrentNode->mSlotKey[ mCurrentSlot - 1],
                       mpCurrentNode->mSlotData[ mCurrentSlot - 1]));
         return &mTemporaryValue;
      }

      /// Key of the current slot
      const key_type& key() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         return mpCurrentNode->mSlotKey[ mCurrentSlot - 1];
      }

      /// Read-only reference to the current data object
      const data_type& data() const
      {
         BTREE_ASSERT( mCurrentSlot > 0);
         return mpCurrentNode->mSlotData[ mCurrentSlot - 1];
      }

      /// Prefix++ advance the iterator to the previous slot
      self& operator ++( std::prefix)
      {
         if (mCurrentSlot > 1)
         {
            --mCurrentSlot;
         } else if (mpCurrentNode->mpPrevLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpPrevLeaf;
            mCurrentSlot = mpCurrentNode->mSlotUse;
         } else
         {
            // this is begin() == rend()
            mCurrentSlot = 0;
         }

         return *this;
      }

      /// Postfix++ advance the iterator to the previous slot
      self operator ++( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator ++();  // rely on the prefix ++ operator
         return tmp;
      }

      /// Prefix-- backstep the iterator to the next slot
      self& operator --( std::prefix)
      {
         if (mCurrentSlot < mpCurrentNode->mSlotUse)
         {
            ++mCurrentSlot;
         } else if (mpCurrentNode->mpNextLeaf != nullptr)
         {
            mpCurrentNode = mpCurrentNode->mpNextLeaf;
            mCurrentSlot = 1;
         } else
         {
            // this is end() == rbegin()
            mCurrentSlot = mpCurrentNode->mSlotUse;
         }

         return *this;
      }

      /// Postfix-- backstep the iterator to the next slot
      self operator --( std::postfix)
      {
         self  tmp = *this;   // copy ourselves
         this->operator --();  // rely on the prefix -- operator
         return tmp;
      }

      /// Equality of iterators
      bool operator ==( const self& x) const
      {
         return (x.mpCurrentNode == mpCurrentNode)
                && (x.mCurrentSlot == mCurrentSlot);
      }

      /// Inequality of iterators
      bool operator !=( const self& x) const
      {
         return (x.mpCurrentNode != mpCurrentNode)
                || (x.mCurrentSlot != mCurrentSlot);
      }
   }; // const_reverse_iterator

public:
   // Small Statistics Structure

   /** A small struct containing basic statistics about the B+ tree. It can be
    * fetched using get_stats(). */
   class tree_stats
   {
   public:
      /// Number of items in the B+ tree
      size_type  mItemCount = 0;

      /// Number of leaves in the B+ tree
      size_type  mLeaves = 0;

      /// Number of inner nodes in the B+ tree
      size_type  mInnerNodes = 0;

      /// Base B+ tree parameter: The number of key/data slots in each leaf
      static constexpr unsigned short  leafslots = btree_self::LeafSlotMax;

      /// Base B+ tree parameter: The number of key slots in each inner node.
      static constexpr unsigned short  innerslots = btree_self::InnerSlotMax;

      /// Zero initialized
      tree_stats() = default;

      /// Return the total number of nodes
      size_type nodes() const
      {
         return mInnerNodes + mLeaves;
      }

      /// Return the average fill of leaves
      double avgfill_leaves() const
      {
        return static_cast< double>( mItemCount) / (mLeaves * leafslots);
      }
   }; // tree_stats

private:
   // Tree Object Data Members

   /// Pointer to the B+ tree's root node, either leaf or inner node
   Node*           mpRoot = nullptr;

   /// Pointer to first leaf in the double linked leaf chain
   LeafNode*       mpHeadLeaf = nullptr;

   /// Pointer to last leaf in the double linked leaf chain
   LeafNode*       mpTailLeaf = nullptr;

   /// Other small statistics about the B+ tree
   tree_stats      mStats;

   /// Key comparison object. More comparison functions are generated from
   /// this < relation.
   key_compare     mKeyLess;

   /// Memory allocator.
   allocator_type  mAllocator;

public:
   // Constructors and Destructor

   /// Default constructor initializing an empty B+ tree with the standard key
   /// comparison function
   explicit btree( const allocator_type& alloc = allocator_type()):
      mAllocator( alloc)
   {
   }

   /// Constructor initializing an empty B+ tree with a special key
   /// comparison object
   explicit btree( const key_compare& kcf,
                   const allocator_type& alloc = allocator_type()):
      mKeyLess( kcf), mAllocator( alloc)
   {
   }

   /// Constructor initializing a B+ tree with the range [first,last)
   template< class InputIterator>
      btree( InputIterator first, InputIterator last,
             const allocator_type& alloc = allocator_type()):
         mAllocator( alloc)
   {
       insert( first, last);
   }

   /// Constructor initializing a B+ tree with the range [first,last) and a
   /// special key comparison objectmpRoot
   template< class InputIterator>
      btree( InputIterator first, InputIterator last,
             const key_compare& kcf,
             const allocator_type& alloc = allocator_type()):
         mKeyLess( kcf), mAllocator( alloc)
   {
      insert( first, last);
   }

   /// Frees up all used B+ tree memory pages
   ~btree()
   {
      clear();
   }

   /// Fast swapping of two identical B+ tree objects.
   void swap( btree_self& from)
   {
      std::swap( mpRoot, from.mpRoot);
      std::swap( mpHeadLeaf, from.mpHeadLeaf);
      std::swap( mpTailLeaf, from.mpTailLeaf);
      std::swap( mStats, from.mStats);
      std::swap( mKeyLess, from.mKeyLess);
      std::swap( mAllocator, from.mAllocator);
   }

public:
   // Key and Value Comparison Function Objects

   /// Function class to compare value_type objects. Required by the STL
   class value_compare
   {
   protected:
      /// Key comparison function from the template parameter
      key_compare  key_comp;

      /// Constructor called from btree::value_comp()
      explicit value_compare( key_compare kc)
          : key_comp(kc)
      { }

      /// Friendly to the btree class so it may call the constructor
      friend class btree< key_type, data_type, value_type, key_compare, traits,
                          AllowDuplicates>;

   public:
       /// Function call "less"-operator resulting in true if x < y.
       bool operator ()( const value_type& x, const value_type& y) const
       {
          return key_comp( x.first, y.first);
       }
   }; // value_compare

   /// Constant access to the key comparison object sorting the B+ tree
   key_compare key_comp() const
   {
      return mKeyLess;
   }

   /// Constant access to a constructed value_type comparison object. Required
   /// by the STL
   value_compare value_comp() const
   {
      return value_compare( mKeyLess);
   }

private:
   // Convenient Key Comparison Functions Generated From key_less

   /// True if a <= b ? constructed from key_less()
   bool key_lessequal( const key_type& a, const key_type b) const
   {
      return !mKeyLess( b, a);
   }

   /// True if a > b ? constructed from key_less()
   bool key_greater( const key_type& a, const key_type& b) const
   {
      return mKeyLess( b, a);
   }

   /// True if a >= b ? constructed from key_less()
   bool key_greaterequal( const key_type& a, const key_type b) const
   {
      return !mKeyLess( a, b);
   }

   /// True if a == b ? constructed from key_less(). This requires the <
   /// relation to be a total order, otherwise the B+ tree cannot be sorted.
   bool key_equal( const key_type& a, const key_type& b) const
   {
      return !mKeyLess( a, b) && !mKeyLess( b, a);
   }

public:
   // Allocators

   /// Return the base node allocator provided during construction.
   allocator_type get_allocator() const
   {
      return mAllocator;
   }

private:
   // Node Object Allocation and Deallocation Functions

   /// Return an allocator for leaf_node objects
   typename LeafNode::alloc_type leaf_node_allocator()
   {
      return typename LeafNode::alloc_type( mAllocator);
   }

   /// Return an allocator for InnerNode objects
   typename InnerNode::alloc_type inner_node_allocator()
   {
      return typename InnerNode::alloc_type( mAllocator);
   }

   /// Allocate and initialize a leaf node
   LeafNode* allocate_leaf()
   {
      LeafNode*  n = new (leaf_node_allocator().allocate( 1)) LeafNode();
      n->initialize();
      mStats.mLeaves++;
      return n;
   }

   /// Allocate and initialize an inner node
   InnerNode* allocate_inner( unsigned short level)
   {
      InnerNode*  n = new (inner_node_allocator().allocate( 1)) InnerNode();
      n->initialize( level);
      mStats.mInnerNodes++;
      return n;
   }

   /// Correctly free either inner or leaf node, destructs all contained key
   /// and value objects
   void free_node( Node* n)
   {
      if (n->isleafnode())
      {
         LeafNode*  ln = static_cast< LeafNode*>( n);
         typename LeafNode::alloc_type  a( leaf_node_allocator());
         a.destroy( ln);
         a.deallocate( ln, 1);
         mStats.mLeaves--;
      } else
      {
         InnerNode*  in = static_cast< InnerNode*>( n);
         typename InnerNode::alloc_type  a( inner_node_allocator());
         a.destroy( in);
         a.deallocate( in, 1);
         mStats.mInnerNodes--;
      }
   }

public:
   // Fast Destruction of the B+ Tree

   /// Frees all key/data pairs and all nodes of the tree
   void clear()
   {
      if (mpRoot != nullptr)
      {
         clear_recursive( mpRoot);
         free_node( mpRoot);

         mpRoot = nullptr;
         mpHeadLeaf = mpTailLeaf = nullptr;

         mStats = tree_stats();
      }

      BTREE_ASSERT( mStats.mItemCount == 0);
   }

private:
   /// Recursively free up nodes
   void clear_recursive( Node* n)
   {
      if (!n->isleafnode())
      {
         InnerNode*  innernode = static_cast< InnerNode*>( n);

         for (unsigned short slot = 0; slot < innernode->mSlotUse + 1; ++slot)
         {
            clear_recursive( innernode->mChildId[ slot]);
            free_node( innernode->mChildId[ slot]);
         } // end for
      } // end if
   }

public:
   // STL Iterator Construction Functions

   /// Constructs a read/data-write iterator that points to the first slot in
   /// the first leaf of the B+ tree.
   iterator begin()
   {
      return iterator( mpHeadLeaf, 0);
   }

   /// Constructs a read/data-write iterator that points to the first invalid
   /// slot in the last leaf of the B+ tree.
   iterator end()
   {
      return iterator( mpTailLeaf, mpTailLeaf ? mpTailLeaf->mSlotUse : 0);
   }

   /// Constructs a read-only constant iterator that points to the first slot
   /// in the first leaf of the B+ tree.
   const_iterator begin() const
   {
      return const_iterator( mpHeadLeaf, 0);
   }

   /// Constructs a read-only constant iterator that points to the first
   /// invalid slot in the last leaf of the B+ tree.
   const_iterator end() const
   {
      return const_iterator( mpTailLeaf, mpTailLeaf ? mpTailLeaf->mSlotUse : 0);
   }

   /// Constructs a read/data-write reverse iterator that points to the first
   /// invalid slot in the last leaf of the B+ tree. Uses STL magic.
   reverse_iterator rbegin()
   {
      return reverse_iterator( end());
   }

   /// Constructs a read/data-write reverse iterator that points to the first
   /// slot in the first leaf of the B+ tree. Uses STL magic.
   reverse_iterator rend()
   {
      return reverse_iterator( begin());
   }

   /// Constructs a read-only reverse iterator that points to the first
   /// invalid slot in the last leaf of the B+ tree. Uses STL magic.
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end());
   }

   /// Constructs a read-only reverse iterator that points to the first slot
   /// in the first leaf of the B+ tree. Uses STL magic.
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin());
   }

private:
   // B+ Tree Node Binary Search Functions

   /// Searches for the first key in the node n less or equal to key. Uses
   /// binary search with an optional linear self-verification. This is a
   /// template function, because the slotkey array is located at different
   /// places in leaf_node and InnerNode.
   template< typename node_type>
      int find_lower( const node_type* n, const key_type& key) const
   {
      if (n->mSlotUse == 0)
         return 0;

      int  lo = 0;
      int  hi = n->mSlotUse - 1;

      while (lo < hi)
      {
         const int  mid = (lo + hi) >> 1;

         if (key_lessequal( key, n->mSlotKey[ mid]))
         {
            hi = mid - 1;
         } else
         {
            lo = mid + 1;
         }
      }

      if (hi < 0 || mKeyLess( n->mSlotKey[ hi], key))
         hi++;

      BTREE_PRINT( "btree::find_lower: on " << n << " key " << key << " -> (" << lo << ") " << hi << ", ");

      // verify result using simple linear search
      if (SelfVerify)
      {
         int  i = n->mSlotUse - 1;
         while (i >= 0 && key_lessequal( key, n->mSlotKey[ i]))
            i--;
         i++;

         BTREE_PRINT( "testfind: " << i << std::endl);
         BTREE_ASSERT( i == hi);
      } else
      {
         BTREE_PRINT( std::endl);
      }

      return hi;
   }

   /// Searches for the first key in the node n greater than key. Uses binary
   /// search with an optional linear self-verification. This is a template
   /// function, because the slotkey array is located at different places in
   /// leaf_node and InnerNode.
   template< typename node_type>
      int find_upper( const node_type* n, const key_type& key) const
   {
      if (n->mSlotUse == 0)
         return 0;

      int  lo = 0;
      int  hi = n->mSlotUse - 1;

      while (lo < hi)
      {
         const int  mid = (lo + hi) >> 1;

         if (mKeyLess( key, n->mSlotKey[ mid]))
         {
            hi = mid - 1;
         } else
         {
            lo = mid + 1;
         }
      }

      if (hi < 0 || key_lessequal( n->mSlotKey[ hi], key))
         hi++;

      BTREE_PRINT( "btree::find_upper: on " << n << " key " << key << " -> (" << lo << ") " << hi << ", ");

      // verify result using simple linear search
      if (SelfVerify)
      {
         int  i = n->mSlotUse - 1;
         while (i >= 0 && mKeyLess( key, n->mSlotKey[ i]))
            i--;
         i++;

         BTREE_PRINT( "btree::find_upper testfind: " << i << std::endl);
         BTREE_ASSERT( i == hi);
      } else
      {
         BTREE_PRINT( std::endl);
      }

      return hi;
   }

public:
   // Access Functions to the Item Count

   /// Return the number of key/data pairs in the B+ tree
   size_type size() const
   {
      return mStats.mItemCount;
   }

   /// Returns true if there is at least one key/data pair in the B+ tree
   bool empty() const
   {
      return size() == size_type( 0);
   }

   /// Returns the largest possible size of the B+ Tree. This is just a
   /// function required by the STL standard, the B+ Tree can hold more items.
   size_type max_size() const
   {
      return size_type( -1);
   }

   /// Return a const reference to the current statistics.
   const struct tree_stats& get_stats() const
   {
      return mStats;
   }

public:
   // Standard Access Functions Querying the Tree by Descending to a Leaf

   /// Non-STL function checking whether a key is in the B+ tree. The same as
   /// (find(k) != end()) or (count() != 0).
   bool exists( const key_type& key) const
   {
      const LeafNode*  leaf = findLeaf( key);
      if (leaf == nullptr)
         return false;

      const int  slot = find_lower( leaf, key);
      return (slot < leaf->mSlotUse) && key_equal( key, leaf->mSlotKey[ slot]);
   } // btree<>::exists

   /// Tries to locate a key in the B+ tree and returns an iterator to the
   /// key/data slot if found. If unsuccessful it returns end().
   iterator find( const key_type& key)
   {
      const LeafNode*  leaf = findLeaf( key);
      if (leaf == nullptr)
         return end();

      const int  slot = find_lower( leaf, key);
      return (slot < leaf->mSlotUse) && key_equal( key, leaf->mSlotKey[ slot])
         ? iterator( const_cast< LeafNode*>( leaf), slot) : end();
   } // btree<>::find

   /// Tries to locate a key in the B+ tree and returns an constant iterator
   /// to the key/data slot if found. If unsuccessful it returns end().
   const_iterator find( const key_type& key) const
   {
      const LeafNode*  leaf = findLeaf( key);
      if (leaf == nullptr)
         return end();

      const int  slot = find_lower( leaf, key);
      return (slot < leaf->mSlotUse) && key_equal( key, leaf->mSlotKey[ slot])
         ? const_iterator( leaf, slot) : end();
   } // btree<>::find

   /// Tries to locate a key in the B+ tree and returns the number of
   /// identical key entries found.
   size_type count( const key_type& key) const
   {
      const Node*  n = mpRoot;
      if (n == nullptr)
         return 0;

      while (!n->isleafnode())
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);
         const int         slot = find_lower( inner, key);

         n = inner->mChildId[ slot];
      }

      const LeafNode*  leaf = static_cast< const LeafNode*>( n);
      int              slot = find_lower( leaf, key);
      size_type        num = 0;

      while ((leaf != nullptr) && (slot < leaf->mSlotUse)
             && key_equal( key, leaf->mSlotKey[ slot]))
      {
         ++num;
         if (++slot >= leaf->mSlotUse)
         {
            leaf = leaf->mpNextLeaf;
            slot = 0;
         }
      } // end while

      return num;
   } // btree<>::count

   /// Searches the B+ tree and returns an iterator to the first pair
   /// equal to or greater than key, or end() if all keys are smaller.
   iterator lower_bound( const key_type& key)
   {
      const LeafNode*  leaf = findLeaf( key);
      if (leaf == nullptr)
         return end();

      const int  slot = find_lower( leaf, key);
      return iterator( const_cast< LeafNode*>( leaf), slot);
   } // btree<>::lower_bound

   /// Searches the B+ tree and returns a constant iterator to the
   /// first pair equal to or greater than key, or end() if all keys
   /// are smaller.
   const_iterator lower_bound( const key_type& key) const
   {
      const LeafNode*  leaf = findLeaf( key);
      if (leaf == nullptr)
         return end();

      const int  slot = find_lower( leaf, key);
      return const_iterator( leaf, slot);
   } // btree<>::lower_bound

   /// Searches the B+ tree and returns an iterator to the first pair
   /// greater than key, or end() if all keys are smaller or equal.
   iterator upper_bound( const key_type& key)
   {
      Node*  n = mpRoot;
      if (n == nullptr)
         return end();

      while (!n->isleafnode())
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);
         const int         slot = find_upper( inner, key);

         n = inner->mChildId[ slot];
      }

      LeafNode*  leaf = static_cast< LeafNode*>( n);
      const int  slot = find_upper( leaf, key);
      return iterator( leaf, slot);
   }

   /// Searches the B+ tree and returns a constant iterator to the
   /// first pair greater than key, or end() if all keys are smaller
   /// or equal.
   const_iterator upper_bound( const key_type& key) const
   {
      const Node*  n = mpRoot;
      if (n == nullptr)
         return end();

      while (!n->isleafnode())
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);
         const int         slot = find_upper( inner, key);

         n = inner->mChildId[ slot];
      }

      const LeafNode*  leaf = static_cast< const LeafNode*>( n);
      const int        slot = find_upper( leaf, key);
      return const_iterator(leaf, slot);
   }

   /// Searches the B+ tree and returns both lower_bound() and upper_bound().
   std::pair< iterator, iterator> equal_range( const key_type& key)
   {
      return std::pair< iterator, iterator>( lower_bound( key),
         upper_bound( key));
   }

   /// Searches the B+ tree and returns both lower_bound() and upper_bound().
   std::pair< const_iterator, const_iterator>
      equal_range( const key_type& key) const
   {
      return std::pair< const_iterator, const_iterator>( lower_bound( key),
         upper_bound( key));
   }

public:
   // B+ Tree Object Comparison Functions

   /// Equality relation of B+ trees of the same type. B+ trees of the same
   /// size and equal elements (both key and data) are considered
   /// equal. Beware of the random ordering of duplicate keys.
   bool operator ==( const btree_self& other) const
   {
      return (size() == other.size())
             && std::equal( begin(), end(), other.begin());
   }

   /// Inequality relation. Based on operator==.
   bool operator !=( const btree_self& other) const
   {
      return !(*this == other);
   }

   /// Total ordering relation of B+ trees of the same type. It uses
   /// std::lexicographical_compare() for the actual comparison of elements.
   bool operator <( const btree_self& other) const
   {
      return std::lexicographical_compare( begin(), end(), other.begin(),
         other.end());
   }

   /// Greater relation. Based on operator<.
   bool operator >( const btree_self& other) const
   {
      return other < *this;
   }

   /// Less-equal relation. Based on operator<.
   bool operator <=( const btree_self& other) const
   {
      return !(other < *this);
   }

   /// Greater-equal relation. Based on operator<.
   bool operator >=( const btree_self& other) const
   {
      return !(*this < other);
   }

public:
   /// Fast Copy: Assign Operator and Copy Constructors

   /// Assignment operator. All the key/data pairs are copied
   btree_self& operator =( const btree_self& other)
   {
      if (this != &other)
      {
         clear();

         mKeyLess = other.key_comp();
         mAllocator = other.get_allocator();

         if (other.size() != 0)
         {
            mStats.mLeaves = mStats.mInnerNodes = 0;
            if (other.mpRoot != nullptr)
            {
               mpRoot = copy_recursive( other.mpRoot);
            }
            mStats = other.mStats;
         }

         if (SelfVerify)
            verify();
      }
      return *this;
   }

   /// Copy constructor. The newly initialized B+ tree object will contain a
   /// copy of all key/data pairs.
   btree( const btree_self& other)
       : mStats( other.mStats),
         mKeyLess( other.key_comp()),
         mAllocator( other.get_allocator())
   {
      if (size() > 0)
      {
         mStats.mLeaves = mStats.mInnerNodes = 0;
         if (other.mpRoot)
         {
            mpRoot = copy_recursive( other.mpRoot);
         }
         if (SelfVerify)
            verify();
      }
   }

private:
   /// Recursively copy nodes from another B+ tree object
   struct Node* copy_recursive( const Node* n)
   {
      if (n->isleafnode())
      {
         const LeafNode*  leaf = static_cast< const LeafNode*>( n);
         LeafNode*        newleaf = allocate_leaf();

         newleaf->mSlotUse = leaf->mSlotUse;
         std::copy( leaf->mSlotKey, leaf->mSlotKey + leaf->mSlotUse,
            newleaf->mSlotKey);
         std::copy( leaf->mSlotData, leaf->mSlotData + leaf->mSlotUse,
            newleaf->mSlotData);

         if (mpHeadLeaf == nullptr)
         {
            mpHeadLeaf = mpTailLeaf = newleaf;
            newleaf->mpPrevLeaf = newleaf->mpNextLeaf = nullptr;
         } else
         {
            newleaf->mpPrevLeaf = mpTailLeaf;
            mpTailLeaf->mpNextLeaf = newleaf;
            mpTailLeaf = newleaf;
         }

         return newleaf;
      } // end if

      const InnerNode*  inner = static_cast< const InnerNode*>( n);
      InnerNode*        new_inner = allocate_inner( inner->mLevel);

      new_inner->mSlotUse = inner->mSlotUse;
      std::copy( inner->mSlotKey, inner->mSlotKey + inner->mSlotUse,
         new_inner->mSlotKey);

      for (unsigned short slot = 0; slot <= inner->mSlotUse; ++slot)
      {
         new_inner->mChildId[ slot] = copy_recursive( inner->mChildId[ slot]);
      }

      return new_inner;
   }

public:
   using insert_result_t = std::pair< iterator, bool>;

   // Public Insertion Functions

   /// Attempt to insert a key/data pair into the B+ tree. If the tree does not
   /// allow duplicate keys, then the insert may fail if it is already
   /// present.
   insert_result_t insert( const pair_type& x)
   {
      return insert_start( x.first, x.second);
   }

   /// Attempt to insert a key/data pair into the B+ tree. Beware that if
   /// key_type == data_type, then the template iterator insert() is called
   /// instead. If the tree does not allow duplicate keys, then the insert may
   /// fail if it is already present.
   insert_result_t insert( const key_type& key, const data_type& data)
   {
      return insert_start( key, data);
   }

   /// Attempt to insert a key/data pair into the B+ tree. This function is the
   /// same as the other insert, however if key_type == data_type then the
   /// non-template function cannot be called. If the tree does not allow
   /// duplicate keys, then the insert may fail if it is already present.
   insert_result_t insert2( const key_type& key, const data_type& data)
   {
      return insert_start( key, data);
   }

   /// Attempt to insert a key/data pair into the B+ tree. The iterator hint
   /// is currently ignored by the B+ tree insertion routine.
   iterator insert( iterator /* hint */, const pair_type& x)
   {
      return insert_start( x.first, x.second).first;
   }

   /// Attempt to insert a key/data pair into the B+ tree. The iterator hint is
   /// currently ignored by the B+ tree insertion routine.
   iterator insert2( iterator /* hint */, const key_type& key,
      const data_type& data)
   {
      return insert_start( key, data).first;
   }

   /// Attempt to insert the range [first,last) of value_type pairs into the B+
   /// tree. Each key/data pair is inserted individually.
   template< typename InputIterator>
      void insert( InputIterator first, InputIterator last)
   {
      InputIterator  iter = first;
      while (iter != last)
      {
         insert( *iter);
         ++iter;
      }
   }

private:
   // Private Insertion Functions

   /// Start the insertion descent at the current root and handle root
   /// splits. Returns true if the item was inserted
   insert_result_t insert_start( const key_type& key, const data_type& value)
   {
      Node*     newchild = nullptr;
      key_type  newkey = key_type();

      if (mpRoot == nullptr)
      {
         mpRoot = mpHeadLeaf = mpTailLeaf = allocate_leaf();
      }

      auto  r = insert_descend( mpRoot, key, value, &newkey, &newchild);

      if (newchild != nullptr)
      {
         InnerNode*  newroot = allocate_inner( mpRoot->mLevel + 1);
         newroot->mSlotKey[ 0] = newkey;

         newroot->mChildId[ 0] = mpRoot;
         newroot->mChildId[ 1] = newchild;

         newroot->mSlotUse = 1;

         mpRoot = newroot;
      }

      // increment itemcount if the item was inserted
      if (r.second) ++mStats.mItemCount;

#ifdef BTREE_DEBUG
      if (Debug)
         print( std::cout);
#endif

      if (SelfVerify)
      {
         verify();
         BTREE_ASSERT( exists( key));
      }

      return r;
   } // btree<>::insert_start

   /// Insert an item into the B+ tree.
   ///
   /// Descend down the nodes to a leaf, insert the key/data pair in a free
   /// slot. If the node overflows, then it must be split and the new split node
   /// inserted into the parent. Unroll / this splitting up to the root.
   insert_result_t
      insert_descend( Node* n, const key_type& key, const data_type& value,
         key_type* splitkey, Node** splitnode)
   {
      if (!n->isleafnode())
      {
         InnerNode*  inner = static_cast< InnerNode*>( n);
         key_type    newkey = key_type();
         Node*       newchild = nullptr;
         int         slot = find_lower( inner, key);

         BTREE_PRINT( "btree::insert_descend into " << inner->mChildId[ slot]
            << std::endl);

         auto  r = insert_descend( inner->mChildId[ slot], key, value, &newkey,
            &newchild);

         if (newchild != nullptr)
         {
            BTREE_PRINT("btree::insert_descend newchild with key " << newkey
               << " node " << newchild << " at slot " << slot << std::endl);

            if (inner->isfull())
            {
               split_inner_node( inner, splitkey, splitnode, slot);

               BTREE_PRINT( "btree::insert_descend done split_inner: putslot: "
                  << slot << " putkey: " << newkey << " upkey: " << *splitkey
                  << std::endl);

#ifdef BTREE_DEBUG
               if (Debug)
               {
                  print_node( std::cout, inner);
                  print_node( std::cout, *splitnode);
               }
#endif

               // check if insert slot is in the split sibling node
               BTREE_PRINT("btree::insert_descend switch: " << slot << " > "
                  << inner->mSlotUse+1 << std::endl);

               if (slot == inner->mSlotUse + 1
                   && inner->mSlotUse < (*splitnode)->mSlotUse)
               {
                  // special case when the insert slot matches the split
                  // place between the two nodes, then the insert key
                  // becomes the split key.

                  BTREE_ASSERT( inner->mSlotUse + 1 < InnerSlotMax);

                  InnerNode*  splitinner = static_cast< InnerNode*>( *splitnode);

                  // move the split key and it's datum into the left node
                  inner->mSlotKey[ inner->mSlotUse] = *splitkey;
                  inner->mChildId[ inner->mSlotUse + 1] = splitinner->mChildId[ 0];
                  inner->mSlotUse++;

                  // set new split key and move corresponding datum into right node
                  splitinner->mChildId[ 0] = newchild;
                  *splitkey = newkey;

                  return r;
               } // end if
               if (slot >= inner->mSlotUse+1)
               {
                  // in case the insert slot is in the newly create split
                  // node, we reuse the code below.

                  slot -= inner->mSlotUse + 1;
                  inner = static_cast< InnerNode*>( *splitnode);
                  BTREE_PRINT( "btree::insert_descend switching to splitted node "
                     << inner << " slot " << slot <<std::endl);
               }
            }

            // put pointer to child node into correct slot
            BTREE_ASSERT(slot >= 0 && slot <= inner->mSlotUse);

            int i = inner->mSlotUse;

            while (i > slot)
            {
               inner->mSlotKey[ i] = inner->mSlotKey[ i - 1];
               inner->mChildId[ i + 1] = inner->mChildId[ i];
               i--;
            }

            inner->mSlotKey[ slot] = newkey;
            inner->mChildId[ slot + 1] = newchild;
            inner->mSlotUse++;
         }

         return r;
      } // end if

      LeafNode*  leaf = static_cast< LeafNode*>( n);
      int        slot = find_lower( leaf, key);

      if (!AllowDuplicates && (slot < leaf->mSlotUse)
          && key_equal( key, leaf->mSlotKey[ slot]))
      {
         return insert_result_t( iterator( leaf, slot), false);
      }

      if (leaf->isfull())
      {
         split_leaf_node( leaf, splitkey, splitnode);

         // check if insert slot is in the split sibling node
         if (slot >= leaf->mSlotUse)
         {
            slot -= leaf->mSlotUse;
            leaf = static_cast< LeafNode*>( *splitnode);
         }
      }

      // put data item into correct data slot

      int  i = leaf->mSlotUse - 1;
      BTREE_ASSERT( i + 1 < LeafSlotMax);

      while (i >= 0 && mKeyLess( key, leaf->mSlotKey[ i]))
      {
         leaf->mSlotKey[ i + 1] = leaf->mSlotKey[ i];
         leaf->mSlotData[ i + 1] = leaf->mSlotData[ i];
         i--;
      } // end while

      leaf->mSlotKey[ i + 1] = key;
      leaf->mSlotData[ i + 1] = value;
      leaf->mSlotUse++;

      if (splitnode && leaf != *splitnode && slot == leaf->mSlotUse - 1)
      {
         // special case: the node was split, and the insert is at the last slot
         // of the old node. then the splitkey must be updated.
         *splitkey = key;
      } // end if

      return insert_result_t( iterator( leaf, i + 1), true);
   } // btree<>::insert_descend

   /// Split up a leaf node into two equally-filled sibling leaves. Returns
   /// the new nodes and it's insertion key in the two parameters.
   void split_leaf_node( LeafNode* leaf, key_type* new_key, Node** new_leaf)
   {
      BTREE_ASSERT( leaf->isfull());

      const unsigned int  mid = (leaf->mSlotUse >> 1);

      BTREE_PRINT( "btree::split_leaf_node on " << leaf << std::endl);

      LeafNode*  new_leaf_ptr = allocate_leaf();

      new_leaf_ptr->mSlotUse = leaf->mSlotUse - mid;

      new_leaf_ptr->mpNextLeaf = leaf->mpNextLeaf;
      if (new_leaf_ptr->mpNextLeaf == nullptr)
      {
         BTREE_ASSERT( leaf == mpTailLeaf);
         mpTailLeaf = new_leaf_ptr;
      } else
      {
         new_leaf_ptr->mpNextLeaf->mpPrevLeaf = new_leaf_ptr;
      }

      for (unsigned int slot = mid; slot < leaf->mSlotUse; ++slot)
      {
         const unsigned int  ni = slot - mid;
         new_leaf_ptr->mSlotKey[ ni] = leaf->mSlotKey[ slot];
         new_leaf_ptr->mSlotData[ ni] = leaf->mSlotData[ slot];
      }

      leaf->mSlotUse = mid;
      leaf->mpNextLeaf = new_leaf_ptr;
      new_leaf_ptr->mpPrevLeaf = leaf;

      *new_key = leaf->mSlotKey[ leaf->mSlotUse - 1];
      *new_leaf = new_leaf_ptr;
   } // btree<>::split_leaf_node

   /// Split up an inner node into two equally-filled sibling nodes. Returns
   /// the new nodes and it's insertion key in the two parameters. Requires
   /// the slot of the item will be inserted, so the nodes will be the same
   /// size after the insert.
   void split_inner_node( InnerNode* inner, key_type* new_key, Node** new_inner,
      unsigned int addslot)
   {
      BTREE_ASSERT( inner->isfull());

      unsigned int  mid = (inner->mSlotUse >> 1);

      BTREE_PRINT( "btree::split_inner: mid " << mid << " addslot " << addslot
         << std::endl);

      // if the split is uneven and the overflowing item will be put into the
      // larger node, then the smaller split node may underflow
      if (addslot <= mid && mid > inner->mSlotUse - (mid + 1))
          mid--;

      BTREE_PRINT( "btree::split_inner: mid " << mid << " addslot "
         << addslot << std::endl);

      BTREE_PRINT( "btree::split_inner_node on " << inner << " into two nodes "
         << mid << " and " << inner->mSlotUse - (mid + 1) << " sized"
         << std::endl);

      InnerNode*  new_inner_ptr = allocate_inner( inner->mLevel);

      new_inner_ptr->mSlotUse = inner->mSlotUse - (mid + 1);

      for (unsigned int slot = mid + 1; slot < inner->mSlotUse; ++slot)
      {
         const unsigned int  ni = slot - (mid + 1);
         new_inner_ptr->mSlotKey[ ni] = inner->mSlotKey[ slot];
         new_inner_ptr->mChildId[ ni] = inner->mChildId[ slot];
      } // end for

      new_inner_ptr->mChildId[ new_inner_ptr->mSlotUse] = inner->mChildId[ inner->mSlotUse];

      inner->mSlotUse = mid;

      *new_key = inner->mSlotKey[ mid];
      *new_inner = new_inner_ptr;
   } // btree<>::split_inner_node

private:
   // Support Class Encapsulating Deletion Results

   /// Result flags of recursive deletion.
   enum result_flags_t
   {
      /// Deletion successful and no fix-ups necessary.
      btree_ok = 0,

      /// Deletion not successful because key was not found.
      btree_not_found = 1,

      /// Deletion successful, the last key was updated so parent slotkeys
      /// need updates.
      btree_update_lastkey = 2,

      /// Deletion successful, children nodes were merged and the parent
      /// needs to remove the empty node.
      btree_fixmerge = 4
   }; // result_flags_t

   /// B+ tree recursive deletion has much information which is needs to be
   /// passed upward.
   struct result_t
   {
      /// Merged result flags
      result_flags_t  flags;

      /// The key to be updated at the parent's slot
      key_type        lastkey;

      /// Constructor of a result with a specific flag, this can also be used
      /// as for implicit conversion.
      result_t( result_flags_t f = btree_ok)
          : flags( f), lastkey()
      { }

      /// Constructor with a lastkey value.
      result_t( result_flags_t f, const key_type& k)
          : flags( f), lastkey( k)
      { }

      /// Test if this result object has a given flag set.
      bool has( result_flags_t f) const
      {
         return (flags & f) != 0;
      }

      /// Merge two results OR-ing the result flags and overwriting lastkeys.
      result_t& operator |= ( const result_t& other)
      {
         flags = result_flags_t( flags | other.flags);

         // we overwrite existing lastkeys on purpose
         if (other.has( btree_update_lastkey))
            lastkey = other.lastkey;

         return *this;
      }
   }; // result_t

public:
   // Public Erase Functions

   /// Erases one (the first) of the key/data pairs associated with the given
   /// key.
   bool erase_one( const key_type& key)
   {
       BTREE_PRINT( "btree::erase_one(" << key << ") on btree size " << size()
          << std::endl);

       if (SelfVerify)
          verify();

       if (mpRoot == nullptr)
          return false;

       const result_t  result = erase_one_descend( key, mpRoot, nullptr, nullptr,
          nullptr, nullptr, nullptr, 0);

       if (!result.has( btree_not_found))
          --mStats.mItemCount;

#ifdef BTREE_DEBUG
       if (Debug)
          print( std::cout);
#endif
       if (SelfVerify)
          verify();

       return !result.has( btree_not_found);
   }

   /// Erases all the key/data pairs associated with the given key. This is
   /// implemented using erase_one().
   size_type erase( const key_type& key)
   {
      size_type  c = 0;

      while (erase_one( key))
      {
         ++c;
         if (!AllowDuplicates)
            break;
      }

      return c;
   }

   /// Erase the key/data pair referenced by the iterator.
   void erase( iterator iter)
   {
      BTREE_PRINT( "btree::erase_iter(" << iter.mpCurrentNode << ","
         << iter.mCurrentSlot << ") on btree size " << size() << std::endl);

      if (SelfVerify)
         verify();

      if (mpRoot == nullptr)
         return;

      const result_t  result = erase_iter_descend( iter, mpRoot, nullptr, nullptr,
         nullptr, nullptr, nullptr, 0);

      if (!result.has( btree_not_found))
         --mStats.mItemCount;

#ifdef BTREE_DEBUG
      if (Debug)
         print( std::cout);
#endif
      if (SelfVerify)
         verify();
   } // btree<>::erase

#ifdef BTREE_TODO
   /// Erase all key/data pairs in the range [first,last). This function is
   /// currently not implemented by the B+ Tree.
   void erase( iterator /* first */, iterator /* last */)
   {
      abort();
   }
#endif

private:
   // Private Erase Functions

   /// Erase one (the first) key/data pair in the B+ tree matching key.
   ///
   /// Descends down the tree in search of key. During the descent the parent,
   /// left and right siblings and their parents are computed and passed down.
   /// Once the key/data pair is found, it is removed from the leaf. If the leaf
   /// underflows 6 different cases are handled. These cases resolve the
   /// underflow by shifting key/data pairs from adjacent sibling nodes, merging
   /// two sibling nodes or trimming the tree.
   result_t erase_one_descend( const key_type& key,
                               Node* curr,
                               Node* left, Node* right,
                               InnerNode* leftparent, InnerNode* rightparent,
                               InnerNode* parent, unsigned int parentslot)
   {
      if (curr->isleafnode())
      {
         LeafNode*  leaf = static_cast< LeafNode*>( curr);
         LeafNode*  leftleaf = static_cast< LeafNode*>( left);
         LeafNode*  rightleaf = static_cast< LeafNode*>( right);

         const int  slot = find_lower( leaf, key);

         if (slot >= leaf->mSlotUse || !key_equal( key, leaf->mSlotKey[ slot]))
         {
            BTREE_PRINT( "Could not find key " << key << " to erase."
               << std::endl);

            return btree_not_found;
         }

         BTREE_PRINT( "Found key in leaf " << curr << " at slot " << slot
            << std::endl);

         for (int i = slot; i < leaf->mSlotUse - 1; i++)
         {
            leaf->mSlotKey[ i] = leaf->mSlotKey[ i + 1];
            leaf->mSlotData[ i] = leaf->mSlotData[ i + 1];
         }

         leaf->mSlotUse--;

         result_t  myres = btree_ok;

         // if the last key of the leaf was changed, the parent is notified
         // and updates the key of this leaf
         if (slot == leaf->mSlotUse)
         {
            if ((parent != nullptr) && (parentslot < parent->mSlotUse))
            {
               BTREE_ASSERT( parent->mChildId[ parentslot] == curr);
               parent->mSlotKey[ parentslot] = leaf->mSlotKey[ leaf->mSlotUse - 1];
            } else if (leaf->mSlotUse >= 1)
            {
               BTREE_PRINT( "Scheduling lastkeyupdate: key "
                  << leaf->mSlotKey[ leaf->mSlotUse - 1] << std::endl);
               myres |= result_t( btree_update_lastkey,
                  leaf->mSlotKey[ leaf->mSlotUse - 1]);
            } else
            {
               BTREE_ASSERT( leaf == mpRoot);
            }
         } // end if

         if (leaf->isunderflow() && !(leaf == mpRoot && leaf->mSlotUse >= 1))
         {
            // determine what to do about the underflow

            // case : if this empty leaf is the root, then delete all nodes
            // and set root to nullptr.
            if (leftleaf == nullptr && rightleaf == nullptr)
            {
               BTREE_ASSERT( leaf == mpRoot);
               BTREE_ASSERT( leaf->mSlotUse == 0);

               free_node( mpRoot);

               mpRoot = leaf = nullptr;
               mpHeadLeaf = mpTailLeaf = nullptr;

               // will be decremented soon by insert_start()
               BTREE_ASSERT( mStats.mItemCount == 1);
               BTREE_ASSERT( mStats.mLeaves == 0);
               BTREE_ASSERT( mStats.mInnerNodes == 0);

               return btree_ok;
            } // end if

            // case : if both left and right leaves would underflow in case of
            // a shift, then merging is necessary. choose the more local merger
            // with our parent
            if ((leftleaf == nullptr || leftleaf->isfew())
                && (rightleaf == nullptr || rightleaf->isfew()))
            {
               if (leftparent == parent)
                  myres |= merge_leaves( leftleaf, leaf, leftparent);
               else
                  myres |= merge_leaves( leaf, rightleaf, rightparent);
            } else if ((leftleaf != nullptr && leftleaf->isfew())
                       && (rightleaf != nullptr && !rightleaf->isfew()))
            {
               // case : the right leaf has extra data, so balance right with current
               if (rightparent == parent)
                  myres |= shift_left_leaf( leaf, rightleaf, rightparent, parentslot);
               else
                  myres |= merge_leaves( leftleaf, leaf, leftparent);
            } else if ((leftleaf != nullptr && !leftleaf->isfew())
                       && (rightleaf != nullptr && rightleaf->isfew()))
            {
               // case : the left leaf has extra data, so balance left with current
               if (leftparent == parent)
                  shift_right_leaf( leftleaf, leaf, leftparent, parentslot - 1);
               else
                  myres |= merge_leaves( leaf, rightleaf, rightparent);
            } else if (leftparent == rightparent)
            {
               // case : both the leaf and right leaves have extra data and our
               // parent, choose the leaf with more data
               if (leftleaf->mSlotUse <= rightleaf->mSlotUse)
                  myres |= shift_left_leaf( leaf, rightleaf, rightparent, parentslot);
               else
                  shift_right_leaf( leftleaf, leaf, leftparent, parentslot - 1);
            } else if (leftparent == parent)
            {
               shift_right_leaf( leftleaf, leaf, leftparent, parentslot - 1);
            } else
            {
               myres |= shift_left_leaf(leaf, rightleaf, rightparent, parentslot);
            }
         } // end if

         return myres;
      } // end if

      // else !curr->isleafnode()
      InnerNode*  inner = static_cast< InnerNode*>( curr);
      InnerNode*  leftinner = static_cast< InnerNode*>( left);
      InnerNode*  rightinner = static_cast< InnerNode*>( right);

      Node*       myleft = nullptr;
      Node*       myright = nullptr;
      InnerNode*  myleftparent = nullptr;
      InnerNode*  myrightparent = nullptr;

      int  slot = find_lower( inner, key);

      if (slot == 0)
      {
         myleft = (left == nullptr) ? nullptr : (static_cast< InnerNode*>( left))->mChildId[ left->mSlotUse - 1];
         myleftparent = leftparent;
      } else
      {
         myleft = inner->mChildId[ slot - 1];
         myleftparent = inner;
      }

      if (slot == inner->mSlotUse)
      {
         myright = (right == nullptr) ? nullptr : (static_cast< InnerNode*>( right))->mChildId[ 0];
         myrightparent = rightparent;
      } else
      {
         myright = inner->mChildId[ slot + 1];
         myrightparent = inner;
      }

      BTREE_PRINT( "erase_one_descend into " << inner->mChildId[slot]
         << std::endl);

      const result_t result = erase_one_descend( key,
                                                 inner->mChildId[ slot],
                                                 myleft, myright,
                                                 myleftparent, myrightparent,
                                                 inner, slot);

      result_t  myres = btree_ok;

      if (result.has( btree_not_found))
      {
         return result;
      }

      if (result.has( btree_update_lastkey))
      {
         if ((parent != nullptr) && parentslot < parent->mSlotUse)
         {
             BTREE_PRINT( "Fixing lastkeyupdate: key " << result.lastkey
                << " into parent " << parent << " at parentslot " << parentslot
                << std::endl);

             BTREE_ASSERT( parent->mChildId[ parentslot] == curr);
             parent->mSlotKey[ parentslot] = result.lastkey;
         } else
         {
            BTREE_PRINT( "Forwarding lastkeyupdate: key " << result.lastkey
               << std::endl);
            myres |= result_t( btree_update_lastkey, result.lastkey);
         }
      }

      if (result.has( btree_fixmerge))
      {
         // either the current node or the next is empty and should be removed
         if (inner->mChildId[ slot]->mSlotUse != 0)
            slot++;

         // this is the child slot invalidated by the merge
         BTREE_ASSERT( inner->mChildId[ slot]->mSlotUse == 0);

         free_node( inner->mChildId[ slot]);

         for (int i = slot; i < inner->mSlotUse; i++)
         {
            inner->mSlotKey[ i - 1] = inner->mSlotKey[ i];
            inner->mChildId[ i] = inner->mChildId[ i + 1];
         }
         inner->mSlotUse--;

         if (inner->mLevel == 1)
         {
            // fix split key for children leaves
            slot--;
            LeafNode*  child = static_cast< LeafNode*>( inner->mChildId[ slot]);
            inner->mSlotKey[ slot] = child->mSlotKey[ child->mSlotUse - 1];
         }
      }

      if (inner->isunderflow() && !(inner == mpRoot && inner->mSlotUse >= 1))
      {
         // case: the inner node is the root and has just one child. that child
         // becomes the new root
         if (leftinner == nullptr && rightinner == nullptr)
         {
            BTREE_ASSERT( inner == mpRoot);
            BTREE_ASSERT( inner->mSlotUse == 0);

            mpRoot = inner->mChildId[ 0];

            inner->mSlotUse = 0;
            free_node( inner);

            return btree_ok;
         } // end if

         // case : if both left and right leaves would underflow in case of
         // a shift, then merging is necessary. choose the more local merger
         // with our parent
         if ((leftinner == nullptr || leftinner->isfew())
             && (rightinner == nullptr || rightinner->isfew()))
         {
            if (leftparent == parent)
                myres |= merge_inner( leftinner, inner, leftparent, parentslot - 1);
            else
                myres |= merge_inner( inner, rightinner, rightparent, parentslot);
         } else if ((leftinner != nullptr && leftinner->isfew())
                    && (rightinner != nullptr && !rightinner->isfew()))
         {
            // case : the right leaf has extra data, so balance right with current
            if (rightparent == parent)
               shift_left_inner( inner, rightinner, rightparent, parentslot);
            else
               myres |= merge_inner( leftinner, inner, leftparent, parentslot - 1);
         } else if ((leftinner != nullptr && !leftinner->isfew())
                    && (rightinner != nullptr && rightinner->isfew()))
         {
            // case : the left leaf has extra data, so balance left with current
            if (leftparent == parent)
               shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
            else
               myres |= merge_inner( inner, rightinner, rightparent, parentslot);
         } else if (leftparent == rightparent)
         {
            // case : both the leaf and right leaves have extra data and our
            // parent, choose the leaf with more data
            if (leftinner->mSlotUse <= rightinner->mSlotUse)
               shift_left_inner( inner, rightinner, rightparent, parentslot);
            else
               shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
         } else if (leftparent == parent)
         {
            shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
         } else
         {
            shift_left_inner( inner, rightinner, rightparent, parentslot);
         }
      }

      return myres;
   } // btree<>::erase_one_descend

   /// Erase one key/data pair referenced by an iterator in the B+ * tree.
   ///
   /// Descends down the tree in search of an iterator. During the descent the
   /// parent, left and right siblings and their parents are computed and
   /// passed down. The difficulty is that the iterator contains only a pointer
   /// to a leaf_node, which means that this function must do a recursive depth
   /// first search for that leaf node in the subtree containing all pairs of
   /// the same key. This subtree can be very large, even the whole tree,
   /// though in practice it would not make sense to have so many duplicate
   /// keys.
   ///
   /// Once the referenced key/data pair is found, it is removed from the leaf
   /// and the same underflow cases are handled as in erase_one_descend.
   result_t erase_iter_descend( const iterator& iter,
                                Node* curr,
                                Node* left, Node* right,
                                InnerNode* leftparent, InnerNode* rightparent,
                                InnerNode* parent, unsigned int parentslot)
   {
      if (curr->isleafnode())
      {
         LeafNode*  leaf = static_cast< LeafNode*>( curr);
         LeafNode*  leftleaf = static_cast< LeafNode*>( left);
         LeafNode*  rightleaf = static_cast< LeafNode*>( right);

         // if this is not the correct leaf, get next step in recursive
         // search
         if (leaf != iter.mpCurrentNode)
         {
            return btree_not_found;
         }

         if (iter.mCurrentSlot >= leaf->mSlotUse)
         {
            BTREE_PRINT( "Could not find iterator (" << iter.mpCurrentNode << ","
               << iter.mCurrentSlot << ") to erase. Invalid leaf node?"
               << std::endl);

            return btree_not_found;
         }

         const int  slot = iter.mCurrentSlot;

         BTREE_PRINT( "Found iterator in leaf " << curr << " at slot " << slot
            << std::endl);

         for (int i = slot; i < leaf->mSlotUse - 1; i++)
         {
            leaf->mSlotKey[ i] = leaf->mSlotKey[ i + 1];
            leaf->mSlotData[ i] = leaf->mSlotData[ i + 1];
         }
         leaf->mSlotUse--;

         result_t  myres = btree_ok;

         // if the last key of the leaf was changed, the parent is notified
         // and updates the key of this leaf
         if (slot == leaf->mSlotUse)
         {
            if ((parent != nullptr) && parentslot < parent->mSlotUse)
            {
               BTREE_ASSERT( parent->mChildId[ parentslot] == curr);
               parent->mSlotKey[ parentslot] = leaf->mSlotKey[ leaf->mSlotUse - 1];
            } else if (leaf->mSlotUse >= 1)
            {
               BTREE_PRINT( "Scheduling lastkeyupdate: key "
                  << leaf->mSlotKey[leaf->mSlotUse - 1] << std::endl);
               myres |= result_t( btree_update_lastkey,
                  leaf->mSlotKey[ leaf->mSlotUse - 1]);
            } else
            {
               BTREE_ASSERT( leaf == mpRoot);
            }
         }

         if (leaf->isunderflow() && !(leaf == mpRoot && leaf->mSlotUse >= 1))
         {
            // determine what to do about the underflow

            // case : if this empty leaf is the root, then delete all nodes
            // and set root to NULL.
            if (leftleaf == nullptr && rightleaf == nullptr)
            {
               BTREE_ASSERT( leaf == mpRoot);
               BTREE_ASSERT( leaf->mSlotUse == 0);

               free_node( mpRoot);

               mpRoot = leaf = nullptr;
               mpHeadLeaf = mpTailLeaf = nullptr;

               // will be decremented soon by insert_start()
               BTREE_ASSERT( mStats.mItemCount == 1);
               BTREE_ASSERT( mStats.mLeaves == 0);
               BTREE_ASSERT( mStats.mInnerNodes == 0);

               return btree_ok;
            } // end if

            // case : if both left and right leaves would underflow in case of
            // a shift, then merging is necessary. choose the more local merger
            // with our parent
            if ((leftleaf == nullptr || leftleaf->isfew())
                && (rightleaf == nullptr || rightleaf->isfew()))
            {
               if (leftparent == parent)
                  myres |= merge_leaves( leftleaf, leaf, leftparent);
               else
                  myres |= merge_leaves( leaf, rightleaf, rightparent);
            } else if ((leftleaf != nullptr && leftleaf->isfew()) &&
                       (rightleaf != nullptr && !rightleaf->isfew()))
            {
               // case : the right leaf has extra data, so balance right with current
               if (rightparent == parent)
                  myres |= shift_left_leaf( leaf, rightleaf, rightparent, parentslot);
               else
                  myres |= merge_leaves( leftleaf, leaf, leftparent);
            } else if ((leftleaf != nullptr && !leftleaf->isfew())
                       && (rightleaf != nullptr && rightleaf->isfew()))
            {
               // case : the left leaf has extra data, so balance left with current
               if (leftparent == parent)
                  shift_right_leaf( leftleaf, leaf, leftparent, parentslot - 1);
               else
                  myres |= merge_leaves( leaf, rightleaf, rightparent);
            } else if (leftparent == rightparent)
            {
               // case : both the leaf and right leaves have extra data and our
               // parent, choose the leaf with more data
               if (leftleaf->mSlotUse <= rightleaf->mSlotUse)
                  myres |= shift_left_leaf( leaf, rightleaf, rightparent, parentslot);
               else
                  shift_right_leaf( leftleaf, leaf, leftparent, parentslot - 1);
            } else if (leftparent == parent)
            {
               shift_right_leaf(leftleaf, leaf, leftparent, parentslot - 1);
            } else
            {
               myres |= shift_left_leaf( leaf, rightleaf, rightparent, parentslot);
            }
         } // end if

         return myres;
      } // end if

      // else !curr->isleafnode()
      InnerNode*  inner = static_cast< InnerNode*>( curr);
      InnerNode*  leftinner = static_cast< InnerNode*>( left);
      InnerNode*  rightinner = static_cast< InnerNode*>( right);

      // find first slot below which the searched iterator might be
      // located.

      result_t  result;
      int       slot = find_lower(inner, iter.key());

      while (slot <= inner->mSlotUse)
      {
         Node*       myleft = nullptr;
         Node*       myright = nullptr;
         InnerNode*  myleftparent = nullptr;
         InnerNode*  myrightparent = nullptr;

         if (slot == 0)
         {
            myleft = (left == nullptr) ? nullptr : (static_cast< InnerNode*>( left))->mChildId[ left->mSlotUse - 1];
            myleftparent = leftparent;
         } else
         {
            myleft = inner->mChildId[ slot - 1];
            myleftparent = inner;
         }

         if (slot == inner->mSlotUse)
         {
            myright = (right == nullptr) ? nullptr : (static_cast< InnerNode*>( right))->mChildId[ 0];
            myrightparent = rightparent;
         } else
         {
            myright = inner->mChildId[ slot + 1];
            myrightparent = inner;
         }

         BTREE_PRINT( "erase_iter_descend into " << inner->mChildId[ slot]
            << std::endl);

         result = erase_iter_descend( iter,
                                      inner->mChildId[ slot],
                                      myleft, myright,
                                      myleftparent, myrightparent,
                                      inner, slot);

         if (!result.has( btree_not_found))
            break;

         // continue recursive search for leaf on next slot

         if (slot < inner->mSlotUse && mKeyLess( inner->mSlotKey[ slot],iter.key()))
            return btree_not_found;

         ++slot;
      } // end while

      if (slot > inner->mSlotUse)
         return btree_not_found;

      result_t myres = btree_ok;

      if (result.has(btree_update_lastkey))
      {
         if ((parent != nullptr) && (parentslot < parent->mSlotUse))
         {
             BTREE_PRINT( "Fixing lastkeyupdate: key " << result.lastkey
                << " into parent " << parent << " at parentslot " << parentslot
                << std::endl);

             BTREE_ASSERT( parent->mChildId[ parentslot] == curr);
             parent->mSlotKey[ parentslot] = result.lastkey;
         } else
         {
            BTREE_PRINT( "Forwarding lastkeyupdate: key " << result.lastkey
               << std::endl);
            myres |= result_t( btree_update_lastkey, result.lastkey);
         }
      }

      if (result.has(btree_fixmerge))
      {
         // either the current node or the next is empty and should be removed
         if (inner->mChildId[ slot]->mSlotUse != 0)
             slot++;

         // this is the child slot invalidated by the merge
         BTREE_ASSERT( inner->mChildId[slot]->mSlotUse == 0);

         free_node(inner->mChildId[slot]);

         for (int i = slot; i < inner->mSlotUse; i++)
         {
            inner->mSlotKey[ i - 1] = inner->mSlotKey[ i];
            inner->mChildId[ i] = inner->mChildId[ i + 1];
         }
         inner->mSlotUse--;

         if (inner->mLevel == 1)
         {
            // fix split key for children leaves
            slot--;
            LeafNode*  child = static_cast< LeafNode*>( inner->mChildId[ slot]);
            inner->mSlotKey[ slot] = child->mSlotKey[ child->mSlotUse - 1];
         }
      }

      if (inner->isunderflow() && !(inner == mpRoot && inner->mSlotUse >= 1))
      {
         // case: the inner node is the root and has just one child. that
         // child becomes the new root
         if (leftinner == nullptr && rightinner == nullptr)
         {
            BTREE_ASSERT( inner == mpRoot);
            BTREE_ASSERT( inner->mSlotUse == 0);

            mpRoot = inner->mChildId[ 0];

            inner->mSlotUse = 0;
            free_node( inner);

            return btree_ok;
         } // end if

         // case : if both left and right leaves would underflow in case of
         // a shift, then merging is necessary. choose the more local merger
         // with our parent
         if ((leftinner == nullptr || leftinner->isfew())
             && (rightinner == nullptr || rightinner->isfew()))
         {
            if (leftparent == parent)
               myres |= merge_inner( leftinner, inner, leftparent, parentslot - 1);
            else
               myres |= merge_inner( inner, rightinner, rightparent, parentslot);
         } else if ((leftinner != nullptr && leftinner->isfew())
                    && (rightinner != nullptr && !rightinner->isfew()))
         {
            // case : the right leaf has extra data, so balance right with current
            if (rightparent == parent)
               shift_left_inner( inner, rightinner, rightparent, parentslot);
            else
               myres |= merge_inner( leftinner, inner, leftparent, parentslot - 1);
         } else if ((leftinner != nullptr && !leftinner->isfew())
                    && (rightinner != nullptr && rightinner->isfew()))
         {
            // case : the left leaf has extra data, so balance left with current
            if (leftparent == parent)
               shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
            else
               myres |= merge_inner( inner, rightinner, rightparent, parentslot);
         } else if (leftparent == rightparent)
         {
            // case : both the leaf and right leaves have extra data and our
            // parent, choose the leaf with more data
            if (leftinner->mSlotUse <= rightinner->mSlotUse)
               shift_left_inner( inner, rightinner, rightparent, parentslot);
            else
               shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
         } else if (leftparent == parent)
         {
            shift_right_inner( leftinner, inner, leftparent, parentslot - 1);
         } else
         {
            shift_left_inner( inner, rightinner, rightparent, parentslot);
         }
      } // end if

      return myres;
   } // btree<>::erase_iter_descend

   /// Merge two leaf nodes. The function moves all key/data pairs from right
   /// to left and sets right's mSlotUse to zero. The right slot is then
   /// removed by the calling parent node.
   result_t merge_leaves( LeafNode* left, LeafNode* right, InnerNode* parent)
   {
      BTREE_PRINT( "Merge leaf nodes " << left << " and " << right
         << " with common parent " << parent << "." << std::endl);
      (void)parent; // ???

      BTREE_ASSERT( left->isleafnode() && right->isleafnode());
      BTREE_ASSERT( parent->mLevel == 1);

      BTREE_ASSERT( left->mSlotUse + right->mSlotUse < LeafSlotMax);

      for (unsigned int i = 0; i < right->mSlotUse; i++)
      {
         left->mSlotKey[ left->mSlotUse + i] = right->mSlotKey[ i];
         left->mSlotData[ left->mSlotUse + i] = right->mSlotData[ i];
      }
      left->mSlotUse += right->mSlotUse;

      left->mpNextLeaf = right->mpNextLeaf;
      if (left->mpNextLeaf)
         left->mpNextLeaf->mpPrevLeaf = left;
      else
         mpTailLeaf = left;

      right->mSlotUse = 0;

      return btree_fixmerge;
   }

   /// Merge two inner nodes. The function moves all key/childid pairs from
   /// right to left and sets right's mSlotUse to zero. The right slot is then
   /// removed by the calling parent node.
   static result_t merge_inner( InnerNode* left, InnerNode* right,
      InnerNode* parent, unsigned int parentslot)
   {
      BTREE_PRINT( "Merge inner nodes " << left << " and " << right
         << " with common parent " << parent << "." << std::endl);

      BTREE_ASSERT( left->mLevel == right->mLevel);
      BTREE_ASSERT( parent->mLevel == left->mLevel + 1);

      BTREE_ASSERT( parent->mChildId[ parentslot] == left);

      BTREE_ASSERT( left->mSlotUse + right->mSlotUse < InnerSlotMax);

      if (SelfVerify)
      {
         // find the left node's slot in the parent's children
         unsigned int  leftslot = 0;
         while (leftslot <= parent->mSlotUse && parent->mChildId[ leftslot] != left)
            ++leftslot;

         BTREE_ASSERT( leftslot < parent->mSlotUse);
         BTREE_ASSERT( parent->mChildId[ leftslot] == left);
         BTREE_ASSERT( parent->mChildId[ leftslot + 1] == right);

         BTREE_ASSERT( parentslot == leftslot);
      }

      // retrieve the decision key from parent
      left->mSlotKey[ left->mSlotUse] = parent->mSlotKey[ parentslot];
      left->mSlotUse++;

      // copy over keys and children from right
      for (unsigned int i = 0; i < right->mSlotUse; i++)
      {
         left->mSlotKey[ left->mSlotUse + i] = right->mSlotKey[ i];
         left->mChildId[ left->mSlotUse + i] = right->mChildId[ i];
      }
      left->mSlotUse += right->mSlotUse;

      left->mChildId[ left->mSlotUse] = right->mChildId[ right->mSlotUse];

      right->mSlotUse = 0;

      return btree_fixmerge;
   } // btree<>::merge_inner

   /// Balance two leaf nodes. The function moves key/data pairs from right to
   /// left so that both nodes are equally filled. The parent node is updated
   /// if possible.
   static result_t shift_left_leaf( LeafNode* left, LeafNode* right,
      InnerNode* parent, unsigned int parentslot)
   {
      BTREE_ASSERT( left->isleafnode() && right->isleafnode());
      BTREE_ASSERT( parent->mLevel == 1);

      BTREE_ASSERT( left->mpNextLeaf == right);
      BTREE_ASSERT( left == right->mpPrevLeaf);

      BTREE_ASSERT( left->mSlotUse < right->mSlotUse);
      BTREE_ASSERT( parent->mChildId[ parentslot] == left);

      const unsigned int  shiftnum = (right->mSlotUse - left->mSlotUse) >> 1;

      BTREE_PRINT( "Shifting (leaf) " << shiftnum << " entries to left "
         << left << " from right " << right << " with common parent "
         << parent << "." << std::endl);

      BTREE_ASSERT( left->mSlotUse + shiftnum < LeafSlotMax);

      // copy the first items from the right node to the last slot in the left node.
      for (unsigned int i = 0; i < shiftnum; i++)
      {
         left->mSlotKey[ left->mSlotUse + i] = right->mSlotKey[ i];
         left->mSlotData[ left->mSlotUse + i] = right->mSlotData[ i];
      }
      left->mSlotUse += shiftnum;

      // shift all slots in the right node to the left

      right->mSlotUse -= shiftnum;
      for (int i = 0; i < right->mSlotUse; i++)
      {
         right->mSlotKey[ i] = right->mSlotKey[ i + shiftnum];
         right->mSlotData[ i] = right->mSlotData[ i + shiftnum];
      }

      // fixup parent
      if (parentslot < parent->mSlotUse)
      {
         parent->mSlotKey[ parentslot] = left->mSlotKey[ left->mSlotUse - 1];
         return btree_ok;
      } // end if

      // the update is further up the tree
      return result_t( btree_update_lastkey, left->mSlotKey[ left->mSlotUse - 1]);
   } // btree<>::shift_left_leaf

   /// Balance two inner nodes. The function moves key/data pairs from right
   /// to left so that both nodes are equally filled. The parent node is
   /// updated if possible.
   static void shift_left_inner( InnerNode* left, InnerNode* right,
      InnerNode* parent, unsigned int parentslot)
   {
      BTREE_ASSERT( left->mLevel == right->mLevel);
      BTREE_ASSERT( parent->mLevel == left->mLevel + 1);

      BTREE_ASSERT( left->mSlotUse < right->mSlotUse);
      BTREE_ASSERT( parent->mChildId[ parentslot] == left);

      const unsigned int  shiftnum = (right->mSlotUse - left->mSlotUse) >> 1;

      BTREE_PRINT( "Shifting (inner) " << shiftnum << " entries to left "
         << left << " from right " << right << " with common parent " << parent
         << "." << std::endl);

      BTREE_ASSERT( left->mSlotUse + shiftnum < InnerSlotMax);

      if (SelfVerify)
      {
         // find the left node's slot in the parent's children and compare to parentslot

         unsigned int  leftslot = 0;
         while (leftslot <= parent->mSlotUse
                && parent->mChildId[ leftslot] != left)
            ++leftslot;

         BTREE_ASSERT( leftslot < parent->mSlotUse);
         BTREE_ASSERT( parent->mChildId[ leftslot] == left);
         BTREE_ASSERT( parent->mChildId[ leftslot + 1] == right);

         BTREE_ASSERT( leftslot == parentslot);
      } // end if

      // copy the parent's decision slotkey and childid to the first new key on the left
      left->mSlotKey[ left->mSlotUse] = parent->mSlotKey[ parentslot];
      left->mSlotUse++;

      // copy the other items from the right node to the last slots in the left node.
      for (unsigned int i = 0; i < shiftnum - 1; i++)
      {
         left->mSlotKey[ left->mSlotUse + i] = right->mSlotKey[ i];
         left->mChildId[ left->mSlotUse + i] = right->mChildId[ i];
      }
      left->mSlotUse += shiftnum - 1;

      // fixup parent
      parent->mSlotKey[ parentslot] = right->mSlotKey[ shiftnum - 1];
      // last pointer in left
      left->mChildId[ left->mSlotUse] = right->mChildId[ shiftnum - 1];

      // shift all slots in the right node

      right->mSlotUse -= shiftnum;
      for (int i = 0; i < right->mSlotUse; i++)
      {
         right->mSlotKey[ i] = right->mSlotKey[ i + shiftnum];
         right->mChildId[ i] = right->mChildId[ i + shiftnum];
      }
      right->mChildId[ right->mSlotUse] = right->mChildId[ right->mSlotUse + shiftnum];
   } // btree<>::shift_left_inner

   /// Balance two leaf nodes. The function moves key/data pairs from left to
   /// right so that both nodes are equally filled. The parent node is updated
   /// if possible.
   static void shift_right_leaf( LeafNode* left, LeafNode* right,
      InnerNode* parent, unsigned int parentslot)
   {
      BTREE_ASSERT( left->isleafnode() && right->isleafnode());
      BTREE_ASSERT( parent->mLevel == 1);

      BTREE_ASSERT( left->mpNextLeaf == right);
      BTREE_ASSERT( left == right->mpPrevLeaf);
      BTREE_ASSERT( parent->mChildId[ parentslot] == left);

      BTREE_ASSERT( left->mSlotUse > right->mSlotUse);

      unsigned int  shiftnum = (left->mSlotUse - right->mSlotUse) >> 1;

      BTREE_PRINT( "Shifting (leaf) " << shiftnum << " entries to right "
         << right << " from left " << left << " with common parent " << parent
         << "." << std::endl);

      if (SelfVerify)
      {
         // find the left node's slot in the parent's children
         unsigned int  leftslot = 0;
         while (leftslot <= parent->mSlotUse
                && parent->mChildId[ leftslot] != left)
            ++leftslot;

         BTREE_ASSERT( leftslot < parent->mSlotUse);
         BTREE_ASSERT( parent->mChildId[ leftslot] == left);
         BTREE_ASSERT( parent->mChildId[ leftslot+1] == right);

         BTREE_ASSERT( leftslot == parentslot);
      } // end if

      // shift all slots in the right node

      BTREE_ASSERT( right->mSlotUse + shiftnum < LeafSlotMax);

      for (int i = right->mSlotUse-1; i >= 0; i--)
      {
         right->mSlotKey[ i + shiftnum] = right->mSlotKey[ i];
         right->mSlotData[ i + shiftnum] = right->mSlotData[ i];
      }
      right->mSlotUse += shiftnum;

      // copy the last items from the left node to the first slot in the right
      // node
      for (unsigned int i = 0; i < shiftnum; i++)
      {
         right->mSlotKey[ i] = left->mSlotKey[ left->mSlotUse - shiftnum + i];
         right->mSlotData[ i] = left->mSlotData[ left->mSlotUse - shiftnum + i];
      }
      left->mSlotUse -= shiftnum;

      parent->mSlotKey[ parentslot] = left->mSlotKey[ left->mSlotUse - 1];
   } // btree<>::shift_right_leaf

   /// Balance two inner nodes. The function moves key/data pairs from left to
   /// right so that both nodes are equally filled. The parent node is updated
   /// if possible.
   static void shift_right_inner( InnerNode* left, InnerNode* right,
      InnerNode* parent, unsigned int parentslot)
   {
      BTREE_ASSERT( left->mLevel == right->mLevel);
      BTREE_ASSERT( parent->mLevel == left->mLevel + 1);

      BTREE_ASSERT( left->mSlotUse > right->mSlotUse);
      BTREE_ASSERT( parent->mChildId[ parentslot] == left);

      unsigned int  shiftnum = (left->mSlotUse - right->mSlotUse) >> 1;

      BTREE_PRINT( "Shifting (leaf) " << shiftnum << " entries to right "
         << right << " from left " << left << " with common parent " << parent
         << "." << std::endl);

      if (SelfVerify)
      {
         // find the left node's slot in the parent's children
         unsigned int leftslot = 0;
         while (leftslot <= parent->mSlotUse
                && parent->mChildId[leftslot] != left)
            ++leftslot;

         BTREE_ASSERT( leftslot < parent->mSlotUse);
         BTREE_ASSERT( parent->mChildId[ leftslot] == left);
         BTREE_ASSERT( parent->mChildId[ leftslot+1] == right);

         BTREE_ASSERT( leftslot == parentslot);
      }

      // shift all slots in the right Node

      BTREE_ASSERT( right->mSlotUse + shiftnum < InnerSlotMax);

      right->mChildId[ right->mSlotUse + shiftnum] = right->mChildId[ right->mSlotUse];
      for (int i = right->mSlotUse-1; i >= 0; i--)
      {
         right->mSlotKey[ i + shiftnum] = right->mSlotKey[ i];
         right->mChildId[ i + shiftnum] = right->mChildId[ i];
      }
      right->mSlotUse += shiftnum;

      // copy the parent's decision slotkey and childid to the last new key on
      // the right
      right->mSlotKey[ shiftnum - 1] = parent->mSlotKey[ parentslot];
      right->mChildId[ shiftnum - 1] = left->mChildId[ left->mSlotUse];

      // copy the remaining last items from the left Node to the first slot in the right Node.
      for (unsigned int i = 0; i < shiftnum - 1; i++)
      {
         right->mSlotKey[ i] = left->mSlotKey[ left->mSlotUse - shiftnum + i + 1];
         right->mChildId[ i] = left->mChildId[ left->mSlotUse - shiftnum + i + 1];
      }

      // copy the first to-be-removed key from the left Node to the parent's decision slot
      parent->mSlotKey[ parentslot] = left->mSlotKey[ left->mSlotUse - shiftnum];

      left->mSlotUse -= shiftnum;
   } // btree<>::shift_right_inner

#ifdef BTREE_DEBUG
public:
   // Debug Printing

   /// Print out the B+ tree structure with keys onto the given ostream. This
   /// function requires that the header is compiled with BTREE_DEBUG and that
   /// key_type is printable via std::ostream.
   void print( std::ostream& os) const
   {
      if (mpRoot != nullptr)
      {
         print_node( os, mpRoot, 0, true);
      }
   }

   /// Print out only the leaves via the double linked list.
   void print_leaves( std::ostream& os) const
   {
      os << "leaves:" << std::endl;

      const LeafNode*  n = mpHeadLeaf;

      while (n != nullptr)
      {
         os << "  " << n << std::endl;

         n = n->mpNextLeaf;
      } // end while
   }

private:

   /// Recursively descend down the tree and print out nodes.
   static void print_node( std::ostream& os, const Node* node,
      unsigned int depth = 0, bool recursive = false)
   {
      for (unsigned int i = 0; i < depth; i++)
         os << "  ";

      os << "node " << node << " level " << node->mLevel << " mSlotUse "
         << node->mSlotUse << std::endl;

      if (node->isleafnode())
      {
          const LeafNode*  leafnode = static_cast< const LeafNode*>( node);

          for (unsigned int i = 0; i < depth; i++)
             os << "  ";
          os << "  leaf prev " << leafnode->mpPrevLeaf << " next "
             << leafnode->mpNextLeaf << std::endl;

          for (unsigned int i = 0; i < depth; i++)
             os << "  ";

          for (unsigned int slot = 0; slot < leafnode->mSlotUse; ++slot)
          {
             os << leafnode->mSlotKey[ slot] << "  ";
             // << "(data: " << leafnode->mSlotData[slot] << ") ";
          } // end for
          os << std::endl;
      } else
      {
         const InnerNode*  innernode = static_cast< const InnerNode*>( node);

         for (unsigned int i = 0; i < depth; i++)
            os << "  ";

         for (unsigned short slot = 0; slot < innernode->mSlotUse; ++slot)
         {
            os << "(" << innernode->mChildId[ slot] << ") "
               << innernode->mSlotKey[ slot] << " ";
         } // end for
         os << "(" << innernode->mChildId[ innernode->mSlotUse] << ")" << std::endl;

         if (recursive)
         {
            for (unsigned short slot = 0; slot < innernode->mSlotUse + 1; ++slot)
            {
               print_node( os, innernode->mChildId[ slot], depth + 1, recursive);
            }
         }
      }
   } // btree<>::print_node
#endif

public:
   // Verification of B+ Tree Invariants

   /// Run a thorough verification of all B+ tree invariants. The program
   /// aborts via assert() if something is wrong.
   void verify() const
   {
      key_type    minkey;
      key_type    maxkey;
      tree_stats  vstats;

      if (mpRoot != nullptr)
      {
         verify_node( mpRoot, &minkey, &maxkey, vstats);

         assert( vstats.mItemCount == mStats.mItemCount);
         assert( vstats.mLeaves == mStats.mLeaves);
         assert( vstats.mInnerNodes == mStats.mInnerNodes);

         verify_leaflinks();
      }
   }

private:

   /// Recursively descend down the tree and verify each node
   void verify_node( const Node* n, key_type* minkey, key_type* maxkey,
      tree_stats& vstats) const
   {
      BTREE_PRINT( "verifynode " << n << std::endl);

      if (n->isleafnode())
      {
         const LeafNode*  leaf = static_cast< const LeafNode*>( n);

         assert( leaf == mpRoot || !leaf->isunderflow());
         assert( leaf->mSlotUse > 0);

         for (unsigned short slot = 0; slot < leaf->mSlotUse - 1; ++slot)
         {
            assert( key_lessequal( leaf->mSlotKey[ slot], leaf->mSlotKey[ slot + 1]));
         }

         *minkey = leaf->mSlotKey[ 0];
         *maxkey = leaf->mSlotKey[ leaf->mSlotUse - 1];

         vstats.mLeaves++;
         vstats.mItemCount += leaf->mSlotUse;
      } else // !n->isleafnode()
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);
         vstats.mInnerNodes++;

         assert( inner == mpRoot || !inner->isunderflow());
         assert( inner->mSlotUse > 0);

         for (unsigned short slot = 0; slot < inner->mSlotUse - 1; ++slot)
         {
            assert( key_lessequal( inner->mSlotKey[ slot], inner->mSlotKey[ slot + 1]));
         }

         for (unsigned short slot = 0; slot <= inner->mSlotUse; ++slot)
         {
            const Node*  subnode = inner->mChildId[ slot];
            key_type     subminkey = key_type();
            key_type     submaxkey = key_type();

            assert( subnode->mLevel + 1 == inner->mLevel);
            verify_node( subnode, &subminkey, &submaxkey, vstats);

            BTREE_PRINT( "verify subnode " << subnode << ": " << subminkey
               << " - " << submaxkey << std::endl);

            if (slot == 0)
               *minkey = subminkey;
            else
               assert(key_greaterequal( subminkey, inner->mSlotKey[ slot - 1]));

            if (slot == inner->mSlotUse)
               *maxkey = submaxkey;
            else
               assert( key_equal( inner->mSlotKey[ slot], submaxkey));

            if (inner->mLevel == 1 && slot < inner->mSlotUse)
            {
               // children are leaves and must be linked together in the
               // correct order
               auto  leafa = static_cast< const LeafNode*>( inner->mChildId[ slot]);
               auto  leafb = static_cast< const LeafNode*>( inner->mChildId[ slot + 1]);

               assert( leafa->mpNextLeaf == leafb);
               assert( leafa == leafb->mpPrevLeaf);
               (void)leafa; (void)leafb; // ???
            }
            if (inner->mLevel == 2 && slot < inner->mSlotUse)
            {
               // verify leaf links between the adjacent inner nodes
               auto  parenta = static_cast< const InnerNode*>( inner->mChildId[ slot]);
               auto  parentb = static_cast< const InnerNode*>( inner->mChildId[ slot + 1]);

               auto  leafa = static_cast< const LeafNode*>( parenta->mChildId[ parenta->mSlotUse]);
               auto  leafb = static_cast< const LeafNode*>( parentb->mChildId[ 0]);

               assert( leafa->mpNextLeaf == leafb);
               assert( leafa == leafb->mpPrevLeaf);
               (void)leafa; (void)leafb; // ???
            }
         } // end for
      } // end if
   } // btree<>::verify_node

   /// Verify the double linked list of leaves.
   void verify_leaflinks() const
   {
      const LeafNode*  n = mpHeadLeaf;

      assert( n != nullptr);
      assert( n->mLevel == 0);
      assert( n->mpPrevLeaf == nullptr);

      unsigned int  testcount = 0;

      while (n != nullptr)
      {
         assert( n->mLevel == 0);
         assert( n->mSlotUse > 0);

         for (unsigned short slot = 0; slot < n->mSlotUse - 1; ++slot)
         {
            assert( key_lessequal( n->mSlotKey[ slot], n->mSlotKey[ slot + 1]));
         }

         testcount += n->mSlotUse;

         if (n->mpNextLeaf)
         {
            assert( key_lessequal( n->mSlotKey[ n->mSlotUse - 1],
               n->mpNextLeaf->mSlotKey[ 0]));

            assert( n == n->mpNextLeaf->mpPrevLeaf);
         } else
         {
            assert( mpTailLeaf == n);
         }

         n = n->mpNextLeaf;
      } // end while

      assert( testcount == size());
   } // btree<>::verify_leaflinks

private:
   // Dump and Restore of B+ Trees

   /// A header for the binary image containing the base properties of the B+
   /// tree. These properties have to match the current template
   /// instantiation.
   struct dump_header
   {
      /// "stx-btree", just to stop the restore() function from loading garbage
      char            signature[12];

      /// Currently 0
      unsigned short  version;

      /// sizeof(key_type)
      unsigned short  key_type_size;

      /// sizeof(data_type)
      unsigned short  data_type_size;

      /// Number of slots in the leaves
      unsigned short  leafslots;

      /// Number of slots in the inner nodes
      unsigned short  innerslots;

      /// Allow duplicates
      bool            mAllowDuplicates;

      /// The item count of the tree
      size_type       itemcount;

      /// Fill the struct with the current B+ tree's properties, itemcount is
      /// not filled.
      void fill()
      {
         // don't want to include string.h just for this signature
         signature[ 0] = 's'; signature[  1] = 't'; signature[  2] = 'x';
         signature[ 3] = '-'; signature[  4] = 'b'; signature[  5] = 't';
         signature[ 6] = 'r'; signature[  7] = 'e'; signature[  8] = 'e';
         signature[ 9] = 0;   signature[ 10] = 0;   signature[ 11] = 0;

         version = 0;
         key_type_size = sizeof( typename btree_self::key_type);
         data_type_size = sizeof( typename btree_self::data_type);
         leafslots = btree_self::LeafSlotMax;
         innerslots = btree_self::InnerSlotMax;
         mAllowDuplicates = btree_self::mAllowDuplicates;
      }

      /// Returns true if the headers have the same vital properties
      bool same( const struct dump_header& o) const
      {
         return (signature[ 0] == 's' && signature[ 1] == 't'
                 && signature[ 2] == 'x' && signature[ 3] == '-'
                 && signature[ 4] == 'b' && signature[ 5] == 't'
                 && signature[ 6] == 'r' && signature[ 7] == 'e'
                 && signature[ 8] == 'e' && signature[ 9] == 0
                 && signature[ 10] == 0 && signature[ 11] == 0)
                && (version == o.version)
                && (key_type_size == o.key_type_size)
                && (data_type_size == o.data_type_size)
                && (leafslots == o.leafslots)
                && (innerslots == o.innerslots)
                && (mAllowDuplicates == o.mAllowDuplicates);
      }
   }; // dump_header

public:

   /// Dump the contents of the B+ tree out onto an ostream as a binary
   /// image. The image contains memory pointers which will be fixed when the
   /// image is restored. For this to work your key_type and data_type must be
   /// integral types and contain no pointers or references.
   void dump( std::ostream& os) const
   {
      struct dump_header  header;
      header.fill();
      header.itemcount = size();

      os.write( reinterpret_cast< char*>( &header), sizeof( header));

      if (mpRoot != nullptr)
      {
         dump_node( os, mpRoot);
      }
   }

   /// Restore a binary image of a dumped B+ tree from an istream. The B+ tree
   /// pointers are fixed using the dump order. For dump and restore to work
   /// your key_type and data_type must be integral types and contain no
   /// pointers or references. Returns true if the restore was successful.
   bool restore( std::istream& is)
   {
      struct dump_header  fileheader;

      is.read( reinterpret_cast< char*>( &fileheader), sizeof( fileheader));
      if (!is.good())
         return false;

      struct dump_header  myheader;
      myheader.fill();
      myheader.itemcount = fileheader.itemcount;

      if (!myheader.same( fileheader))
      {
         BTREE_PRINT( "btree::restore: file header does not match instantiation "
            "signature." << std::endl);
         return false;
      }

      clear();

      if (fileheader.itemcount > 0)
      {
         mpRoot = restore_node( is);
         if (mpRoot == nullptr)
            return false;

         mStats.mItemCount = fileheader.itemcount;
      }

#ifdef BTREE_DEBUG
      if (Debug)
         print( std::cout);
#endif
      if (SelfVerify)
         verify();

      return true;
   } // btree<>::restore

private:

   /// Recursively descend down the tree and dump each node in a precise order
   void dump_node( std::ostream& os, const Node* n) const
   {
      BTREE_PRINT( "dump_node " << n << std::endl);

      if (n->isleafnode())
      {
         const LeafNode*  leaf = static_cast< const LeafNode*>( n);

         os.write( reinterpret_cast< const char*>( leaf), sizeof( *leaf));
      } else // !n->isleafnode()
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);

         os.write( reinterpret_cast< const char*>( inner), sizeof( *inner));

         for (unsigned short slot = 0; slot <= inner->mSlotUse; ++slot)
         {
            const Node*  subnode = inner->mChildId[ slot];

            dump_node( os, subnode);
         } // end for
      } // end if
   } // btree<>::dump_node

   /// Read the dump image and construct a tree from the node order in the
   /// serialization.
   Node* restore_node( std::istream& is)
   {
      union
      {
         Node       top;
         LeafNode   leaf;
         InnerNode  inner;
      } nu;

      // first read only the top of the node
      is.read( reinterpret_cast< char*>( &nu.top), sizeof( nu.top));
      if (!is.good())
         return nullptr;

      if (nu.top.isleafnode())
      {
         // read remaining data of leaf node
         is.read( reinterpret_cast< char*>( &nu.leaf) + sizeof( nu.top),
            sizeof( nu.leaf) - sizeof( nu.top));
         if (!is.good())
            return nullptr;

         LeafNode*  newleaf = allocate_leaf();

         // copy over all data, the leaf nodes contain only their double linked list pointers
         *newleaf = nu.leaf;

         // reconstruct the linked list from the order in the file
         if (mpHeadLeaf == nullptr)
         {
            BTREE_ASSERT( newleaf->mpPrevLeaf == nullptr);
            mpHeadLeaf = mpTailLeaf = newleaf;
         } else
         {
            newleaf->mpPrevLeaf = mpTailLeaf;
            mpTailLeaf->mpNextLeaf = newleaf;
            mpTailLeaf = newleaf;
         }

         return newleaf;
      } // end if

      // read remaining data of inner node
      is.read( reinterpret_cast< char*>( &nu.inner) + sizeof( nu.top),
         sizeof( nu.inner) - sizeof( nu.top));
      if (!is.good())
         return nullptr;

      InnerNode*  new_inner = allocate_inner( 0);

      // copy over all data, the inner nodes contain only pointers to their children
      *new_inner = nu.inner;

      for (unsigned short slot = 0; slot <= new_inner->mSlotUse; ++slot)
      {
         new_inner->mChildId[ slot] = restore_node( is);
      }

      return new_inner;
   } // btreee<>::restore_node

   /// Find the leaf node in which the value with the given key should be.
   ///
   /// @param[in]  key  The of the data to find.
   /// @return
   ///    Pointer to the leaf node in which the value with the given key could
   ///    be, NULL if the tree is empty.
   /// @since  x.y.z, 13.02.2019
   const LeafNode* findLeaf( const key_type& key) const
   {
      const Node*  n = mpRoot;
      if (n == nullptr)
         return nullptr;

      while (!n->isleafnode())
      {
         const InnerNode*  inner = static_cast< const InnerNode*>( n);
         const int         slot = find_lower( inner, key);

         n = inner->mChildId[ slot];
      } // end while

      return static_cast< const LeafNode*>( n);
   } // btree<>::findLeaf

}; // btree<>


#undef BTREE_PRINT
#undef BTREE_ASSERT
#undef BTREE_MAX
#undef BTREE_FRIENDS


} // namespace celma::container


#endif   // CELMA_CONTAINERS_BTREE_HPP


// =====  END OF btree.hpp  =====

