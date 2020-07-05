
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of binary trees by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestBinaryTreeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/container/binary_tree.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::container::BinaryTree;
using celma::prog_args::Handler;



/// Test error case that can occur with a binary tree.
///
/// @since  x.y.z, 30.06.2020
BOOST_AUTO_TEST_CASE( test_binary_tree_errors)
{

   // try to set invalid value mode
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but binary tree empty
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // try to add a formatter for a specific position
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->addFormatPos( 1, celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));

      auto const  as2a = make_arg_array( "-b this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // a binary tree cannot be sorted
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setSortData(), std::logic_error);
   } // end scope

} // test_binary_tree_errors



/// For completeness: Set value mode "required" again.
///
/// @since  x.y.z, 30.06.2020
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler           ah( 0);
   BinaryTree< int>  bt = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  x.y.z, 30.06.2020
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 6);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // first check with the default list separator
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-b 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 6);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

} // test_list_sep



/// Test that the cardinality is checked correctly.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( test_cardinality)
{

   Handler           ah( 0);
   BinaryTree< int>  bt = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
      ->setCardinality( celma::prog_args::cardinality_max( 3)));

   auto const  as2a = make_arg_array( "-b 4,5,6,7", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);
   BOOST_REQUIRE_EQUAL( bt.size(), 6);

   int  exp_val = 1;
   for (auto btree_iter : bt)
   {
      BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
      ++exp_val;
   } // end for

} // test_cardinality



/// Test feature to handle multiple, separate values.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 6);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-b 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 8);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, -1);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler           ah( Handler::hfEndValues);
      BinaryTree< int>  bt = { 1, 2, 3};
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 7);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 6);

      int  exp_val = 1;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // now the default values should be cleared
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-b 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 2);

      int  exp_val = 4;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-b 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 5);

      int  exp_val = 4;
      for (auto btree_iter : bt)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // set default values, make argument optional, binary tree should be empty
   // when argument is used with value(s)
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-b", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( bt.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the binary
/// tree.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                   ah( 0);
   BinaryTree< std::string>  bt;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-b monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( bt.size(), 3);

   int  idx = 0;
   for (auto btree_iter : bt)
   {
      if (idx == 0)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, "monday");
      } else if (idx == 1)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, "tuesday");
      } else if (idx == 2)
      {
         BOOST_REQUIRE_EQUAL( btree_iter, "wednesday");
      } else
      {
         BOOST_REQUIRE( idx < 3);
      } // end if
      ++idx;
   } // end for

} // format_values



/// Test feature that only unique values should be stored in the binary tree.
/// Setting the same value multiple times would simply override in the binary
/// tree.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values overwrite silently
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values"));

      auto const  as2a = make_arg_array( "-b 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 5);

      int  exp_val = 2;
      for (auto btree_iter : bt)
      {
         if (exp_val == 5)
            ++exp_val;

         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( exp_val, 8);
   } // end scope

   // mode "ignore unique data without errors" can be set, even when it does not
   // make much sense
   {
      Handler           ah( 0);
      BinaryTree< int>  bt;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-b 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( bt.size(), 5);

      int  exp_val = 2;
      for (auto btree_iter : bt)
      {
         if (exp_val == 5)
            ++exp_val;

         BOOST_REQUIRE_EQUAL( btree_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( exp_val, 8);
   } // end scope

   // duplicates should lead to an error, also when conflicting with pre-set
   // values
   {
      Handler           ah( 0);
      BinaryTree< int>  bt = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-b 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a binary tree.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream        std_out;
   std::ostringstream        std_err;
   Handler                   ah( std_out, std_err, Handler::hfListArgVar);
   BinaryTree< std::string>  bt;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( bt), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "--list-arg-vars "
      "-b MONDAY,tuesday,wEdNeSdAy --list-arg-vars", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'celma::container::BinaryTree<std::string>', destination container 'bt', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'celma::container::BinaryTree<std::string>', destination container 'bt', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



/// Test constraint "disjoint" with two binary trees.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( disjoint_binary_trees)
{

   using celma::prog_args::disjoint;

   {
      Handler           ah( 0);
      BinaryTree< int>  bt1;
      BinaryTree< int>  bt2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( bt1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( bt2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,2,3 -r 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // throw if the data in the binary trees is not disjoint
   {
      Handler           ah( 0);
      BinaryTree< int>  bt1;
      BinaryTree< int>  bt2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( bt1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( bt2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,2,3 -r 4,5,6,1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // disjoint_binary_trees



// =====  END OF test_argh_dest_binary_tree_c.cpp  =====

