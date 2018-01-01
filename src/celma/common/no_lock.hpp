
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
/// See documentation of class celma::common::NoLock.


#ifndef CELMA_COMMON_NO_LOCK_HPP
#define CELMA_COMMON_NO_LOCK_HPP


namespace celma { namespace common {


/// Provides a 'no lock' behaviour for places where a lock object is required
/// but no real locking is needed.
/// @since  x.y.z, 01.01.2018
class NoLock
{
public:
   /// Does nothing.
   /// @since  x.y.z, 01.01.2018
   inline void lock() const noexcept( true)
   {
   } // NoLock::lock

   /// Does nothing.
   /// @since  x.y.z, 01.01.2018
   inline void unlock() const noexcept( true)
   {
   } // NoLock::unlock

   /// Does more of nothing.
   /// @return  Always \c true.
   /// @since  x.y.z, 01.01.2018
   inline bool try_lock() const noexcept( true)
   {
      return true;
   } // NoLock::try_lock

}; // NoLock


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_NO_LOCK_HPP


// ===========================  END OF no_lock.hpp  ===========================

