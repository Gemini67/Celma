
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
/// See documentation of class celma::common::ScopeExitExecute.


#pragma once


#include <functional>


namespace celma::common {


/// Helper class to execute some code when the scope is left.
///
/// @since  1.28.0, 18.06.2019
class ScopeExitExecute final
{
public:
   /// The type of the function to store/execute: No parameter(s), no return
   /// value.
   using executor = std::function< void( void)>;

   /// Constructor, stores the function/lambda to execute.
   ///
   /// @param[in]  func
   ///    Function/lambda to execute when the object goes out of scope.
   /// @since  1.28.0, 18.06.2019
   ScopeExitExecute( executor func);

   // Copy-/Move-construction not allowed.
   ScopeExitExecute( const ScopeExitExecute&) = delete;
   ScopeExitExecute( ScopeExitExecute&&) = delete;

   /// The destructor, executes the function that was passed to the constructor
   /// in an exception-safe way.
   ///
   /// @since  1.28.0, 18.06.2019
   ~ScopeExitExecute();

   // Copy-/Move-assignment not allowed.
   ScopeExitExecute& operator =( const ScopeExitExecute&) = delete;
   ScopeExitExecute& operator =( ScopeExitExecute&&) = delete;

private:
   /// The function/lambda/whatever to execute in the constructor.
   executor  mFunc;

}; // ScopeExitExecute


// inlined methods
// ===============


inline ScopeExitExecute::ScopeExitExecute( executor func):
   mFunc( func)
{
} // ScopeExitExecute::ScopeExitExecute


inline ScopeExitExecute::~ScopeExitExecute()
{

   try
   {
      mFunc();
   } catch (...)
   {
   } // end try

} // ScopeExitExecute::~ScopeExitExecute


} // namespace celma::common


// =====  END OF scope_exit_execute.hpp  =====

