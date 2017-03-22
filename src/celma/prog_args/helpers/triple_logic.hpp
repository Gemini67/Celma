
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::helpers::TripleLogic.


#ifndef CELMA_PROG_ARGS_HELPERS_TRIPLE_LOGIC_HPP
#define CELMA_PROG_ARGS_HELPERS_TRIPLE_LOGIC_HPP


namespace celma { namespace prog_args { namespace helpers {


/// Use for handling arguments that support triple value logic:
/// - Argument not used, initial value remains unchanged.
/// - Argument used without value, the 'no value' value is set.
/// - Argument is used with value.
/// .
/// @tparam  T  The type of the destination variable/value to set.
/// @since  0.14.0, 23.02.2017  (moved to namespace helpers)
/// @since  0.13.2, 17.02.2017
template< typename T> class TripleLogic
{
public:
   /// Constructor.
   /// @param[in]  var       The variable to set the value on.
   /// @param[in]  no_value  The value to set if assign() is called without a
   ///                       value (i.e. empty string).
   /// @since  0.13.2, 17.02.2017
   TripleLogic( T& var, const T& no_value):
      mDestVar( var),
      mNoValue( no_value)
   {
   } // TripleLogic< T>::TripleLogic

   /// Called when the argument was used, assigns the value from \a new_value if
   /// it is a valid value, assigns #mNoValue otherwise.
   /// @param[in]  new_value  The value passed on the command line, may be an
   ///                        empty string (i.e. no value was set).
   /// @since  0.13.2, 17.02.2017
   void assign( const std::string& new_value)
   {
      if (new_value.empty())
         mDestVar = mNoValue;
      else
         mDestVar = boost::lexical_cast< T>( new_value);
   } // TripleLogic< T>::assign

private:
   /// The destination variable to assign the value to.
   T&       mDestVar;
   /// The value to assign if no value was specified on the command line.
   const T  mNoValue;

}; // TripleLogic< T>


} // namespace helpers
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_HELPERS_TRIPLE_LOGIC_HPP


// =========================  END OF triple_logic.hpp  =========================

