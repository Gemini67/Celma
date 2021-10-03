
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "argument constraints" in the module
**    celma::prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, headerfile include
#include "celma/prog_args.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgHConstraintsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"


using celma::prog_args::Handler;



/// Check that errors are caught.
/// Errors processed in te handler class can be checked with any constraint
/// type.
///
/// @since  1.23.0 04.04.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( nullptr), std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::all_of( "")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::any_of( "one_arg")),
         std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "d", DEST_VAR( dummy), "no name"));

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::one_of( "d;d")),
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

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::one_of( "d,dummy2;y")),
         std::invalid_argument);
      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::one_of( "y,dummy1;d")),
         std::invalid_argument);
   } // end scope

   // constraint is not activated
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "d", DEST_VAR( dummy), "no name")
         ->addConstraint( nullptr), std::invalid_argument);
   } // end scope

   // constraint is not activated
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "d", DEST_VAR( dummy), "no name")
         ->addConstraint( celma::prog_args::requiresArg( "")),
         std::invalid_argument);

      BOOST_REQUIRE_THROW( ah.addArgument( "d", DEST_VAR( dummy), "no name")
         ->addConstraint( celma::prog_args::excludes( "")),
         std::invalid_argument);
   } // end scope

} // errors



/// Check the argument-constraint 'requiresArg'.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires_arg)
{

   std::string  name;
   int          idx;


   // constraint is not activated
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1"),
         std::runtime_error);
   } // end scope

   // constraint met, no error
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 5"));
   } // end scope

} // constraint_requires_arg



/// Check the argument-constraint 'requiresArg' with one argument that requires
/// two other arguments.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires_arg_two)
{

   std::string  name;
   int          idx;
   std::string  opt;


   // constraint is not activated
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1"),
         std::runtime_error);
   } // end scope

   // constraint error: third argument not used/set
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1 -i 5"),
         std::runtime_error);
   } // end scope

   // constraint met with character argument, no error
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 5 -o all"));
   } // end scope

   // constraint met with log argument, no error
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 5 --opt all"));
   } // end scope

   // constraint met with character argument, no error, different argument order
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -o all -i 5"));
   } // end scope

   // constraint met with log argument, no error, different argument order
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i;o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index");
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 --opt all -i 5"));
   } // end scope

} // constraint_requires_arg_two



/// Check the argument-constraint 'requiresArg' with an argument that requires a
/// second one, which in turn requires a third one.<br>
/// Logic-wise this is the same as the previous test case, but the runtime
/// implications are different.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_requires_arg_chaining)
{

   std::string  name;
   int          idx;
   std::string  opt;


   // constraint is not activated
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // constraint error: second argument not used/set
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1"),
         std::runtime_error);
   } // end scope

   // constraint error: third argument not used/set
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1 -i 5"),
         std::runtime_error);
   } // end scope

   // constraint met with character argument, no error
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 5 -o all"));
   } // end scope

   // constraint met with log argument, no error
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "i"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 5 --opt all"));
   } // end scope

} // constraint_requires_arg_chaining



/// Check the argument-constraint 'requiresArg' with two different arguments that
/// both require a third argument.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_required_twice)
{

   std::string  name;
   int          idx;
   std::string  opt;


   // constraint is not activated
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // constraint required once, first arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1"),
         std::runtime_error);
   } // end scope

   // constraint required once, second arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 56"),
         std::runtime_error);
   } // end scope

   // constraint required twice
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1 -i 56"),
         std::runtime_error);
   } // end scope

   // constraint required once, fulfilled, short arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -o 1"));
   } // end scope

   // constraint required once, fulfilled, short arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 56 -o 1"));
   } // end scope

   // constraint required twice, fulfilled, short arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 56 -o 1"));
   } // end scope

   // constraint required twice, fulfilled, long arg
   {
      Handler  ah( 0);

      ah.addArgument( "n",     DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "i",     DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::requiresArg( "o,opt"));
      ah.addArgument( "o,opt", DEST_VAR( opt),  "Optional");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n name1 -i 56 --opt=1"));
   } // end scope

} // constraint_required_twice



/// Check the argument-constraint 'excludes'.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_excludes)
{

   std::string  name;
   int          idx;


   // constraint is not activated
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // constraint not activated, use now not forbidden argument
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 5"));
   } // end scope

   // constraint error: try to use excluded argument
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n name1 -i 5"),
         std::runtime_error);
   } // end scope

   // constraint not activated yet ...
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 7 -n name1"));
   } // end scope

   // both arguments exclude each other
   {
      Handler  ah( 0);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addConstraint( celma::prog_args::excludes( "i"));
      ah.addArgument( "i", DEST_VAR( idx),  "Index")
         ->addConstraint( celma::prog_args::excludes( "n"));;

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 7 -n name1"),
         std::runtime_error);
   } // end scope

} // constraint_excludes



