   
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::ReadBuffer<>.


#ifndef CELMA_COMMON_READ_BUFFER_HPP
#define CELMA_COMMON_READ_BUFFER_HPP


#include <cassert>
#include <cstddef>
#include <cstring>
#include <memory>


namespace celma { namespace common {


// Class EmptyReadPolicy
// =====================


/// Default policy for the class ReadBuffer: Does nothing.
///
/// @since  x.y.z, 05.01.2019
class EmptyReadPolicy
{
public:
   /// Called when data was read from the source, i.e. readData() was called:
   /// Does nothing.
   ///
   /// @param  Ignored.
   /// @since  x.y.z, 25.01.2019
   void sourceRead( size_t)
   {
   } // EmptyReadPolicy::sourceRead

   /// Called when data was read from the internal buffer and copied into the
   /// outgoing destination buffer: Does nothing.
   ///
   /// @param  Ignored.
   /// @since  x.y.z, 25.01.2019
   void bufferRead( size_t)
   {
   } // EmptyReadPolicy::bufferRead

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  x.y.z, 25.01.2019
   size_t numSourceReads() const
   {
      return 0;
   } // EmptyReadPolicy::numSourceReads

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  x.y.z, 25.01.2019
   size_t bytesReadFromSource() const
   {
      return 0;
   } // EmptyReadPolicy::bytesReadFromSource

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  x.y.z, 25.01.2019
   size_t numBufferReads() const
   {
      return 0;
   } // EmptyReadPolicy::numBufferReads

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  x.y.z, 25.01.2019
   size_t bytesReadFromBuffer() const
   {
      return 0;
   } // EmptyReadPolicy::bytesReadFromBuffer

}; // EmptyReadPolicy


// Class ReadCountPolicy
// =====================


/// Use this policy with the class ReadBuffer to get statistics about how often
/// the functions were called and how many bytes of data were handled.
///
/// @since  x.y.z, 25.01.2019
class ReadCountPolicy
{
public:
   /// Called when data was read from the source, i.e. readData() was called.
   ///
   /// @param[in]  num_bytes  Number of bytes that were read from the source.
   /// @since  x.y.z, 25.01.2019
   void sourceRead( size_t num_bytes)
   {
      ++mNumSourceReads;
      mBytesSourceRead += num_bytes;
   } // ReadCountPolicy::sourceRead

   /// Called when data was read from the internal buffer and copied into the
   /// outgoing destination buffer.
   ///
   /// @param[in]  num_bytes  Number of bytes that were copied from the buffer.
   /// @since  x.y.z, 25.01.2019
   void bufferRead( size_t num_bytes)
   {
      ++mNumBufferReads;
      mBytesBufferedRead += num_bytes;
   } // ReadCountPolicy::bufferRead

   /// Returns how many times data was read from the source.
   ///
   /// @return  Number of times that data was read from the source.
   /// @since  x.y.z, 25.01.2019
   size_t numSourceReads() const
   {
      return mNumSourceReads;
   } // ReadCountPolicy::numSourceReads

   /// Returns how much data was read from the source so far.
   ///
   /// @return  Amount of data in bytes that was read from the source.
   /// @since  x.y.z, 25.01.2019
   size_t bytesReadFromSource() const
   {
      return mBytesSourceRead;
   } // ReadCountPolicy::bytesReadFromSource

   /// Returns how many times data was copied from the internal buffer into the
   /// outgoing buffer.
   ///
   /// @return  Number of times that data was copied from the buffer.
   /// @since  x.y.z, 25.01.2019
   size_t numBufferReads() const
   {
      return mNumBufferReads;
   } // ReadCountPolicy::numBufferReads

