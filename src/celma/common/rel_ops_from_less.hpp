
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::RelOpsFromLess.


#ifndef CELMA_COMMON_REL_OPS_FROM_LESS_HPP
#define CELMA_COMMON_REL_OPS_FROM_LESS_HPP


namespace celma { namespace common {


/// Helper class that provides all relational comparison operators for a class
/// that only provides the less comparison operator.
///
/// @tparam  T  The type of the class to provide the relational operators for.
/// @since  1.11.0, 24.08.2018
template< typename T> class RelOpsFromLess
{
public:
   /// Less-equal comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this object is less than or equal to the \a other object.
   /// @since
   ///    1.11.0, 24.08.2018
   bool operator <=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(other < self);
   } // RelOpsFromLess< T>::operator <=

   /// Equality comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this object is equal to the \a other object.
   /// @since
   ///    1.11.0, 24.08.2018
   bool operator ==( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(self < other) && !(other < self);
   } // RelOpsFromLess< T>::operator ==

   /// Not-equal comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this object is not equal to the \a other object.
   /// @since
   ///    1.11.0, 24.08.2018
   bool operator !=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return (self < other) || (other < self);
   } // RelOpsFromLess< T>::operator !=

   /// Greater-equal comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this object is greater than or equal to the \a other object.
   /// @since
   ///    1.11.0, 24.08.2018
   bool operator >=( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return !(self < other);
   } // RelOpsFromLess< T>::operator >=

   /// Greater-than comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this object is greater than the \a other object.
   /// @since
   ///    1.11.0, 24.08.2018
   bool operator >( const T& other) const
   {
      auto  self = static_cast< const T&>( *this);
      return other < self;
   } // RelOpsFromLess< T>::operator >

}; // RelOpsFromLess< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_REL_OPS_FROM_LESS_HPP


// =====  END OF rel_ops_from_less.hpp  =====

