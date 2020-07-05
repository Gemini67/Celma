
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes
/// - celma::container::detail::TreeIterator<>
/// - celma::container::detail::ConstTreeIterator<>
/// - celma::container::detail::ReverseTreeIterator<>
/// - celma::container::detail::ConstReverseTreeIterator<>



#ifndef CELMA_CONTAINER_DETAIL_TREE_ITERATOR_HPP
#define CELMA_CONTAINER_DETAIL_TREE_ITERATOR_HPP


#include <iterator>
#include "celma/common/pre_postfix.hpp"


namespace celma::container::detail {


/// Common iterator for tree classes.
///
/// @tparam  N  The type of the nodes with which the tree is built.
/// @since x.y.z, 25.03.2017
template< typename N> class TreeIterator
{
public:
   /// Default constructor.
   ///
   /// @since x.y.z, 25.03.2017
   TreeIterator() = default;

   /// Constructor for an iterator that points to a specific position/node.
   ///
   /// @param[in]  node  Pointer to the node to which the iterator should point.
   /// @since x.y.z, 25.03.2017
   TreeIterator( N* node):
      mpNode( node)
   {
   } // TreeIterator< N>::TreeIterator

   /// Const indirection/dereference operator.
   ///
   /// @return  Const reference of the value of the current node.
   /// @since x.y.z, 05.07.2020
   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   } // TreeIterator< N>::operator *

   /// Indirection/Dereference operator.
   ///
   /// @return  Reference of the value of the current node.
   /// @since x.y.z, 25.03.2017
   typename N::value_type& operator *()
   {
      return *mpNode->getValue();
   } // TreeIterator< N>::operator *

   /// Const member access operator.
   ///
   /// @return  Const pointer to the current value of the node.
   /// @since  x.y.z, 05.07.2020
   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   } // TreeIterator< N>::operator ->

   /// Member access operator.
   ///
   /// @return  Pointer to the current value of the node.
   /// @since x.y.z, 25.03.2017
   typename N::value_type* operator ->()
   {
      return mpNode->getValue();
   } // TreeIterator< N>::operator ->

   /// Prefix increment operator.
   ///
   /// @return  This iterator, pointing to the next position.
   /// @since x.y.z, 25.03.2017
   TreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   } // TreeIterator< N>::operator ++

   /// Postfix increment operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 25.03.2017
   TreeIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return copy;
   } // TreeIterator< N>::operator ++

   /// Prefix decrement operator.
   ///
   /// @return  This iterator, pointing to the previous position.
   /// @since x.y.z, 25.03.2017
   TreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->derement();
      return *this;
   } // TreeIterator< N>::operator --

   /// Postfix decrement operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 25.03.2017
   TreeIterator operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return copy;
   } // TreeIterator< N>::operator --

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to the same position/node.
   /// @since x.y.z, 25.03.2017
   bool operator ==( const TreeIterator& other) const
   {
      return mpNode == other.mpNode;
   } // TreeIterator< N>::operator ==

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to different positions/
   ///    nodes.
   /// @since x.y.z, 25.03.2017
   bool operator !=( const TreeIterator& other) const
   {
      return mpNode != other.mpNode;
   } // TreeIterator< N>::operator !=

   /// Returns a pointer to the current node that the iterator points to.
   ///
   /// @return  Pointer to the current node.
   /// @since  x.y.z, 27.04.2017
   operator N*()
   {
      return mpNode;
   } // TreeIterator< N>::operator N*

private:
   /// The pointer to the node.
   N*  mpNode = nullptr;

}; // TreeIterator< N>


