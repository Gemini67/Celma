
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Performance measurement program for "integer to tring" and similar
**    conversions.
**
--*/


// OS/C lib includes
#include <cstdlib>


// C++ Standard Library includes
#include <string>


// Boost includes
#include "boost/lexical_cast.hpp"


// project includes
#include "celma/format/int2string.hpp"
#include "celma/test/measure.hpp"


namespace {


/// Measure using the function celma::format::int2string().
/// @since  0.13.5, 28.02.2017
void measure_int2str()
{

   const std::string  result( celma::format::int2string( ::rand()));


   if (result.empty())
   {
      ::exit( EXIT_FAILURE);
   } // end if
      
} // measure_int2str


/// Measure conversion using boost::lexical_cast<>.
/// @since  0.13.5, 28.02.2017
void measure_boost_lexical_cast()
{

   const std::string  result( boost::lexical_cast< std::string>( ::rand()));


   if (result.empty())
   {
      ::exit( EXIT_FAILURE);
   } // end if
      
} // measure_boost_lexical_cast


/// Measure conversion using std::ostringstream.
/// @since  0.13.5, 28.02.2017
void measure_ostringstream()
{

   std::ostringstream  oss;


   oss << ::rand();

   const std::string  result( oss.str());

   if (result.empty())
   {
      ::exit( EXIT_FAILURE);
   } // end if
      
} // measure_ostringstream


/// Measure the function sprintf().
/// @since  0.13.5, 28.02.2017
void measure_sprintf()
{

   char  buffer[ 128];


   ::sprintf( buffer, "%d", ::rand());

   const std::string  result( buffer);

   if (result.empty())
   {
      ::exit( EXIT_FAILURE);
   } // end if
      
} // measure_sprintf


/// Measure the function std::to_string().
/// @since  0.13.5, 28.02.2017
void measure_to_string()
{


   const std::string  result( std::to_string( ::rand()));


   if (result.empty())
   {
      ::exit( EXIT_FAILURE);
   } // end if
      
} // measure_to_string


} // namespace



/// The main function.
/// @since  0.13.5, 28.02.2017
int main()
{

   ::srand( 102030405);
   std::ignore = celma::test::measure( 1000000, "int2str", measure_int2str);
   
   ::srand( 102030405);
   std::ignore = celma::test::measure( 1000000, "boost::lexical_cast", measure_boost_lexical_cast);

   ::srand( 102030405);
   std::ignore = celma::test::measure( 1000000, "std::ostringstream", measure_ostringstream);

   ::srand( 102030405);
   std::ignore = celma::test::measure( 1000000, "sprintf", measure_sprintf);

   ::srand( 102030405);
   std::ignore = celma::test::measure( 1000000, "std::to_string", measure_to_string);

} // main



// =====  END OF test_int2str_perf.cpp  =====

