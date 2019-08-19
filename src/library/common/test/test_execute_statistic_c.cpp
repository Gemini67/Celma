
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "execute statistic", using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/common/execute_statistic.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ExecuteStatisticTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/global_fixture_access.hpp"
#include "celma/test/test_prog_arguments.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::common::ExecuteStatistic;


namespace {


/// Test environment initialisation: Need the start argument of the test program.
///
/// @since  1.22.0, 02.04.2019
class TestEnvironment: public celma::test::GlobalFixtureAccess< TestEnvironment>
{
public:
   /// Constructor.
   ///
   /// @since  1.22.0, 02.04.2019
   TestEnvironment():
      celma::test::GlobalFixtureAccess< TestEnvironment>(),
      mProgArgs()
   {
   } // TestEnvironment::TestEnvironment

   /// Returns the number of arguments.
   ///
   /// @return  The number of arguments passed to the test program.
   /// @since  1.22.0, 03.04.2019
   int argC() const
   {
      return mProgArgs.argC();
   } // TestEnvironment::argC

   /// Returns the pointer to the list of arguments.
   ///
   /// @return  Pointer to the list of argument strings.
   /// @since  1.22.0, 03.04.2019
   char** argV() const
   {
      return mProgArgs.argV();
   } // TestEnvironment::argV

private:
   /// Provides information about the program argments.
   celma::test::TestProgArguments  mProgArgs;

}; // TestEnvironment


} // namespace


BOOST_GLOBAL_FIXTURE( TestEnvironment);



/// First simple tests.
///
/// @since  1.30.0, 23.06.2019
BOOST_AUTO_TEST_CASE( basic_execute_statistic)
{

   if (TestEnvironment::object().argC() > 1)
   {
      ExecuteStatistic::instance().erasePathPrefix(
        std::string( TestEnvironment::object().argV()[ 1]) + "/");
   } // end if

   BOOST_REQUIRE_EQUAL( ExecuteStatistic::instance().size(), 0);

   COUNT_EXECUTIONS;

   BOOST_REQUIRE_EQUAL( ExecuteStatistic::instance().size(), 1);

   auto  executions = GET_EXECUTIONS();
   BOOST_REQUIRE_EQUAL( executions, 1);

   ExecuteStatistic::instance().reset();
   BOOST_REQUIRE_EQUAL( ExecuteStatistic::instance().size(), 1);

   executions = GET_EXECUTIONS();
   BOOST_REQUIRE_EQUAL( executions, 0);

} // basic_execute_statistic



/// Use two call points in the same function.
///
/// @since  1.30.0, 14.08.2019
BOOST_AUTO_TEST_CASE( two_call_points)
{

   const size_t  previous_size = ExecuteStatistic::instance().size();

   COUNT_EXECUTIONS;

   BOOST_REQUIRE_EQUAL( ExecuteStatistic::instance().size(), previous_size + 1);

   auto  executions = GET_EXECUTIONS();
   BOOST_REQUIRE_EQUAL( executions, 1);

   for (int i = 0; i < 3; ++i)
   {
      COUNT_EXECUTIONS;
   } // end for

   BOOST_REQUIRE_EQUAL( ExecuteStatistic::instance().size(), previous_size + 2);

   executions = GET_EXECUTIONS();
   BOOST_REQUIRE_EQUAL( executions, 3);

} // two_call_points



/// Check if iterating over the call points returns all entries.
///
/// @since  1.30.0, 14.08.2019
BOOST_AUTO_TEST_CASE( check_iteration)
{

   int  nbr = 0;


   for (auto const& call_points : ExecuteStatistic::instance())
   {
      if (nbr == 0)
      {
         BOOST_REQUIRE_EQUAL( call_points.second, 0);
      } else if (nbr == 1)
      {
         BOOST_REQUIRE_EQUAL( call_points.second, 1);
      } else
      {
         BOOST_REQUIRE_EQUAL( call_points.second, 3);
      } // end if
      ++nbr;
   } // end for

   BOOST_REQUIRE_EQUAL( nbr, 3);

} // check_iteration



/// Check the output of the call points.
///
/// @since  1.30.0, 14.08.2019
BOOST_AUTO_TEST_CASE( check_output)
{

   std::ostringstream  oss;


   oss << ExecuteStatistic::instance();

   BOOST_REQUIRE( !oss.str().empty());

   if (TestEnvironment::object().argC() > 1)
   {
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
         "src/library/common/test/test_execute_statistic_c.cpp: basic_execute_statistic::test_method[104] = 0\n"
         "src/library/common/test/test_execute_statistic_c.cpp: two_call_points::test_method[129] = 1\n"
         "src/library/common/test/test_execute_statistic_c.cpp: two_call_points::test_method[138] = 3\n"));
   } // end if

} // check_output



// =====  END OF test_execute_statistic.cpp  =====
