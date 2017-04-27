
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

   /// Assigns the contents of another binary tree to this object.<br>
   /// The specialty of this function is that it always creates a well balanced
   /// tree.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  x.y.z, 31.03.2017
   void assign( const BinaryTree& other);

   auto insert( const T& value);

   /// @since  x.y.z, 03.04.2017
   iterator find( const T& value);

   /// @since  x.y.z, 03.04.2017
   const_iterator find( const T& value) const;

   /// @since  x.y.z, 03.04.2017
   iterator lower_bound( const T& value);

   /// @since  x.y.z, 03.04.2017
   const_iterator lower_bound( const T& value) const;

   /// @since  x.y.z, 23.04.2017
   iterator upper_bound( const T& value);

   /// @since  x.y.z, 23.04.2017
   const_iterator upper_bound( const T& value) const;

   void clear();

   /// 
   /// @param[in]  pos  .
   /// @return  .
   /// @since  x.y.z, 24.04.2017
   iterator erase( iterator pos);

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
   /// @since x.y.z, 03.04.2017
   node_t* recursiveCopy( size_t count, node_t* parent,
                          const_iterator& other_iter);
   /// @since  x.y.z, 03.04.2017
   node_t* findNode( const T& value) const;
   /// @since  x.y.z, 03.04.2017
   node_t* lowerBoundNode( const T& value) const;
   /// @since  x.y.z, 23.04.2017
   node_t* upperBoundNode( const T& value) const;
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;
   iterator erase_root();

   size_t mCount = 0;
 
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
   mpRoot()
{
   if (this != &other)
   {
      mpRoot = other.mpRoot;
      mCount = other.mCount;
   } // end if
} // BinaryTree< T>::BinaryTree


template< typename T> BinaryTree< T>::~BinaryTree()
{
   clear();
} // BinaryTree< T>::~BinaryTree


template< typename T> void BinaryTree< T>::assign( const BinaryTree& other)
{
   if (this != &other)
   {
      clear();
      mCount = other.mCount;
      auto  other_iter( other.cbegin());
      mpRoot.reset( recursiveCopy( mCount, nullptr, other_iter));
   } // end if
} // BinaryTree< T>::assign


template< typename T> auto BinaryTree< T>::insert( const T& value)
{
   if (!mpRoot)
   {
      mpRoot = std::make_unique< node_t>( value);
      mCount = 1;
      return std::pair< iterator, bool>( begin(), true);
   } // end if

   return recursiveInsert( mpRoot.get(), value);
} // BinaryTree< T>::BinaryTree


template< typename T>
   typename BinaryTree< T>::iterator BinaryTree< T>::find( const T& value)
{
   return iterator( findNode( value));
} //


template< typename T>
   typename BinaryTree< T>::const_iterator
      BinaryTree< T>::find( const T& value) const
{
   return const_iterator( findNode( value));
} //


template< typename T>
   typename BinaryTree< T>::iterator
      BinaryTree< T>::lower_bound( const T& value)
{
   return iterator( lowerBoundNode( value));
} // 


template< typename T>
   typename BinaryTree< T>::const_iterator
      BinaryTree< T>::lower_bound( const T& value) const
{
   return const_iterator( lowerBoundNode( value));
} // 


template< typename T>
   typename BinaryTree< T>::iterator
      BinaryTree< T>::upper_bound( const T& value)
{
   return iterator( upperBoundNode( value));
} // 


template< typename T>
   typename BinaryTree< T>::const_iterator
      BinaryTree< T>::upper_bound( const T& value) const
{
   return const_iterator( upperBoundNode( value));
} // 


template< typename T> void BinaryTree< T>::clear()
{
   mpRoot.reset();
   mCount = 0;
} // BinaryTree< T>::clear


template< typename T>
   typename BinaryTree< T>::iterator BinaryTree< T>::erase( iterator pos)
{
   if (pos == end())
      return iterator();

   if (mpRoot == pos)
      return erase_root();

   auto  next = pos;
   ++next;

   auto  node_to_delete = static_cast< node_t*>( pos);
   --mCount;

   if (!node_to_delete->left && !node_to_delete->right)
   {
      // delete a leaf
      node_to_delete->parent.reset();
      return next;
   } // end if

   if (!node_to_delete->right)
   {
      node_to_delete->parent->replaceChild( node_to_delete, node_to_delete->left.release());
      return next;
   } // end if

   if (!node_to_delete->left)
   {
      // no left sub-tree: right moves up
      node_to_delete->parent->replaceChild( node_to_delete, node_to_delete->right.release());
      return next;
   } // end if

   // both left and right sub-trees exist
   // set next greater node as new root
   auto  next_node = static_cast< node_t*>( next);

   // re-attach right sub-tree, if there is one
   if (next_node->right)
      next_node->parent->releaseReplaceChild( next_node, next_node->right.release());
   else
      // detach from previous position to make sure the node is not deleted
      next_node->parent->releaseChild( next_node);

   // now we have the new root node, completely detached
   next_node->left.reset( node_to_delete->left.release());
   next_node->right.reset( node_to_delete->right.release());
   next_node->parent = node_to_delete->parent;
   return next;
} // 


template< typename T> bool BinaryTree< T>::empty() const
{
   return !mpRoot;
} // BinaryTree< T>::empty


