
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


#ifndef CELMA_CONTAINERS_DETAIL_TREE_ITERATOR_HPP
#define CELMA_CONTAINERS_DETAIL_TREE_ITERATOR_HPP


#include <iterator>
#include "celma/common/pre_postfix.hpp"


namespace celma { namespace containers { namespace detail {


/// @since x.y.z, 25.03.2017
template< typename N> class TreeIterator
{
public:
   using iterator_category = std::bidirectional_iterator_tag;

   TreeIterator():
      mpNode( nullptr)
   {
   } // TreeIterator< N>::TreeIterator

   TreeIterator( N* node):
      mpNode( node)
   {
   } // TreeIterator< N>::TreeIterator

   typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   }

   typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   }

   TreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   }

   TreeIterator& operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return *this;
   }

   TreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->derement();
      return *this;
   }

   TreeIterator& operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return *this;
   }

   bool operator ==( const TreeIterator& other) const
   {
      return mpNode == other.mpNode;
   }

   bool operator !=( const TreeIterator& other) const
   {
      return mpNode != other.mpNode;
   }

private:
   N*  mpNode;

}; // TreeIterator< N>


/// @since x.y.z, 25.03.2017
template< typename N> class ConstTreeIterator
{
public:
   using iterator_category = std::bidirectional_iterator_tag;

   ConstTreeIterator():
      mpNode( nullptr)
   {
   } // ConstTreeIterator< N>::ConstTreeIterator

   ConstTreeIterator( N* node):
      mpNode( node)
   {
   } // ConstTreeIterator< N>::ConstTreeIterator

   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   }

   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   }

   ConstTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   }

   ConstTreeIterator& operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return *this;
   }

   ConstTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->derement();
      return *this;
   }

   ConstTreeIterator& operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return *this;
   }

   bool operator ==( const ConstTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   }

   bool operator !=( const ConstTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   }

private:
   N* const  mpNode;

}; // ConstTreeIterator< N>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_TREE_ITERATOR_HPP


// ========================  END OF tree_iterator.hpp  ========================

