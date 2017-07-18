
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


#ifndef CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP
#define CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP


#include "celma/containers/binary_tree_node.hpp"


namespace celma { namespace containers { namespace detail {


/// @since  x.y.z, 25.03.2017
template< typename T> class BalancedBinaryTreeNode:
   public BinaryTreeNode< T>
{
public:
   size_t  balance = 0;

}; // BalancedBinaryTreeNode< T>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_BALANCED_BINARY_TREE_NODE_HPP


// ==================  END OF balanced_binary_tree_node.hpp  ==================

