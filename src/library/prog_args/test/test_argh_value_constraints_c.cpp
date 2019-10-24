
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
**    Test program for the feature "argument value constraints" in the module
**    celma::prog_args::Handler, using the Boost.Test framework.
**
--*/


// module to test, headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgHValueConstraintsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using celma::prog_args::differ;



/// Check that errors are caught.
/// Errors processed in te handler class can be checked with any constraint
/// type.
///
/// @since  1.31.0, 22.10.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( nullptr), std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "any arg")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d", DEST_VAR( dummy), "dummy"));

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "d;d")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      dummy1;
      int      dummy2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d,dummy1", DEST_VAR( dummy1),
         "no name"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "y,dummy2", DEST_VAR( dummy2),
         "no name"));

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "d,dummy2;y")),
         std::invalid_argument);
      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "y,dummy1;d")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      dummy1;
      int      dummy2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d,dummy1", DEST_VAR( dummy1),
         "no name"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "y,dummy2", DEST_VAR( dummy2),
         "no name"));

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< std::string>( "d;y")),
         std::invalid_argument);
   } // end scope

   {
      Handler      ah( 0);
      int          dummy1;
      std::string  dummy2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d,dummy1", DEST_VAR( dummy1),
         "no name"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "y,dummy2", DEST_VAR( dummy2),
         "no name"));

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< std::string>( "d;y")),
         std::invalid_argument);
   } // end scope

   {
      Handler      ah( 0);
      int          dummy1;
      std::string  dummy2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d,dummy1", DEST_VAR( dummy1),
         "no name"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "y,dummy2", DEST_VAR( dummy2),
         "no name"));

      BOOST_REQUIRE_THROW( ah.addConstraint( differ< int>( "d;y")),
         std::invalid_argument);
   } // end scope

} // errors



/// Verify that a "differ" constraint on two strings works correctly.
///
/// @since  1.31.0, 22.10.2019
BOOST_AUTO_TEST_CASE( constraint_differ_string)
{

   // constraint is not checked
   {
      Handler      ah( 0);
      std::string  primary;
      std::string  backup;
      auto const   as2a = make_arg_array( "", nullptr);

      ah.addArgument( "p", DEST_VAR( primary), "Primary");
      ah.addArgument( "b", DEST_VAR( backup),  "Backup");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< std::string>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler      ah( 0);
      std::string  primary;
      std::string  backup;
      auto const   as2a = make_arg_array( "-p server1", nullptr);

      ah.addArgument( "p", DEST_VAR( primary), "Primary");
      ah.addArgument( "b", DEST_VAR( backup),  "Backup");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< std::string>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked
   {
      Handler      ah( 0);
      std::string  primary;
      std::string  backup;
      auto const   as2a = make_arg_array( "-p server1 -b server2", nullptr);

      ah.addArgument( "p", DEST_VAR( primary), "Primary");
      ah.addArgument( "b", DEST_VAR( backup),  "Backup");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< std::string>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint complains
   {
      Handler      ah( 0);
      std::string  primary;
      std::string  backup;
      auto const   as2a = make_arg_array( "-p server1 -b server1", nullptr);

      ah.addArgument( "p", DEST_VAR( primary), "Primary");
      ah.addArgument( "b", DEST_VAR( backup),  "Backup");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< std::string>( "p;b")));

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // constraint_differ_string



/// Verify that a "differ" constraint on two integer variables works correctly.
/// 
/// @since  1.31.0, 22.10.2019
BOOST_AUTO_TEST_CASE( constraint_differ_int)
{

   // constraint is not checked
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      auto const  as2a = make_arg_array( "", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      auto const  as2a = make_arg_array( "-p 13", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      auto const  as2a = make_arg_array( "-b 42", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 42", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint complains
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 13", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b")));

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // constraint_differ_int



/// Verify that a "differ" constraint on three integer variables works correctly.
/// 
/// @since  1.31.0, 23.10.2019
BOOST_AUTO_TEST_CASE( constraint_differ_int3)
{

   // constraint is not checked
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-b 42", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is not checked since only one argument is used
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-q 4711", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked with 1 and 2
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 42", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked with 1 and 3
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -q 4711", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked with 2 and 3
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-b 42 -q 4711", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint is successfully checked with 1, 2 and 3
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 42 -q 4711", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint complains
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 13", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // constraint complains
   {
      Handler     ah( 0);
      int         primary_id = -1;
      int         backup_id = -1;
      int         quorum_id = -1;
      auto const  as2a = make_arg_array( "-p 13 -b 42 -q 13", nullptr);

      ah.addArgument( "p", DEST_VAR( primary_id), "Primary id");
      ah.addArgument( "b", DEST_VAR( backup_id),  "Backup id");
      ah.addArgument( "q", DEST_VAR( quorum_id),  "Quorum id");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( differ< int>( "p;b;q")));

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // constraint_differ_int3



// =====  END OF test_argh_value_constraints_c.cpp  =====

