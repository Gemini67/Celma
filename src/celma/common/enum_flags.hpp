
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
/// See documentation of template class celma::common::EnumFlags.


#ifndef CELMA_COMMON_ENUM_FLAGS_HPP
#define CELMA_COMMON_ENUM_FLAGS_HPP


#include <initializer_list>
#include <iomanip>
#include <ostream>
#include <type_traits>


namespace celma { namespace common {


/// This class helps to solve the problems that can occur when a list of bit-
/// values are defined.<br>
/// For example, you can use an enum to define these values. Then you need to
/// define a special value for 0, or just remember to start with 1 for the first
/// enum value. Then you define each value as a left-shift by 1 of the previous
/// value. So, if you insert a value, you have to make sure that the following
/// value uses the new value for initialisation etc.<br>
/// You get more problems if you want to define your enum as a scoped enum, i.e.
/// an enum class. Unlike C (or plain) enums, a value from a scoped enum cannot
/// be easily converted into an integer value.<br>
/// So, just define your enum, the first value may be 0, and then just use this
/// template to handle the sets of bit-values from your enum.<br>
/// You can use variables of this class just like a set of bits/flags
/// afterwards, assign enum values or compare against them as if the enum would
/// be defined with bit-shifting.<br>
/// Main difference when using this class instead of a simple \c int: Don't
/// assign logically-or'ed values, but a list of values instead.<br>
/// But, on the other hand, it is possible to build an enum set by or-ing
/// multiple enum values. All it takes is that the or-operator (template)
/// provided at the end of this module must be defined in the same namespace
/// as the enum it should work on. In other words: Add the corresponding using
/// clause.
///
/// @tparam  E  The enum whose values should be treated like bit-flags.
/// @tparam  T  The underlying integer type used to represent the set values.
/// @since 0.8, 11.11.2016
template< typename E, typename T = typename std::underlying_type< E>::type>
   class EnumFlags
{
public:
   // constructors
   // ------------

   /// Default constructor, no flag set.
   ///
   /// @since 0.8, 11.11.2016
   EnumFlags() noexcept;

   /// Constructor with a single bit/flag to set.<br>
   /// Not 'explicit' on purpose to allow e.g. passing enum values to a function
   /// that expects an EnumFlags parameter.
   ///
   /// @param[in]  start_value  The bit/flag to set.
   /// @since 0.8, 11.11.2016
   // cppcheck-suppress noExplicitConstructor
   EnumFlags( E start_value) noexcept;

   /// Constructor with an initializer list of enum values, i.e. multiple bits/
   /// flags to set.
   /// @param[in]  start_set  The list of bits/flags to set.
   /// @since 0.8, 11.11.2016
   explicit EnumFlags( std::initializer_list< E> start_set) noexcept;

   /// Use default copy constructor.
   EnumFlags( const EnumFlags&) = default;
   /// Allow move constructor (actually copies).
   EnumFlags( EnumFlags&&) = default;
   /// Use default destructor.
   ~EnumFlags() = default;

   // assignment
   // ----------

   /// Assign a single bit/flag.
   /// @param[in]  value  The single bit/flag to set.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator =( E value) noexcept;

   /// Assign a list of enum values.
   /// @param[in]  enum_set  The list of enum values to set.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator =( std::initializer_list< E> enum_set) noexcept;

   /// Use default copy-assignment operator
   EnumFlags& operator =( const EnumFlags&) = default;

   // comnparison
   // -----------

   /// Compares against a single bit/flag.
   /// @param[in]  value  The single enum value to compare against.
   /// @return  \c true if only this bit/flag is set.
   /// @since  0.8, 13.11.2016
   bool operator ==( E value) const noexcept;

   /// Compares against a list of bits/flags.
   /// @param[in]  enum_set  The list of values to compare against.
   /// @return  \c true if exactly the specified bits/flags are set.
   /// @since  0.8, 13.11.2016
   bool operator ==( std::initializer_list< E> enum_set) const noexcept;

   /// Compares against the set of another object.
   /// @param[in]  enum_flags  The other object to compare against.
   /// @return  \c true if the two objects have exactly the same bits/flags set.
   /// @since  0.8, 13.11.2016
   bool operator ==( const EnumFlags& enum_flags) const noexcept;

