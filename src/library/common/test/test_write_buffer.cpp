
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
**    Test program for the template celma::common::WriteBuffer, using the
**    Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/write_buffer.hpp"


// Boost includes
#define BOOST_TEST_MODULE DataBufferTest
#include <boost/test/unit_test.hpp>


using celma::common::WriteBuffer;


namespace {


class TestWriteBuffer : public WriteBuffer< 100>
{
public:
   static size_t  mDataWritten;
   static int     mWriteCalled;

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 01.01.2019
   virtual ~TestWriteBuffer()
   {
      flush();
   }

private:
   using WriteBuffer< 100UL>::writeData;

   virtual void writeData( const unsigned char* const, size_t len) const override
   {
      mDataWritten += len;
      ++mWriteCalled;
   }

};


class TestWriteBufferCount : public WriteBuffer< 100, celma::common::CountPolicy>
{
public:
   static size_t  mDataWritten;
   static int     mWriteCalled;

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 04.01.2019
   virtual ~TestWriteBufferCount()
   {
      flush();
   }

private:
   using WriteBuffer< 100, celma::common::CountPolicy>::writeData;

   virtual void writeData( const unsigned char* const, size_t len) const override
   {
      mDataWritten += len;
      ++mWriteCalled;
   }

};


size_t  TestWriteBuffer::mDataWritten = 0;
int     TestWriteBuffer::mWriteCalled = 0;
size_t  TestWriteBufferCount::mDataWritten = 0;
int     TestWriteBufferCount::mWriteCalled = 0;


} // namespace



/// Test some functions on an empty buffer.
///
/// @since  x.y.z, 01.01.2019
BOOST_AUTO_TEST_CASE( empty_buffer)
{

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);

} // empty_buffer



/// Test some functions on an empty buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( empty_buffer_count)
{

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 0);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
   BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

} // empty_buffer_count



/// Test with data in the buffer.
///
/// @since  x.y.z, 01.01.2019
BOOST_AUTO_TEST_CASE( append_once)
{

   TestWriteBuffer::mDataWritten = 0;
   TestWriteBuffer::mWriteCalled = 0;

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 50);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 50);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_once



/// Test with data in the buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_once_count)
{

   TestWriteBufferCount::mDataWritten = 0;
   TestWriteBufferCount::mWriteCalled = 0;

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 50);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 50);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 50);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_once_count



/// Test with more data in the buffer.
///
/// @since  x.y.z, 01.01.2019
BOOST_AUTO_TEST_CASE( append_multiple)
{

   TestWriteBuffer::mDataWritten = 0;
   TestWriteBuffer::mWriteCalled = 0;

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 50);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);

      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 100);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_multiple



/// Test with more data in the buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_multiple_count)
{

   TestWriteBufferCount::mDataWritten = 0;
   TestWriteBufferCount::mWriteCalled = 0;

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 50);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

      buff.append( "01234567890123456789012345678901234567890123456789", 50);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 100);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 2);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 100);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 0);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_multiple_count



/// Test buffer overflow.
///
/// @since  x.y.z, 01.01.2019
BOOST_AUTO_TEST_CASE( append_too_much)
{

   TestWriteBuffer::mDataWritten = 0;
   TestWriteBuffer::mWriteCalled = 0;

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 80);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 80);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 120);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 2);

} // append_too_much



/// Test buffer overflow.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_too_much_count)
{

   TestWriteBufferCount::mDataWritten = 0;
   TestWriteBufferCount::mWriteCalled = 0;

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 80);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 80);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 1);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 3);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 120);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 80);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 120);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 2);

} // append_too_much_count



/// Attempt to add a data block that is the same size as the buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_large_on_empty)
{

   TestWriteBuffer::mDataWritten = 0;
   TestWriteBuffer::mWriteCalled = 0;

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789"
                   "012345678901234567890123456789",
         100);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_large_on_empty



/// Attempt to add a data block that is the same size as the buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_large_on_empty_count)
{

   TestWriteBufferCount::mDataWritten = 0;
   TestWriteBufferCount::mWriteCalled = 0;

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789"
                   "012345678901234567890123456789",
         100);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 100);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 1);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 100);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 100);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 1);

} // append_large_on_empty_count



/// Attempt to add a data block that is bigger than the buffer.
///
/// @since  x.y.z, 01.01.2019
BOOST_AUTO_TEST_CASE( append_large)
{

   TestWriteBuffer::mDataWritten = 0;
   TestWriteBuffer::mWriteCalled = 0;

   {
      TestWriteBuffer  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 0);

      buff.append( "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789",
         120);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 160);
      BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 2);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 160);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 2);

} // append_large



/// Attempt to add a data block that is bigger than the buffer.
///
/// @since  x.y.z, 04.01.2019
BOOST_AUTO_TEST_CASE( append_large_count)
{

   TestWriteBufferCount::mDataWritten = 0;
   TestWriteBufferCount::mWriteCalled = 0;

   {
      TestWriteBufferCount  buff;

      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);

      buff.append( "0123456789012345678901234567890123456789", 40);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 40);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 0);

      buff.append( "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789"
                   "01234567890123456789012345678901234567890123456789",
         120);
      BOOST_REQUIRE_EQUAL( buff.buffered(), 0);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mDataWritten, 160);
      BOOST_REQUIRE_EQUAL( TestWriteBufferCount::mWriteCalled, 2);

      BOOST_REQUIRE_EQUAL( buff.numAppendCalled(), 2);
      BOOST_REQUIRE_EQUAL( buff.bytesAppended(), 160);
      BOOST_REQUIRE_EQUAL( buff.numFlushCalled(), 2);
      BOOST_REQUIRE_EQUAL( buff.bytesFlushed(), 160);
   } // end scope

   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mDataWritten, 160);
   BOOST_REQUIRE_EQUAL( TestWriteBuffer::mWriteCalled, 2);

} // append_large_count



// =====  END OF test_write_buffer.cpp  =====

