
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/



// module to test headerfile include
#include "celma/container/shared_container.hpp"


// Boost includes
#define BOOST_TEST_MODULE SharedContainerTest
#include <boost/test/unit_test.hpp>


using celma::container::Segment;


namespace {


class SetData
{
public:
   ///
   /// @param[in]  i  .
   /// @since  x.y.z, 06.04.2021
   explicit SetData( int i):
      mInt( i),
      mFloat( ::sqrt( i))
   {
   } // SetData::SetData

   ///
   /// @param[in]  i  .
   /// @param[in]  v  .
   /// @since  x.y.z, 07.04.2021
   SetData( int i, double v):
      mInt( i),
      mFloat( v)
   {
   } // SetData::SetData

   bool operator <( const SetData& other) const
   {
      return mInt < other.mInt;
   } // SetData::operator <

private:
   int     mInt;
   double  mFloat;
}; // SetData


} // namespace



/// Test creating the shared list and inserting data.
///
/// @since  x.y.z, 06.04.2021
BOOST_AUTO_TEST_CASE( shared_list)
{

   using celma::container::SharedList;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the list in this segment
   SharedList< int>  sl( s, "MyList");

   // insert data into the list
   for (int i = 500; i < 600; ++i)
   {
      sl->push_back( i);
   } // end for

   BOOST_REQUIRE_EQUAL( sl->size(), 100);

} // shared_list



/// Test creating the shared map and inserting data.
///
/// @since  x.y.z, 01.04.2021
BOOST_AUTO_TEST_CASE( shared_map)
{

   using celma::container::SharedMap;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the map in this segment
   SharedMap< int, float>  sm( s, "MyMap");

   // insert data into the map
   for (int i = 0; i < 100; ++i)
   {
      sm->insert( SharedMap< int, float>::value_type( i, static_cast< float>( i)));
   } // end for

   BOOST_REQUIRE_EQUAL( sm->size(), 100);

} // shared_map



/// Test creating a shared multi-map and inserting data.
///
/// @since  x.y.z, 07.04.2021
BOOST_AUTO_TEST_CASE( shared_multi_map)
{

   using celma::container::SharedMultiMap;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the multi-map in this segment
   SharedMultiMap< int, float>  smm( s, "MyMultiMap");

   // insert data into the map
   for (int i = 700; i < 800; ++i)
   {
      smm->insert( SharedMultiMap< int, float>::value_type( i, static_cast< float>( i)));
      smm->insert( SharedMultiMap< int, float>::value_type( i, static_cast< float>( i * i)));
   } // end for

   BOOST_REQUIRE_EQUAL( smm->size(), 200);

} // shared_multi_map



/// Test creating a shared multi-set and inserting data.
///
/// @since  x.y.z, 06.04.2021
BOOST_AUTO_TEST_CASE( shared_multi_set)
{

   using celma::container::SharedMultiSet;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the set in this segment
   SharedMultiSet< SetData>  sms( s, "MyMultiSet");

   // insert data into the set
   for (int i = 600; i < 700; ++i)
   {
      sms->insert( SetData( i));
      sms->insert( SetData( i, static_cast< double>( i * i)));
   } // end for

   BOOST_REQUIRE_EQUAL( sms->size(), 200);

} // shared_multi_set



/// Test creating the shared set and inserting data.
///
/// @since  x.y.z, 06.04.2021
BOOST_AUTO_TEST_CASE( shared_set)
{

   using celma::container::SharedSet;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the set in this segment
   SharedSet< SetData>  ss( s, "MySet");

   // insert data into the set
   for (int i = 400; i < 500; ++i)
   {
      ss->insert( SetData( i));
   } // end for

   BOOST_REQUIRE_EQUAL( ss->size(), 100);

} // shared_set



/// Test creating the shared map and inserting data.
///
/// @since  x.y.z, 01.04.2021
BOOST_AUTO_TEST_CASE( shared_unordered_map)
{

   using celma::container::SharedUnorderedMap;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the existing shared segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the unordered map in this segment
   SharedUnorderedMap< int, float>  sum( s, "MyUnorderedMap", 17);

   // insert data into the map
   for (int i = 100; i < 200; ++i)
   {
      sum->insert( SharedUnorderedMap< int, float>::value_type( i, static_cast< float>( i)));
   } // end for

   BOOST_REQUIRE_EQUAL( sum->size(), 100);

} // shared_unordered_map



/// Test creating a shared vector and inserting data.
///
/// @since  x.y.z, 06.04.2021
BOOST_AUTO_TEST_CASE( shared_vector)
{

   using celma::container::SharedVector;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the map in this segment
   SharedVector< int>  sv( s, "MyVector");

   // insert data into the map
   for (int i = 200; i < 300; ++i)
   {
      sv->push_back( i);
   } // end for

   BOOST_REQUIRE_EQUAL( sv->size(), 100);

} // shared_vector



/// Test creating the shared map and unordered map in the same segment.
///
/// @since  x.y.z, 01.04.2021
BOOST_AUTO_TEST_CASE( both_maps)
{

   using celma::container::SharedMap;
   using celma::container::SharedUnorderedMap;

   // start from scratch
   boost::interprocess::shared_memory_object::remove( "MySharedMemory");

   // now create the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( s.wasCreated());

   // now create the map in this segment
   SharedMap< int, float>  sm( s, "MyMap");

   // insert data into the map
   for (int i = 0; i < 100; ++i)
   {
      sm->insert( SharedMap< int, float>::value_type( i, static_cast< float>( i)));
   } // end for

   BOOST_REQUIRE_EQUAL( sm->size(), 100);

   // now create the unordered map in the same segment
   SharedUnorderedMap< int, float>  sum( s, "MyUnorderedMap", 17);

   // insert data into the map
   for (int i = 100; i < 200; ++i)
   {
      sum->insert( SharedUnorderedMap< int, float>::value_type( i, static_cast< float>( i)));
   } // end for

   BOOST_REQUIRE_EQUAL( sum->size(), 100);
   BOOST_REQUIRE_EQUAL( sm->size(), 100);

} // both_maps



/// Test accessing the previously created shared maps.
///
/// @since  x.y.z, 01.04.2021
BOOST_AUTO_TEST_CASE( both_maps_re_attach)
{

   using celma::container::SharedMap;
   using celma::container::SharedUnorderedMap;

   // now access the shared memory segment
   Segment  s( "MySharedMemory", 65536);

   BOOST_REQUIRE( !s.wasCreated());

   // now access the map in this segment
   SharedMap< int, float>  sm( s, "MyMap");

   BOOST_REQUIRE_EQUAL( sm->size(), 100);

   for (int i = 0; i < 100; ++i)
   {
      BOOST_REQUIRE( sm->find( i) != sm->end());
   } // end for

   // now access the unordered map in the same segment
   SharedUnorderedMap< int, float>  sum( s, "MyUnorderedMap", 17);

   BOOST_REQUIRE_EQUAL( sum->size(), 100);

   for (int i = 100; i < 200; ++i)
   {
      BOOST_REQUIRE( sum->find( i) != sum->end());
   } // end for

} // both_maps_re_attach



// =====  END OF test_shared_container_c.cpp  =====