   /// Compares against a single bit/flag.
   /// @param[in]  value  The single enum value to compare against.
   /// @return  \c true if more/other bits/flags are set.
   /// @since  0.8, 13.11.2016
   bool operator !=( E value) const noexcept;

   /// Compares against a list of bits/flags.
   /// @param[in]  enum_set  The list of values to compare against.
   /// @return  \c true if at least one other bit/flag is set.
   /// @since  0.8, 13.11.2016
   bool operator !=( std::initializer_list< E> enum_set) const noexcept;

   /// Compares against the set of another object.
   /// @param[in]  enum_flags  The other object to compare against.
   /// @return  \c true if the two objects differ in at least one bit/flag.
   /// @since  0.8, 13.11.2016
   bool operator !=( const EnumFlags& enum_flags) const noexcept;

   bool operator !=( const T& value) const noexcept;

   // set construction operators
   // --------------------------

   /// Returns a new EnumFlags object with all the bits of this object plus the
   /// given bit/flag set.
   ///
   /// @param[in]  or_value  The additional enum value/flag to set.
   /// @return  New object with all bits set as described.
   /// @since  1.8.0, 26.07.2018
   EnumFlags operator |( E or_value) noexcept;

   // modifiers
   // ---------

   /// Also set the specified bit/value (logically or).
   /// @param[in]  or_value  The additional bit/value to set.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator |=( E or_value) noexcept;

   /// Also set the specified list of bits/values (logically or).
   /// @param[in]  enum_set  The additional bits/values to set.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator |=( std::initializer_list< E> enum_set) noexcept;

   /// Also set the flags from the other object (logically or).
   /// @param[in]  enum_flags  The other object whose flags should be set too.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator |=( const EnumFlags& enum_flags) noexcept;

   /// Logical and with a single flag/bit.
   /// @param[in]  and_value  The bit/flag to logically and with.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator &=( E and_value) noexcept;

   /// Logical and with a list of flags/bits.
   /// @param[in]  enum_set  The bits/flags to logically and with.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator &=( std::initializer_list< E> enum_set) noexcept;

   /// Logical and with the flags/bits from another object.
   /// @param[in]  enum_flags  The other object to logically and the flags/bits
   ///                         with.
   /// @return  Self.
   /// @since 0.8, 11.11.2016
   EnumFlags& operator &=( const EnumFlags& enum_flags) noexcept;

   /// Logical exclusive-or with a single flag/bit.
   /// @param[in]  exclusive_or_value  The bit/flag to logically exclusive-or
   ///                                 with.
   /// @return  Self.
   /// @since 0.8, 13.11.2016
   EnumFlags& operator ^=( E exclusive_or_value) noexcept;

   /// Logical exclusive-or with a list of flags/bits.
   /// @param[in]  enum_set  The bits/flags to logically exclusive-or with.
   /// @return  Self.
   /// @since 0.8, 13.11.2016
   EnumFlags& operator ^=( std::initializer_list< E> enum_set) noexcept;

   /// Logical exclusive-or with the flags/bits from another object.
   /// @param[in]  enum_flags  The other object to logically exclusive-or the
   ///                         flags/bits with.
   /// @return  Self.
   /// @since 0.8, 13.11.2016
   EnumFlags& operator ^=( const EnumFlags& enum_flags) noexcept;

   /// Clears all the bits/flags.
   /// @since  0.8, 13.11.2016
   void reset() noexcept;

   /// Clears the specified bit/flag, if it is set.
   /// @param[in]  clear_value  The bit/flag to clear.
   /// @since  0.8, 14.11.2016
   void clear( E clear_value) noexcept;

   /// Clears all the bits/flags from the list which are set.
   /// @param[in]  clear_set  The list of bits/flags to clear.
   /// @since  0.8, 14.11.2016
   void clear( std::initializer_list< E> clear_set) noexcept;

   /// Clears all the bits/flags that are set in the other object.
   /// @param[in]  clear_flags  The other object which contains the bits/flags
   ///                          to clear.
   /// @since  0.8, 14.11.2016
   void clear( const EnumFlags& clear_flags) noexcept;

