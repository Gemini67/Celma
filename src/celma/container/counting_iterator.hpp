
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::container::CountingIterator.


#ifndef CELMA_CONTAINER_COUNTING_ITERATOR_HPP
#define CELMA_CONTAINER_COUNTING_ITERATOR_HPP


#include "celma/common/pre_postfix.hpp"


namespace celma::container {


// Class ICountResult
// ==================


/// Interface of the class that holds the final counter.
/// @since  0.2, 04.04.2016
class ICountResult
{
public:
   /// Empty, virtual destructor.
   /// @since  0.2, 04.04.2016
   virtual ~ICountResult() = default;

   /// This method must be implemented by the derived class.<br>
   /// It is called by the CountingIterator object when it is deleted, and is
   /// used to set the number of elements that were found while iterating over
   /// the result set.
   /// @param[in]  theCount  The number of element found.
   /// @since  0.2, 04.04.2016
   virtual void setCount( int theCount) = 0;

}; // ICountResult


// Class CountingIterator
// ======================


/// Implementation of an iterator wrapper that provides the count/index/position
/// of the current element.
/// @tparam  BaseType  The base iterator type to wrap with this counter.
/// @since  0.2, 04.04.2016
template< class BaseType> class CountingIterator: public BaseType
{
public:
   /// Constructor.
   /// @param[in]  obj  Pointer to the object in which the final count will be
   ///                  stored when the iterator object is destroyed.
   /// @param[in]  it   The iterator to initialise the underlying base with.
   /// @since  0.2, 04.04.2016
   CountingIterator( ICountResult* obj, const BaseType& it);

   /// Copy contructor.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  0.2, 04.04.2016
   CountingIterator( const CountingIterator& other);

   /// Destructor<br>
   /// Stores the number of elements found while iterating in the object passed
   /// to the constructor.
   /// @since  0.2, 04.04.2016
   ~CountingIterator();

   /// Prefix increment operator.
   /// @return  The incremented iterator.
   /// @since  0.2, 04.04.2016
   CountingIterator& operator ++( std::prefix);

   /// Postfix increment operator.
   /// @return  An iterator object with the previous value.
   /// @since  0.2, 04.04.2016
   CountingIterator operator ++( std::postfix);

   /// Assignment operator
   /// @param[in]  other  The other object to copy the data from.
   /// @return  This object.
   /// @since  0.2, 04.04.2016
   CountingIterator& operator =( const CountingIterator& other);

   /// The current count/index/position (whatever you want to call it) of the
   /// element in the iteration.
   /// @return  The number of the current element.
   /// @since  0.2, 04.04.2016
   int currentNum() const;

private:
   /// Pointer to the object to store the final count in.
   ICountResult*  mpObj;
   /// The counter.
   int            mIterCounter;

}; // CountingIterator< BaseType>


// inlined methods
// ===============


template< class BaseType>
   CountingIterator< BaseType>::CountingIterator( ICountResult* obj,
                                                  const BaseType& it):
      BaseType( it),
      mpObj( obj),
      mIterCounter( 0)
{
} // CountingIterator< BaseType>::CountingIterator


template< class BaseType>
   CountingIterator< BaseType>::CountingIterator( const CountingIterator& other):
      BaseType( other),
      mpObj( other.mpObj),
      mIterCounter( other.mIterCounter)
{
} // CountingIterator< BaseType>::CountingIterator


template< class BaseType>
   CountingIterator< BaseType>::~CountingIterator()
{
   if (mpObj != nullptr)
      mpObj->setCount( mIterCounter);
} // CountingIterator< BaseType>::~CountingIterator


template< class BaseType>
   CountingIterator< BaseType>& CountingIterator< BaseType>::operator ++( std::prefix)
{
   ++mIterCounter;
   BaseType::operator ++();
   return *this;
} // CountingIterator< BaseType>::operator ++


template< class BaseType>
   CountingIterator< BaseType> CountingIterator< BaseType>::operator ++( std::postfix)
{
   CountingIterator  result( *this);

   ++mIterCounter;
   BaseType::operator ++();

   return result;
} // CountingIterator< BaseType>::operator ++


template< class BaseType>
   CountingIterator< BaseType>&
      CountingIterator< BaseType>::operator =( const CountingIterator< BaseType>& other)
{
   if (this != &other)
   {
      BaseType::operator =( other);
      mIterCounter = other.mIterCounter;
   } // end if
   return *this;
} // CountingIterator< BaseType>::operator =


template< class BaseType> int CountingIterator< BaseType>::currentNum() const
{
   return mIterCounter;
} // CountingIterator< BaseType>::currentNum


} // namespace celma::container


#endif   // CELMA_CONTAINER_COUNTING_ITERATOR_HPP


// =====  END OF counting_iterator.hpp  =====

