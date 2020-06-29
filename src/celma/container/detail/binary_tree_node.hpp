
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
/// See documentation of template class
/// celma::container::detail::BinaryTreeNode<>.


#ifndef CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_HPP
#define CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_HPP


#include "celma/container/detail/binary_tree_node_base.hpp"


namespace celma::container::detail {


/// Nodes of a binary tree.<br>
/// Does not only store the data and the pointers, but also contains part of the
/// logic/implementation of the tree.
///
/// @tparam  T  The type of the data to store in a node.
/// @since  x.y.z, 25.03.2017
template< typename T> class BinaryTreeNode:
   public BinaryTreeNodeBase< T, BinaryTreeNode< T>>
{
public:
   using value_type = T;
   using base_node_t = BinaryTreeNodeBase< T, BinaryTreeNode< T>>;
   using base_node_t::mpLeft;
   using base_node_t::mpRight;
   using base_node_t::mpParent;
   using base_node_t::mValue;
   using base_node_t::releaseReplaceChild;

   /// Constructor for an empty (no data), new node.
   ///
   /// @param[in]  parent_node  Pointer to the parent node.
   /// @since  x.y,y, 03.04.2017
   explicit BinaryTreeNode( BinaryTreeNode* parent_node):
      base_node_t( parent_node)
   {
   } // BinaryTreeNode< T>::BinaryTreeNode

   /// Constructor for a new node with data.
   ///
   /// @param[in]  new_value
   ///    The data to store in this new node.
   /// @param[in]  parent_node
   ///    Pointer to the parent node.
   /// @since  x.y,y, 24.03.2017
   explicit BinaryTreeNode( const T& new_value, BinaryTreeNode* parent_node = nullptr):
      base_node_t( new_value, parent_node)
   {
   } // BinaryTreeNode< T>::BinaryTreeNode

   ~BinaryTreeNode() override = default;

   /// Detaches a node from the binary tree. The node can be deleted afterwards.
   ///
   /// @param[in]  next_greater
   ///    Pointer to the node with the next-greater value, if there exists one.
   /// @return
   ///    Pointer to the node to use as new root, if the root node was deleted.
   /// @since  x.y.z, 27.04.2017
   BinaryTreeNode* detach( BinaryTreeNode* next_greater)
   {

      // test if this node has any child nodes
      if (!mpLeft)
      {
         if (!mpRight)
         {
            if (mpParent != nullptr)
               mpParent->releaseChild( this);
            // no sub-tree at all: can be deleted right away
            return nullptr;
         } // end if

         // no left sub-tree: attach my right to my parent (if I have one)
         if (mpParent == nullptr)
         {
            mpRight->mpParent = nullptr;
            return mpRight.release();
         } // end if

         mpParent->releaseReplaceChild( this, mpRight.release());
         return nullptr;
      } // end if

      if (!mpRight)
      {
         // no right sub-tree: attach my left to my parent (if I have one)
         if (mpParent == nullptr)
         {
            mpLeft->mpParent = nullptr;
            return mpLeft.release();
         } // end if

         mpParent->releaseReplaceChild( this, mpLeft.release());
         return nullptr;
      } // end if

      // both left and right sub-trees exist
      // replace myself with my next greater

      // next greater cannot be NULL, since right was not NULL
      // next_greater left must be NULL, otherwise this left node/tree would
      // contain another greater
      // if the next_greater node has a right node, this right node must be
      // attached to next_greater's parent
      if (next_greater->mpParent != nullptr)
      {
         if (next_greater->mpRight)
         {
            next_greater->mpParent->releaseReplaceChild( next_greater, next_greater->mpRight.release());
            next_greater->mpRight->mpParent = next_greater->mpParent;
         } else
         {
            next_greater->mpParent->releaseChild( next_greater);
         } // end if
      } // end if

      // now next_greater is detached, give it my nodes
      next_greater->mpLeft.reset( mpLeft.release());
      next_greater->mpRight.reset( mpRight.release());

      if (next_greater->mpLeft)
         next_greater->mpLeft->mpParent = next_greater;
      if (next_greater->mpRight)
         next_greater->mpRight->mpParent = next_greater;

      // if there is parent, tell him he's got a new child
      if (mpParent != nullptr)
      {
         mpParent->releaseReplaceChild( this, next_greater);
         next_greater->mpParent = mpParent;
         return nullptr;
      } // end if

      next_greater->mpParent = nullptr;
      return next_greater;
   } // BinaryTreeNode< T>::detach
   
   /// Replaces a child node/pointer with a new child/node.<br>
   /// Checks if the given old child was the left or the right child node, and
   /// replaces the corresponding pointer with the new one.<br>
   /// The old/previous child node is deleted.
   ///
   /// @param[in]  old_child
   ///    Pointer to the old child/node that should be replaced.
   /// @param[in]  new_child
   ///    The new child/node that should be stored instead.
   /// @since  x.y.z, 24.04.2017
   void replaceChild( BinaryTreeNode* old_child, BinaryTreeNode* new_child)
   {
      if (mpLeft.get() == old_child)
         mpLeft.reset( new_child);
      else
         mpRight.reset( new_child);
   } // BinaryTreeNode< T>::replaceChild

   /// Releases a child node.
   ///
   /// @param[in]  child_node  Pointer to the child/node to release.
   /// @since  x.y.z, 24.04.2017
   void releaseChild( BinaryTreeNode* child_node)
   {
      if (mpLeft.get() == child_node)
         mpLeft.release();
      else
         mpRight.release();
   } // BinaryTreeNode< T>::releaseChild

}; // BinaryTreeNode< T>


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_BINARY_TREE_NODE_HPP


// =====  END OF binary_tree_node.hpp  =====