/// Common const iterator for tree classes.
///
/// @tparam  N  The type of the nodes with which the tree is built.
/// @since x.y.z, 25.03.2017
template< typename N> class ConstTreeIterator
{
public:
   /// Default constructor.
   ///
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator() = default;

   /// Constructor for a const iterator that points to a specific position/node.
   ///
   /// @param[in]  node  Pointer to the node to which the iterator should point.
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator( N* node):
      mpNode( node)
   {
   } // ConstTreeIterator< N>::ConstTreeIterator

   /// Const indirection/dereference operator.
   ///
   /// @return  Const reference of the value of the current node.
   /// @since x.y.z, 25.03.2017
   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   } // ConstTreeIterator< N>::operator *

   /// Const member access operator.
   ///
   /// @return  Const pointer to the current value of the node.
   /// @since x.y.z, 25.03.2017
   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   } // ConstTreeIterator< N>::operator ->

   /// Prefix increment operator.
   ///
   /// @return  This iterator, pointing to the next position.
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   } // ConstTreeIterator< N>::operator ++

   /// Postfix increment operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return copy;
   } // ConstTreeIterator< N>::operator ++

   /// Prefix decrement operator.
   ///
   /// @return  This iterator, pointing to the previous position.
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   } // ConstTreeIterator< N>::operator --

   /// Postfix decrement operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 25.03.2017
   ConstTreeIterator operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return copy;
   } // ConstTreeIterator< N>::operator --

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to the same position/node.
   /// @since x.y.z, 25.03.2017
   bool operator ==( const ConstTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   } // ConstTreeIterator< N>::operator ==

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to different positions/
   ///    nodes.
   /// @since x.y.z, 25.03.2017
   bool operator !=( const ConstTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   } // ConstTreeIterator< N>::operator !=

   /// Returns a pointer to the current node that the iterator points to.
   ///
   /// @return  Pointer to the current node.
   /// @since  x.y.z, 27.04.2017
   operator N*()
   {
      return mpNode;
   } // ConstTreeIterator< N>::operator N*
   
private:
   /// The pointer to the node.
   N*  mpNode = nullptr;

}; // ConstTreeIterator< N>


/// Common reverse iterator for tree classes.
///
/// @tparam  N  The type of the nodes with which the tree is built.
/// @since x.y.z, 02.04.2017
template< typename N> class ReverseTreeIterator
{
public:
   /// Default constructor.
   ///
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator() = default;

   /// Constructor for a reverse iterator that points to a specific position
   /// node.
   ///
   /// @param[in]  node  Pointer to the node to which the iterator should point.
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator( N* node):
      mpNode( node)
   {
   } // ReverseTreeIterator< N>::ReverseTreeIterator

   /// Const indirection/dereference operator.
   ///
   /// @return  Const reference of the value of the current node.
   /// @since x.y.z, 02.04.2017
   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   } // ReverseTreeIterator< N>::operator *

   /// Indirection/Dereference operator.
   ///
   /// @return  Reference of the value of the current node.
   /// @since x.y.z, 02.04.2017
   typename N::value_type& operator *()
   {
      return *mpNode->getValue();
   } // ReverseTreeIterator< N>::operator *

   /// Const member access operator.
   ///
   /// @return  Const pointer to the current value of the node.
   /// @since x.y.z, 02.04.2017
   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   } // ReverseTreeIterator< N>::operator ->

   /// Member access operator.
   ///
   /// @return  Pointer to the current value of the node.
   /// @since x.y.z, 02.04.2017
   typename N::value_type* operator ->()
   {
      return mpNode->getValue();
   } // ReverseTreeIterator< N>::operator ->

   /// Prefix increment operator.
   ///
   /// @return  This iterator, pointing to the next position.
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   } // ReverseTreeIterator< N>::operator ++

   /// Postfix increment operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return copy;
   } // ReverseTreeIterator< N>::operator ++

   /// Prefix decrement operator.
   ///
   /// @return  This iterator, pointing to the previous position.
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   } // ReverseTreeIterator< N>::operator --

   /// Postfix decrement operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 02.04.2017
   ReverseTreeIterator operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return copy;
   } // ReverseTreeIterator< N>::operator --

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to the same position/node.
   /// @since x.y.z, 02.04.2017
   bool operator ==( const ReverseTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   } // ReverseTreeIterator< N>::operator ==

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to different positions/
   ///    nodes.
   /// @since x.y.z, 02.04.2017
   bool operator !=( const ReverseTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   } // ReverseTreeIterator< N>::operator !=

   /// Returns a pointer to the current node that the iterator points to.
   ///
   /// @return  Pointer to the current node.
   /// @since  x.y.z, 05.07.2020
   operator N*()
   {
      return mpNode;
   } // ReverseTreeIterator< N>::operator N*

private:
   /// The pointer to the node.
   N*  mpNode = nullptr;

}; // ReverseTreeIterator< N>


