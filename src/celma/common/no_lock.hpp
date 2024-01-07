
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::NoLock.


#pragma once


namespace celma::common {


/// Provides a 'no lock' behaviour for places where a lock object is required
/// but no real locking is needed.
/// @since  1.15.1, 01.01.2018
class NoLock
{
public:
   /// Does nothing.
   /// @since  1.15.1, 01.01.2018
   inline void lock() const noexcept( true)
   {
   } // NoLock::lock

   /// Does nothing.
   /// @since  1.15.1, 01.01.2018
   inline void unlock() const noexcept( true)
   {
   } // NoLock::unlock

   /// Does more of nothing.
   /// @return  Always \c true.
   /// @since  1.15.1, 01.01.2018
   inline bool try_lock() const noexcept( true)
   {
      return true;
   } // NoLock::try_lock

}; // NoLock


} // namespace celma::common


// =====  END OF no_lock.hpp  =====

