
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module TextFile using the Boost.Test module.
**
--*/


// headerfile of the module to test
#include "celma/common/text_file.hpp"


// Boost includes
#define BOOST_TEST_MODULE TextFileTest
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::EmptyLineFilter;
using celma::common::FileLineStat;
using celma::common::NoFilter;
using celma::common::StatLineHandler;
using celma::common::TextFile;


using FilterStatTextFile = TextFile< EmptyLineFilter, StatLineHandler>;


BOOST_TEST_DONT_PRINT_LOG_VALUE( TextFile<>::const_iterator);
BOOST_TEST_DONT_PRINT_LOG_VALUE( FilterStatTextFile::const_iterator);


namespace {

const int  NumLines = 169;
const int  NumEmptyLines = 46;
const int  NumTextLines = NumLines - NumEmptyLines;

const char* const  File = "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp";

} // namespace



/// Test some error conditions.
/// @since  x.y.z, 13.06.2017
BOOST_AUTO_TEST_CASE( test_error_handling)
{

   {
      TextFile<>  ctf;
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

   {
      BOOST_REQUIRE_THROW( TextFile<>( ""), std::runtime_error);
   } // end scope

   {
      TextFile<>  ctf( "there is no such file");
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

} // test_error_handling



/// Use the class with the default policies: no filter, no line handler.
/// @since  x.y.z, 13.04.2016
BOOST_AUTO_TEST_CASE( default_policies)
{

   TextFile<>  ctf( File);
   int         num_lines = 0;
   int         num_empty_lines = 0;


   for (auto const& line : ctf)
   {
      if (line.empty())
         ++num_empty_lines;
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, NumLines);
   BOOST_REQUIRE_EQUAL( num_empty_lines, NumEmptyLines);

} // default_policies



/// Use the class with the default policies: no filter, no line handler.
/// @since  x.y.z, 13.06.2017
BOOST_AUTO_TEST_CASE( default_policies_set)
{

   TextFile<>  ctf;
   int         num_lines = 0;
   int         num_empty_lines = 0;


   ctf.set( File);

   for (auto const& line : ctf)
   {
      if (line.empty())
         ++num_empty_lines;
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, NumLines);
   BOOST_REQUIRE_EQUAL( num_empty_lines, NumEmptyLines);

} // default_policies_set



/// Read the text file but ignore empty lines.
/// @since  x.y.z, 13.04.2016
BOOST_AUTO_TEST_CASE( no_empty_lines)
{

   TextFile< EmptyLineFilter>  ctf( File);
   int                         num_lines = 0;
   int                         num_empty_lines = 0;


   for (auto const& line : ctf)
   {
      if (line.empty())
         ++num_empty_lines;
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, NumTextLines);


} // no_empty_lines



/// Read all lines, now also create a statistic.
/// @since  x.y.z, 13.04.2016
BOOST_AUTO_TEST_CASE( statistics_only)
{

   TextFile< NoFilter, StatLineHandler>  ctf( File);
   FileLineStat                          fls;


   for (auto it = ctf.begin(); it != ctf.end(); ++it)
   {
      it.setEndStat( &fls);
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      NumLines);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,  0);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, NumLines);

} // statistics_only



/// Read file, filter empty lines, create statistic.
/// @since  x.y.z, 13.04.2016
BOOST_AUTO_TEST_CASE( statistics_no_empty_lines)
{

   FilterStatTextFile  ctf( File);
   FileLineStat        fls;


   for (auto it = ctf.begin(); it != ctf.end(); ++it)
   {
      it.setEndStat( &fls);
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      NumLines);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,  NumEmptyLines);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, NumTextLines);

} // statistics_no_empty_lines



/// Create a copy of the iterator and test that both return the same results
/// afterwards.
/// @since  x.y.z, 16.05.2017
BOOST_AUTO_TEST_CASE( copy_default_policies)
{

   TextFile<>  ctf( File);
   int         num_lines = 0;
   auto        iter( ctf.begin());


   for (; iter != ctf.end(); ++iter)
   {
      if (++num_lines > 11)
         break;
   } // end for

   auto  second_iter( iter);

   BOOST_REQUIRE_EQUAL( iter, second_iter);
   BOOST_REQUIRE_EQUAL( *iter, *second_iter);

   ++iter;
   BOOST_REQUIRE( iter != ctf.end());

   ++second_iter;
   BOOST_REQUIRE( second_iter != ctf.end());

   BOOST_REQUIRE_EQUAL( iter, second_iter);
   BOOST_REQUIRE_EQUAL( *iter, *second_iter);

   ++second_iter;
   BOOST_REQUIRE( second_iter != ctf.end());

   ++iter;
   BOOST_REQUIRE( iter != ctf.end());

   BOOST_REQUIRE_EQUAL( iter, second_iter);
   BOOST_REQUIRE_EQUAL( *iter, *second_iter);

} // copy_default_policies



/// Create a copy of the iterator with policies Read file, filter empty lines,
/// create statistic.
/// @since  x.y.z, 13.04.2016
BOOST_AUTO_TEST_CASE( copy_statistics_no_empty_lines)
{

   FilterStatTextFile  ctf( File);
   FileLineStat        fls;
   int                 num_lines = 0;
   auto                iter( ctf.begin());


   iter.setEndStat( &fls);

   for (; iter != ctf.end(); ++iter)
   {
      if (++num_lines > 11)
         break;
   } // end for

   auto  second_iter( iter);

   while (iter != ctf.end())
   {
      BOOST_REQUIRE_EQUAL( iter, second_iter);
      BOOST_REQUIRE_EQUAL( *iter, *second_iter);

      ++iter;
      ++second_iter;

      if (iter != ctf.end())
      {
         BOOST_REQUIRE( second_iter != ctf.end());
      } // end if
   } // end while
      
} // copy_statistics_no_empty_lines



// ========================  END OF test_text_file.cpp  ========================

