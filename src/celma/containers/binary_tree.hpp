
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
/// See documentation of template class celma::containers::BinaryTree<>.


#ifndef CELMA_CONTAINERS_BINARY_TREE_HPP
#define CELMA_CONTAINERS_BINARY_TREE_HPP


#include <cassert>
#include <iterator>
#include <memory>
#include <utility>
#include "celma/containers/detail/binary_tree_node.hpp"
#include "celma/containers/detail/tree_iterator.hpp"


namespace celma { namespace containers {


/// A simple, non-balancing binary tree.<br>
/// Inserting values in order will result in a linked list.<br>
/// One way to balance a tree is to assign it to a new object.
///
/// @tparam  T
///    The type of the values to store in the binary tree.
/// @tparam  C
///    The comparator to use for comparing two values and building the sorted
///    tree.
/// @since
///    x.y.z, 24.03.2017
template< typename T, typename C = std::less< T>> class BinaryTree
{
public:
   /// Type of the nodes with which the binary tree is built.
   using node_t = detail::BinaryTreeNode< T>;
   /// Type of the iterator.
   using iterator = detail::TreeIterator< node_t>;
   /// Type of the const iterator.
   using const_iterator = detail::ConstTreeIterator< node_t>;
   /// Type of the reverse iterator.
   using reverse_iterator = detail::ReverseTreeIterator< node_t>;
   /// Type of the const reverse iterator.
   using const_reverse_iterator = detail::ConstReverseTreeIterator< node_t>;

   /// Default constructor, constructs an empty tree.
   ///
   /// @since  x.y.z, 24.03.2017
   BinaryTree() = default;

   /// Copy constructor.<br>
   /// Does not create an identical copy of the source tree, but an optimised
   /// (path-length wise) version.
   ///
   /// @param[in]  other  The other binary tree to copy the data from.
   /// @since  x.y.z, 24.03.2017
   BinaryTree( const BinaryTree& other);

   /// Move constructor. Takes the tree from the other object.
   ///
   /// @param[in]  other  The other object to take the tree from..
   /// @since  x.y.z, 24.03.2017
   BinaryTree( BinaryTree&& other);

   /// Destructor, removes the elements from the tree.
   ///
   /// @since  x.y.z, 24.03.2017
   ~BinaryTree() = default;

   /// Assigns the contents of another binary tree to this object.<br>
   /// The specialty of this function is that it always creates a well balanced
   /// tree.
   ///
   /// @param[in]  other  The other object to copy the data from.
   /// @since  x.y.z, 31.03.2017
   void assign( const BinaryTree& other);

   /// Inserts a new value into the binary tree.
   ///
   /// @param[in]  value  The value to insert.
   /// @return
   ///    A pair of values: An iterator pointing to the position of the element
   ///    inserted into the tree, and a boolean value that is \c false if the
   ///    insert fails: value already exists.
   /// @since  x.y.z, 27.03.2018
   auto insert( const T& value);

   /// Searches for the given value in the tree and returns its position, when
   /// found.
   ///
   /// @param[in]  value  The value to search for in the tree.
   /// @return
   ///    Iterator pointing to the element in the tree when the value was found,
   ///    end() iterator otherwise.
   /// @since  x.y.z, 03.04.2017
   iterator find( const T& value);

   /// Searches for the given value in the tree and returns its position, when
   /// found.
   ///
   /// @param[in]  value  The value to search for in the tree.
   /// @return
   ///    Const iterator pointing to the element in the tree when the value was
   ///    found, end() iterator otherwise.
   /// @since  x.y.z, 03.04.2017
   const_iterator find( const T& value) const;

   /// Returns the lower bound for the given value, i.e. the last entry whose
   /// value is lower than or equal to the given value.
   ///
   /// @param[in]  value  The value to determine the lower bound for.
   /// @return
   ///    Iterator pointing to the last element in the tree whose value is less
   ///    than or equal to the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 03.04.2017
   iterator lower_bound( const T& value);

   /// Returns the lower bound for the given value, i.e. the last entry whose
   /// value is lower than or equal to the given value.
   ///
   /// @param[in]  value  The value to determine the lower bound for.
   /// @return
   ///    Const iterator pointing to the last element in the tree whose value is
   ///    less than or equal to the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 03.04.2017
   const_iterator lower_bound( const T& value) const;

   /// Returns the upper bound for the given value, i.e. the first entry whose
   /// value is greater than the given value.
   ///
   /// @param[in]  value  The value to determine the upper bound for.
   /// @return
   ///    Iterator pointing to the first element in the tree whose value is
   ///    greater than the given value. Points to end() if \a value is greater
   ///    than the greatest value stored in the tree.
   /// @since  x.y.z, 23.04.2017
   iterator upper_bound( const T& value);

   /// Returns the upper bound for the given value, i.e. the first entry whose
   /// value is greater than the given value.
   ///
   /// @param[in]  value  The value to determine the upper bound for.
   /// @return
   ///    Const iterator pointing to the first element in the tree whose value
   ///    is greater than the given value. Points to end() if \a value is
   ///    greater than the greatest value stored in the tree.
   /// @since  x.y.z, 23.04.2017
   const_iterator upper_bound( const T& value) const;

   /// Clears the tree, i.e. removes all elements stored in the tree.
   ///
   /// @since  x.y.z, 24.03.2017
   void clear();

   /// Removes the element at the given position.
   ///
   /// @param[in]  pos  Iterator pointing to the element to remove.
   /// @return  Iterator pointing to the next element.
   /// @since  x.y.z, 24.04.2017
   iterator erase( iterator pos);

   /// Returns if the tree is empty.
   ///
   /// @return  \c true if the tree is empty.
   /// @since  x.y.z, 24.03.2017
   bool empty() const;

   /// Returns the size of the tree, i.e. the number of elements currently
   /// stored in the tree.
   ///
   /// @return  The number of elements currently stored in the tree.
   /// @since  x.y.z, 24.03.2017
   size_t size() const;

   /// Checks the pointer structure of the binary tree.
   ///
   /// @return  \c true if all pointers are pointing to the correct node.
   /// @since  x.y.z, 06.02.2019
   bool check() const;

   // iterators

   /// Returns an iterator pointing to the first element in the tree.
   ///
   /// @return  Iterator pointing to the first element in the tree.
   /// @since  x.y.z, 24.03.2017
   iterator begin();

   /// Returns a const iterator pointing to the first element in the tree.
   ///
   /// @return  Const iterator pointing to the first element in the tree.
   /// @since  x.y.z, 24.03.2017
   const_iterator cbegin() const;

   /// Returns an iterator pointing behind the last element in the tree.
   ///
   /// @return  Iterator pointing behind the last element in the tree.
   /// @since  x.y.z, 24.03.2017
   iterator end();

   /// Returns a const iterator pointing behind the last element in the tree.
   ///
   /// @return  Const iterator pointing behind the last element in the tree.
   /// @since  x.y.z, 24.03.2017
   const_iterator cend() const;

   /// Returns a reverse iterator pointing to the last element in the tree.
   ///
   /// @return  Reverse iterator pointing to the last element in the tree.
   /// @since  x.y.z, 31.03.2017
   reverse_iterator rbegin();

   /// Returns a const reverse iterator pointing to the last element in the tree.
   ///
   /// @return  Const reverse iterator pointing to the last element in the tree.
   /// @since  x.y.z, 31.03.2017
   const_reverse_iterator crbegin() const;

   /// Returns a reverse iterator pointing before the first element in the tree.
   ///
   /// @return  Reverse iterator pointing before the first element in the tree.
   /// @since  x.y.z, 31.03.2017
   reverse_iterator rend();

   /// Returns a const reverse iterator pointing before the first element in the
   /// tree.
   ///
   /// @return
   ///    Const reverse iterator pointing before the first element in the tree.
   /// @since  x.y.z, 31.03.2017
   const_reverse_iterator crend() const;

   /// Assignment operator, copies the elements from the other binary tree.
   ///
   /// @param[in]  other  The other binary tree to copy the data from.
   /// @return  This object.
   /// @since  x.y.z, 31.03.2017
   BinaryTree& operator =( const BinaryTree& other);

protected:
   /// Pointer to the root node of the binary tree.
   std::unique_ptr< node_t>  mpRoot;

private:
   /// Recursively iterates down the tree until the position to insert a new
   /// element/value is found.
   ///
   /// @param[in]  parent_node
   ///    Pointer to the parent node to try to append the element to.
   /// @param[in]  new_value
   ///    The new value to insert into the tree.
   /// @return
   ///    Pair of iterator pointing to the newly inserted element/value and a
   ///    boolean value that indicates if the insert operation was successful.
   /// @since  x.y.z, 28.03.2018
   auto recursiveInsert( node_t* parent_node, const T& new_value);

   /// Helper function to recursively copy the contents of one binary tree into
   /// this on.
   ///
   /// @param[in]  count
   ///    Number of remaining elements to copy into this subtree.
   /// @param[in]  parent
   ///    Pointer to the parent node.
   /// @param[in]  other_iter
   ///    Iterator for getting the values to insert from the other tree.
   /// @return  Pointer to the new node that was created.
   /// @since  x.y.z, 03.04.2017
   node_t* recursiveCopy( size_t count, node_t* parent,
                          const_iterator& other_iter);

   /// Tries to non-recursively find the node with the given value.
   ///
   /// @param[in]  value  The value to search in the binary tree.
   /// @return
   ///    Pointer to the node that contains the given value, nullptr if the
   ///    value was not found.
   /// @since  x.y.z, 03.04.2017
   node_t* findNode( const T& value) const;

   /// Tries to non-recursively find the last node that contains a value that is
   /// less than or equal to the given value.
   ///
   /// @param[in]  value  The value to search the lower bound for.
   /// @return
   ///    Pointer to the node that contains the lower bound, nullptr if no
   ///    matching node was not found.
   /// @since  x.y.z, 03.04.2017
   node_t* lowerBoundNode( const T& value) const;

   /// Tries to non-recursively find the first node that contains a value that
   /// is greater than the given value.
   ///
   /// @param[in]  value  The value to search the upper bound for.
   /// @return
   ///    Pointer to the node that contains the upper bound, nullptr if no
   ///    matching node was not found.
   /// @since  x.y.z, 03.04.2017
   node_t* upperBoundNode( const T& value) const;

   /// Recursively iterates over all nodes in the binary tree and calls the
   /// given functor for each node.
   ///
   /// @param[in]  current_node
   ///    Pointer to the next node to visit.
   /// @param[in]  fun
   ///    The functor to call for each node.
   /// @since  x.y.z, 24.03.2017
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;

   /// Object with the comparator that is used to compare two values.
   C       mCompareLess;
   /// Number of elements/values currently in the tree.
   size_t  mCount = 0;
 
}; // BinaryTree< T, C>


// inlined methods
// ===============


template< typename T, typename C> BinaryTree< T, C>::BinaryTree( const BinaryTree& other):
   mpRoot()
{
   assign( other);
} // BinaryTree< T, C>::BinaryTree


template< typename T, typename C> BinaryTree< T, C>::BinaryTree( BinaryTree&& other):
   mpRoot()
{
   if (this != &other)
   {
      mpRoot = other.mpRoot;
      mCount = other.mCount;
   } // end if
} // BinaryTree< T, C>::BinaryTree


template< typename T, typename C> void BinaryTree< T, C>::assign( const BinaryTree& other)
{
   if (this != &other)
   {
      clear();
      mCount = other.mCount;
      if (mCount > 0)
      {
         auto  other_iter( other.cbegin());
         mpRoot.reset( recursiveCopy( mCount, nullptr, other_iter));
      } // end if
   } // end if
} // BinaryTree< T, C>::assign


template< typename T, typename C> auto BinaryTree< T, C>::insert( const T& value)
{
   if (!mpRoot)
   {
      mpRoot = std::make_unique< node_t>( value);
      mCount = 1;
      return std::pair< iterator, bool>( begin(), true);
   } // end if

   return recursiveInsert( mpRoot.get(), value);
} // BinaryTree< T, C>::BinaryTree


template< typename T, typename C>
   typename BinaryTree< T, C>::iterator BinaryTree< T, C>::find( const T& value)
{
   return iterator( findNode( value));
} // BinaryTree< T, C>::find


template< typename T, typename C>
   typename BinaryTree< T, C>::const_iterator
      BinaryTree< T, C>::find( const T& value) const
{
   return const_iterator( findNode( value));
} // BinaryTree< T, C>::find


template< typename T, typename C>
   typename BinaryTree< T, C>::iterator
      BinaryTree< T, C>::lower_bound( const T& value)
{
   return iterator( lowerBoundNode( value));
} // BinaryTree< T, C>::lower_bound


template< typename T, typename C>
   typename BinaryTree< T, C>::const_iterator
      BinaryTree< T, C>::lower_bound( const T& value) const
{
   return const_iterator( lowerBoundNode( value));
} // BinaryTree< T, C>::lower_bound


template< typename T, typename C>
   typename BinaryTree< T, C>::iterator
      BinaryTree< T, C>::upper_bound( const T& value)
{
   return iterator( upperBoundNode( value));
} // BinaryTree< T, C>::upper_bound


template< typename T, typename C>
   typename BinaryTree< T, C>::const_iterator
      BinaryTree< T, C>::upper_bound( const T& value) const
{
   return const_iterator( upperBoundNode( value));
} // BinaryTree< T, C>::upper_bound


template< typename T, typename C> void BinaryTree< T, C>::clear()
{
   mpRoot.reset();
   mCount = 0;
} // BinaryTree< T, C>::clear


template< typename T, typename C>
   typename BinaryTree< T, C>::iterator BinaryTree< T, C>::erase( iterator pos)
{
   if (pos == end())
      return iterator();

   auto  node_to_delete = static_cast< node_t*>( pos);
   auto  next_greater = node_to_delete->increment();
   auto  new_root = node_to_delete->detach( next_greater);

   --mCount;

   if (mpRoot.get() == node_to_delete)
      mpRoot.reset( new_root);
   else
      // if the node to delete was not the root node, it must be deleted now
      delete node_to_delete;

   return iterator( next_greater);
} // BinaryTree< T, C>::erase


template< typename T, typename C> bool BinaryTree< T, C>::empty() const
{
   return !mpRoot;
} // BinaryTree< T, C>::empty


template< typename T, typename C> std::size_t BinaryTree< T, C>::size() const
{
//   std::size_t  count = 0;
//   recursiveVisit( mpRoot.get(), [&count]( auto const&) { ++count; });
   return mCount;
} // BinaryTree< T, C>::size


template< typename T, typename C> bool BinaryTree< T, C>::check() const
{
   if (!mpRoot)
      return true;
   bool    is_valid = (mpRoot->mpParent == nullptr);
   size_t  num_nodes = 0;
   recursiveVisit( mpRoot.get(), [&]( auto const& current_node)
      {
         ++num_nodes;
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
      }
   );
   return is_valid && (mCount == num_nodes);
} // BinaryTree< T, C>::check

template< typename T, typename C> typename BinaryTree< T, C>::iterator BinaryTree< T, C>::begin()
{
   return mpRoot ? iterator( mpRoot->first()) : iterator();
} // BinaryTree< T, C>::begin


template< typename T, typename C>
   typename BinaryTree< T, C>::const_iterator BinaryTree< T, C>::cbegin() const
{
   return mpRoot ? const_iterator( mpRoot->first()) : const_iterator();
} // BinaryTree< T, C>::cbegin


template< typename T, typename C> typename BinaryTree< T, C>::iterator BinaryTree< T, C>::end()
{
   return iterator();
} // BinaryTree< T, C>::end


template< typename T, typename C>
   typename BinaryTree< T, C>::const_iterator BinaryTree< T, C>::cend() const
{
   return const_iterator();
} // BinaryTree< T, C>::cend


template< typename T, typename C>
   typename BinaryTree< T, C>::reverse_iterator BinaryTree< T, C>::rbegin()
{
   return mpRoot ? reverse_iterator( mpRoot->last()) : reverse_iterator();
} // BinaryTree< T, C>::rbegin


template< typename T, typename C>
   typename BinaryTree< T, C>::const_reverse_iterator BinaryTree< T, C>::crbegin() const
{
   return mpRoot ? const_reverse_iterator( mpRoot->last()) : const_reverse_iterator();
} // BinaryTree< T, C>::crbegin


template< typename T, typename C>
   typename BinaryTree< T, C>::reverse_iterator BinaryTree< T, C>::rend()
{
   return reverse_iterator();
} // BinaryTree< T, C>::rend


template< typename T, typename C>
   typename BinaryTree< T, C>::const_reverse_iterator BinaryTree< T, C>::crend() const
{
   return const_reverse_iterator();
} // BinaryTree< T, C>::crend


template< typename T, typename C>
   BinaryTree< T, C>& BinaryTree< T, C>::operator =( const BinaryTree& other)
{
   assign( other);
   return *this;
} // BinaryTree< T, C>::operator =


template< typename T, typename C> auto BinaryTree< T, C>::recursiveInsert( node_t* parent_node,
                                                            const T& new_value)
{
   if (mCompareLess( new_value, parent_node->mValue))
   {
      if (!parent_node->mpLeft)
      {
         parent_node->mpLeft = std::make_unique< node_t>( new_value, parent_node);
         ++mCount;
         return std::pair< iterator, bool>( iterator( parent_node->mpLeft.get()), true);
      } // end if
      return recursiveInsert( parent_node->mpLeft.get(), new_value);
   } // end if
   
   if (mCompareLess( parent_node->mValue, new_value))
   {
      if (!parent_node->mpRight)
      {
         parent_node->mpRight = std::make_unique< node_t>( new_value, parent_node);
         ++mCount;
         return std::pair< iterator, bool>( iterator( parent_node->mpRight.get()), true);
      } // end if
      return recursiveInsert( parent_node->mpRight.get(), new_value);
   } // end if

   // values are equal, something we don't support:
   return std::pair< iterator, bool>( iterator( parent_node), false);
} // BinaryTree< T, C>::recursiveInsert


template< typename T, typename C>
   typename BinaryTree< T, C>::node_t*
      BinaryTree< T, C>::recursiveCopy( size_t count, node_t* parent,
         const_iterator& other_iter)
{
   if (count == 0)
      return nullptr;

   auto  new_node = new node_t( parent);

   // first insert element(s) into left sub-tree
   new_node->mpLeft.reset( recursiveCopy( count / 2, new_node, other_iter));

   // (only) now we can assign the value and increment the iterator
   new_node->mValue = *other_iter;
   ++other_iter;

   // finally, insert element(s) into the right sub-tree
   new_node->mpRight.reset( recursiveCopy( count - 1 - (count / 2), new_node,
      other_iter));

   return new_node;
} // BinaryTree< T, C>::recursiveCopy


template< typename T, typename C>
   typename BinaryTree< T, C>::node_t*
      BinaryTree< T, C>::findNode( const T& value) const
{
   auto  current = mpRoot.get();
   while (current != nullptr)
   {
      if (mCompareLess( value, current->mValue))
         current = current->mpLeft.get();
      else if (mCompareLess( current->mValue, value))
         current = current->mpRight.get();
      else
         return current;
   } // end while
   return nullptr;
} // BinaryTree< T, C>::findNode


template< typename T, typename C>
   typename BinaryTree< T, C>::node_t*
      BinaryTree< T, C>::lowerBoundNode( const T& value) const
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
} // BinaryTree< T, C>::lowerBoundNode


template< typename T, typename C>
   typename BinaryTree< T, C>::node_t*
      BinaryTree< T, C>::upperBoundNode( const T& value) const
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
} // BinaryTree< T, C>::upperBoundNode


template< typename T, typename C> template< typename F>
   void BinaryTree< T, C>::recursiveVisit( node_t* current_node, F fun) const
{

   if (current_node == nullptr)
      return;

   recursiveVisit( current_node->mpLeft.get(), fun);

   fun( current_node);

   recursiveVisit( current_node->mpRight.get(), fun);

} // BinaryTree< T, C>::recursiveVisit


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BINARY_TREE_HPP


// =====  END OF binary_tree.hpp  =====