   // checks
   // ------

   /// Returns if a specific bit/flag is set.
   /// @param[in]  and_value  The single bit/flag to check if it is set.
   /// @return  \c true if the specified bit/flag is set.
   /// @since  0.8, 11.11.2016
   bool operator &( E and_value) const noexcept;

   /// Insertion operator for EnumFlags.<br>
   /// Prints a string in the form '<set-hex-value> = <enum-name1> (enum-value), ...<br>
   /// Requires an insertion operator on the enum that prints the name.
   /// @param[in]  os  The stream to print to.
   /// @param[in]  ef  The object to dump the bit-set of.
   /// @return  The stream as passed in.
   /// @since  0.8, 14.11.2016
   friend std::ostream& operator <<( std::ostream& os, const EnumFlags& ef) noexcept
   {
      bool  first = true;
      os << "0x" << std::hex << ef.mSetValue << std::dec;
      for (T bit = 0; bit < static_cast< T>( sizeof( T)) * 8; ++bit)
      {
         if (ef.mSetValue & bitval( static_cast< E>( bit)))
         {
            if (first)
            {
               os << " = ";
               first = false;
            } else
            {
               os << ", ";
            } // end if

            os << static_cast< E>( bit) << " (" << bit << ")";
         } // end if
      } // end for
      return os;
   } // operator <<

private:
   /// Computes the bit-mask value for an enum value.
   /// @param[in]  enum_value  The enum value to compute the bit-mask for.
   /// @return  The bit-mask of the enum value.
   /// @since  0.8, 11.11.2016
   static T bitval( E enum_value) noexcept
   {
      return 0x01 << static_cast< T>( enum_value);
   } // EnumFlags< E, T>::bitval

