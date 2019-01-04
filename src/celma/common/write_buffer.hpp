
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
/// See documentation of template class celma::common::WriteBuffer<>.


#ifndef CELMA_COMMON_WRITE_BUFFER_HPP
#define CELMA_COMMON_WRITE_BUFFER_HPP


#include <cstring>
#include <memory>
#include <cstddef>


namespace celma { namespace common {


/// Default policy for the class WriteBuffer: Does nothing.
///
/// @since  x.y.z, 04.01.2019
class EmptyPolicy
{
public:
   /// Called when data is appended to the write buffer: Does nothing.
   ///
   /// @param  Ignored.
   /// @since  x.y.z, 04.01.2019
   void appended( size_t /* len */)
   {
   } // EmptyPolicy::appended

   /// Called when data is written to the destination: Does nothing.
   ///
   /// @param  Ignored.
   /// @since  x.y.z, 04.01.2019
   void flushed( size_t /* len */)
   {
   } // EmptyPolicy::flushed

}; // EmptyPolicy


/// Use this policy with the class WriteBuffer to get statistics about how often
/// the functions were called and how many bytes of data were handled.
///
/// @since  x.y.z, 04.01.2019
class CountPolicy
{
public:
   /// Called when data is appended to the write buffer. Counts the number of
   /// calls and how many bytes were appended.
   ///
   /// @param[in]  len  Number of bytes that were appended.
   /// @since  x.y.z, 04.01.2019
   void appended( size_t len)
   {
      ++mNumAppendCalled;
      mBytesAppended += len;
   } // CountPolicy::appended

   /// Called when data is written to the destination. This can be either from
   /// the buffer, or directly if a large block of data was passed.<br>
   /// Counts the number of calls and the amount of bytes written.
   ///
   /// @param[in]  len  Number of bytes that were written to the destination.
   /// @since  x.y.z, 04.01.2019
   void flushed( size_t len)
   {
      ++mNumFlushCalled;
      mBytesFlushed += len;
   } // CountPolicy::flushed

   /// Returns how many times WriteBuffer::append() was called.
   ///
   /// @return
   ///    Number of times that the append method was called in the class
   ///    WriteBuffer.
   /// @since  x.y.z, 04.01.2019
   size_t numAppendCalled() const
   {
      return mNumAppendCalled;
   } // CountPolicy::numAppendCalled

   /// Returns how many bytes were passed to the WriteBuffer object through
   /// calling the append method.<br>
   /// This does not necessarily mean that the data was appended to the internal
   /// buffer: If a block of data was passed that is larger than the buffer, it
   /// is directly written to the destination.
   ///
   /// @return
   ///    Number of bytes passed to WriteBuffer::append().
   /// @since  x.y.z, 04.01.2019
   size_t bytesAppended() const
   {
      return mBytesAppended;
   } // CountPolicy::bytesAppended

   /// Returns how many times WriteBuffer::flush() was called, either externally
   /// or internally when the buffer was full/more free space was needed.<br>
   /// This includes also the calls to write a large block of data directly to
   /// the destination.
   ///
   /// @return
   ///    Number of times that data was flushed, either from the internal
   ///    buffer or directly.
   /// @since  x.y.z, 04.01.2019
   size_t numFlushCalled() const
   {
      return mNumFlushCalled;
   } // CountPolicy::numFlushCalled

