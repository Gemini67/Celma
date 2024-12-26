
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class
/// celma::containers::detail::BalancedBinaryTreeNode<>.


#ifndef CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP
#define CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP


#include "celma/containers/detail/binary_tree_node_base.hpp"


namespace celma { namespace containers { namespace detail {


/// Node of a balanced binary tree.<br>
/// Basically a normal binary tree node, plus the balance information.
///
/// @tparam  T  The type of the value to store in the node.
/// @since  x.y.z, 25.03.2017
template< typename T> class BalancedBinaryTreeNode:
   public BinaryTreeNodeBase< T, BalancedBinaryTreeNode< T>>
{
public:
   // need to make the symbols from the base class available
   using value_type = T;
   using base_node_t = BinaryTreeNodeBase< T, BalancedBinaryTreeNode< T>>;
   using base_node_t::mpLeft;
   using base_node_t::mpRight;
   using base_node_t::mpParent;
   using base_node_t::mValue;
   using base_node_t::releaseReplaceChild;

   /// Constructor, no value, but parent node pointer.
   ///
   /// @param[in]  parent  Pointer to the parent node to store.
   /// @since  x.y.z, 25.03.2017
   explicit BalancedBinaryTreeNode( BalancedBinaryTreeNode* parent):
      base_node_t( parent)
   {
std::cout << "   allocated balanced binary tree node " << this << std::endl;
   } // BalancedBinaryTreeNode< T>::BalancedBinaryTreeNode
      
   /// Constructor with value and optional parent node pointer.
   ///
   /// @param[in]  data
   ///    The data to store in this node.
   /// @param[in]  parent
   ///    Pointer to the parent node to store.
   /// @since  x.y.z, 25.03.2017
   explicit BalancedBinaryTreeNode( const T& data,
      BalancedBinaryTreeNode* parent = nullptr):
         base_node_t( data, parent)
   {
std::cout << "   allocated balanced binary tree node " << this << std::endl;
   } // BalancedBinaryTreeNode< T>::BalancedBinaryTreeNode

   // no copying or moving
   BalancedBinaryTreeNode( const BalancedBinaryTreeNode&) = delete;
   BalancedBinaryTreeNode( BalancedBinaryTreeNode&&) = delete;
//   ~BalancedBinaryTreeNode() = default;
   ~BalancedBinaryTreeNode()
   {
std::cout << "   deleted balanced binary tree node " << this << std::endl;
   }

   /// The balance of the sub-tree below this node:
   /// - 0: Subtrees are balanced, i.e. both subtrees have the same number of
   ///   elements.
   /// - -1: Subtree on the left is greater, i.e. has one element more than the
   ///   subtree on the right. More than one (1) element difference is not
   ///   allowed.
   /// - +1: Subtree on the right is greater, i.e. has one element more than the
   ///   subtree on the left. More than one (1) element difference is not
   ///   allowed.
   int8_t  mBalance = 0;

}; // BalancedBinaryTreeNode< T>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP


// =====  END OF balanced_binary_tree_node.hpp  =====

