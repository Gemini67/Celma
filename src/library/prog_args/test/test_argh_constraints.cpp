
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
**    Test program for the feature "argument constraints" in the module
**    celma::prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgHConstraintsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;
using std::runtime_error;
using std::string;



/// Check the argument-constraint 'requires'.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires)
{

   string  name;
   int     idx;


   // constraint is not activated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);
   } // end scope

   // constraint met, no error
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // constraint_requires



/// Check the argument-constraint 'requires' with one argument that requires two
/// other arguments.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires_two)
{

   string  name;
   int     idx;
   string  opt;


   // constraint is not activated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint error: third argument not used/set
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint met with character argument, no error
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5 -o all", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint met with log argument, no error
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5 --opt all", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint met with character argument, no error, different argument order
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -o all -i 5", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint met with log argument, no error, different argument order
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 --opt all -i 5", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // constraint_requires_two



/// Check the argument-constraint 'requires' with an argument that requires a
/// second one, which in turn requires a third one.<br>
/// Logic-wise this is the same as the previous test case, but the runtime
/// implications are different.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires_chaining)
{

   string  name;
   int     idx;
   string  opt;


   // constraint is not activated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint error: third argument not used/set
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint met with character argument, no error
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5 -o all", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint met with log argument, no error
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5 --opt all", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // constraint_requires_chaining



/// Check the argument-constraint 'requires' with two different arguments that
/// both require a third argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_required_twice)
{

   string  name;
   int     idx;
   string  opt;


   // constraint is not activated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint required once, first arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint required once, second arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 56", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint required twice
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 56", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint required once, fulfilled, short arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -o 1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint required once, fulfilled, short arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 56 -o 1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint required twice, fulfilled, short arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 56 -o 1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint required twice, fulfilled, long arg
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 56 --opt=1", nullptr);


      ah.addArgument( "n",     DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::requires( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // constraint_required_twice



/// Check the argument-constraint 'excludes'.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_excludes)
{

   string  name;
   int     idx;


   // constraint is not activated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint not activated, use now not forbidden argument
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 5", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // constraint error: try to use excluded argument
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n name1 -i 5", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // constraint not activated yet ...
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 7 -n name1", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // both arguments exclude each other
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 7 -n name1", nullptr);


      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index")
                    ->addConstraint( celma::prog_args::excludes( "n"));;

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

} // constraint_excludes



/// Check the constraint 'all of'.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_all_of)
{

   string  name;
   int     idx;
   int     rate;


   // invalid list of arguments: unknown argument
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r;a")), runtime_error);
   } // end scope

   // invalid list of arguments: short/long mixed
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_THROW( ah.addConstraint(
                              celma::prog_args::all_of( "n;i,name;r")),
                           runtime_error);
   } // end scope

   // none of the specified arguments used: constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // none of the specified arguments used, only another/not relevant:
   // constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-a 7", nullptr);
      int                    valueA;
      

      ah.addArgument( "a",       DEST_VAR( valueA), "Value A");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // one of the specified arguments used: constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // not all of the specified arguments used: constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 5 -r 17", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // all of the specified arguments used: constraint is fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname -i 5 -r 17", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // same but: specify mix of argument specs
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname -i 5 -r 17", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // same but: use combination of short and long arguments
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "--name myname -i 5 --rate 17", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      // specify mix of argument specs
      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // same but: mixed in other arguments not relevant for the constraint
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-a 5 -b 7 -n myname -i 5 -c 5 -r 17", nullptr);
      int                    valueA;
      int                    valueB;
      int                    valueC;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "b",       DEST_VAR( valueB), "Value b");
      ah.addArgument( "c",       DEST_VAR( valueC), "Value c");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      // specify mix of argument specs
      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // constraint_all_of



/// Check the constraint 'any of'.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_any_of)
{

   string  name;
   int     idx;
   int     rate;


   // none of the arguments is used: constraint is fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // none of the arguments is used, only another/not relevant argument:
   // constraint is fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-a 756", nullptr);
      int                    valueA;


      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // one of the arguments is used: constraint is fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname -i 7", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 7 -r 545", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;index;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "--rate 5 -a 77 -i 7", nullptr);
      int                    valueA;


      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;index;rate")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

} // constraint_any_of



/// Check the constraint 'one of'.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_one_of)
{

   string  name;
   int     idx;
   int     rate;


   // no argument used: constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // no/another argument used: constraint is not fulfilled
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-a 6", nullptr);
      int                    valueA;


      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "--index 5", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "name;i;rate")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-i 17", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;index;r")));
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // try to use two of the arguments: constraint violated
   {
      Handler                ah( 0);
      const ArgString2Array  as2a( "-n myname --index=8", nullptr);


      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV), runtime_error);
   } // end scope

} // constraint_one_of



/// Try a mix of various constraints.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_mix)
{

   // -n mandatory, -i or -p required, -f when -p, -d or -w or -s one of optional
   class TestData
   {
   public:
      explicit TestData( const string& prog_args):
         ah( 0),
         as2a( prog_args, nullptr),
         name(),
         input_name(),
         path(),
         format_name(),
         display( false),
         do_write( false),
         do_store( false)
      {

         ah.addArgument( "n,name",    DEST_VAR( name),        "Name")
                       ->setIsMandatory();
         ah.addArgument( "i,input",   DEST_VAR( input_name),  "Input Name");
         ah.addArgument( "p,path",    DEST_VAR( path),        "Path")
                       ->addConstraint( celma::prog_args::requires( "f,format"));
         ah.addArgument( "f,format",  DEST_VAR( format_name), "Format");
         ah.addArgument( "d,display", DEST_VAR( display),     "Display");
         ah.addArgument( "w,write",   DEST_VAR( do_write),    "Write");
         ah.addArgument( "s,store",   DEST_VAR( do_store),    "Store");

         BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "input;path")));
         BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "d;w;s")));

      } // end TestData::TestData

      Handler                ah;
      const ArgString2Array  as2a;
      string                 name;
      string                 input_name;
      string                 path;
      string                 format_name;
      bool                   display;
      bool                   do_write;
      bool                   do_store;

   }; // TestData

   // mandatory argument not set
   {
      TestData  td( "");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   // celma::prog_args::one_of requirement validated
   {
      TestData  td( "--name myname");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   // minimum set of arguments, okay
   {
      TestData  td( "--name myname -i input_source");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   // minimum set of arguments, okay
   {
      TestData  td( "--name myname --input=input_source");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   // both of mutually exlusive arguments set, contraint violated
   {
      TestData  td( "--name myname --input input_source --path=my_path");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   // additional required argument missing
   {
      TestData  td( "--name myname -p from_path");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   // all necessary arguments set
   {
      TestData  td( "--name myname -p from_path --format=formatname");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   // all necessary arguments set plus one of the optional group
   {
      TestData  td( "--name myname -p from_path --format=formatname -d");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   // all necessary arguments set plus one of the optional group
   {
      TestData  td( "--name myname -p from_path --format=formatname -w");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   // attempt to set two arguments from the optional group: constraint violated
   {
      TestData  td( "--name myname -p from_path --format=formatname -w -s");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

} // constraint_mix



// =====  END OF test_argh_constraints.cpp  =====

