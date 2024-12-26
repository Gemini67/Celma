
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::containers::BinaryTreeMap.


#ifndef CELMA_CONTAINERS_BINARY_TREE_HPP
#define CELMA_CONTAINERS_BINARY_TREE_HPP


#include <iterator>
#include <memory>
#include <utility>
#include "celma/containers/detail/binary_tree_node.hpp"
#include "celma/containers/detail/tree_iterator.hpp"


namespace celma { namespace containers {


/// @since  x.y.z, 26.03.2018
template< typename K, typename V> class BinaryTreeMap
{
public:
   using value_type = std::pair< K, V>;
   using node_t = detail::BinaryTreeNode< value_type>;
   using iterator = detail::TreeIterator< node_t>;
   using const_iterator = detail::ConstTreeIterator< node_t>;

   using reverse_iterator = detail::ReverseTreeIterator< node_t>;
   using const_reverse_iterator = detail::ConstReverseTreeIterator< node_t>;

   BinaryTreeMap();
   BinaryTreeMap( const BinaryTreeMap& other);
   BinaryTreeMap( BinaryTreeMap&& other);
   ~BinaryTreeMap();

   /// Assigns the contents of another binary tree map to this object.<br>
   /// The specialty of this function is that it always creates a well balanced
   /// tree.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  x.y.z, 26.03.2018
   void assign( const BinaryTreeMap& other);

   auto insert( const T& value);

   /// @since  x.y.z, 26.03.2018
   iterator find( const T& value);

   /// @since  x.y.z, 26.03.2018
   const_iterator find( const T& value) const;

   /// @since  x.y.z, 26.03.2018
   iterator lower_bound( const T& value);

   /// @since  x.y.z, 26.03.2018
   const_iterator lower_bound( const T& value) const;

   /// @since  x.y.z, 26.03.2018
   iterator upper_bound( const T& value);

   /// @since  x.y.z, 26.03.2018
   const_iterator upper_bound( const T& value) const;

   void clear();

   /// 
   /// @param[in]  pos  .
   /// @return  .
   /// @since  x.y.z, 24.04.2017
   iterator erase( iterator pos);

   bool empty() const;

   size_t size() const;

   iterator begin();
   const_iterator cbegin() const;
   iterator end();
   const_iterator cend() const;
   /// @since  x.y.z, 26.03.2018
   reverse_iterator rbegin();
   /// @since  x.y.z, 26.03.2018
   const_reverse_iterator crbegin() const;
   /// @since  x.y.z, 26.03.2018
   reverse_iterator rend();
   /// @since  x.y.z, 26.03.2018
   const_reverse_iterator crend() const;

   /// @since  x.y.z, 26.03.2018
   BinaryTreeMap& operator =( const BinaryTreeMap& other);

protected:
   std::unique_ptr< node_t>  mpRoot;

private:
   auto recursiveInsert( node_t* parent_node, const T& new_value);
   node_t* first() const;
   node_t* last() const;
   /// @since  x.y.z, 26.03.2018
   node_t* recursiveCopy( size_t count, node_t* parent,
                          const_iterator& other_iter);
   /// @since  x.y.z, 26.03.2018
   node_t* findNode( const T& value) const;
   /// @since  x.y.z, 26.03.2018
   node_t* lowerBoundNode( const T& value) const;
   /// @since  x.y.z, 26.03.2018
   node_t* upperBoundNode( const T& value) const;
   template< typename F> void recursiveVisit( node_t* current_node, F fun) const;

   size_t mCount = 0;
 
}; // BinaryTreeMap< K, V>


// inlined methods
// ===============


template< typename K, typename V> BinaryTreeMap< K, V>::BinaryTreeMap():
   mpRoot()
{
} // BinaryTreeMap< K, V>::BinaryTreeMap


template< typename K, typename V> BinaryTreeMap< K, V>::BinaryTreeMap( const BinaryTreeMap& other):
   mpRoot()
{
   assign( other);
} // BinaryTreeMap< K, V>::BinaryTreeMap


template< typename K, typename V> BinaryTreeMap< K, V>::BinaryTreeMap( BinaryTreeMap&& other):
   mpRoot()
{
   if (this != &other)
   {
      mpRoot = other.mpRoot;
      mCount = other.mCount;
   } // end if
} // BinaryTreeMap< K, V>::BinaryTreeMap


template< typename K, typename V> BinaryTreeMap< K, V>::~BinaryTreeMap()
{
   clear();
} // BinaryTreeMap< K, V>::~BinaryTreeMap


template< typename K, typename V> void BinaryTreeMap< K, V>::assign( const BinaryTreeMap& other)
{
   if (this != &other)
   {
      clear();
      mCount = other.mCount;
      auto  other_iter( other.cbegin());
      mpRoot.reset( recursiveCopy( mCount, nullptr, other_iter));
   } // end if
} // BinaryTreeMap< K, V>::assign


template< typename K, typename V> auto BinaryTreeMap< K, V>::insert( const T& value)
{
   if (!mpRoot)
   {
      mpRoot = std::make_unique< node_t>( value);
      mCount = 1;
      return std::pair< iterator, bool>( begin(), true);
   } // end if

   return recursiveInsert( mpRoot.get(), value);
} // BinaryTreeMap< K, V>::BinaryTreeMap


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::iterator BinaryTreeMap< K, V>::find( const T& value)
{
   return iterator( findNode( value));
} //


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_iterator
      BinaryTreeMap< K, V>::find( const T& value) const
{
   return const_iterator( findNode( value));
} //


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::iterator
      BinaryTreeMap< K, V>::lower_bound( const T& value)
{
   return iterator( lowerBoundNode( value));
} // 


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_iterator
      BinaryTreeMap< K, V>::lower_bound( const T& value) const
{
   return const_iterator( lowerBoundNode( value));
} // 


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::iterator
      BinaryTreeMap< K, V>::upper_bound( const T& value)
{
   return iterator( upperBoundNode( value));
} // 


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_iterator
      BinaryTreeMap< K, V>::upper_bound( const T& value) const
{
   return const_iterator( upperBoundNode( value));
} // 


template< typename K, typename V> void BinaryTreeMap< K, V>::clear()
{
   mpRoot.reset();
   mCount = 0;
} // BinaryTreeMap< K, V>::clear


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::iterator BinaryTreeMap< K, V>::erase( iterator pos)
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
} // 


template< typename K, typename V> bool BinaryTreeMap< K, V>::empty() const
{
   return !mpRoot;
} // BinaryTreeMap< K, V>::empty


template< typename K, typename V> std::size_t BinaryTreeMap< K, V>::size() const
{
//   std::size_t  count = 0;
//   recursiveVisit( mpRoot.get(), [&count]( auto const&) { ++count; });
   return mCount;
} // BinaryTreeMap< K, V>::size


template< typename K, typename V> typename BinaryTreeMap< K, V>::iterator BinaryTreeMap< K, V>::begin()
{
   return mpRoot ? iterator( first()) : iterator();
} // BinaryTreeMap< K, V>::begin


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_iterator BinaryTreeMap< K, V>::cbegin() const
{
   return mpRoot ? const_iterator( first()) : const_iterator();
} // BinaryTreeMap< K, V>::cbegin


template< typename K, typename V> typename BinaryTreeMap< K, V>::iterator BinaryTreeMap< K, V>::end()
{
   return iterator();
} // BinaryTreeMap< K, V>::end


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_iterator BinaryTreeMap< K, V>::cend() const
{
   return const_iterator();
} // BinaryTreeMap< K, V>::cend


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::reverse_iterator BinaryTreeMap< K, V>::rbegin()
{
   return mpRoot ? reverse_iterator( last()) : reverse_iterator();
} // BinaryTreeMap< K, V>::rbegin


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_reverse_iterator
      BinaryTreeMap< K, V>::crbegin() const
{
   return mpRoot ? const_reverse_iterator( last()) : const_reverse_iterator();
} // BinaryTreeMap< K, V>::crbegin


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::reverse_iterator BinaryTreeMap< K, V>::rend()
{
   return reverse_iterator();
} // BinaryTreeMap< K, V>::rend


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::const_reverse_iterator
      BinaryTreeMap< K, V>::crend() const
{
   return const_reverse_iterator();
} // BinaryTreeMap< K, V>::crend


template< typename K, typename V>
   BinaryTreeMap< K, V>&
      BinaryTreeMap< K, V>::operator =( const BinaryTreeMap& other)
{
   assign( other);
   return *this;
} // BinaryTreeMap< K, V>::operator =


template< typename K, typename V>
   auto BinaryTreeMap< K, V>::recursiveInsert( node_t* parent_node,
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
} // BinaryTreeMap< K, V>::recursiveInsert


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t* BinaryTreeMap< K, V>::first() const
{
   auto  p_first = mpRoot.get();
   while (p_first->left)
      p_first = p_first->left.get();
   return p_first;
} // 


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t* BinaryTreeMap< K, V>::last() const
{
   auto  p_last = mpRoot.get();
   while (p_last->right)
      p_last = p_last->right.get();
   return p_last;
} // 


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t*
      BinaryTreeMap< K, V>::recursiveCopy( size_t count, node_t* parent,
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


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t*
      BinaryTreeMap< K, V>::findNode( const T& value) const
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


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t*
      BinaryTreeMap< K, V>::lowerBoundNode( const T& value) const
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


template< typename K, typename V>
   typename BinaryTreeMap< K, V>::node_t*
      BinaryTreeMap< K, V>::upperBoundNode( const T& value) const
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


template< typename K, typename V> template< typename F>
   void BinaryTreeMap< K, V>::recursiveVisit( node_t* current_node, F fun) const
{

   if (current_node == nullptr)
      return;

   recursiveVisit( current_node->left.get(), fun);

   fun( current_node);

   recursiveVisit( current_node->right.get(), fun);

} // BinaryTreeMap< K, V>::recursiveVisit


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BINARY_TREE_HPP


// =====  END OF binary_tree.hpp  =====

