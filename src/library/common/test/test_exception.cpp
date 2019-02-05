
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
**    Test program for the functions of the module Exception.
**
--*/


// module to test header file include
#include "celma/common/celma_exception.hpp"


// C++ Standard Library includes
#include <iostream>
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ExceptionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/format/auto_sprintf.hpp"


namespace {


/// Throw a Celma runtime error.
///
/// @since  0.2, 07.04.2016
void throwRuntimeError()
{

   throw CELMA_RuntimeError( "my fault ;-)");
} // throwRuntimeError


/// Throw a Celma logic error.
///
/// @since  0.2, 07.04.2016
void throwLogicError()
{

   throw CELMA_LogicError( "your fault ;-)");
} // throwLogicError


/// Throw a logic error, use AutoSprintf to create the exception text.
///
/// @since  0.2, 07.04.2016
void throwLogicErrorPrintf()
{

   throw CELMA_LogicError(
      celma::format::AutoSprintf( "text with %d parameters in %d %s formats",
         3, 2, "different"));
} // throwLogicErrorPrintf


/// Catch an exception, re-throw it in another exception.
///
/// @since  0.2, 07.04.2016
void catchRethrow()
{

   try
   {
      throwRuntimeError();
   } catch (const celma::common::ExceptionBase& eb)
   {
      throw CELMA_LogicError( eb);
   } // end try

   throw CELMA_RuntimeError( "should not get here!");

} // catchRethrow


} // namespace



/// Check catching logic errors.
///
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_logic_error)
{

   try
   {
      throwLogicError();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::exception& e)
   {
      std::cout << "caught exception: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicError();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::logic_error& e)
   {
      std::cout << "caught logic error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicError();
      BOOST_FAIL( "exception not thrown");
   } catch (const celma::common::CelmaLogicError& e)
   {
      std::cout << "caught Celma logic error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // test_logic_error



/// Check catching runtime errors.
///
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_runtime_error)
{

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::exception& e)
   {
      std::cout << "caught exception: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::runtime_error& e)
   {
      std::cout << "caught runtime error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwRuntimeError();
      BOOST_FAIL( "exception not thrown");
   } catch (const celma::common::CelmaRuntimeError& e)
   {
      std::cout << "caught Celma runtime error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // test_runtime_error



/// Check catching errors with special formatted text.
///
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_logic_error_printf)
{

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::exception& e)
   {
      std::cout << "caught exception: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const std::logic_error& e)
   {
      std::cout << "caught logic error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

   try
   {
      throwLogicErrorPrintf();
      BOOST_FAIL( "exception not thrown");
   } catch (const celma::common::CelmaLogicError& e)
   {
      std::cout << "caught Celma logic error: << " << e.what() << std::endl;
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // test_logic_error_printf



/// Check catching errors that were re-thrown.
///
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_rethrow)
{

   try
   {
      catchRethrow();
      BOOST_FAIL( "exception not thrown");
   } catch (const celma::common::CelmaLogicError& e)
   {
      std::cout << "caught expected exception: << " << e.what() << std::endl;
   } catch (const celma::common::CelmaRuntimeError& e)
   {
      BOOST_FAIL( "caught runtime error, expected logic error");
   } catch (const std::exception& e)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } catch (...)
   {
      BOOST_FAIL( "caught exception with wrong type");
   } // end try

} // test_rethrow



// =====  END OF test_exception.cpp  =====

