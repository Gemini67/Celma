
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
/// See documentation of template class celma::containers::BalancedBinaryTree<>.


#ifndef CELMA_CONTAINERS_BALANCED_BINARY_TREE_HPP
#define CELMA_CONTAINERS_BALANCED_BINARY_TREE_HPP


#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include "celma/containers/detail/balanced_binary_tree_node.hpp"
#include "celma/containers/detail/tree_iterator.hpp"


namespace celma { namespace containers {


/// Implementation of a balanced binary tree.
///
/// @tparam  T
///    The type of the values to store.
/// @tparam  C
///    The type of the less-comparison function to use, default: std::less<>.
/// @since  x.y.z, 02.04.2017
///    (integration into Celma started)
/// @since  31.12.2002
///    (original implementation)
template< typename T, typename C = std::less< T>> class BalancedBinaryTree
{
public:
   /// Type of the nodes with which the binary tree is built.
   using node_t = detail::BalancedBinaryTreeNode< T>;
   /// Type of the iterator.
   using iterator = detail::TreeIterator< node_t>;
   /// Type of the const iterator.
   using const_iterator = detail::ConstTreeIterator< node_t>;
   /// Type of the reverse iterator.
   using reverse_iterator = detail::ReverseTreeIterator< node_t>;
   /// Type of the const reverse iterator.
   using const_reverse_iterator = detail::ConstReverseTreeIterator< node_t>;

   /// @since  x.y.z, 02.04.2017
   BalancedBinaryTree() = default;
   BalancedBinaryTree( const BalancedBinaryTree& other);
   BalancedBinaryTree( BalancedBinaryTree&& other);
   ~BalancedBinaryTree() = default;

   /// Insert the given data into the tree.
   ///
   /// @param[in]  data  The data to insert in the tree.
   /// @return
   ///    Pair with an iterator that points to the node with the data in the
   ///    tree and a boolean flag set to \c true when the data could be
   ///    inserted, an end() iterator and \c false otherwise.
   /// @since  x.y.z, 31.12.2002
   std::pair< iterator, bool> insert( const T& data);

   /// Deletes the given element.
   ///
   /// @param[in]  data  The key data of the element to delete.
   /// @return
   ///    Iterator pointing to the next greater node in the tree, end() when the
   ///    data was not found in the tree or there was no greater node left.
   /// @since  x.y.z, 12.09.2018
   iterator erase( const T& data);

   /// Deletes the node that the iterator points to.
   ///
   /// @param[in]  it  Iterator pointing to the node to delete.
   /// @return
   ///    Iterator pointing to the next greater node in the tree, end() when
   ///    there was no greater node left.
   /// @since  x.y.z, 19.02.2019
   iterator erase( iterator it);

   /// Deletes the node that the iterator points to.
   ///
   /// @param[in]  it  Iterator pointing to the node to delete.
   /// @return
   ///    Const iterator pointing to the next greater node in the tree, end()
   ///    when there was no greater node left.
   /// @since  x.y.z, 19.02.2019
   const_iterator erase( const_iterator it);

   /// Searches the data in 'data' in the tree and returns an iterator pointing
   /// to them if found.
   ///
   /// @param[in]  data  Pointer to the data to search for.
   /// @return  Iterator pointing to the data or end() if not found.
   /// @since  x.y.z, 31.12.2002
   iterator find( const T& data);

   /// Searches the data in 'data' in the tree and returns an iterator pointing
   /// to them if found.
   ///
   /// @param[in]  data  Pointer to the data to search for.
   /// @return  Const iterator pointing to the data or end() if not found.
   /// @since  x.y.z, 31.12.2002
   const_iterator find( const T& data) const;

   /// Returns the lower bound for the given value, i.e. the last entry whose
   /// value is lower than or equal to the given value.
   ///
   /// @param[in]  value  The value to determine the lower bound for.
   /// @return
   ///    Iterator pointing to the last element in the tree whose value is less
   ///    than or equal to the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 19.02.2019
   iterator lower_bound( const T& data);

   /// Returns the lower bound for the given value, i.e. the last entry whose
   /// value is lower than or equal to the given value.
   ///
   /// @param[in]  value  The value to determine the lower bound for.
   /// @return
   ///    Const iterator pointing to the last element in the tree whose value is
   ///    less than or equal to the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 19.02.2019
   const_iterator lower_bound( const T& data) const;

   /// Returns the upper bound for the given value, i.e. the first entry whose
   /// value is greater than the given value.
   ///
   /// @param[in]  value  The value to determine the upper bound for.
   /// @return
   ///    Iterator pointing to the first element in the tree whose value is
   ///    greater than the given value. Points to end() if \a value is greater
   ///    than the greatest value stored in the tree.
   /// @since  x.y.z, 19.02.2019
   iterator upper_bound( const T& data);

   /// Returns the upper bound for the given value, i.e. the first entry whose
   /// value is greater than the given value.
   ///
   /// @param[in]  value  The value to determine the upper bound for.
   /// @return
   ///    Const iterator pointing to the first element in the tree whose value
   ///    is greater than the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 19.02.2019
   const_iterator upper_bound( const T& data) const;

   std::pair< iterator, iterator> equal_range( const T& data);

   std::pair< const_iterator, const_iterator> equal_range( const T& data) const;

   /// Returns an iterator pointing to the first element in the tree.
   ///
   /// @return  Iterator pointing to the first element in the tree.
   /// @since  x.y.z, 02.04.2017
   iterator begin();

   /// Returns a const iterator pointing to the first element in the tree.
   ///
   /// @return  Const iterator pointing to the first element in the tree.
   /// @since  x.y.z, 02.04.2017
   const_iterator cbegin() const;

   /// Returns an iterator pointing behind the last element in the tree.
   ///
   /// @return  Iterator pointing behind the last element in the tree.
   /// @since  x.y.z, 02.04.2017
   iterator end();

   /// Returns a const iterator pointing behind the last element in the tree.
   ///
   /// @return  Const iterator pointing behind the last element in the tree.
   /// @since  x.y.z, 02.04.2017
   const_iterator cend() const;

   /// Returns a reverse iterator pointing to the last element in the tree.
   ///
   /// @return  Reverse iterator pointing to the last element in the tree.
   /// @since  x.y.z, 02.04.2017
   reverse_iterator rbegin();

   /// Returns a const reverse iterator pointing to the last element in the tree.
   ///
   /// @return  Const reverse iterator pointing to the last element in the tree.
   /// @since  x.y.z, 02.04.2017
   const_reverse_iterator crbegin() const;

   /// Returns a reverse iterator pointing before the first element in the tree.
   ///
   /// @return  Reverse iterator pointing before the first element in the tree.
   /// @since  x.y.z, 02.04.2017
   reverse_iterator rend();

   /// Returns a const reverse iterator pointing before the first element in the
   /// tree.
   ///
   /// @return
   ///    Const reverse iterator pointing before the first element in the tree.
   /// @since  x.y.z, 02.04.2017
   const_reverse_iterator crend() const;

   /// Deletes all entries in the tree.
   ///
   /// @since  x.y.z, 31.12.2002
   void clear();

   /// Returns the number of entries in the tree.
   ///
   /// @return  The number of entries in the tree.
   /// @since  x.y.z, 31.12.2002
   size_t size() const;

   /// Returns if the tree is currently empty.
   ///
   /// @return  \c true if the tree is empty.
   /// @since  x.y.z, 19.02.2019
   bool empty() const;

   /// Checks the tree structure and the order.
   ///
   /// @return  \c true if no error was found.
   /// @since  x.y.z, 19.02.2019
   bool check() const;

private:
   /// Returns the node with the next greater value, starting from the given
   /// node. If a matching node is found, it is unlinked from the tree
   /// structure.
   ///
   /// @param[in]  start
   ///    The node to start the search from.
   /// @param[in]  act_x
   ///    Pointer to the node with that value for which the next-greater is
   ///    required.
   /// @param[in]  level
   ///    0 if the found node should be attached to left child pointer in
   ///    \a start, 1 to attach to the right child pointer..
   /// @return
   ///    Pointer to the greater node that was found, NULL if no mathing node
   ///    was found.
   /// @since  x.y.z, 31.12.2002
   node_t* getUnlinkedGreater( node_t* start, node_t* act_x, int8_t level) const;

   /// Returns the node with the next smaller value, starting from the given
   /// node. If a matching node is found, it is unlinked from the tree
   /// structure.
   ///
   /// @param[in]  start
   ///    The node to start the search from.
   /// @param[in]  act_x
   ///    Pointer to the node with that value for which the next-smaller is
   ///    required.
   /// @param[in]  level
   ///    0 if the found node should be attached to left child pointer in
   ///    \a start, 1 to attach to the right child pointer..
   /// @return
   ///    Pointer to the smaller node that was found, NULL if no mathing node
   ///    was found.
   /// @since  x.y.z, 31.12.2002
   node_t* getUnlinkedSmaller( node_t* start, node_t* act_x, int8_t level) const;

   /// Unlinks the node old node from the tree, replacing it with the new node.
   /// 
   /// @param[in]  oldEle
   ///    Pointer to the old node that should be unlinked from the tree.
   /// @param[in]  newEle
   ///    Pointer to the new node that should be linked into the tree instead.
   /// @since  x.y.z, 31.12.2002
   void replace( node_t* oldEle, node_t* newEle);

   /// Recursively iterates over the tree to find the position to insert the new
   /// node/data.<br>
   /// If a subtree would become unbalanced by the insert, the subtree is re-
   /// balanced first.
   ///
   /// @param[in]  start
   ///    The pointer in the parent node into which's subtree the new data will
   ///    be inserted.
   /// @param[in]  before
   ///    Pointer to the parent node.
   /// @param[in]  data
   ///    The new node with the new data to insert.
   /// @return
   ///    \c true if the insert was successful, i.e. no node with the same data
   ///    was found.
   /// @since  x.y.z, 31.12.2002
   bool recursiveInsert( std::unique_ptr< node_t>& start, node_t* before,
      node_t* data);

   /// Unlinks the node pointed to by 'del_x' from the tree.
   /// The node itself is not deleted.
   bool recursiveDelete( node_t*& remove_node, node_t*& next_greater,
      std::unique_ptr< node_t>& start, node_t* del_x);

   /// Copies the contents from one subtree into a new subtree.
   ///
   /// @param[in]  from
   ///    The pointer to the node/subtree to copy from.
   /// @param[in]  prev
   ///    Pointer to the parent node of the new subtree.
   /// @return  Pointer to the new node/subtree that was created.
   /// @since  x.y.z, 31.12.2002
   node_t* recursiveCopy( node_t* from, node_t* prev);

   /// 
   /// @param[in]  value
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 21.02.2019
   node_t* lowerBoundNode( const T& value) const;

   /// 
   /// @param[in]  value
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 21.02.2019
   node_t* upperBoundNode( const T& value) const;

   /// Recursively iterates over all nodes in the balanced binary tree and calls
   /// the given functor for each node.
   ///
   /// @param[in]  current_node
   ///    Pointer to the next node to visit.
   /// @param[in]  fun
   ///    The functor to call for each node.
   /// @since  x.y.z, 20.02.2018
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;

   std::unique_ptr< node_t>  mpRoot;
   size_t                    mEntries = 0;
   C                         mCompareLess;

}; // BalancedBinaryTree< T, C>


// inlined methods
// ===============


template< typename T, typename C>
   BalancedBinaryTree< T, C>::BalancedBinaryTree( const BalancedBinaryTree& other)
{

   mEntries = other.mEntries;

   mpRoot.reset( recursiveCopy( other.mpRoot.get(), nullptr));

} // BalancedBinaryTree< T, C>::BalancedBinaryTree


template< typename T, typename C>
   BalancedBinaryTree< T, C>::BalancedBinaryTree( BalancedBinaryTree&& other):
      mpRoot( std::move( other.mpRoot))
{
} // BalancedBinaryTree< T, C>::BalancedBinaryTree


template< typename T, typename C>
   std::pair< typename BalancedBinaryTree< T, C>::iterator, bool>
      BalancedBinaryTree< T, C>::insert( const T& data)
{

   node_t*     new_ele = new node_t( data);
   const bool  result = recursiveInsert( mpRoot, nullptr, new_ele);

   if (result)
   {
      ++mEntries;
      return std::pair< iterator, bool>( iterator( new_ele), true);
   } // end if

   // insert failed, have to delete newly allocated element
   delete new_ele;

   return std::pair< iterator, bool>( end(), false);
} // BalancedBinaryTree< T, C>::insert


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::erase( const T& data)
{

   auto  remove_node = find( data);

   if (remove_node != end())
   {
      return erase( remove_node);
   } // end if

   return end();
} // BalancedBinaryTree< T, C>::erase


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::erase( iterator it)
{

   node_t*  remove_node = nullptr;
   node_t*  next_node = nullptr;

   if (recursiveDelete( remove_node, next_node, mpRoot, static_cast< node_t*>( it)))
   {
      // RecursiveDelete only removes the node from the tree, so:
      delete remove_node;
      --mEntries;
      return (next_node != nullptr) ? iterator( next_node) : end();
   } // end if

   return end();
} // BalancedBinaryTree< T, C>::erase


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::erase( const_iterator it)
{
   return erase( *it);
} // BalancedBinaryTree< T, C>::erase


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::find( const T& data)
{

   node_t*  act = mpRoot.get();

   while (act != nullptr)
   {
      if (mCompareLess( data, act->mValue))
      {
         act = act->left();
      } else if (mCompareLess( act->mValue, data))
      {
         act = act->right();
      } else
      {
         // equal
         break;
      } // end if
   } // end while

   if (act != nullptr)
      return iterator( act);

   return end();
} // BalancedBinaryTree< T, C>::find


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::find( const T& data) const
{

   node_t*  act = mpRoot.get();

   while (act != nullptr)
   {
      if (mCompareLess( data, act->mValue))
      {
         act = act->left();
      } else if (mCompareLess( act->mValue, data))
      {
         act = act->right();
      } else
      {
         // equal
         break;
      } // end if
   } // end while

   if (act != nullptr)
      return const_iterator( act);

   return cend();
} // BalancedBinaryTree< T, C>::find


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::lower_bound( const T& data)
{
   return iterator( lowerBoundNode( data));
} // BalancedBinaryTree< T, C>::lower_bound


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::lower_bound( const T& data) const
{
   return const_iterator( lowerBoundNode( data));
} // BalancedBinaryTree< T, C>::lower_bound


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::upper_bound( const T& data)
{
   return iterator( upperBoundNode( data));
} // BalancedBinaryTree< T, C>::upper_bound


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::upper_bound( const T& data) const
{
   return const_iterator( upperBoundNode( data));
} // BalancedBinaryTree< T, C>::upper_bound


template< typename T, typename C>
   std::pair< typename BalancedBinaryTree< T, C>::iterator,
      typename BalancedBinaryTree< T, C>::iterator>
         BalancedBinaryTree< T, C>::equal_range( const T& data)
{
   return std::pair< iterator, iterator>( lower_bound( data), upper_bound( data));
} // BalancedBinaryTree< T, C>::equal_range


template< typename T, typename C>
   std::pair< typename BalancedBinaryTree< T, C>::const_iterator,
      typename BalancedBinaryTree< T, C>::const_iterator>
         BalancedBinaryTree< T, C>::equal_range( const T& data) const
{
   return std::pair< const_iterator, const_iterator>( lower_bound( data),
      upper_bound( data));
} // BalancedBinaryTree< T, C>::equal_range


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator
      BalancedBinaryTree< T, C>::begin()
{

   return mpRoot ? iterator( mpRoot->first()) : iterator();
} // BalancedBinaryTree< T, C>::begin


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::cbegin() const
{

   return mpRoot ? const_iterator( mpRoot->first()) : const_iterator();
} // BalancedBinaryTree< T, C>::cbegin


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::iterator BalancedBinaryTree< T, C>::end()
{

   return iterator();
} // BalancedBinaryTree< T, C>::end


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_iterator
      BalancedBinaryTree< T, C>::cend() const
{

   return const_iterator();
} // BalancedBinaryTree< T, C>::cend


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::reverse_iterator
      BalancedBinaryTree< T, C>::rbegin()
{
   return mpRoot ? reverse_iterator( mpRoot->last()) : reverse_iterator();
} // BalancedBinaryTree< T, C>::rbegin


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_reverse_iterator
      BalancedBinaryTree< T, C>::crbegin() const
{
   return mpRoot ? const_reverse_iterator( mpRoot->last()) : const_reverse_iterator();
} // BalancedBinaryTree< T, C>::crbegin


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::reverse_iterator
      BalancedBinaryTree< T, C>::rend()
{
   return reverse_iterator();
} // BalancedBinaryTree< T, C>::rend


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::const_reverse_iterator
      BalancedBinaryTree< T, C>::crend() const
{
   return const_reverse_iterator();
} // BalancedBinaryTree< T, C>::crend


template< typename T, typename C> void BalancedBinaryTree< T, C>::clear()
{

   if (mpRoot)
   {
      mpRoot.reset();
      mEntries = 0;
   } // end if

} // BalancedBinaryTree< T, C>::clear


template< typename T, typename C> size_t BalancedBinaryTree< T, C>::size() const
{
   return mEntries;
} // BalancedBinaryTree< T, C>::size


template< typename T, typename C> bool BalancedBinaryTree< T, C>::empty() const
{
   return mEntries == 0;
} // BalancedBinaryTree< T, C>::empty


template< typename T, typename C> bool BalancedBinaryTree< T, C>::check() const
{
   if (!mpRoot)
      return true;

   bool    is_valid = (mpRoot->mpParent == nullptr)
      && (std::abs( mpRoot->mBalance) < 2);
   size_t  num_nodes = 0;

   recursiveVisit( mpRoot.get(), [&]( auto const& current_node)
      {
         ++num_nodes;
         if (std::abs( current_node->mBalance) >= 2)
         {
            is_valid = false;
         } else
         {
            if (current_node->mpLeft)
            {
               if (!mCompareLess( current_node->mpLeft->mValue, current_node->mValue))
               {
                  is_valid = false;
               } // end if
            } // end if
            if (current_node->mpRight)
            {
               if (!mCompareLess( current_node->mValue, current_node->mpRight->mValue))
               {
                  is_valid = false;
               } // end if
            } // end if
            is_valid = is_valid && current_node->check();
         } // end if
      }
   );
   return is_valid && (mEntries == num_nodes);
} // BalancedBinaryTree< T, C>::check


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::node_t*
      BalancedBinaryTree< T, C>::getUnlinkedGreater( node_t* start, node_t* act_x,
         int8_t level) const
{

   node_t*  was_removed = nullptr;

   if (start->mpLeft)
   {
      if ((was_removed = getUnlinkedGreater( start->left(), act_x, 1)) != nullptr)
      {
         // !NULL = was_removed = correct the balance
         ++start->mBalance;
      } // end if

   // there is no left (anymore), so the current node is the next greater
   // node/value that we were looking for
   } else if ((act_x == nullptr) || mCompareLess( start->mValue, act_x->mValue))
   {
      was_removed = start;
      // the current value meets the requirements
      if (level)
      {
         start->mpParent->mpLeft.release();
         start->mpParent->mpLeft.reset( start->mpRight.release());
      } else
      {
         start->mpParent->mpRight.release();
         start->mpParent->mpRight.reset( start->mpRight.release());
      } // end if
      if (start->mpRight)
         start->mpRight->mpParent = start->mpParent;
   } // end if

   return was_removed;
} // BalancedBinaryTree< T, C>::getUnlinkedGreater


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::node_t*
      BalancedBinaryTree< T, C>::getUnlinkedSmaller( node_t* start, node_t* act_x,
         int8_t level) const
{

   node_t*  was_removed = nullptr;


   if (start->mpRight)
   {
      if ((was_removed = getUnlinkedSmaller( start->right(), act_x, 1)) != nullptr)
      {
         // !NULL = was_removed = correct the balance
         --start->mBalance;
      } // end if

   // there is no right (anymore), so the current node is the next smaller
   // node/value that we were looking for
   } else if ((act_x == nullptr) || mCompareLess( act_x->mValue, start->mValue))
   {
      was_removed = start;
      // the current value meets the requirements
      if (level)
      {
         start->mpParent->mpRight.release();
         start->mpParent->mpRight.reset( start->mpLeft.release());
      } else
      {
         start->mpParent->mpLeft.release();
         start->mpParent->mpLeft.reset( start->mpLeft.release());
      } // end if
      if (start->mpLeft)
         start->mpLeft->mpParent = start->mpParent;
   } // end if

   return was_removed;
} // BalancedBinaryTree< T, C>::getUnlinkedSmaller


template< typename T, typename C>
   void BalancedBinaryTree< T, C>::replace( node_t* old_ele, node_t* new_ele)
{

   // reconnect the pointers of the parent node
   if ((new_ele->mpParent = old_ele->mpParent) != nullptr)
   {
      old_ele->mpParent->releaseReplaceChild( old_ele, new_ele);
   } else
   {
      mpRoot.release();
      mpRoot.reset( new_ele);
   } // end if

   new_ele->mBalance = old_ele->mBalance;

   // reconnect the child nodes
   new_ele->mpLeft.release();
   new_ele->mpLeft.reset( old_ele->mpLeft.release());
   if (new_ele->mpLeft)
   {
      new_ele->mpLeft->mpParent = new_ele;
   } // end if
   new_ele->mpRight.release();
   new_ele->mpRight.reset( old_ele->mpRight.release());
   if (new_ele->mpRight)
   {
      new_ele->mpRight->mpParent = new_ele;
   } // end if

} // BalancedBinaryTree< T, C>::replace


template< typename T, typename C>
   bool BalancedBinaryTree< T, C>::recursiveInsert( std::unique_ptr< node_t>& start,
                                                    node_t* before,
                                                    node_t* data)
{

   if (!start)
   {
      start.reset( data);
      data->mpParent = before;
      return true;
   } // end if
   
   node_t*  act = start.get();
   node_t*  found = nullptr;
   bool     result = false;

   if (mCompareLess( data->mValue, act->mValue))
   {
      // have to insert on the left
      if (act->mBalance - 1 > -2)
      {
         // can continue to insert on the left
         if ((result = recursiveInsert( act->mpLeft, act, data)))
         {
            --act->mBalance;
         } // end if
      } else if ((found = getUnlinkedSmaller( act->left(), data, 0)) != nullptr)
      {
         // have to re-order first -> look for the next-smaller
         // replace act by the one we found
         replace( act, found);
         if ((result = recursiveInsert( found->mpLeft, found, data)))
         {
            if ((result = recursiveInsert( found->mpRight, found, act)))
            {
               ++found->mBalance;
            } // end if
         } // end if
      } else
      {
         // the node we found is smaller tan the new one -> x becomes start
         replace( act, data);
         if ((result = recursiveInsert( data->mpRight, data, act)))
         {
            ++data->mBalance;
         } // end if
      } // end if
   } else if (mCompareLess( act->mValue, data->mValue))
   {
      // have to insert on the right
      if (act->mBalance + 1 < 2)
      {
         if ((result = recursiveInsert( act->mpRight, act, data)))
         {
            act->mBalance++;
         } // end if
      } else if ((found = getUnlinkedGreater( act->right(), data, 0)) != nullptr)
      {
         // have to re-order first -> look for the next-greater
         // replace act by the one we found
         replace( act, found);
         if ((result = recursiveInsert( found->mpRight, found, data)))
         {
            if ((result = recursiveInsert( found->mpLeft, found, act)))
            {
               --found->mBalance;
            } // end if
         } // end if
      } else
      {
         // the one we found is greater than the new entry -> x becomes start
         replace( act, data);
         if ((result = recursiveInsert( data->mpLeft, data, act)))
         {
            --data->mBalance;
         } // end if
      } // end if
   } else
   {
      // same data exists already
      errno = EEXIST;
      return false;
   } // end if

   return result;
} // BalancedBinaryTree< T, C>::recursiveInsert


template< typename T, typename C>
   bool BalancedBinaryTree< T, C>::recursiveDelete( node_t*& remove_node,
      node_t*& next_node, std::unique_ptr< node_t>& start, node_t* del_x)
{

   if (!start)
      return false;

   node_t*  act = start.get();
   bool     result = true;

   if (act == del_x)
   {
      // here it is
      remove_node = act;
      if (!act->mpLeft && !act->mpRight)
      {
         // no more children, so: have to delete the pointer in the parent only
         start.release();
      } else if (!act->mpLeft)
      {
         // unlink current node, move act's right node up
         act->mpRight->mpParent = act->mpParent;
         // right node must be a leaf, otherwise the subtree would be inbalanced
         // so the right node is the next greater
         next_node = act->mpRight.get();
         // now make the pointer that pointed to me point to my right
         start.release();
         start.reset( act->mpRight.release());
      } else if (!act->mpRight)
      {
         // unlink current node, move act's left up
         act->mpLeft->mpParent = act->mpParent;
         // parent node must be the next greater
         next_node = act->mpParent;
         // now make the pointer that pointed to me point to my left
         start.release();
         start.reset( act->mpLeft.release());

      // so we have a node with two children: replace by appropriate node
      } else if (act->mBalance == -1)
      {
         // subtree is heavier on the left side: look for smaller value
         // that is done by going left once and then search for the right-most
         // node in the subtree
         node_t*  found = act->decrement();
         if ((result = recursiveDelete( remove_node, next_node, act->mpLeft, found)))
         {
            replace( act, found);
            ++found->mBalance;
         } // end if
      } else
      {
         // subtree is fully balanced or heavier on the right side:
         // look for greater value
         node_t*  found = act->increment();
         if ((result = recursiveDelete( remove_node, next_node, act->mpRight, found)))
         {
            replace( act, found);
            --found->mBalance;
         } // end if
      } // end if
   } else if (mCompareLess( del_x->mValue, act->mValue))
   {
      if (act->mBalance + 1 < 2)
      {
         if ((result = recursiveDelete( remove_node, next_node, act->mpLeft, del_x)))
         {
            ++act->mBalance;
         } // end if
      } else
      {
         // we have to reorganise
         // this mean we look for the next-greater value, delete this node,
         // assign the value to the current node and insert the old value of
         // the current node
         // afterwards continue to delete
         node_t*  found = act->increment();
         if ((result = recursiveDelete( remove_node, next_node, act->mpRight, found)))
         {
            replace( act, found);
            recursiveInsert( found->mpLeft, found, act);
            if ((result = recursiveDelete( remove_node, next_node, found->mpLeft, del_x)))
            {
               --found->mBalance;
            } // end if
         } // end if
      } // end if
   } else if (act->mBalance - 1 > -2)
   {
      if ((result = recursiveDelete( remove_node, next_node, act->mpRight, del_x)))
      {
         --act->mBalance;
      } // end if
   } else
   {
      // we have to reorganise
      // this mean we look for the next-smaller value, delete this node,
      // assign the value to the current node and insert the old value of
      // the current node
      // afterwards continue to delete
      node_t*  found = act->decrement();
      if ((result = recursiveDelete( remove_node, next_node, act->mpLeft, found)))
      {
         replace( act, found);
         recursiveInsert( found->mpRight, found, act);
         if ((result = recursiveDelete( remove_node, next_node, found->mpRight,
            del_x)))
         {
            ++found->mBalance;
         } // end if
      } // end if
   } // end if

   return result;
} // BalancedBinaryTree< T, C>::recursiveDelete


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::node_t*
      BalancedBinaryTree< T, C>::recursiveCopy( node_t* from, node_t* prev)
{

   if (from == nullptr)
      return nullptr;

std::cout << "copy from node     " << from << ", value = " << from->mValue << ", balance = " << (int) from->mBalance << std::endl
          << "from->left         " << from->left() << ", from->right " << from->right() << std::endl;
   node_t*  new_ele = new node_t( from->mValue, prev);
std::cout << "allocated new node " << new_ele << ", value = " << new_ele->mValue << std::endl;

   new_ele->mBalance = from->mBalance;

   if (from->mpLeft)
      new_ele->mpLeft.reset( recursiveCopy( from->left(), new_ele));

   if (from->mpRight)
      new_ele->mpRight.reset( recursiveCopy( from->right(), new_ele));

   return new_ele;
} // BalancedBinaryTree< T, C>::recursiveCopy


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::node_t*
      BalancedBinaryTree< T, C>::lowerBoundNode( const T& value) const
{
   auto     current = mpRoot.get();
   node_t*  first_upper = nullptr;
   while (current != nullptr)
   {
      if (mCompareLess( value, current->mValue))
      {
         // may already be the first upper
         first_upper = current;
         current     = current->mpLeft.get();
      } else if (mCompareLess( current->mValue, value))
      {
         // value stored in node is less than the value we are looking for
         // could still have a match in the right sub-tree
         current = current->mpRight.get();
      } else
      {
         // equality is the best match for lower bound
         return current;
      } // end if
   } // end while
   return first_upper;
} // BalancedBinaryTree< T, C>::lowerBoundNode


template< typename T, typename C>
   typename BalancedBinaryTree< T, C>::node_t*
      BalancedBinaryTree< T, C>::upperBoundNode( const T& value) const
{
   auto     current = mpRoot.get();
   node_t*  first_upper = nullptr;
   while (current != nullptr)
   {
      if (mCompareLess( value, current->mValue))
      {
         // may already be the first upper
         if ((first_upper == nullptr)
             || (mCompareLess( current->mValue, first_upper->mValue)))
            first_upper = current;
         current = current->mpLeft.get();
      } else
      {
         // value stored in node is less than or equal to the value we are
         // looking for
         // could still have a greater value in the right sub-tree
         current = current->mpRight.get();
      } // end if
   } // end while
   return first_upper;
} // BalancedBinaryTree< T, C>::upperBoundNode


template< typename T, typename C> template< typename F>
   void BalancedBinaryTree< T, C>::recursiveVisit( node_t* current_node, F fun)
      const
{

   if (current_node == nullptr)
      return;

   recursiveVisit( current_node->mpLeft.get(), fun);

   fun( current_node);

   recursiveVisit( current_node->mpRight.get(), fun);

} // BalancedBinaryTree< T, C>::recursiveVisit


} // namespace containers
} // namespace celma


#endif // CELMA_CONTAINERS_BALANCED_BINARY_TREE_HPP


// ===== END OF balanced_binary_tree.hpp  =====
