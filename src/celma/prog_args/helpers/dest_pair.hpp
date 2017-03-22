
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
/// See documentation of class celma::prog_args::helpers::DestPair.


#ifndef CELMA_PROG_ARGS_HELPERS_DEST_PAIR_HPP
#define CELMA_PROG_ARGS_HELPERS_DEST_PAIR_HPP


namespace celma { namespace prog_args { namespace helpers {


/// Use for the case where one argument/command line value should result in
/// setting values on two variables.
/// @tparam  T1  The type of the destination variable/value to store the value
///              from the command line in.
/// @tparam  T2  The type of the second destination variable, where the
///              specified value is set when assign() is called.
/// @since  0.14.0, 05.03.2017
template< typename T1, typename T2> class DestPair
{
public:
   /// Constructor.
   /// @param[in]  var1      The first destination variable.
   /// @param[in]  var2      The second destination variable.
   /// @param[in]  v2_value  The value to assign to the second destination
   ///                       variable.
   /// @since  0.14.0, 05.03.2017
   DestPair( T1& var1, T2& var2, const T2& v2_value):
      mDestVar1( var1),
      mDestVar2( var2),
      mValue( v2_value)
   {
   } // DestPair< T1, T2>::DestPair

   /// Called when the argument was used, assigns the value from \a new_value
   /// and the specified value to the second variable.
   /// @param[in]  new_value  The value passed on the command line.
   /// @since  0.14.0, 05.03.2017
   void assign( const std::string& new_value)
   {
      mDestVar1 = boost::lexical_cast< T>( new_value);
      mDestVar2 = mValue;
   } // DestPair< T1, T2>::assign

private:
   /// The first destination variable to assign the value from the command line
   /// to.
   T1&       mDestVar1;
   /// The second destination variable, is assigned the specified value.
   T2&       mDestVar2;
   /// The value to assign to the second destination variable.
   const T2  mValue;

}; // DestPair< T1, T2>


} // namespace helpers
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_HELPERS_DEST_PAIR_HPP


// ==========================  END OF dest_pair.hpp  ==========================

