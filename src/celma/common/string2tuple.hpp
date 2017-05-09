
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
/// See documentation of template function celma::common::tuple_at_index.


#ifndef CELMA_COMMON_TUPLE_AT_INDEX_HPP
#define CELMA_COMMON_TUPLE_AT_INDEX_HPP


#include <cassert>
#include <string>
#include <tuple>
#include <boost/lexical_cast.hpp>

#include "celma/common/tuple_at_index.hpp"
#include "celma/common/tuple_length.hpp"


namespace celma { namespace common {


class TupleValueAssign
{
public:
   TupleValueAssign( const std::string& value):
      mValue( value)
   {
   }

   template< typename T> void operator()( T& tuple_value) const
   {
      tuple_value = boost::lexical_cast< T>( mValue);
   }

private:
   const std::string  mValue;

};


template< typename T> void string2tuple( T& dest_tuple, const std::string& str)
{

   int                     idx = 0;
   std::string::size_type  last_pos = 0; 
   std::string::size_type  comma_pos = 0; 

   while ((comma_pos = str.find( ',', last_pos)) != std::string::npos)
   {
      const std::string       curr_value( str, last_pos, comma_pos - last_pos);
      const TupleValueAssign  tva( curr_value);

      tuple_at_index( idx, dest_tuple, tva);

      last_pos = comma_pos + 1;
      ++idx;
   } // end while

   // still have to handle the last part of the string
   const std::string       curr_value( str, last_pos);
   const TupleValueAssign  tva( curr_value);

   tuple_at_index( idx, dest_tuple, tva);

   std::cout << "tuple length = " << tuple_length( dest_tuple) << std::endl;
   assert( idx + 1 == tuple_length( dest_tuple));

/*
   using a generic lampda with c++ 14
      tuple_at_index( idx, dest_tuple, [&]( auto& tuple_val)
      {
         tuple_val = boost::lexical_cast< decltype< tuple_val>>( curr_value);
      });
*/

}


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_TUPLE_AT_INDEX_HPP


// =========================  END OF string2tuple.hpp  =========================

