
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template function celma::common::string2tuple<>()


#pragma once


#include <cassert>
#include <string>
#include <tuple>
#include <boost/lexical_cast.hpp>

#include "celma/common/tuple_at_index.hpp"
#include "celma/common/tuple_length.hpp"


namespace celma::common {


namespace detail {


/// Helper class that stores a value in string format and then provides the
/// converted value upon request.
///
/// @since  x.y.z, 19.12.2016
class TupleValueAssign
{
public:
   /// Constructor, stores the value to convert later.
   /// @param[in]  value  String with the value to convert.
   /// @since  x.y.z, 19.12.2016
   explicit TupleValueAssign( const std::string& value):
      mValue( value)
   {
   } // TupleValueAssign::TupleValueAssign

   /// Converts the value to the requested type and assigns it to the given tuple
   /// element.
   ///
   /// @tparam  T  Type to convert the value to.
   /// @param[out]  tuple_value  Tuple element to assign the converted value to.
   /// @since  x.y.z, 19.12.2016
   template< typename T> void operator()( T& tuple_value) const
   {
      tuple_value = boost::lexical_cast< T>( mValue);
   } // TupleValueAssign:operator ()

private:
   /// Stores the string with the value to convert.
   const std::string  mValue;

}; // TupleValueAssign


} // namespace detail


/// Converts multiple values from a comma-separated list in a string, and assigns
/// the values to a tuple.
///
/// @tparam  T  Type of the tuple.
/// @param[out]  dest_tuple  Tuple to assign the values from the string to.
/// @param[in]   str         String with the list of values to convert.
/// @since  x.y.z, 19.12.2016
template< typename T> void string2tuple( T& dest_tuple, const std::string& str)
{

   int                     idx = 0;
   std::string::size_type  last_pos = 0; 
   std::string::size_type  comma_pos = 0; 

   while ((comma_pos = str.find( ',', last_pos)) != std::string::npos)
   {
      const std::string               curr_value( str, last_pos, comma_pos - last_pos);
      const detail::TupleValueAssign  tva( curr_value);

      tuple_at_index( idx, dest_tuple, tva);

      last_pos = comma_pos + 1;
      ++idx;
   } // end while

   // still have to handle the last part of the string
   const std::string               curr_value( str, last_pos);
   const detail::TupleValueAssign  tva( curr_value);

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

} // string2tuple


} // namespace celma::common


// =====  END OF string2tuple.hpp  =====

