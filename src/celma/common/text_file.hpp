
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
/// See documentation of template celma::common::TextFile.


#ifndef CELMA_COMMON_TEXT_FILE_HPP
#define CELMA_COMMON_TEXT_FILE_HPP


#include <string>
#include <fstream>
#include <stdexcept>
#include "celma/common/detail/stream_line_iterator.hpp"
#include "celma/common/detail/filter_policy.hpp"
#include "celma/common/detail/line_handler_policy.hpp"


namespace celma { namespace common {


using detail::EmptyLineFilter;
using detail::FileLineStat;
using detail::NoFilter;
using detail::StatLineHandler;


/// @since  0.3, 13.04.2016
template< typename FilterPolicy = detail::NoFilter,
          typename LineHandlerPolicy = detail::DummyLineHandler> class TextFile
{
public:
   TextFile();
   explicit TextFile( const std::string& fname);
   ~TextFile();

   TextFile( const TextFile&) = delete;
   TextFile& operator =( const TextFile&) = delete;

   void set( const std::string& fname);

   typedef detail::StreamLineIterator< std::ifstream, FilterPolicy, LineHandlerPolicy>  iterator;

   iterator begin();
   iterator end();

private:
   std::ifstream  mStream;

}; // TextFile< FilterPolicy, LineHandlerPolicy>


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile():
      mStream()
{
}


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::TextFile( const std::string& fname):
      mStream( fname)
{
   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "could not open file '" + fname + "'");
}


template< typename FilterPolicy, typename LineHandlerPolicy>
   TextFile< FilterPolicy, LineHandlerPolicy>::~TextFile()
{
   mStream.close();
}


template< typename FilterPolicy, typename LineHandlerPolicy>
   void TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::set( const std::string& fname)
{

   if (mStream && mStream.is_open())
      mStream.close();

   mStream.open( fname);

   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "could not open file '" + fname + "'");
}


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::begin()
{
   if (!mStream || !mStream.is_open())
      throw std::runtime_error( "file is not open");
   mStream.seekg( 0);
   return iterator( mStream);
}


template< typename FilterPolicy, typename LineHandlerPolicy>
   typename TextFile< FilterPolicy, LineHandlerPolicy>::iterator
      TextFile< FilterPolicy, LineHandlerPolicy>::TextFile::end()
{
   return iterator( mStream, true);
}


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TEXT_FILE_HPP


// ==========================  END OF text_file.hpp  ==========================

