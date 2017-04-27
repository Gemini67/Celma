
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
      return copy;
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
      return copy;
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
      return copy;
   }

   ConstTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   }

   ConstTreeIterator& operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return copy;
   }

   bool operator ==( const ConstTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   }

   bool operator !=( const ConstTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   }

   /// 
   /// @return  .
   /// @since  x.y.z, 24.04.2017
   operator N*()
   {
      return mpNode;
   } // 
   
private:
   N*  mpNode;

}; // ConstTreeIterator< N>


/// @since x.y.z, 02.04.2017
template< typename N> class ReverseTreeIterator
{
public:
   using iterator_category = std::bidirectional_iterator_tag;

   ReverseTreeIterator():
      mpNode( nullptr)
   {
   } // ReverseTreeIterator< N>::ReverseTreeIterator

   ReverseTreeIterator( N* node):
      mpNode( node)
   {
   } // ReverseTreeIterator< N>::ReverseTreeIterator

   typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   }

   typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   }

   ReverseTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   }

   ReverseTreeIterator& operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return *this;
   }

   ReverseTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   }

   ReverseTreeIterator& operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return *this;
   }

   bool operator ==( const ReverseTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   }

   bool operator !=( const ReverseTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   }

private:
   N*  mpNode;

}; // ReverseTreeIterator< N>


/// @since x.y.z, 02.04.2017
template< typename N> class ConstReverseTreeIterator
{
public:
   using iterator_category = std::bidirectional_iterator_tag;

   ConstReverseTreeIterator():
      mpNode( nullptr)
   {
   } // ConstReverseTreeIterator< N>::ConstReverseTreeIterator

   ConstReverseTreeIterator( N* node):
      mpNode( node)
   {
   } // ConstReverseTreeIterator< N>::ConstReverseTreeIterator

   const typename N::value_type& operator *() const
   {
      return *mpNode->getValue();
   }

   const typename N::value_type* operator ->() const
   {
      return mpNode->getValue();
   }

   ConstReverseTreeIterator& operator ++( std::prefix)
   {
      mpNode = mpNode->decrement();
      return *this;
   }

   ConstReverseTreeIterator& operator ++( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->decrement();
      return *this;
   }

   ConstReverseTreeIterator& operator --( std::prefix)
   {
      mpNode = mpNode->increment();
      return *this;
   }

   ConstReverseTreeIterator& operator --( std::postfix)
   {
      auto  copy( *this);
      mpNode = mpNode->increment();
      return *this;
   }

   bool operator ==( const ConstReverseTreeIterator& other) const
   {
      return mpNode == other.mpNode;
   }

   bool operator !=( const ConstReverseTreeIterator& other) const
   {
      return mpNode != other.mpNode;
   }

private:
   N*  mpNode;

}; // ConstReverseTreeIterator< N>


} // namespace detail
} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_DETAIL_TREE_ITERATOR_HPP


// ========================  END OF tree_iterator.hpp  ========================

