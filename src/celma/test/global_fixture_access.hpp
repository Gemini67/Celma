
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::test::@@@.


#ifndef CELMA_TEST_GLOBAL_FIXTURE_ACCESS_HPP
#define CELMA_TEST_GLOBAL_FIXTURE_ACCESS_HPP


#include <stdexcept>


namespace celma { namespace test {


/// Helper class to get a access to a global fixture object used in a test
/// program.<br>
/// In more general term, this class provides access to a singleton object
/// through a static method of this class, i.e. without an object.<br>
/// The Boost.Test framework creates a single object of global fixture objects.
/// However, these objects are not accessible to the test functions. Well,
/// actually they are, but the name is created by a Boost.Test macro, and if
/// that would change you'd have to adapt all test programs.<br>
/// So, derive your class from this template here, and then the test functions
/// can use the object() function to access the (single) object of this class.
///
/// @since  1.11.0, 31.08.2018
template< typename T> class GlobalFixtureAccess
{
public:
   /// Returns the global fixture object.
   ///
   /// @since  1.11.0, 31.08.2018
   static T& object()
   {
      // should never happen, but this way it would be easier to find if ...
      if (mpMe == nullptr)
         throw std::runtime_error( "I am not yet initialised");
      return *mpMe;
   } // GlobalFixtureAccess< T>::object

   /// Constructor. Initialises the pointer to myself.
   ///
   /// @since  1.11.0, 31.08.2018
   GlobalFixtureAccess()
   {
      // should never happen, but this way it would be easier to find if ...
      if (mpMe != nullptr)
         throw std::runtime_error( "I am already initialised");
      mpMe = static_cast< T*>( this);
   } // GlobalFixtureAccess< T>::GlobalFixtureAccess

   /// Destructor. Don't delete anything, just reset the pointer.
   ///
   /// @since  1.11.0, 31.08.2018
   ~GlobalFixtureAccess()
   {
      mpMe = nullptr;
   } // GlobalFixtureAccess< T>::~GlobalFixtureAccess

private:
   /// Static pointer to myself.
   static T*  mpMe;

}; // GlobalFixtureAccess< T>


template< typename T> T* GlobalFixtureAccess< T>::mpMe = nullptr;


} // namespace test
} // namespace celma


#endif   // CELMA_TEST_GLOBAL_FIXTURE_ACCESS_HPP


// =====  END OF global_fixture_access.hpp  =====

