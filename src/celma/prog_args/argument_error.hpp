
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::argument_error.


#pragma once


#include <stdexcept>
#include <string>


namespace celma::prog_args {



/// Project specific exception class used for errors when evaluating command
/// line arguments.
/// This class was introduced partly because SonarQube complains that
/// std::runtime_error is a generic exception and should not be used directly.
/// @since  x.y.z, 20.05.2021
class argument_error : public std::runtime_error
{
public:
   /// Constructor with a std::string.
   /// @param[in]  arg  Text for the exception.
   /// @since  x.y.z, 20.05.2021
   explicit argument_error( const std::string& arg) noexcept( true);

   /// Constructor with a C string.
   /// @param[in]  arg  Text for the exception.
   /// @since  x.y.z, 20.05.2021
   explicit argument_error( const char* arg) noexcept( true);

   // default copy- and move-construction is okay
   argument_error( const argument_error&) = default;
   argument_error( argument_error&&) = default;

   /// Default virtual destructor is fine.
   ~argument_error() noexcept( true) override = default;

   // default copy- and move-assignment is okay
   argument_error& operator =( const argument_error&) = default;
   argument_error& operator =( argument_error&&) = default;

}; // argument_error



} // namespace celma::prog_args


// =====  END OF argument_error.hpp  =====

