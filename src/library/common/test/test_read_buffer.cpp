
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::common::ReadBuffer, using the
**    Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/read_buffer.hpp"


// C++ Standard Library includes
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ReadBufferTest
#include <boost/test/unit_test.hpp>


using celma::common::ReadBuffer;


namespace {


class TestReadBuffer: public ReadBuffer< 100>
{
public:
   TestReadBuffer() = default;

   void setNextReadLen( const std::initializer_list< int>& values)
   {
      mNextReadLen.assign( values);
   }

private:
   using ReadBuffer< 100UL>::readData;

   virtual size_t readData( unsigned char* dest, size_t) override
   {
      const int  len = mNextReadLen[ 0];

      ::memset( dest, mFillChar, len);
      mFillChar = (mFillChar == 'z') ? 'a' : (mFillChar + 1);

      if (mNextReadLen.size() > 1)
         mNextReadLen.erase( mNextReadLen.begin());

      return len;
   }

   std::vector< int>  mNextReadLen;
   char               mFillChar = 'a';

}; // TestReadBuffer


class TestReadBufferCount:
   public ReadBuffer< 100, celma::common::ReadCountPolicy>
{
public:
   TestReadBufferCount() = default;

   void setNextReadLen( const std::initializer_list< int>& values)
   {
      mNextReadLen.assign( values);
   }

private:
   using ReadBuffer< 100UL, celma::common::ReadCountPolicy>::readData;

   virtual size_t readData( unsigned char* dest, size_t) override
   {
      const int  len = mNextReadLen[ 0];

      ::memset( dest, mFillChar, len);
      mFillChar = (mFillChar == 'z') ? 'a' : (mFillChar + 1);

      if (mNextReadLen.size() > 1)
         mNextReadLen.erase( mNextReadLen.begin());

      return len;
   }

   std::vector< int>  mNextReadLen;
   char               mFillChar = 'a';

}; // TestReadBufferCount


} // namespace



/// Test some functions on an empty buffer.
///
/// @since  1.20.0, 05.01.2019
BOOST_AUTO_TEST_CASE( empty_buffer)
{

   {
      TestReadBuffer  buff;
      char*           dummy = nullptr;

      BOOST_REQUIRE_THROW( buff.get( dummy, 100), std::runtime_error);
   } // end scope


   {
      TestReadBuffer  buff;
      char            dummy[ 100];

      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 0));
   } // end scope

   {
      TestReadBuffer  buff;
      char            dummy[ 100];

      BOOST_REQUIRE_THROW( buff.get( dummy, 120), std::runtime_error);
   } // end scope

} // empty_buffer



/// Test some functions on an empty buffer with read statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( empty_buffer_count)
{

   {
      TestReadBufferCount  buff;
      char*                dummy = nullptr;

      BOOST_REQUIRE_THROW( buff.get( dummy, 100), std::runtime_error);

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 0);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 0);
   } // end scope

   {
      TestReadBufferCount  buff;
      char                 dummy[ 100];

      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 0));

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 0);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 0);
   } // end scope

   {
      TestReadBufferCount  buff;
      char                 dummy[ 100];

      BOOST_REQUIRE_THROW( buff.get( dummy, 120), std::runtime_error);

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 0);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 0);
   } // end scope

} // empty_buffer_count



/// Read data once.
///
/// @since  1.20.0, 24.01.2019
BOOST_AUTO_TEST_CASE( read_once)
{

   // all data available after first read
   {
      TestReadBuffer  buff;
      char            dummy[ 100];

      buff.setNextReadLen( { 75 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 75);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);
   } // end scope

   // two internal reads needed for the data
   {
      TestReadBuffer  buff;
      char            dummy[ 100];

      buff.setNextReadLen( { 40, 35 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 40);
      ::memset( &cmpBuf[ 40], 'b', 35);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);
   } // end scope

   // two internal reads needed for the data
   {
      TestReadBuffer  buff;
      char            dummy[ 100];

      buff.setNextReadLen( { 40, 40 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 60));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 40);
      ::memset( &cmpBuf[ 40], 'b', 20);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 60) == 0);
   } // end scope

} // read_once



