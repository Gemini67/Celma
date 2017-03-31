
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::containers::detail::@@@.


#ifndef CELMA_CONTAINERS_DETAIL_BINARY_TREE_NODE_HPP
#define CELMA_CONTAINERS_DETAIL_BINARY_TREE_NODE_HPP


namespace celma { namespace containers { namespace detail {


template< typename T> class BinaryTreeNode
{
public:
   using value_type = T;

   /// @since  x.y,y 24.03.2017
   BinaryTreeNode( const T& new_value, BinaryTreeNode* parent_node = nullptr):
      parent( parent_node),
      left( nullptr),
      right( nullptr),
      value( new_value)
   {
   } // BinaryTreeNode< T>::BinaryTreeNode

   /// Increment a node (pointer), i.e. go to next greater element in the
   /// tree.<br>
   /// The next greater element is in the right sub-tree, and there in the
   /// last left node (leaf).<br>
   /// If there is no right sub-tree, check if the current element was in the
   /// right sub-tree of its parent, which means that it was processed
   /// already.
   /// @return  Pointer to the next element in the tree, NULL if no next
   ///          element exists.
   /// @since  x.y.z, 25.03.2017
   BinaryTreeNode* increment() const
   {
      // have right subtree?
      if (right != nullptr)
      {
         // have greater values
         BinaryTreeNode*  next = right;
         while (next->left != nullptr)
            next = next->left;
         return next;
      } // end if

      // do we have a parent node, or are we the root?
      if (parent == nullptr)
         return nullptr;

      // am I the left node of my parent? then my parent is the next node
      if (parent->left == this)
         return parent;

      // find next parent node, where we come from the left sub-tree
      BinaryTreeNode* next = parent;
      while ((next != nullptr) && (next->right != nullptr) &&
             (next == next->right->parent))
         next = next->parent;

      // if we stopped at a node with a right sub-tree, we have not been there
      // yet
      if ((next != nullptr) && (next->right != nullptr))
         return next->increment();
      return next;
   }

   BinaryTreeNode derement() const
   {
      return nullptr;
   }

   T* getValue()
   {
      return &value;
   }

   BinaryTreeNode*  parent;
   BinaryTreeNode*  left;
   BinaryTreeNode*  right;
   T                value;

}; // BinaryTreeNode< T>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_BINARY_TREE_NODE_HPP


// =======================  END OF binary_tree_node.hpp  =======================

