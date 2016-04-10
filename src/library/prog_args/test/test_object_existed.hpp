
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
/// See documentation of template celma::common::TestObjectExisted.


#ifndef CELMA_COMMON_TEST_OBJECT_EXISTED_HPP
#define CELMA_COMMON_TEST_OBJECT_EXISTED_HPP


#include <cassert>


namespace celma { namespace common {


/// Checks if at least one instance of a specific class was created.
/// @tparam  T  The class to check if an object was created of.<br>
///             The class must provide a static member variable
///             \c mNumObjectsCreated, which counts the number of objects
///             created.
/// @since  0.2, 10.04.2016
template< class T> class TestObjectExisted
{
public:
   /// Destructor, checks if at least one object was created of class T.
   /// @since  6.0, 22.01.2014
   ~TestObjectExisted()
   {
      assert( T::mNumObjectsCreated > 0);
      assert( T::mRestartProcess);
   } // end TestObjectExisted::~TestObjectExisted

}; // TestObjectExisted


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TEST_OBJECT_EXISTED_HPP


// =========================  END OF test_object_existed.hpp  =========================