   /// The set of flags.
   T  mSetValue;

}; // EnumFlags< E, T>


// inlined methods
// ===============


template< typename E, typename T> EnumFlags< E, T>::EnumFlags() noexcept:
   mSetValue( 0)
{
} // EnumFlags< E, T>::EnumFlags


template< typename E, typename T>
   EnumFlags< E, T>::EnumFlags( E start_value) noexcept:
      mSetValue( bitval( start_value))
{
} // EnumFlags< E, T>::EnumFlags


template< typename E, typename T>
   EnumFlags< E, T>::EnumFlags( std::initializer_list< E> start_set) noexcept:
      mSetValue( 0)
{
   for (auto flag : start_set)
      mSetValue |= bitval( flag);
} // EnumFlags< E, T>::EnumFlags


template< typename E, typename T>
   EnumFlags< E, T>& EnumFlags< E, T>::operator =( E value) noexcept
{
   mSetValue = bitval( value);
   return *this;
} // EnumFlags< E, T>::operator =


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator =( std::initializer_list< E> enum_set) noexcept
{
   mSetValue = 0;
   for (auto flag : enum_set)
      mSetValue |= bitval( flag);
   return *this;
} // EnumFlags< E, T>::operator =


template< typename E, typename T>
   bool EnumFlags< E, T>::operator ==( E value) const noexcept
{
   return mSetValue == bitval( value);
} // EnumFlags< E, T>::operator ==


template< typename E, typename T>
   bool EnumFlags< E, T>::operator ==( std::initializer_list< E> enum_set)
                                     const noexcept
{
   return *this == EnumFlags( enum_set);
} // EnumFlags< E, T>::operator ==


template< typename E, typename T>
   bool EnumFlags< E, T>::operator ==( const EnumFlags& enum_flags)
                                     const noexcept
{
   return mSetValue == enum_flags.mSetValue;
} // EnumFlags< E, T>::operator ==


template< typename E, typename T>
   bool EnumFlags< E, T>::operator !=( E value) const noexcept
{
   return mSetValue != bitval( value);
} // EnumFlags< E, T>::operator !=


template< typename E, typename T>
   bool EnumFlags< E, T>::operator !=( std::initializer_list< E> enum_set)
                                     const noexcept
{
   return *this != EnumFlags( enum_set);
} // EnumFlags< E, T>::operator !=


template< typename E, typename T>
   bool EnumFlags< E, T>::operator !=( const EnumFlags& enum_flags)
                                     const noexcept
{
   return mSetValue != enum_flags.mSetValue;
} // EnumFlags< E, T>::operator !=


template< typename E, typename T>
   bool EnumFlags< E, T>::operator !=( const T& value) const noexcept
{
   return mSetValue != value;
} // EnumFlags< E, T>::operator !=


template< typename E, typename T>
   EnumFlags< E, T> EnumFlags< E, T>::operator |( E or_value) noexcept
{
   auto  copy( *this);
   copy |= or_value;
   return copy;
} // EnumFlags< E, T>::operator |


template< typename E, typename T>
   EnumFlags< E, T>& EnumFlags< E, T>::operator |=( E or_value) noexcept
{
   mSetValue |= bitval( or_value);
   return *this;
} // EnumFlags< E, T>::operator |=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator |=( std::initializer_list< E> enum_set) noexcept
{
   for (auto flag : enum_set)
      mSetValue |= bitval( flag);
   return *this;
} // EnumFlags< E, T>::operator |=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator |=( const EnumFlags& enum_flags) noexcept
{
   mSetValue |= enum_flags.mSetValue;
   return *this;
} // EnumFlags< E, T>::operator |=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator &=( E and_value) noexcept
{
   mSetValue &= bitval( and_value);
   return *this;
} // EnumFlags< E, T>::operator &=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator &=( std::initializer_list< E> enum_set) noexcept
{
   return *this &= EnumFlags( enum_set);
} // EnumFlags< E, T>::operator &=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator &=( const EnumFlags& enum_flags) noexcept
{
   mSetValue &= enum_flags.mSetValue;
   return *this;
} // EnumFlags< E, T>::operator &=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator ^=( E and_value) noexcept
{
   mSetValue ^= bitval( and_value);
   return *this;
} // EnumFlags< E, T>::operator ^=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator ^=( std::initializer_list< E> enum_set) noexcept
{
   return *this ^= EnumFlags( enum_set);
} // EnumFlags< E, T>::operator ^=


template< typename E, typename T>
   EnumFlags< E, T>&
      EnumFlags< E, T>::operator ^=( const EnumFlags& enum_flags) noexcept
{
   mSetValue ^= enum_flags.mSetValue;
   return *this;
} // EnumFlags< E, T>::operator ^=


template< typename E, typename T>
   void EnumFlags< E, T>::clear( E clear_value) noexcept
{
   const T  clear_bit = bitval( clear_value);
   if (mSetValue & clear_bit)
      mSetValue -= clear_bit;
} // EnumFlags< E, T>::clear


template< typename E, typename T>
   void EnumFlags< E, T>::clear( std::initializer_list< E> clear_set) noexcept
{
   for (auto flag : clear_set)
   {
      const T  clear_bit = bitval( flag);
      if (mSetValue & clear_bit)
         mSetValue -= clear_bit;
   } // end for
} // EnumFlags< E, T>::clear


template< typename E, typename T>
   void EnumFlags< E, T>::clear( const EnumFlags& clear_flags) noexcept
{
   mSetValue &= ~clear_flags.mSetValue;
} // EnumFlags< E, T>::clear


template< typename E, typename T> void EnumFlags< E, T>::reset() noexcept
{
   mSetValue = 0;
   return *this;
} // EnumFlags< E, T>::reset


template< typename E, typename T>
   bool EnumFlags< E, T>::operator &( E and_value) const noexcept
{
   return (mSetValue & bitval( and_value)) != 0;
} // EnumFlags< E, T>::operator &


/// Helper function to logically or two enum values as enum flags.<br>
/// Defined in celma namespace, add a using clause to your module if needed.
///
/// @param[in]  lhs
///    The first enum value to store.
/// @param[in]  rhs
///    The second enum value to store.
/// @return
///    An EnumFlags object where the two flags are set.
/// @since
///    1.8.0, 26.07.2018
template< typename E, typename T = typename std::underlying_type< E>::type>
   EnumFlags< E, T> operator |( E lhs, E rhs)
{
   EnumFlags< E, T>  ef( lhs);
   ef |= rhs;
   return ef;
} // operator |


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_ENUM_FLAGS_HPP


// =====  END OF enum_flags.hpp  =====

