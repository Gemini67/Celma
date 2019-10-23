
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
/// See documentation of template classes celma::common::RelOpsFromLess<>,
/// celma::common::RelOpsFromCompare<>.


#ifndef CELMA_COMMON_COMPARABLE_HPP
#define CELMA_COMMON_COMPARABLE_HPP


namespace celma { namespace common {


/// Helper class that provides all relational comparison operators for a class
/// that only provides the less comparison operator.<br>
/// Use this class as base class of the class to extend (CRTP):<br>
///   <pre>class MyComparableClass: public RelOpsFromLess< MyComparableClass></pre><br>
/// If your class provides a compare method instead of a less-than operator, use
/// celma::common::RelOpsFromCompare<> instead.
///
/// @tparam  T  The type of the class to provide the relational operators for.
/// @since  1.31.0, 14.10.201
///    (moved here)
/// @since  1.11.0, 24.08.2018
template< typename T> class RelOpsFromLess
{
public:
   /// Less-equal comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less than or equal to \a other.
   /// @since  1.11.0, 24.08.2018
   bool operator <=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(other < self);
   } // RelOpsFromLess< T>::operator <=

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is equal to \a other.
   /// @since  1.11.0, 24.08.2018
   bool operator ==( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(self < other) && !(other < self);
   } // RelOpsFromLess< T>::operator ==

   /// Not-equal comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is not equal to \a other.
   /// @since  1.11.0, 24.08.2018
   bool operator !=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return (self < other) || (other < self);
   } // RelOpsFromLess< T>::operator !=

   /// Greater-equal comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater than or equal to \a other.
   /// @since  1.11.0, 24.08.2018
   bool operator >=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(self < other);
   } // RelOpsFromLess< T>::operator >=

   /// Greater-than comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater than the \a other object.
   /// @since  1.11.0, 24.08.2018
   bool operator >( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return other < self;
   } // RelOpsFromLess< T>::operator >

}; // RelOpsFromLess< T>


/// Template that provides all relational operators for classes that provide a
/// public compare() function in the form:
///    <pre>int compare( const <classname>& other) const;</pre><br>
/// Use this class as base class of the class to extend (CRTP):<br>
///   <pre>class MyComparableClass: public RelOpsFromCompare< MyComparableClass></pre><br>
/// If your class provides a less-than operator instead of a compare method, use
/// celma::common::RelOpsFromLess<> instead.
///
/// @tparam  T  The type of the class to provide relational operator for.
/// @since  1.31.0, 14.10.201
///    (moved here)
/// @since  1.22.0, 27.03.2019
template< typename T> class RelOpsFromCompare
{
public:
   /// Less-than operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less-than \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator <( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) < 0;
   } // RelOpsFromCompare< T>::operator <
 
   /// Less-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less-than or equal to \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator <=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) <= 0;
   } // RelOpsFromCompare< T>::operator <=
 
   /// Equality operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is equal to \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator ==( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) == 0;
   } // RelOpsFromCompare< T>::operator ==
 
   /// Greater-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater-than or equal to \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator >=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) >= 0;
   } // RelOpsFromCompare< T>::operator >=
 
   /// Greater operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is greater than \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator >( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) > 0;
   } // RelOpsFromCompare< T>::operator >
 
   /// Not-equal operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is different from \a other.
   /// @since  1.22.0, 27.03.2019
   bool operator !=( const T& other) const
   {
      const T&  self = static_cast< const T&>( *this);
      return self.compare( other) != 0;
   } // RelOpsFromCompare< T>::operator !=
 
}; // RelOpsFromCompare< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_COMPARABLE_HPP


// =====  END OF comparable.hpp  =====