/// Read data once, with a buffer with read statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( read_once_count)
{

   // all data available after first read
   {
      TestReadBufferCount  buff;
      char                 dummy[ 100];

      buff.setNextReadLen( { 75 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 75);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 75);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 75);
   } // end scope

   // two internal reads needed for the data
   {
      TestReadBufferCount  buff;
      char                 dummy[ 100];

      buff.setNextReadLen( { 40, 35 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 40);
      ::memset( &cmpBuf[ 40], 'b', 35);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 75);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 75);
   } // end scope

   // two internal reads needed for the data
   {
      TestReadBufferCount  buff;
      char                 dummy[ 100];

      buff.setNextReadLen( { 40, 40 });
      BOOST_REQUIRE_NO_THROW( buff.get( dummy, 60));

      char  cmpBuf[ 100];
      ::memset( cmpBuf, 'a', 40);
      ::memset( &cmpBuf[ 40], 'b', 20);
      BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 60) == 0);

      BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 80);
      BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 60);
   } // end scope

} // read_once_count



/// One message that must be read in many parts.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( many_parts)
{

   TestReadBuffer  buff;
   char            dummy[ 100];
   char            cmpBuf[ 100];


   buff.setNextReadLen( { 1 });
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 52));

   for (int i = 0; i < 26; ++i)
   {
      cmpBuf[ i] = 'a' + i;
      cmpBuf[ i + 26] = 'a' + i;
   } // end for

   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 52) == 0);

} // many_parts



/// One message that must be read in many parts, using a buffer with statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( many_parts_count)
{

   TestReadBufferCount  buff;
   char                 dummy[ 100];
   char                 cmpBuf[ 100];


   buff.setNextReadLen( { 1 });
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 52));

   for (int i = 0; i < 26; ++i)
   {
      cmpBuf[ i] = 'a' + i;
      cmpBuf[ i + 26] = 'a' + i;
   } // end for

   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 52) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 52);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 52);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 52);

} // many_parts_count



/// Multiple reads from one large data block.
///
/// @since  1.20.0, 24.01.2019
BOOST_AUTO_TEST_CASE( read_multiple)
{

   TestReadBuffer  buff;
   char            dummy[ 100];
   char            cmpBuf[ 100];


   buff.setNextReadLen( { 75 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 30));

   ::memset( cmpBuf, 'a', 30);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 30) == 0);

   // second part
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 45));

   ::memset( cmpBuf, 'a', 45);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 45) == 0);

} // read_multiple



/// Multiple reads from one large data block, using a buffer with statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( read_multiple_count)
{

   TestReadBufferCount  buff;
   char                 dummy[ 100];
   char                 cmpBuf[ 100];


   buff.setNextReadLen( { 75 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 30));

   ::memset( cmpBuf, 'a', 30);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 30) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 75);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 30);

   // second part
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 45));

   ::memset( cmpBuf, 'a', 45);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 45) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 75);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 75);

} // read_multiple_count



/// Read multiple large messages, each provided as one.
///
/// @since  1.20.0, 24.01.2019
BOOST_AUTO_TEST_CASE( large_messages)
{

   TestReadBuffer  buff;
   char            dummy[ 100];
   char            cmpBuf[ 100];


   buff.setNextReadLen( { 75, 80, 85 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 75);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   // second message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 80));

   ::memset( cmpBuf, 'b', 80);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 80) == 0);

   // third message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 85));

   ::memset( cmpBuf, 'c', 85);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 85) == 0);

} // large_messages



