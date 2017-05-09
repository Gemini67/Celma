
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


#include <memory>


namespace celma { namespace containers { namespace detail {


/// @since  x.y.z, 25.03.2017
template< typename T> class BinaryTreeNode
{
public:
   using value_type = T;

   /// @since  x.y,y, 03.04.2017
   BinaryTreeNode( BinaryTreeNode* parent_node):
      parent( parent_node),
      left(),
      right(),
      value()
   {
   } // BinaryTreeNode< T>::BinaryTreeNode

   /// @since  x.y,y, 24.03.2017
   BinaryTreeNode( const T& new_value, BinaryTreeNode* parent_node = nullptr):
      parent( parent_node),
      left(),
      right(),
      value( new_value)
   {
   } // BinaryTreeNode< T>::BinaryTreeNode

   /// Increment a node (pointer), i.e. go to the next greater element in the
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
      // have right sub-tree?
      if (right)
      {
         // have greater values
         auto  next = right.get();
         while (next->left)
            next = next->left.get();
         return next;
      } // end if

      // find next parent node, where we come from the left sub-tree
      auto  next( parent);
      auto  coming_from( this);
      while ((next != nullptr) && (coming_from == next->right.get()))
      {
         coming_from = next;
         next        = next->parent;
      } // end while

      return next;
   }

   /// Decrement a node (pointer), i.e. go to the previous/smaller element in
   /// the tree.<br>
   /// The previous element is either the greatest in the left sub-tree, or the
   /// the parent.<br>
   /// @return  Pointer to the previous element in the tree, NULL if no previous
   ///          element exists.
   /// @since  x.y.z, 02.04.2017
   BinaryTreeNode* decrement() const
   {
      // have left sub-tree?
      if (left)
      {
         // have smaller values
         auto  previous = left.get();
         while (previous->right)
            previous = previous->right.get();
         return previous;
      } // end if

      // find previous parent node, where we come from the right sub-tree
      auto  previous( parent);
      auto  coming_from( this);
      while ((previous != nullptr) && (coming_from == previous->left.get()))
      {
         coming_from = previous;
         previous    = previous->parent;
      } // end while

      return previous;
   }

   T* getValue()
   {
      return &value;
   }

   /// 
   /// @param[in]  old_child  .
   /// @param[in]  new_child  .
   /// @since  x.y.z, 24.04.2017
   void replaceChild( BinaryTreeNode* old_child, BinaryTreeNode* new_child)
   {
      // no right sub-tree: left moves up
      if (left == old_child)
         left.reset( new_child);
      else
         right.reset( new_child);
   } // 

   /// 
   /// @param[in]  old_child  .
   /// @param[in]  new_child  .
   /// @since  x.y.z, 24.04.2017
   void releaseReplaceChild( BinaryTreeNode* old_child, BinaryTreeNode* new_child)
   {
      // no right sub-tree: left moves up
      if (left == old_child)
      {
         left.release();
         left.reset( new_child);
      } else
      {
         right.release();
         right.reset( new_child);
      } // end if
   } // 

   /// 
   /// @param[in]  child_node  .
   /// @since  x.y.z, 24.04.2017
   void releaseChild( BinaryTreeNode* child_node)
   {
      if (left == child_node)
         left.release();
      else
         right.release();
   } // 

   /// Pointer to the parent node.
   BinaryTreeNode*                   parent;
   /// Left node pointer, use unique pointer to make sure it is deleted when the
   /// tree is deleted.
   std::unique_ptr< BinaryTreeNode>  left;
   /// Right node pointer, use unique pointer to make sure it is deleted when
   /// the tree is deleted.
   std::unique_ptr< BinaryTreeNode>  right;
   /// The value stored in this node.
   T                                 value;

}; // BinaryTreeNode< T>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_BINARY_TREE_NODE_HPP


// =======================  END OF binary_tree_node.hpp  =======================
