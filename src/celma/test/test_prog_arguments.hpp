
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::test::TestProgArguments.


#pragma once


namespace celma::test {


/// Helper class to get access to the test program arguments.
///
/// @since  1.22.0, 02.04.2019
class TestProgArguments
{
public:
   /// Constructor. Internally stores the number of arguments and the pointer to
   /// the list of arguments.
   ///
   /// @since  1.22.0, 02.04.2019
   TestProgArguments()
   {
      mArgC  = boost::unit_test::framework::master_test_suite().argc;
      mpArgV = boost::unit_test::framework::master_test_suite().argv;
   } // TestProgArguments::TestProgArguments

   /// Returns the number of arguments.
   ///
   /// @return  Number of arguments passed to the test program.
   /// @since  1.22.0, 02.04.2019
   [[nodiscard]] int argC() const
   {
      return mArgC;
   } // TestProgArguments::argC

   /// Returns the pointer to the list of arguments.
   ///
   /// @return  Pointer to the list of argument strings.
   /// @since  1.22.0, 02.04.2019
   [[nodiscard]] char** argV() const
   {
      return mpArgV;
   } // TestProgArguments::argV

private:
   /// Number of arguments.
   int     mArgC;
   /// Pointer to the list of arguments.
   char**  mpArgV;

}; // TestProgArguments


} // namespace celma::test


// =====  END OF test_prog_arguments.hpp  =====