/// Read multiple large messages, each provided as one, using a buffer with
/// statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( large_messages_count)
{

   TestReadBufferCount  buff;
   char                 dummy[ 100];
   char                 cmpBuf[ 100];


   buff.setNextReadLen( { 75, 80, 85 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 75);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 75);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 75);

   // second message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 80));

   ::memset( cmpBuf, 'b', 80);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 80) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 155);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 155);

   // third message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 85));

   ::memset( cmpBuf, 'c', 85);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 85) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 240);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 240);

} // large_messages_count



/// Mixed messages and internal reads.
///
/// @since  1.20.0, 24.01.2019
BOOST_AUTO_TEST_CASE( mixed_reads)
{

   // all data available after first read
   TestReadBuffer  buff;
   char            dummy[ 100];
   char            cmpBuf[ 100];


   buff.setNextReadLen( { 20, 50, 10 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 35));

   ::memset( cmpBuf, 'a', 20);
   ::memset( &cmpBuf[ 20], 'b', 15);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 35) == 0);

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 20));

   ::memset( cmpBuf, 'b', 20);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 20) == 0);

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 25));

   ::memset( cmpBuf, 'b', 15);
   ::memset( &cmpBuf[ 15], 'c', 10);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 25) == 0);

} // mixed_reads



/// Mixed messages and internal reads, using a buffer with statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( mixed_reads_count)
{

   // all data available after first read
   TestReadBufferCount  buff;
   char                 dummy[ 100];
   char                 cmpBuf[ 100];


   buff.setNextReadLen( { 20, 50, 10 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 35));

   ::memset( cmpBuf, 'a', 20);
   ::memset( &cmpBuf[ 20], 'b', 15);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 35) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 70);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 35);

   // second message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 20));

   ::memset( cmpBuf, 'b', 20);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 20) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 70);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 55);

   // third message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 25));

   ::memset( cmpBuf, 'b', 15);
   ::memset( &cmpBuf[ 15], 'c', 10);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 25) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 80);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 80);

} // mixed_reads_count



/// Read multiple large messages, some provided through mixed internal reads.
///
/// @since  1.20.0, 24.01.2019
BOOST_AUTO_TEST_CASE( large_mixed)
{

   TestReadBuffer  buff;
   char            dummy[ 100];
   char            cmpBuf[ 100];


   buff.setNextReadLen( { 100, 75, 75, 50 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 75);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   // second message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 25);
   ::memset( &cmpBuf[ 25], 'b', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   // third message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'b', 25);
   ::memset( &cmpBuf[ 25], 'c', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   // fourth and last message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'c', 25);
   ::memset( &cmpBuf[ 25], 'd', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

} // large_mixed



/// Read multiple large messages, some provided through mixed internal reads,
/// using a buffer with statistics.
///
/// @since  1.20.0, 25.01.2019
BOOST_AUTO_TEST_CASE( large_mixed_count)
{

   TestReadBufferCount  buff;
   char                 dummy[ 100];
   char                 cmpBuf[ 100];


   buff.setNextReadLen( { 100, 75, 75, 50 });

   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 75);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 100);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 1);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 75);

   // second message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'a', 25);
   ::memset( &cmpBuf[ 25], 'b', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 175);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 2);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 150);

   // third message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'b', 25);
   ::memset( &cmpBuf[ 25], 'c', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 250);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 3);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 225);

   // fourth and last message
   BOOST_REQUIRE_NO_THROW( buff.get( dummy, 75));

   ::memset( cmpBuf, 'c', 25);
   ::memset( &cmpBuf[ 25], 'd', 50);
   BOOST_REQUIRE( ::memcmp( cmpBuf, dummy, 75) == 0);

   BOOST_REQUIRE_EQUAL( buff.numSourceReads(), 4);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromSource(), 300);
   BOOST_REQUIRE_EQUAL( buff.numBufferReads(), 4);
   BOOST_REQUIRE_EQUAL( buff.bytesReadFromBuffer(), 300);

} // large_mixed_count



// =====  END OF test_read_buffer.cpp  =====

