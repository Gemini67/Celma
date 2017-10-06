
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
/// See documentation of template class celma::common::Manipulator.


#ifndef CELMA_COMMON_MANIPULATOR_HPP
#define CELMA_COMMON_MANIPULATOR_HPP


namespace celma { namespace common {


/// Generic stream manipulator class. Stores the given value until the
/// corresponding insertion operator assigns it appropriately.<br>
/// Define the manipulator name and type you actually want with a using
/// clause.<br>
/// If you need two different manipulators in the same class/namespace with the
/// same value type, you can use the second template parameter, the \a TAG, to
/// disambiguate the two types.<br>
/// @tparam  T    The type of the value to store.
/// @tparam  TAG  Optional, additional tag value, may be used to disambiguate
///               multiple using's for the same type.
/// @since  x.y.z, 27.09.2017
template< typename T, int TAG = 0> class Manipulator
{
public:
   /// Constructor. Stores the given value.
   /// @param[in]  val  The value to store.
   /// @since  x.y.z, 27.09.2017
   explicit Manipulator( const T& val);

   // some defaulted or deleted methods
   Manipulator( const Manipulator&) = delete;
   Manipulator( Manipulator&&) = default;
   ~Manipulator() = default;
   Manipulator& operator =( const Manipulator&) = delete;

   /// Returns the stored value.
   /// @return  The value passed to the constructor.
   /// @since  x.y.z, 27.09.2017
   const T& value() const;

private:
   /// The value to store.
   const T  mValue;

}; // Manipulator< T, TAG>


// inlined methods
// ===============


template< typename T, int TAG> Manipulator< T, TAG>::Manipulator( const T& val):
   mValue( val)
{
} // Manipulator< T, TAG>::Manipulator


template< typename T, int TAG> const T& Manipulator< T, TAG>::value() const
{
   return mValue;
} // Manipulator< T, TAG>::value


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_MANIPULATOR_HPP


// =========================  END OF manipulator.hpp  =========================

