
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ICardinality.


#ifndef CELMA_PROG_ARGS_DETAIL_I_CARDINALITY_HPP
#define CELMA_PROG_ARGS_DETAIL_I_CARDINALITY_HPP


#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Base class for implementation of cardinality checks.<br>
/// Derived classes must implement both methods:
/// - gotValue() is called every time before assign() is called for the argument.
/// - check() is called after all arguments were evaluated, should check if e.g.
///   minimum requirements were met.
/// .
/// If a cardinality check fails, the method(s) should throw an exception.
/// @since  0.2, 10.04.2016
class ICardinality
{
public:
   /// Empty, virtual destructor.
   /// @since  0.2, 10.04.2016
   virtual ~ICardinality() = default;

   /// Called by the framework when the argument was detected in the command
   /// line (actually may be without a value).
   /// @since  0.2, 10.04.2016
   virtual void gotValue() = 0;

   /// Called by the framework at the end of the command line processing.
   /// @since  0.2, 10.04.2016
   virtual void check() = 0;

   /// Should return a text description of the cardinality.
   ///
   /// @return  String with the text description of the cardinality.
   /// @since  1.14.0, 02.10.2018
   virtual std::string cardinalityStr() const = 0;

protected:
   /// Constructor. Does not really need to be protected, but emphasizes the
   /// point that objects of this class can only be created through classes
   /// derived from it.
   /// @since  0.2, 10.04.2016
   ICardinality() = default;

   /// Counter for the number of calls/values.
   int  mNumValues = 0;

}; // ICardinality


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_CARDINALITY_HPP


// =====  END OF i_cardinality.hpp  =====

