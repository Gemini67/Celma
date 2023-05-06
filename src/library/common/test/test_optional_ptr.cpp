
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "optional pointer", using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/common/optional_ptr.hpp"


// Boost includes
#define BOOST_TEST_MODULE optionalPtrTest
#include <boost/test/unit_test.hpp>


using celma::common::OptionalPtr;


namespace 
{


/// Helper class to verify object creations and deletions.
/// @since  1.48.0, 03.05.2023
class TestCountInstances
{
public:
   /// Counts the current number of objects of this class.
   static uint64_t  mInstances;

   /// Constructor, increases the current object count.
   TestCountInstances()
   {
      ++mInstances;
   }
   /// Copy-Constructor, also increases the current object count.
   TestCountInstances( const TestCountInstances&)
   {
      ++mInstances;
   }
   /// Destructor, decreases the current object count again.
   ~TestCountInstances()
   {
      --mInstances;
   }

   int instances() const
   {
      return mInstances;
   }

   int currentInstances()
   {
      return mInstances;
   }

}; // TestCountInstances


uint64_t  TestCountInstances::mInstances = 0;


} // namespace



/// Basic tests.
/// @since  1.48.0, 03.05.2023
BOOST_AUTO_TEST_CASE( basics)
{

   // empty pointer, no object created
   {
      OptionalPtr< TestCountInstances>  optr;

      BOOST_REQUIRE( !optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // externally owned object
   {
      TestCountInstances*  my_object = new TestCountInstances;

      {
         OptionalPtr< TestCountInstances>  optr( my_object);

         BOOST_REQUIRE( optr);
         BOOST_REQUIRE( !optr.isOwning());
         BOOST_REQUIRE( optr.get() == my_object);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

         // test object method access through pointer
         BOOST_REQUIRE_EQUAL( optr->instances(), 1);
         BOOST_REQUIRE_EQUAL( optr->currentInstances(), 1);

         auto &  obj_ref = *optr;

         BOOST_REQUIRE_EQUAL( obj_ref.instances(), 1);
         BOOST_REQUIRE_EQUAL( obj_ref.currentInstances(), 1);
      } // end scope

      // now only the optional ptr object itself should be gone
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // optional ptr owns object
   {
      {
         OptionalPtr< TestCountInstances>  optr( std::make_unique< TestCountInstances>());

         BOOST_REQUIRE( optr);
         BOOST_REQUIRE( optr.isOwning());
         BOOST_REQUIRE( optr.get() != nullptr);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

         // test object method access through const reference
         auto const&  const_ref_optr = optr;
         BOOST_REQUIRE_EQUAL( const_ref_optr->instances(), 1);

         auto const &  obj_ref = *const_ref_optr;

         BOOST_REQUIRE_EQUAL( obj_ref.instances(), 1);
      } // end scope

      // now also the test object must have been deleted
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // optional ptr owns assigned object
   {
      {
         OptionalPtr< TestCountInstances>  optr;

         optr.reset( std::make_unique< TestCountInstances>());

         BOOST_REQUIRE( optr);
         BOOST_REQUIRE( optr.isOwning());
         BOOST_REQUIRE( optr.get() != nullptr);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);
      } // end scope

      // now also the test object must have been deleted
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // basics



/// Test reset.
/// @since  1.48.0, 03.05.2023
BOOST_AUTO_TEST_CASE( reset)
{

   // externally owned object
   {
      TestCountInstances*  my_object = new TestCountInstances;
      OptionalPtr< TestCountInstances>  optr( my_object);

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == my_object);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      // only the internal pointer should be cleared
      optr.reset();

      BOOST_REQUIRE( !optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // owning
   {
      OptionalPtr< TestCountInstances>  optr( std::make_unique< TestCountInstances>());

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      auto *  save_ptr = optr.get();

      // reset with other object
      optr.reset( std::make_unique< TestCountInstances>());

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);
      BOOST_REQUIRE( optr.get() != save_ptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);

   // owning, reset with non-owning
   {
      OptionalPtr< TestCountInstances>  optr( std::make_unique< TestCountInstances>());

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      auto *  save_ptr = optr.get();

      // reset with other object
      TestCountInstances*  my_object = new TestCountInstances;
      optr.reset( my_object);

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);
      BOOST_REQUIRE( optr.get() != save_ptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);

} // reset



/// Test release.
/// @since  1.48.0, 03.05.2023
BOOST_AUTO_TEST_CASE( release)
{

   // externally owned object
   {
      TestCountInstances*               my_object = new TestCountInstances;
      OptionalPtr< TestCountInstances>  optr( my_object);

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == my_object);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      // test object should not be deleted
      auto *  save_ptr = optr.release();

      BOOST_REQUIRE( !optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == nullptr);

      BOOST_REQUIRE_EQUAL( save_ptr, my_object);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // owning
   {
      OptionalPtr< TestCountInstances>  optr( std::make_unique< TestCountInstances>());

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      // was owning, but still should not be deleted now
      auto *  save_ptr = optr.release();

      BOOST_REQUIRE( !optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete save_ptr;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // reset



/// Test move.
/// @since  1.48.0, 03.05.2023
BOOST_AUTO_TEST_CASE( move)
{

   // move constructor
   {
      TestCountInstances*  my_object = new TestCountInstances;

      {
         OptionalPtr< TestCountInstances>  optr( my_object);

         BOOST_REQUIRE( optr);
         BOOST_REQUIRE( !optr.isOwning());
         BOOST_REQUIRE( optr.get() == my_object);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

         OptionalPtr< TestCountInstances>  new_optr( std::move( optr));

         BOOST_REQUIRE( !optr);
         BOOST_REQUIRE( !optr.isOwning());
         BOOST_REQUIRE( optr.get() == nullptr);

         BOOST_REQUIRE( new_optr);
         BOOST_REQUIRE( !new_optr.isOwning());
         BOOST_REQUIRE( new_optr.get() == my_object);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);
      } // end scope

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // move assignment
   {
      TestCountInstances*  my_object = new TestCountInstances;

      {
         OptionalPtr< TestCountInstances>  optr( my_object);

         BOOST_REQUIRE( optr);
         BOOST_REQUIRE( !optr.isOwning());
         BOOST_REQUIRE( optr.get() == my_object);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

         OptionalPtr< TestCountInstances>  new_optr;
         new_optr = std::move( optr);

         BOOST_REQUIRE( !optr);
         BOOST_REQUIRE( !optr.isOwning());
         BOOST_REQUIRE( optr.get() == nullptr);

         BOOST_REQUIRE( new_optr);
         BOOST_REQUIRE( !new_optr.isOwning());
         BOOST_REQUIRE( new_optr.get() == my_object);

         BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);
      } // end scope

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      delete my_object;

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

   // move assignment with owning
   {
      OptionalPtr< TestCountInstances>  optr( std::make_unique< TestCountInstances>());

      BOOST_REQUIRE( optr);
      BOOST_REQUIRE( optr.isOwning());
      BOOST_REQUIRE( optr.get() != nullptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);

      auto *  save_ptr = optr.get();

      OptionalPtr< TestCountInstances>  new_optr( std::make_unique< TestCountInstances>());
      new_optr = std::move( optr);

      BOOST_REQUIRE( !optr);
      BOOST_REQUIRE( !optr.isOwning());
      BOOST_REQUIRE( optr.get() == nullptr);

      BOOST_REQUIRE( new_optr);
      BOOST_REQUIRE( new_optr.isOwning());
      BOOST_REQUIRE( new_optr.get() == save_ptr);

      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);

} // move



// =====  END OF test_optional_ptr.cpp  =====

