
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module TextFile using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE TextFileTest
#include <boost/test/unit_test.hpp>
#include <utility>


// project includes
#include "celma/common/text_file.hpp"


using namespace std;
using namespace celma;


/// Use the class with the default policies: no filter, no line handler.
/// @since  0.3, 13.04.2016
BOOST_AUTO_TEST_CASE( default_policies)
{

   common::TextFile<>  ctf( "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp");
   int                 num_lines = 0;


   for (auto const& line : ctf)
   {
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, 128);

} // end default_policies



/// 
/// @since  0.3, 13.04.2016
BOOST_AUTO_TEST_CASE( no_empty_lines)
{

   common::TextFile< common::EmptyLineFilter>  ctf( "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp");
   int                                         num_lines = 0;


   for (auto const& line : ctf)
   {
      ++num_lines;
   } // end for

   BOOST_REQUIRE_EQUAL( num_lines, 87);

} // end no_empty_lines



/// 
/// @since  0.3, 13.04.2016
BOOST_AUTO_TEST_CASE( statistics_only)
{

   common::TextFile< common::NoFilter, common::StatLineHandler>  ctf( "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp");
   common::FileLineStat                                          fls;


   for (auto it = ctf.begin(); it != ctf.end(); ++it)
   {
      it.setEndStat( &fls);
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      128);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,    0);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, 128);

} // end statistics_only



/// 
/// @since  0.3, 13.04.2016
BOOST_AUTO_TEST_CASE( statistics_no_empty_lines)
{

   common::TextFile< common::EmptyLineFilter, common::StatLineHandler>  ctf( "/home/rene/projects/Celma/textfile/src/celma/common/text_file.hpp");
   common::FileLineStat                                                 fls;


   for (auto it = ctf.begin(); it != ctf.end(); ++it)
   {
      it.setEndStat( &fls);
   } // end for

   BOOST_REQUIRE_EQUAL( fls.linesRead,      128);
   BOOST_REQUIRE_EQUAL( fls.linesFiltered,  41);
   BOOST_REQUIRE_EQUAL( fls.linesProcessed, 87);

} // end statistics_no_empty_lines



// ========================  END OF test_text_file.cpp  ========================

