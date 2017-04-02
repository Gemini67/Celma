
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
#include <memory>
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

   using reverse_iterator = detail::ReverseTreeIterator< node_t>;
   using const_reverse_iterator = detail::ConstReverseTreeIterator< node_t>;

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
   const_iterator cbegin() const;
   iterator end();
   const_iterator cend() const;
   /// @since  x.y.z, 31.03.2017
   reverse_iterator rbegin();
   /// @since  x.y.z, 31.03.2017
   const_reverse_iterator crbegin() const;
   /// @since  x.y.z, 31.03.2017
   reverse_iterator rend();
   /// @since  x.y.z, 31.03.2017
   const_reverse_iterator crend() const;

   /// @since  x.y.z, 31.03.2017
   BinaryTree& operator =( const BinaryTree& other);

protected:
   std::unique_ptr< node_t>  mpRoot;

private:
   auto recursiveInsert( node_t* parent_node, const T& new_value);
   node_t* first() const;
   node_t* last() const;
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;
 
}; // BinaryTree< T>


// inlined methods
// ===============


template< typename T> BinaryTree< T>::BinaryTree():
   mpRoot()
{
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::BinaryTree( const BinaryTree& other):
   mpRoot()
{
   assign( other);
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::BinaryTree( BinaryTree&& other):
   mpRoot( other.mpRoot)
{
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
   if (!mpRoot)
   {
      mpRoot = std::make_unique< node_t>( value);
      return std::pair< iterator, bool>( begin(), true);
   } // end if

   return recursiveInsert( mpRoot.get(), value);
} // BinaryTree< T>::BinaryTree


template< typename T> void BinaryTree< T>::clear()
{
   mpRoot.reset();
} // BinaryTree< T>::clear


template< typename T> bool BinaryTree< T>::empty() const
{
   return !mpRoot;
} // BinaryTree< T>::empty


template< typename T> std::size_t BinaryTree< T>::size() const
{
   std::size_t  count = 0;
   recursiveVisit( mpRoot.get(), [&count]( auto const&) { ++count; });
   return count;
} // BinaryTree< T>::size


template< typename T> typename BinaryTree< T>::iterator BinaryTree< T>::begin()
{
   if (!mpRoot)
      return iterator();
   return iterator( first());
} // BinaryTree< T>::begin


template< typename T>
   typename BinaryTree< T>::const_iterator BinaryTree< T>::cbegin() const
{
   if (!mpRoot)
      return const_iterator();
   return const_iterator( first());
} // BinaryTree< T>::cbegin


template< typename T> typename BinaryTree< T>::iterator BinaryTree< T>::end()
{
   return iterator();
} // BinaryTree< T>::end


template< typename T>
   typename BinaryTree< T>::const_iterator BinaryTree< T>::cend() const
{
   return const_iterator();
} // BinaryTree< T>::cend


template< typename T>
   typename BinaryTree< T>::reverse_iterator BinaryTree< T>::rbegin()
{
   if (!mpRoot)
      return reverse_iterator();
   return reverse_iterator( last());
} // BinaryTree< T>::rbegin


template< typename T>
   typename BinaryTree< T>::const_reverse_iterator BinaryTree< T>::crbegin() const
{
   if (!mpRoot)
      return const_reverse_iterator();
   return const_reverse_iterator( last());
} // BinaryTree< T>::crbegin


template< typename T>
   typename BinaryTree< T>::reverse_iterator BinaryTree< T>::rend()
{
   return reverse_iterator();
} // BinaryTree< T>::rend


template< typename T>
   typename BinaryTree< T>::const_reverse_iterator BinaryTree< T>::crend() const
{
   return const_reverse_iterator();
} // BinaryTree< T>::crend


template< typename T>
   BinaryTree< T>& BinaryTree< T>::operator =( const BinaryTree& other)
{
   clear();
   assign( other);
   return *this;
} // BinaryTree< T>::operator =


template< typename T> auto BinaryTree< T>::recursiveInsert( node_t* parent_node,
                                                            const T& new_value)
{
   if (new_value < parent_node->value)
   {
      if (!parent_node->left)
      {
         parent_node->left = std::make_unique< node_t>( new_value, parent_node);
         return std::pair< iterator, bool>( iterator( parent_node->left.get()), true);
      } // end if
      return recursiveInsert( parent_node->left.get(), new_value);
   } // end if
   
   if (parent_node->value < new_value)
   {
      if (!parent_node->right)
      {
         parent_node->right = std::make_unique< node_t>( new_value, parent_node);
         return std::pair< iterator, bool>( iterator( parent_node->right.get()), true);   // @@@
      } // end if
      return recursiveInsert( parent_node->right.get(), new_value);
   } // end if

   // values are equal, something we don't support:
   return std::pair< iterator, bool>( end(), false);
} // BinaryTree< T>::recursiveInsert


template< typename T>
   typename BinaryTree< T>::node_t* BinaryTree< T>::first() const
{
   auto  p_first = mpRoot.get();
   while (p_first->left)
      p_first = p_first->left.get();
   return p_first;
} // 


template< typename T>
   typename BinaryTree< T>::node_t* BinaryTree< T>::last() const
{
   auto  p_last = mpRoot.get();
   while (p_last->right)
      p_last = p_last->right.get();
   return p_last;
} // 


template< typename T> template< typename F>
   void BinaryTree< T>::recursiveVisit( node_t* current_node, F fun) const
{

   if (current_node == nullptr)
      return;

   recursiveVisit( current_node->left.get(), fun);

   fun( current_node);

   recursiveVisit( current_node->right.get(), fun);

} // BinaryTree< T>::recursiveVisit


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BINARY_TREE_HPP


// =========================  END OF binary_tree.hpp  =========================

