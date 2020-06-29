
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
/// See documentation of template class
/// celma::container::detail::BinaryTreeNodeBase<>.


#ifndef CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_BASE_HPP
#define CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_BASE_HPP


#include <memory>


namespace celma::container::detail {


/// Base class for nodes of binary trees.<br>
/// Stores the data and the pointers and provides some methods that are common
/// for all binary trees.
///
/// @tparam  T
///    The type of the data to store in a node.
/// @tparam  N
///    The real node type.
/// @since  x.y.z, 20.02.2019
template< typename T, typename N> class BinaryTreeNodeBase
{
public:
   /// Constructor for an empty (no data), new node.
   ///
   /// @param[in]  parent_node  Pointer to the parent node.
   /// @since  x.y,y, 03.04.2017
   explicit BinaryTreeNodeBase( N* parent_node):
      mpParent( parent_node),
      mpLeft(),
      mpRight(),
      mValue()
   {
   } // BinaryTreeNodeBase< T, N>::BinaryTreeNodeBase

   /// Constructor for a new node with data.
   ///
   /// @param[in]  new_value
   ///    The data to store in this new node.
   /// @param[in]  parent_node
   ///    Pointer to the parent node.
   /// @since  x.y,y, 24.03.2017
   explicit BinaryTreeNodeBase( const T& new_value, N* parent_node = nullptr):
      mpParent( parent_node),
      mpLeft(),
      mpRight(),
      mValue( new_value)
   {
   } // BinaryTreeNodeBase< T, N>::BinaryTreeNodeBase

   // no copying or moving.
   BinaryTreeNodeBase( const BinaryTreeNodeBase&) = delete;
   BinaryTreeNodeBase( BinaryTreeNodeBase&&) = delete;

   /// Default destructor is fine.
   virtual ~BinaryTreeNodeBase() = default;

   /// Returns the pointer to the left-side node.
   ///
   /// @return  The pointer to the node on the left side, may be NULL.
   /// @since  x.y.z, 20.02.2019
   N* left()
   {
      return mpLeft.get();
   } // BinaryTreeNodeBase< T, N>::left

   /// Returns the pointer to the right-side node.
   ///
   /// @return  The pointer to the node on the right side, may be NULL.
   /// @since  x.y.z, 20.02.2019
   N* right()
   {
      return mpRight.get();
   } // BinaryTreeNodeBase< T, N>::right

   /// Increment a node (pointer), i.e. go to the next greater element in the
   /// tree.<br>
   /// The next greater element is in the right sub-tree, and there in the
   /// last left node (leaf).<br>
   /// If there is no right sub-tree, check if the current element was in the
   /// right sub-tree of its parent, which means that it was processed
   /// already.
   ///
   /// @return
   ///    Pointer to the next element in the tree, NULL if no next element
   ///    exists.
   /// @since  x.y.z, 25.03.2017
   N* increment() const
   {
      // have right sub-tree?
      if (mpRight)
      {
         // have greater values
         auto  next = mpRight.get();
         while (next->mpLeft)
            next = next->mpLeft.get();
         return next;
      } // end if

      // find the next parent node, where we come up from the right sub-tree
      auto  next( mpParent);
      auto  coming_from( this);
      while ((next != nullptr) && (coming_from == next->mpRight.get()))
      {
         coming_from = next;
         next        = next->mpParent;
      } // end while

      return next;
   } // BinaryTreeNodeBase< T, N>::increment

   /// Decrement a node (pointer), i.e. go to the previous/smaller element in
   /// the tree.<br>
   /// The previous element is either the greatest in the left sub-tree, or the
   /// the parent.<br>
   ///
   /// @return
   ///    Pointer to the previous element in the tree, NULL if no previous
   ///    element exists.
   /// @since  x.y.z, 02.04.2017
   N* decrement() const
   {
      // have left sub-tree?
      if (mpLeft)
      {
         // have smaller values
         auto  previous = mpLeft.get();
         while (previous->mpRight)
            previous = previous->mpRight.get();
         return previous;
      } // end if

      // find the previous parent node, where we come up from the left sub-tree
      auto  previous( mpParent);
      auto  coming_from( this);
      while ((previous != nullptr) && (coming_from == previous->mpLeft.get()))
      {
         coming_from = previous;
         previous    = previous->mpParent;
      } // end while

      return previous;
   } // BinaryTreeNodeBase< T, N>::decrement

   /// Returns the value stored internally.
   ///
   /// @return  Pointer to the internally stored value.
   /// @since  x.y.z, 25.03.2017
   T* getValue()
   {
      return &mValue;
   } // BinaryTreeNodeBase< T, N>::getValue

   /// Check the consistency of the current node: If it has a parent node,
   /// either the parent's left or right pointer must point to this.<br>
   /// Since the nodes don't know the comparison function, we can't check the
   /// order of the elements here.
   ///
   /// @return
   ///    \c true if the link between this node and its parent node is correct.
   /// @since  x.y.z, 21.02.2019
   bool check() const
   {
      if (mpParent != nullptr)
      {
         if ((mpParent->mpLeft.get() != this) 
             && (mpParent->mpRight.get() != this))
         {
            return false;
         } // end if
      } // end if
      return true;
   } // BinaryTreeNodeBase< T, N>:: check

   /// Replaces a child node/pointer with a new child/node.<br>
   /// Checks if the given old child was the left or the right child node, and
   /// replaces the corresponding pointer with the new one.<br>
   /// The old/previous child node is not deleted.
   /// 
   /// @param[in]  old_child
   ///    Pointer to the old child/node that should be replaced.
   /// @param[in]  new_child
   ///    The new child/node that should be stored instead.
   /// @since  x.y.z, 24.04.2017
   void releaseReplaceChild( N* old_child, N* new_child)
   {
      if (mpLeft.get() == old_child)
      {
         mpLeft.release();
         mpLeft.reset( new_child);
      } else
      {
         mpRight.release();
         mpRight.reset( new_child);
      } // end if
   } // BinaryTreeNodeBase< T, N>::releaseReplaceChild

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 07.03.2019  (moved here from binary tree)
   N* first() const
   {
      const N*  p_first = static_cast< const N*>( this);
      while (p_first->mpLeft)
         p_first = p_first->mpLeft.get();
      return const_cast< N*>( p_first);
   } // BinaryTreeNodeBase< T, N>::first

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 07.03.2019  (moved here from binary tree)
   N* last() const
   {
      const N*  p_last = static_cast< const N*>( this);
      while (p_last->mpRight)
         p_last = p_last->mpRight.get();
      return const_cast< N*>( p_last);
   } // BinaryTreeNodeBase< T, N>::last


   /// Pointer to the parent node.
   N*                   mpParent = nullptr;
   /// Left node pointer, use unique pointer to make sure it is deleted when the
   /// tree is deleted.
   std::unique_ptr< N>  mpLeft;
   /// Right node pointer, use unique pointer to make sure it is deleted when
   /// the tree is deleted.
   std::unique_ptr< N>  mpRight;
   /// The value stored in this node.
   T                    mValue;

}; // BinaryTreeNodeBase< T, N>


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_BASE_HPP


// =====  END OF binary_tree_node_base.hpp  =====