template< typename T> std::size_t BinaryTree< T>::size() const
{
//   std::size_t  count = 0;
//   recursiveVisit( mpRoot.get(), [&count]( auto const&) { ++count; });
   return mCount;
} // BinaryTree< T>::size


template< typename T> typename BinaryTree< T>::iterator BinaryTree< T>::begin()
{
   return mpRoot ? iterator( first()) : iterator();
} // BinaryTree< T>::begin


template< typename T>
   typename BinaryTree< T>::const_iterator BinaryTree< T>::cbegin() const
{
   return mpRoot ? const_iterator( first()) : const_iterator();
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
   return mpRoot ? reverse_iterator( last()) : reverse_iterator();
} // BinaryTree< T>::rbegin


template< typename T>
   typename BinaryTree< T>::const_reverse_iterator BinaryTree< T>::crbegin() const
{
   return mpRoot ? const_reverse_iterator( last()) : const_reverse_iterator();
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
         ++mCount;
         return std::pair< iterator, bool>( iterator( parent_node->left.get()), true);
      } // end if
      return recursiveInsert( parent_node->left.get(), new_value);
   } // end if
   
   if (parent_node->value < new_value)
   {
      if (!parent_node->right)
      {
         parent_node->right = std::make_unique< node_t>( new_value, parent_node);
         ++mCount;
         return std::pair< iterator, bool>( iterator( parent_node->right.get()), true);   // @@@
      } // end if
      return recursiveInsert( parent_node->right.get(), new_value);
   } // end if

   // values are equal, something we don't support:
   return std::pair< iterator, bool>( iterator( parent_node), false);
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


template< typename T>
   typename BinaryTree< T>::node_t*
      BinaryTree< T>::recursiveCopy( size_t count, node_t* parent,
                                     const_iterator& other_iter)
{
   if (count == 0)
      return nullptr;

   auto  new_node = new node_t( parent);

   // first insert element(s) into left sub-tree
   new_node->left.reset( recursiveCopy( count / 2, new_node, other_iter));

   // (only) now we can assign the value and increment the iterator
   new_node->value = *other_iter;
   ++other_iter;

   // finally, insert element(s) into the right sub-tree
   new_node->right.reset( recursiveCopy( count - 1 - (count / 2), new_node,
                                         other_iter));

   return new_node;
} // 


template< typename T>
   typename BinaryTree< T>::node_t*
      BinaryTree< T>::findNode( const T& value) const
{
   auto  current = mpRoot.get();
   while (current != nullptr)
   {
      if (value < current->value)
         current = current->left.get();
      else if (current->value < value)
         current = current->right.get();
      else
         return current;
   } // end while
   return nullptr;
} //


template< typename T>
   typename BinaryTree< T>::node_t*
      BinaryTree< T>::lowerBoundNode( const T& value) const
{
   auto     current = mpRoot.get();
   node_t*  first_upper = nullptr;
   while (current != nullptr)
   {
      if (value < current->value)
      {
         // may already be the first upper
         first_upper = current;
         current     = current->left.get();
      } else if (current->value < value)
      {
         // value stored in node is less than the value we are looking for
         // could still have a match in the right sub-tree
         current = current->right.get();
      } else
      {
         // equality is the best match for lower bound
         return current;
      } // end if
   } // end while
   return first_upper;
} //


template< typename T>
   typename BinaryTree< T>::node_t*
      BinaryTree< T>::upperBoundNode( const T& value) const
{
   auto     current = mpRoot.get();
   node_t*  first_upper = nullptr;
   while (current != nullptr)
   {
      if (value < current->value)
      {
         // may already be the first upper
         if ((first_upper == nullptr) || (current->value < first_upper->value))
            first_upper = current;
         current = current->left.get();
      } else
      {
         // value stored in node is less than or equal to the value we are
         // looking for
         // could still have a greater value in the right sub-tree
         current = current->right.get();
      } // end if
   } // end while
   return first_upper;
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


template< typename T>
   typename BinaryTree< T>::iterator BinaryTree< T>::erase_root()
{
   if (!mpRoot.left && !mpRoot.right)
   {
      // last element removed from tree
      mpRoot.reset();
      mCount = 0;
      return iterator();
   } // end if
   if (!mpRoot.right)
   {
      // no right sub-tree: left is new root
      mpRoot.reset( mpRoot.left.release());
      mpRoot.parent = nullptr;
      --mCount;
      return iterator();
   } // end if
   if (!mpRoot.left)
   {
      // no left sub-tree: right is new root
      mpRoot.reset( mpRoot.right.release());
      mpRoot.parent = nullptr;
      --mCount;
      return iterator( mpRoot);
   } // end if
   // both left and right sub-trees exist
   // set next greater node as new root
   auto  new_root = mpRoot->increment();
   // re-attach right sub-tree, if there is one
   if (new_root->right)
      new_root->parent.releaseReplaceChild( new_root, new_root->right.release());
   else
      // detach from previous position to make sure the node is not deleted
      new_root->parent.releaseChild( new_root);
   // now we have the new root node, completely detached
   new_root->left.reset( mpRoot.left.release());
   new_root->right.reset( mpRoot.right.release());
   new_root->parent = nullptr;
   mpRoot.reset( new_root);
   --mCount;
   return iterator( mpRoot);
} // 


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BINARY_TREE_HPP


// =========================  END OF binary_tree.hpp  =========================

