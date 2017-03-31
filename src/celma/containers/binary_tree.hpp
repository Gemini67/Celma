
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
/// See documentation of class celma::containers::@@@.


#ifndef CELMA_CONTAINERS_BINARY_TREE_HPP
#define CELMA_CONTAINERS_BINARY_TREE_HPP


#include <iterator>
#include <utility>
#include "celma/containers/detail/binary_tree_node.hpp"
#include "celma/containers/detail/tree_iterator.hpp"


namespace celma { namespace containers {


/// @since  x.y.z, 24.03.2017
template< typename T> class BinaryTree
{
public:
   using node_t = detail::BinaryTreeNode< T>;
   using iterator = detail::TreeIterator< node_t>;
   using const_iterator = detail::ConstTreeIterator< node_t>;

   using reverse_iterator = std::reverse_iterator< iterator>;
   using const_reverse_iterator = std::reverse_iterator< const_iterator>;

   BinaryTree();
   BinaryTree( const BinaryTree& other);
   BinaryTree( BinaryTree&& other);
   ~BinaryTree();

   /// @since  x.y.z, 31.03.2017
   void assign( const BinaryTree& other);

   auto insert( const T& value);

   void clear();

   bool empty() const;

   std::size_t size() const;

   iterator begin();
//   const_iterator cbegin() const;
   iterator end();
//   const_iterator cend() const;
   iterator rbegin();
//   const_iterator crbegin() const;
   iterator rend();
//   const_iterator crend() const;

   /// @since  x.y.z, 31.03.2017
   BinaryTree& operator =( const BinaryTree& other);

protected:
   node_t*  mpRoot;

private:
   void recursiveDelete( node_t* current_node);
   auto recursiveInsert( node_t* parent_node, const T& new_value);
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;
 
}; // BinaryTree< T>


// inlined methods
// ===============


template< typename T> BinaryTree< T>::BinaryTree():
   mpRoot( nullptr)
{
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::BinaryTree( const BinaryTree& other):
   mpRoot( nullptr)
{
   assign( other);
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::BinaryTree( BinaryTree&& other):
   mpRoot( other.mpRoot)
{
   other.mpRoot = nullptr;
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::~BinaryTree()
{
   clear();
} // BinaryTree< T>::~BinaryTree


template< typename T> void BinaryTree< T>::assign( const BinaryTree& other)
{
   clear();
   // @@@
} // BinaryTree< T>::assign


template< typename T> auto BinaryTree< T>::insert( const T& value)
{
   if (mpRoot == nullptr)
   {
      mpRoot = new node_t( value);
      return std::pair< iterator, bool>( begin(), true);
   } // end if

   return recursiveInsert( mpRoot, value);
} // BinaryTree< T>::BinaryTree


template< typename T> void BinaryTree< T>::clear()
{
   if (mpRoot != nullptr)
   {
      recursiveDelete( mpRoot);
      mpRoot = nullptr;
   } // end if
} // BinaryTree< T>::clear


template< typename T> bool BinaryTree< T>::empty() const
{
   return mpRoot == nullptr;
} // BinaryTree< T>::empty


template< typename T> std::size_t BinaryTree< T>::size() const
{
   std::size_t  count = 0;
   recursiveVisit( mpRoot, [&count]( auto const&) { ++count; });
   return count;
} // BinaryTree< T>::size


template< typename T> typename BinaryTree< T>::iterator BinaryTree< T>::begin()
{
   if (mpRoot == nullptr)
      return iterator();

   node_t*  first = mpRoot;
   while (first->left != nullptr)
      first = first->left;

   return iterator( first);
} // BinaryTree< T>::begin


template< typename T> typename BinaryTree< T>::iterator BinaryTree< T>::end()
{
   return iterator();
} // BinaryTree< T>::end


template< typename T>
   BinaryTree< T>& BinaryTree< T>::operator =( const BinaryTree& other)
{
   clear();
   assign( other);
   return *this;
} // BinaryTree< T>::operator =


template< typename T>
   void BinaryTree< T>::recursiveDelete( node_t* current_node)
{

   if (current_node->left != nullptr)
      recursiveDelete( current_node->left);
   if (current_node->right != nullptr)
      recursiveDelete( current_node->right);

   delete current_node;

} // BinaryTree< T>::recursiveDelete


template< typename T> auto BinaryTree< T>::recursiveInsert( node_t* parent_node,
                                                            const T& new_value)
{
   if (new_value < parent_node->value)
   {
      if (parent_node->left == nullptr)
      {
         parent_node->left = new node_t( new_value, parent_node);
         return std::pair< iterator, bool>( iterator( parent_node->left), true);
      } // end if
      return recursiveInsert( parent_node->left, new_value);
   } // end if
   
   if (parent_node->value < new_value)
   {
      if (parent_node->right == nullptr)
      {
         parent_node->right = new node_t( new_value, parent_node);
         return std::pair< iterator, bool>( iterator( parent_node->right), true);   // @@@
      } // end if
      return recursiveInsert( parent_node->right, new_value);
   } // end if

   // values are equal, something we don't support:
   return std::pair< iterator, bool>( end(), false);
} // BinaryTree< T>::recursiveInsert


template< typename T> template< typename F>
   void BinaryTree< T>::recursiveVisit( node_t* current_node, F fun) const
{

   if (current_node == nullptr)
      return;

   recursiveVisit( current_node->left, fun);

   fun( current_node);

   recursiveVisit( current_node->right, fun);

} // BinaryTree< T>::recursiveVisit


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BINARY_TREE_HPP


// =========================  END OF binary_tree.hpp  =========================