/// Common const reverse iterator for tree classes.
///
/// @tparam  N  The type of the nodes with which the tree is built.
/// @since x.y.z, 02.04.2017
template< typename N> class ConstReverseTreeIterator
{
public:
   /// Default constructor.
   ///
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator() = default;

   /// Constructor for a const reverse iterator that points to a specific
   /// position node.
   ///
   /// @param[in]  node  Pointer to the node to which the iterator should point.
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator( N* node):
      mpNode( node)
   {
   } // ConstReverseTreeIterator< N>::ConstReverseTreeIterator

   /// Const indirection/dereference operator.
   ///
   /// @return  Const reference of the value of the current node.
   /// @since x.y.z, 02.04.2017
   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   } // ConstReverseTreeIterator< N>::operator *

   /// Const member access operator.
   ///
   /// @return  Const pointer to the current value of the node.
   /// @since x.y.z, 02.04.2017
   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   } // ConstReverseTreeIterator< N>::operator ->

   /// Prefix increment operator.
   ///
   /// @return  This iterator, pointing to the next position.
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   } // ConstReverseTreeIterator< N>::operator ++

   /// Postfix increment operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return copy;
   } // ConstReverseTreeIterator< N>::operator ++

   /// Prefix decrement operator.
   ///
   /// @return  This iterator, pointing to the previous position.
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   } // ConstReverseTreeIterator< N>::operator --

   /// Postfix decrement operator.
   ///
   /// @return
   ///    Iterator pointing the position of this iterator when this operator was
   ///    called.
   /// @since x.y.z, 02.04.2017
   ConstReverseTreeIterator operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return copy;
   } // ConstReverseTreeIterator< N>::operator --

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to the same position/node.
   /// @since x.y.z, 02.04.2017
   bool operator ==( const ConstReverseTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   } // ConstReverseTreeIterator< N>::operator ==

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if this object and the other point to different positions/
   ///    nodes.
   /// @since x.y.z, 02.04.2017
   bool operator !=( const ConstReverseTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   } // ConstReverseTreeIterator< N>::operator !=

   /// Returns a pointer to the current node that the iterator points to.
   ///
   /// @return  Pointer to the current node.
   /// @since  x.y.z, 05.07.2020
   operator N*()
   {
      return mpNode;
   } // ReverseTreeIterator< N>::operator N*

private:
   /// The pointer to the node.
   N*  mpNode = nullptr;

}; // ConstReverseTreeIterator< N>


} // namespace celma::container::detail


namespace std {


/// Specialisation of std::iterator_traits for the tree iterator.
///
/// @since  x.y.z, 05.07.2020
template< typename N>
   struct iterator_traits< celma::container::detail::TreeIterator< N>>
{
   using difference_type = ptrdiff_t;
   using value_type = typename N::value_type;
   using pointer = typename N::value_type*;
   using reference = typename N::value_type&;
   using iterator_category = bidirectional_iterator_tag;
}; // iterator_traits< celma::container::detail::TreeIterator< N>>


/// Specialisation of std::iterator_traits for the const tree iterator.
///
/// @since  x.y.z, 05.07.2020
template< typename N>
   struct iterator_traits< celma::container::detail::ConstTreeIterator< N>>
{
   using difference_type = ptrdiff_t;
   using value_type = typename N::value_type;
   using pointer = typename N::value_type*;
   using reference = typename N::value_type&;
   using iterator_category = bidirectional_iterator_tag;
}; // iterator_traits< celma::container::detail::ConstTreeIterator< N>>


/// Specialisation of std::iterator_traits for the reverse tree iterator.
///
/// @since  x.y.z, 05.07.2020
template< typename N>
   struct iterator_traits< celma::container::detail::ReverseTreeIterator< N>>
{
   using difference_type = ptrdiff_t;
   using value_type = typename N::value_type;
   using pointer = typename N::value_type*;
   using reference = typename N::value_type&;
   using iterator_category = bidirectional_iterator_tag;
}; // iterator_traits< celma::container::detail::ReverseTreeIterator< N>>


/// Specialisation of std::iterator_traits for the const reverse tree iterator.
///
/// @since  x.y.z, 05.07.2020
template< typename N>
   struct iterator_traits< celma::container::detail::ConstReverseTreeIterator< N>>
{
   using difference_type = ptrdiff_t;
   using value_type = typename N::value_type;
   using pointer = typename N::value_type*;
   using reference = typename N::value_type&;
   using iterator_category = bidirectional_iterator_tag;
}; // iterator_traits< celma::container::detail::ConstReverseTreeIterator< N>>


} // namespace std


#endif   // CELMA_CONTAINER_DETAIL_TREE_ITERATOR_HPP


// =====  END OF tree_iterator.hpp  =====

