
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::ObjectEnumerator.


#ifndef CELMA_COMMON_OBJECT_ENUMERATOR_HPP
#define CELMA_COMMON_OBJECT_ENUMERATOR_HPP


#include <cstdint>


namespace celma { namespace common {


/// Helper class to enumerate all objects of a class.
/// Use this template with the CRTP:
///   class Counter: public ObjectEnumerator< Counter>
/// This (the CRTP) is necessary to make sure that multiple enumerated classes
/// in the same application are counted separately.
///
/// @tparam  T  The class to enumerate the objects of.
/// @tparam  C  The type to use for the counter.
/// @since  0.2, 10.04.2016
template< typename T, typename C = uint64_t> class ObjectEnumerator
{
public:
   /// Default destructor is fine.
   ~ObjectEnumerator() = default;

   /// Returns the number of this object.
   ///
   /// @return  The number of this (super) object.
   /// @since  0.2, 10.04.2016
   C objectNbr() const
   {
      return mObjectNbr;
   } // ObjectEnumerator< T, C>::objectNbr

protected:
   /// Constructor. Stores the number of the current, new object.<br>
   /// Protected to make sure that no stand-alone objects of this class can be
   /// created.
   ///
   /// @since  0.2, 10.04.2016
   ObjectEnumerator():
      mObjectNbr( mObjectCounter++)
   {
   } // ObjectEnumerator< T, C>::ObjectEnumerator

   /// Copy constructor. Makes sure that copy-created object get their own,
   /// unique number.
   ///
   /// @since  0.2, 10.04.2016
   ObjectEnumerator( const ObjectEnumerator& /* other */):
      mObjectNbr( mObjectCounter++)
   {
   } // ObjectEnumerator< T, C>::ObjectEnumerator

   /// Move constructor. Makes sure that move-created object get their own,
   /// unique number.
   ///
   /// @since  1.11.0, 22.08.2018
   ObjectEnumerator( ObjectEnumerator&& /* other */):
      mObjectNbr( mObjectCounter++)
   {
   } // ObjectEnumerator< T, C>::ObjectEnumerator

private:
   /// Number of the next object.
   static C  mObjectCounter;
   /// Number of the owning object.
   const C   mObjectNbr;

}; // ObjectEnumerator< T, C>


template< typename T, typename C> C ObjectEnumerator< T, C>::mObjectCounter = 0;


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_OBJECT_ENUMERATOR_HPP


// =====  END OF object_enumerator.hpp  =====