   /// Returns the number of bytes that were written to the destination.
   ///
   /// @return
   ///    Number of bytes written to the destination so far, either from the
   ///    internal buffer or directly.
   /// @since  x.y.z, 04.01.2019
   size_t bytesFlushed() const
   {
      return mBytesFlushed;
   } // CountPolicy::bytesFlushed

private:
   /// Counts the number of times that WriteBuffer::append() was called.
   size_t mNumAppendCalled = 0;
   /// Counts the number of bytes to passed to the WriteBuffer object.
   size_t mBytesAppended = 0;
   /// Counts the number of times that data was written to the destination,
   /// either from WriteBuffer::flush() or directly from a large data block.
   size_t mNumFlushCalled = 0;
   /// Counts the amount of bytes written to the destination.
   size_t mBytesFlushed = 0;

}; // CountPolicy


/// Use this base class to collect data in a buffer and then write all data from
/// the buffer into a file or a socket or ...<br>
/// Of course writeData() is called to write the data from the buffer to the
/// destination. Call flush() to force writing all the data currently in the
/// buffer to the destination.<br>
/// Finally, when the buffer should be flushed one last time when the object is
/// deleted, call flush() from the destructor of the derived class.
///
/// @tparam  N
///    The size of the buffer to use.
/// @tparam  P
///    The statistics policy to use by this class.<br>
///    Default = EmptyPolicy, a policy that counts nothing.
/// @since  x.y.z, 01.01.2019
template< size_t N, typename P = EmptyPolicy> class WriteBuffer: public P
{
public:
   /// Default constructor, allocates the buffer.
   ///
   /// @since  x.y.z, 01.01.2019
   WriteBuffer();

   // No copying or moving.
   WriteBuffer( const WriteBuffer&) = delete;
   WriteBuffer( WriteBuffer&&) = delete;

   /// Empty, virtual destructor.<br>
   /// To make sure that all data in the buffer is written to the destination,
   /// call flush() from the destructor of the derived class.
   ///
   /// @since  x.y.z, 01.01.2019
   virtual ~WriteBuffer() = default;

   // No assignment.
   WriteBuffer& operator =( const WriteBuffer&) = delete;
   WriteBuffer& operator =( WriteBuffer&&) = delete;

   /// Appends data to the buffer.<br>
   /// If there is not enough space left in the buffer, the buffer is flushed.<br>
   /// The function only fails if flushing the buffer is requested and this
   /// fails, i.e. an exception is thrown by writeData().
   ///
   /// @tparam  T
   ///    The type of the pointer to the data.
   /// @param[in]  data
   ///    Pointer to the data to append to the buffer.
   /// @param[in]  len
   ///    The length of the data block.
   /// @since  x.y.z, 01.01.2019
   template< typename T> void append( const T* const data, size_t len);

   /// Writes all data from the buffer to the destination. Does nothing if the
   /// buffer is empty.
   ///
   /// @since  x.y.z, 01.01.2019
   void flush();

   /// Returns the amount of data currently stored in the buffer.
   ///
   /// @return  Amount of data currently stored in the buffer.
   /// @since  x.y.z, 01.01.2019
   size_t buffered() const;

protected:
   /// Called to actually write data to the destination.<br>
   /// The function must always write all data, ev. using a loop. If writing all
   /// data is impossible, throw an exception.
   ///
   /// @param[in]  data
   ///    Pointer to the beginning of the data block to write.
   /// @param[in]  len
   ///    Length of the data block to write.
   /// @since  x.y.z, 01.01.2019
   virtual void writeData( const unsigned char* const data, size_t len) const = 0;

private:
   /// The internal buffer.
   std::unique_ptr< unsigned char[]>  mpBuffer;
   /// Write position to append data, i.e. number of bytes currently stored in
   /// the buffer.
   size_t                             mWritePos = 0;

}; // WriteBuffer< N, P>


// inlined methods
// ===============


template< size_t N, typename P> WriteBuffer< N, P>::WriteBuffer():
   mpBuffer( new unsigned char[ N])
{
} // WriteBuffer< N, P>::WriteBuffer


template< size_t N, typename P>
   template< typename T>
      void WriteBuffer< N, P>::append( const T* const data, size_t len)
{
   P::appended( len);

   if (len >= N)
   {
      // the data block is larger than the buffer
      flush();
      writeData( reinterpret_cast< const unsigned char* const>( data), len);
      P::flushed( len);
   } else if (N - mWritePos < len)
   {
      // data block fits in buffer, but there is not enough free space
      flush();
      ::memcpy( mpBuffer.get(), data, len);
      mWritePos = len;
   } else
   {
      ::memcpy( &mpBuffer[ mWritePos], data, len);
      mWritePos += len;
   } // end if
} // WriteBuffer< N, P>::append


template< size_t N, typename P> void WriteBuffer< N, P>::flush()
{
   if (mWritePos > 0)
   {
      writeData( mpBuffer.get(), mWritePos);
      P::flushed( mWritePos);
      mWritePos = 0;
   } // end if
} // WriteBuffer< N, P>::flush


template< size_t N, typename P> size_t WriteBuffer< N, P>::buffered() const
{
   return mWritePos;
} // WriteBuffer< N, P>::buffered


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_WRITE_BUFFER_HPP


// =====  END OF write_buffer.hpp  =====

