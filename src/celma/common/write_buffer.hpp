
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


#include <cstddef>
#include <cstring>
#include <memory>
#include <stdexcept>


namespace celma { namespace common {


// Class EmptyWritePolicy
// ======================


/// Default policy for the class WriteBuffer: Does nothing.
///
/// @since  1.20.0, 04.01.2019
class EmptyWritePolicy
{
public:
   /// Called when data is appended to the write buffer: Does nothing.
   ///
   /// @param  Ignored.
   /// @since  1.20.0, 04.01.2019
   void appended( size_t /* len */)
   {
   } // EmptyWritePolicy::appended

   /// Called when data is written to the destination: Does nothing.
   ///
   /// @param  Ignored.
   /// @since  1.20.0, 04.01.2019
   void flushed( size_t /* len */)
   {
   } // EmptyWritePolicy::flushed

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  1.20.0, 25.01.2019
   size_t numAppendCalled() const
   {
      return 0;
   } // EmptyWritePolicy::numAppendCalled

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  1.20.0, 25.01.2019
   size_t bytesAppended() const
   {
      return 0;
   } // EmptyWritePolicy::bytesAppended

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  1.20.0, 25.01.2019
   size_t numFlushCalled() const
   {
      return 0;
   } // EmptyWritePolicy::numFlushCalled

   /// Always returns 0.
   ///
   /// @return  0.
   /// @since  1.20.0, 25.01.2019
   size_t bytesFlushed() const
   {
      return 0;
   } // EmptyWritePolicy::bytesFlushed

}; // EmptyWritePolicy


// Class WriteCountPolicy
// ======================


/// Use this policy with the class WriteBuffer to get statistics about how often
/// the functions were called and how many bytes of data were handled.
///
/// @since  1.20.0, 04.01.2019
class WriteCountPolicy
{
public:
   /// Called when data is appended to the write buffer. Counts the number of
   /// calls and how many bytes were appended.
   ///
   /// @param[in]  len  Number of bytes that were appended.
   /// @since  1.20.0, 04.01.2019
   void appended( size_t len)
   {
      ++mNumAppendCalled;
      mBytesAppended += len;
   } // WriteCountPolicy::appended

   /// Called when data is written to the destination. This can be either from
   /// the buffer, or directly if a large block of data was passed.<br>
   /// Counts the number of calls and the amount of bytes written.
   ///
   /// @param[in]  len  Number of bytes that were written to the destination.
   /// @since  1.20.0, 04.01.2019
   void flushed( size_t len)
   {
      ++mNumFlushCalled;
      mBytesFlushed += len;
   } // WriteCountPolicy::flushed

   /// Returns how many times WriteBuffer::append() was called.
   ///
   /// @return
   ///    Number of times that the append method was called in the class
   ///    WriteBuffer.
   /// @since  1.20.0, 04.01.2019
   size_t numAppendCalled() const
   {
      return mNumAppendCalled;
   } // WriteCountPolicy::numAppendCalled

   /// Returns how many bytes were passed to the WriteBuffer object through
   /// calling the append method.<br>
   /// This does not necessarily mean that the data was appended to the internal
   /// buffer: If a block of data was passed that is larger than the buffer, it
   /// is directly written to the destination.
   ///
   /// @return
   ///    Number of bytes passed to WriteBuffer::append().
   /// @since  1.20.0, 04.01.2019
   size_t bytesAppended() const
   {
      return mBytesAppended;
   } // WriteCountPolicy::bytesAppended

   /// Returns how many times WriteBuffer::flush() was called, either externally
   /// or internally when the buffer was full/more free space was needed.<br>
   /// This includes also the calls to write a large block of data directly to
   /// the destination.
   ///
   /// @return
   ///    Number of times that data was flushed, either from the internal
   ///    buffer or directly.
   /// @since  1.20.0, 04.01.2019
   size_t numFlushCalled() const
   {
      return mNumFlushCalled;
   } // WriteCountPolicy::numFlushCalled

   /// Returns the number of bytes that were written to the destination.
   ///
   /// @return
   ///    Number of bytes written to the destination so far, either from the
   ///    internal buffer or directly.
   /// @since  1.20.0, 04.01.2019
   size_t bytesFlushed() const
   {
      return mBytesFlushed;
   } // WriteCountPolicy::bytesFlushed

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

}; // WriteCountPolicy


// Template Class WriteBuffer
// ==========================


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
///    Default = EmptyWritePolicy, a policy that counts nothing.
/// @since  1.20.0, 01.01.2019
template< size_t N, typename P = EmptyWritePolicy> class WriteBuffer: public P
{
public:
   /// Default constructor, allocates the buffer.
   ///
   /// @since  1.20.0, 01.01.2019
   WriteBuffer();

   // No copying or moving.
   WriteBuffer( const WriteBuffer&) = delete;
   WriteBuffer( WriteBuffer&&) = delete;

   /// Empty, virtual destructor.<br>
   /// To make sure that all data in the buffer is written to the destination,
   /// call flush() from the destructor of the derived class.
   ///
   /// @since  1.20.0, 01.01.2019
   virtual ~WriteBuffer() = default;

   // No assignment.
   WriteBuffer& operator =( const WriteBuffer&) = delete;
   WriteBuffer& operator =( WriteBuffer&&) = delete;

   /// Appends data to the buffer.<br>
   /// If there is not enough space left in the buffer, the buffer is flushed.<br>
   /// The function fails if a NULL pointer is passed, or if flushing the buffer
   /// is requested and this fails, i.e. an exception is thrown by
   /// writeData().<br>
   /// Does nothing when a length of 0 is passed.
   ///
   /// @tparam  T
   ///    The type of the pointer to the data.
   /// @param[in]  data
   ///    Pointer to the data to append to the buffer.
   /// @param[in]  len
   ///    The length of the data block.
   /// @since  1.20.0, 01.01.2019
   template< typename T> void append( const T* const data, size_t len) noexcept( false);

   /// Writes all data from the buffer to the destination. Does nothing if the
   /// buffer is empty.
   ///
   /// @since  1.20.0, 01.01.2019
   void flush();

   /// Returns the amount of data currently stored in the buffer.
   ///
   /// @return  Amount of data currently stored in the buffer.
   /// @since  1.20.0, 01.01.2019
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
   /// @since  1.20.0, 01.01.2019
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
         noexcept( false)
{
   if (len == 0)
      return;
   if (data == nullptr)
      throw std::runtime_error( "NULL pointer passed to append()");

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

