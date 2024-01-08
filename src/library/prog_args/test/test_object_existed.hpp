
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::common::TestObjectExisted.


#pragma once


#include <cassert>


namespace celma::common {


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
   } // TestObjectExisted::~TestObjectExisted

}; // TestObjectExisted


} // namespace celma::common


// =====  END OF test_object_existed.hpp  =====

