
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::ObjectCounter.


#ifndef CELMA_COMMON_OBJECT_COUNTER_HPP
#define CELMA_COMMON_OBJECT_COUNTER_HPP


namespace celma { namespace common {


/// Helper class to count the current number of objects of a class.<br>
/// Use this template with the CRTP:
///   class Counter: public ObjectCounter< Counter>
/// This (the CRTP) is necessary to make sure that multiple counted classes
/// in the same application are counted separately.
/// @tparam  T  The class to count the objects of.
/// @tparam  C  The type to use for the counter.
/// @since  0.2, 10.04.2016
template< typename T, typename C = uint64_t> class ObjectCounter
{
public:
   /// Returns the current number of objects of this class.
   /// @return  Current number of objects of the super class.
   /// @since  0.2, 10.04.2016
   static C numObjects()
   {
      return mNumObjects;
   } // end ObjectCounter< T, C>::numObjects

protected:
   /// Constructor, increments the object counter.<br>
   /// Protected to make sure that no stand-alone objects of this class can be
   /// created.
   /// @since  0.2, 10.04.2016
   ObjectCounter()
   {
      ++mNumObjects;
   } // end ObjectCounter< T, C>::ObjectCounter

   /// Copy constructor, also increments the object counter.
   /// @since  0.2, 10.04.2016
   ObjectCounter( const ObjectCounter& /* other */)
   {
      ++mNumObjects;
   } // end ObjectCounter< T, C>::ObjectCounter

   /// Destructor, decrements the object counter.
   /// @since  0.2, 10.04.2016
   ~ObjectCounter()
   {
      --mNumObjects;
   } // end ObjectCounter< T, C>::~ObjectCounter

private:
   /// Current number of object of the super class.
   static C  mNumObjects;

}; // ObjectCounter< T, C>


template< typename T, typename C> C ObjectCounter< T, C>::mNumObjects = 0;


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_OBJECT_COUNTER_HPP


// =========================  END OF object_counter.hpp  =========================