/// Check the constraint 'all of'.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_all_of)
{

   std::string  name;
   int          idx;
   int          rate;


   // invalid list of arguments: unknown argument
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r;a")),
         std::invalid_argument);
   } // end scope

   // invalid list of arguments: short/long mixed
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_THROW( ah.addConstraint(
                              celma::prog_args::all_of( "n;i,name;r")),
                           std::invalid_argument);
   } // end scope

   // none of the specified arguments used: constraint is not fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, ""), std::runtime_error);
   } // end scope

   // none of the specified arguments used, only another/not relevant:
   // constraint is not fulfilled
   {
      Handler  ah( 0);
      int      valueA;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value A");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-a 7"), std::runtime_error);
   } // end scope

   // one of the specified arguments used: constraint is not fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n myname"),
         std::runtime_error);
   } // end scope

   // not all of the specified arguments used: constraint is not fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 5 -r 17"),
         std::runtime_error);
   } // end scope

   // all of the specified arguments used: constraint is fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW(
         ah.addConstraint( celma::prog_args::all_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n myname -i 5 -r 17"));
   } // end scope

   // same but: specify mix of argument specs
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint(
         celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n myname -i 5 -r 17"));
   } // end scope

   // same but: use combination of short and long arguments
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      // specify mix of argument specs
      BOOST_REQUIRE_NO_THROW(
         ah.addConstraint( celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( ah, "--name myname -i 5 --rate 17"));
   } // end scope

   // same but: mixed in other arguments not relevant for the constraint
   {
      Handler  ah( 0);
      int      valueA;
      int      valueB;
      int      valueC;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "b",       DEST_VAR( valueB), "Value b");
      ah.addArgument( "c",       DEST_VAR( valueC), "Value c");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      // specify mix of argument specs
      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::all_of( "n;index;r,rate")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah,
         "-a 5 -b 7 -n myname -i 5 -c 5 -r 17"));
   } // end scope

} // constraint_all_of



/// Check the constraint 'any of'.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_any_of)
{

   std::string  name;
   int          idx;
   int          rate;


   // none of the arguments is used: constraint is fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // none of the arguments is used, only another/not relevant argument:
   // constraint is fulfilled
   {
      Handler  ah( 0);
      int      valueA;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-a 756"));
   } // end scope

   // one of the arguments is used: constraint is fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n myname"));
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n myname -i 7"),
         std::runtime_error);
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;index;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 7 -r 545"),
         std::runtime_error);
   } // end scope

   // try to use two of the specified arguments: constraint is violated
   {
      Handler  ah( 0);
      int      valueA;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "n;index;rate")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--rate 5 -a 77 -i 7"),
         std::runtime_error);
   } // end scope

} // constraint_any_of



/// Check the constraint 'one of'.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_one_of)
{

   std::string  name;
   int          idx;
   int          rate;


   // no argument used: constraint is not fulfilled
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name), "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),  "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate), "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, ""), std::runtime_error);
   } // end scope

   // no/another argument used: constraint is not fulfilled
   {
      Handler  ah( 0);
      int      valueA;

      ah.addArgument( "a",       DEST_VAR( valueA), "Value a");
      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-a 6"), std::runtime_error);
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n myname"));
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "name;i;rate")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--index 5"));
   } // end scope

   // use one of the arguments: constraint is met
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;index;r")));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 17"));
   } // end scope

   // try to use two of the arguments: constraint violated
   {
      Handler  ah( 0);

      ah.addArgument( "n,name",  DEST_VAR( name),   "Name");
      ah.addArgument( "i,index", DEST_VAR( idx),    "Index");
      ah.addArgument( "r,rate",  DEST_VAR( rate),   "Rate");

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "n;i;r")));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-n myname --index=8"),
         std::runtime_error);
   } // end scope

} // constraint_one_of



/// Try a mix of various constraints.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( constraint_mix)
{

   // -n mandatory, -i or -p required, -f when -p, -d or -w or -s one of optional
   class TestData
   {
   public:
      TestData():
         ah( 0),
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
            ->addConstraint( celma::prog_args::requiresArg( "f,format"));
         ah.addArgument( "f,format",  DEST_VAR( format_name), "Format");
         ah.addArgument( "d,display", DEST_VAR( display),     "Display");
         ah.addArgument( "w,write",   DEST_VAR( do_write),    "Write");
         ah.addArgument( "s,store",   DEST_VAR( do_store),    "Store");

         BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::one_of( "input;path")));
         BOOST_REQUIRE_NO_THROW( ah.addConstraint( celma::prog_args::any_of( "d;w;s")));

      } // TestData::TestData

      Handler      ah;
      std::string  name;
      std::string  input_name;
      std::string  path;
      std::string  format_name;
      bool         display;
      bool         do_write;
      bool         do_store;

   }; // TestData

   // mandatory argument not set
   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, ""), std::runtime_error);
   } // end scope

   // celma::prog_args::one_of requirement validated
   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "--name myname"),
         std::runtime_error);
   } // end scope

   // minimum set of arguments, okay
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( td.ah, "--name myname -i input_source"));
   } // end scope

   // minimum set of arguments, okay
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( td.ah, "--name myname --input=input_source"));
   } // end scope

   // both of mutually exlusive arguments set, contraint violated
   {
      TestData  td;

      BOOST_REQUIRE_THROW(
         evalArgumentString( td.ah,
            "--name myname --input input_source --path=my_path"),
         std::runtime_error);
   } // end scope

   // additional required argument missing
   {
      TestData  td;

      BOOST_REQUIRE_THROW(
         evalArgumentString( td.ah, "--name myname -p from_path"),
         std::runtime_error);
   } // end scope

   // all necessary arguments set
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( td.ah,
            "--name myname -p from_path --format=formatname"));
   } // end scope

   // all necessary arguments set plus one of the optional group
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( td.ah,
            "--name myname -p from_path --format=formatname -d"));
   } // end scope

   // all necessary arguments set plus one of the optional group
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW(
         evalArgumentString( td.ah,
            "--name myname -p from_path --format=formatname -w"));
   } // end scope

   // attempt to set two arguments from the optional group: constraint violated
   {
      TestData  td;

      BOOST_REQUIRE_THROW(
         evalArgumentString( td.ah,
            "--name myname -p from_path --format=formatname -w -s"),
         std::runtime_error);
   } // end scope

} // constraint_mix



// =====  END OF test_argh_constraints_c.cpp  =====

