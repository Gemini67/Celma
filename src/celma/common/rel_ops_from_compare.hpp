
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::RelOpsFromCompare.


#ifndef CELMA_COMMON_REL_OPS_FROM_COMPARE_HPP
#define CELMA_COMMON_REL_OPS_FROM_COMPARE_HPP


namespace celma { namespace common {


/// Template that provides all relational operators for classes that provide a
/// public compare() function in the form:
///    <pre>int compare( const <classname>& other) const;</pre><br>
/// Use this class as base class of the class to extend (CRTP):<br>
///   <pre>class MyComparableClass: public RelOpsFromCompare< MyComparableClass></pre><br>
/// If your class provides a less-than operator instead of a compare method, use
/// celma::common::RelOpsFromLess<> instead.
///
/// @tparpam  T  The type of the class to provide relational operator for.
/// @since  x.y.z, 27.03.2019
template< class T> class RelOpsFromCompare
{
public:
   /// Less-than operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less-than \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator <( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) < 0;
   } // RelOpsFromCompare< T>::operator <
 
   /// Less-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less-than or equal to \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator <=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) <= 0;
   } // RelOpsFromCompare< T>::operator <=
 
   /// Equality operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is equal to \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator ==( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) == 0;
   } // RelOpsFromCompare< T>::operator ==
 
   /// Greater-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater-than or equal to \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator >=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) >= 0;
   } // RelOpsFromCompare< T>::operator >=
 
   /// Greater operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater than \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator >( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) > 0;
   } // RelOpsFromCompare< T>::operator >
 
   /// Not-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is different from \a other.
   /// @since  x.y.z, 27.03.2019
   bool operator !=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) != 0;
   } // RelOpsFromCompare< T>::operator !=
 
}; // RelOpsFromCompare< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_REL_OPS_FROM_COMPARE_HPP


// =====  END OF rel_ops_from_compare.hpp  =====