   /// Returns how much data was copied from the buffer so far.
   ///
   /// @return  Amount of data in bytes that data was copied from the buffer.
   /// @since  x.y.z, 25.01.2019
   size_t bytesReadFromBuffer() const
   {
      return mBytesBufferedRead;
   } // ReadCountPolicy::bytesReadFromBuffer

private:
   /// Counts the source reads.
   size_t  mNumSourceReads = 0;
   /// Counts the number of bytes read from the source.
   size_t  mBytesSourceRead = 0;
   /// Counts how many times data was copied from the internal buffer.
   size_t  mNumBufferReads = 0;
   /// Counts the number of bytes copied from the internal buffer.
   size_t  mBytesBufferedRead = 0;

}; // ReadCountPolicy


// Template Class ReadBuffer
// =========================


/// Can be used to minimize the read accesses to e.g. a socket or a file.<br>
/// Of course it can also work the other way round, if a large message must be
/// obtained from the source in multipe parts until the whole message is
/// available.<br>
/// Internally a buffer is managed, and every time data is needed, the module
/// tries to fill the internal buffer.<br>
/// So, to minimize the read operations, the buffer must be bigger than the
/// expected data blocks.<br>
/// The buffer must also be bigger than the maximum size of a data block that
/// is expected.
///
/// @tparam  N
///    The size of the internal buffer to use.
/// @tparam  P
///    The statistics policy to use by this class.<br>
///    Default = EmptyReadPolicy, a policy that counts nothing.
/// @since  x.y.z, 05.01.2019
template< size_t N, typename P = EmptyReadPolicy> class ReadBuffer: public P
{
public:
   /// Constructor, initialises the internal buffer (does not read anything yet).
   ///
   /// @since  x.y.z, 05.01.2019
   ReadBuffer();

   // No copying.
   ReadBuffer( const ReadBuffer&) = delete;
   ReadBuffer( ReadBuffer&&) = delete;

   /// Default destructor.
   virtual ~ReadBuffer() = default;

   // No assignment.
   ReadBuffer& operator =( const ReadBuffer&) = delete;
   ReadBuffer& operator =( ReadBuffer&&) = delete;

   /// Returns the data from the internal buffer. If the buffer does not hold
   /// enough data, readData() is called to get more data from the source until
   /// all the requested data is available.<br>
   /// The function fails if a NULL data pointer is passed. It simply returns
   /// if the given length is 0.<br>
   /// readData() is called until the requested data is available, or readData()
   /// exits by throwing an exception.
   ///
   /// @tparam
   ///    The type of the data pointer.
   /// @param[in]  data
   ///    Pointer to the buffer to return the data in.
   /// @param[in]  len
   ///    Length of the data in bytes to return.
   /// @since
   ///    x.y.z, 25.01.2019
   template< typename T> void get( T* data, size_t len) noexcept( false);

protected:
   /// Called when more data is needed.
   ///
   /// @param[in]  data
   ///    Pointer to the buffer to read the data into.
   /// @param[in]  len
   ///    Maximum length of the data to read.
   /// @return
   ///    Number of bytes of data actually read.
   /// @since
   ///    x.y.z, 25.01.2019
   virtual size_t readData( unsigned char* data, size_t len) = 0;

private:
   /// Prepares the buffer for reading and then calls readData() in a loop
   /// until the required amount of data is available.
   ///
   /// @param[in]  min_length  Minimum amount of data to read.
   /// @since  x.y.z, 25.01.2019
   void fillBuffer( size_t min_length = 0);

   /// The internal buffer.
   std::unique_ptr< unsigned char[]>  mpBuffer;
   /// Position in the data buffer where the available data starts.
   size_t                             mDataStart = 0;
   /// Position to read the next data block into, i.e. 1 position after the
   /// last data byte.
   size_t                             mDataEnd = 0;

}; // ReadBuffer< N, P>


// inlined methods
// ===============


template< size_t N, typename P> ReadBuffer< N, P>::ReadBuffer():
   mpBuffer( new unsigned char[ N])
{
} // ReadBuffer< N, P>::ReadBuffer


template< size_t N, typename P>
   template< typename T> void ReadBuffer< N, P>::get( T* data, size_t len)
{
   if (len == 0)
      return;
   if (data == nullptr)
      throw std::runtime_error( "NULL pointer passed to get()");
   if (len > N)
      throw std::runtime_error( "length requested from get() exceeds buffer length");

   // invariant
   assert( mDataStart <= mDataEnd);

   // check if we already have enough data in the buffer
   if (len <= (mDataEnd - mDataStart))
   {
      ::memcpy( data, &mpBuffer[ mDataStart], len);
      mDataStart += len;
      P::bufferRead( len);
      return;
   } // end if
   fillBuffer( len);
   // only returns when the buffer holds enough data
   ::memcpy( data, &mpBuffer[ mDataStart], len);
   mDataStart += len;
   P::bufferRead( len);
} // ReadBuffer< N, P>::get


template< size_t N, typename P> void ReadBuffer< N, P>::fillBuffer( size_t min_length)
{

   if (mDataStart == mDataEnd)
   {
      mDataStart = mDataEnd = 0;
   } else if (N - mDataStart < min_length)
   {
      ::memmove( &mpBuffer[ 0], &mpBuffer[ mDataStart], mDataEnd - mDataStart);
      mDataEnd -= mDataStart;
      mDataStart = 0;
   } // end if

   // invariant
   assert( mDataStart <= mDataEnd);

   do
   {
      const size_t data_read = readData( &mpBuffer[ mDataEnd], N - mDataEnd);
      mDataEnd += data_read;
      P::sourceRead( data_read);
   } while ((mDataEnd - mDataStart) < min_length);
} // ReadBuffer< N, P>::fillBuffer


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_READ_BUFFER_HPP


// =====  END OF read_buffer.hpp  =====

