
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
**    Test program for the functions of the module Exception.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ExceptionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/format/auto_sprintf.hpp"
#include "celma/common/celma_exception.hpp"


using namespace std;
using namespace celma;



/// Throw a Celma runtime error.
/// @since  0.2, 07.04.2016
static void throwRuntimeError()
{

   throw CELMA_RuntimeError( "my fault ;-)");
} // end throwRuntimeError



/// Throw a Celma logic error.
/// @since  0.2, 07.04.2016
static void throwLogicError()
{

   throw CELMA_LogicError( "your fault ;-)");
} // end throwLogicError



/// Throw a logic error, use AutoSprintf to create the exception text.
/// @since  0.2, 07.04.2016
static void throwLogicErrorPrintf()
{

   throw CELMA_LogicError( format::AutoSprintf( "text with %d parameters in %d %s formats",
                                                3, 2, "different"));
} // end throwLogicErrorPrintf



/// Catch an exception, re-throw it in another exception.
/// @since  0.2, 07.04.2016
static void catchRethrow()
{

   try
   {
      throwRuntimeError();
   } catch (const common::ExceptionBase& eb)
   {
      throw CELMA_LogicError( eb);
   } // end try

   throw CELMA_RuntimeError( "should not get here!");

} // end catchRethrow



/// Check catching logic errors.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_logic_error)
{

   try
   {
      throwLogicError();
      BOOST_FAIL( "exception not thrown");
   } catch (const exception& e)
   {
      cout << "caught exception: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicError();
     BOOST_FAIL( "exception not thrown");
   } catch (const logic_error& e)
   {
      cout << "caught logic error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicError();
      BOOST_FAIL( "exception not thrown");
   } catch (const common::CelmaLogicError& e)
   {
      cout << "caught Celma logic error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // end test_logic_error



/// Check catching runtime errors.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_runtime_error)
{

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const exception& e)
   {
      cout << "caught exception: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const runtime_error& e)
   {
      cout << "caught runtime error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const common::CelmaRuntimeError& e)
   {
      cout << "caught Celma runtime error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // end test_runtime_error



/// Check catching errors with special formatted text.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_logic_error_printf)
{

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const exception& e)
   {
      cout << "caught exception: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const logic_error& e)
   {
      cout << "caught logic error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const common::CelmaLogicError& e)
   {
      cout << "caught Celma logic error: << " << e.what() << endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // end test_logic_error_printf



/// Check catching errors that were re-thrown.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_rethrow)
{

   try
   {
      catchRethrow();
      BOOST_FAIL( "exception not thrown");
   } catch (const common::CelmaLogicError& e)
   {
      cout << "caught expected exception: << " << e.what() << endl;
   } catch (const common::CelmaRuntimeError& e)
   {
      BOOST_FAIL( "caught runtime error, expected logic error");
   } catch (const exception& e)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // end test_rethrow



// =========================  END OF test_exception.cpp  =========================

