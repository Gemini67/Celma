
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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


using FilterStatTextFile = TextFile< EmptyLineFilter, StatLineHandler,
   FileLineStat>;


BOOST_TEST_DONT_PRINT_LOG_VALUE( TextFile<>::const_iterator)
BOOST_TEST_DONT_PRINT_LOG_VALUE( FilterStatTextFile::const_iterator)


namespace {

const char* const  File = "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp";

/// @since  1.3.0, 15.02.2018
class TestFixture
{
public:
   /// Total number of lines in the input file.
   static int  NumLines;
   /// Number of empty lines in the file.
   static int  NumEmptyLines;
   /// Number of lines with text (total number of lines minus number of empty
   /// lines).
   static int  NumTextLines;

   /// Constructor of the test fixture class.<br>
   /// When used for the first time, counts the lines in the test file.
   /// @since  1.3.0, 15.02.2018
   TestFixture();

}; // TestFixture

int  TestFixture::NumLines = -1;
int  TestFixture::NumEmptyLines = -1;
int  TestFixture::NumTextLines = -1;

} // namespace



/// Test some error conditions.
/// @since  1.3.0, 13.06.2017
BOOST_AUTO_TEST_CASE( test_error_handling)
{

   {
      BOOST_REQUIRE_THROW( TextFile<>( ""), std::runtime_error);
   } // end scope

   {
      TextFile<>  ctf;
      BOOST_REQUIRE_THROW( ctf.set( ""), std::runtime_error);
   } // end scope

   {
      TextFile<>  ctf;
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

   {
      FilterStatTextFile  ctf;
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

   {
      TextFile<>  ctf( "there is no such file");
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

   {
      FilterStatTextFile  ctf( "there is no such file");
      BOOST_REQUIRE_THROW( ctf.begin(), std::runtime_error);
   } // end scope

} // test_error_handling



/// Use the class with the default policies: no filter, no line handler.
/// @since  1.3.0, 13.04.2016
BOOST_FIXTURE_TEST_CASE( default_policies, TestFixture)
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
/// @since  1.3.0, 13.06.2017
BOOST_FIXTURE_TEST_CASE( default_policies_set, TestFixture)
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



/// Use the class with the default policies: no filter, no line handler.
/// @since  1.3.0, 15.02.2018
BOOST_FIXTURE_TEST_CASE( default_policies_set_const, TestFixture)
{

   const TextFile<>  ctf( File);
   int               num_lines = 0;


   for (auto iter = ctf.cbegin(); iter != ctf.cend(); ++iter)
   {
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, NumLines);

} // default_policies_set_const



/// Read the text file but ignore empty lines.
/// @since  1.3.0, 13.04.2016
BOOST_FIXTURE_TEST_CASE( no_empty_lines, TestFixture)
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
/// @since  1.3.0, 13.04.2016
BOOST_FIXTURE_TEST_CASE( statistics_only, TestFixture)
{

   TextFile< NoFilter, StatLineHandler, FileLineStat>  ctf( File);
   FileLineStat  fls;
   int           num_lines = 0;


   ctf.setStatObj( fls);

   {
      auto  copy( ctf);
      auto  iter = copy.begin();
      BOOST_REQUIRE( iter.stat() == nullptr);
   } // end scope

   for (auto it = ctf.begin(); it != ctf.end(); ++it)
   {
      BOOST_REQUIRE_EQUAL( it.lineNbr(), num_lines);
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      num_lines);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,  0);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, num_lines);

} // statistics_only



/// Read file, filter empty lines, create statistic.
/// @since  1.3.0, 13.04.2016
BOOST_FIXTURE_TEST_CASE( statistics_no_empty_lines, TestFixture)
{

   FilterStatTextFile  ctf( File);
   FileLineStat        fls;
   int                 num_lines = 0;


   ctf.setStatObj( fls);

   for (auto it = ctf.begin(); it != ctf.end(); it++)
   {
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      NumLines);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,  NumEmptyLines);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, NumTextLines);

} // statistics_no_empty_lines



/// Create a copy of the iterator and test that both return the same results
/// afterwards.
/// @since  1.3.0, 16.05.2017
BOOST_FIXTURE_TEST_CASE( copy_default_policies, TestFixture)
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
/// @since  1.3.0, 13.04.2016
BOOST_FIXTURE_TEST_CASE( copy_statistics_no_empty_lines, TestFixture)
{

   FilterStatTextFile  ctf( File);
   FileLineStat        fls;
   int                 num_lines = 0;
   auto                iter( ctf.begin());


   ctf.setStatObj( fls);

   for (; iter != ctf.end(); ++iter)
   {
      if (++num_lines > 11)
         break;
   } // end for

   auto  second_iter( iter);

   BOOST_REQUIRE( second_iter.stat() == nullptr);

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



namespace {



/// Constructor of the test fixture class.<br>
/// When used for the first time, counts the lines in the test file.
/// @since  1.3.0, 15.02.2018
TestFixture::TestFixture()
{

   if (NumLines != -1)
      return;

   std::ifstream  ifs( File);
   std::string    line;

   assert( ifs.is_open());

   NumLines = 0;
   NumEmptyLines = 0;

   while (std::getline( ifs, line))
   {
      ++NumLines;
      if (line.empty())
         ++NumEmptyLines;
   } // end while

   NumTextLines = NumLines - NumEmptyLines;

} // TestFixture::TestFixture



} // namespace


// =====  END OF test_text_file.cpp  =====

