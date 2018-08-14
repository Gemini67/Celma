
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
/// See documentation of class celma::prog_args::LevelCounter.


#ifndef CELMA_PROG_ARGS_LEVEL_COUNTER_HPP
#define CELMA_PROG_ARGS_LEVEL_COUNTER_HPP


#include "celma/common/pre_postfix.hpp"


namespace celma { namespace prog_args {


/// Helper class for handling a "level counter", i.e. a command line argument
/// that is incremented every time the corresponding argument is used.
///
/// @since  1.10.0, 11.08.2018
class LevelCounter
{
public:
   /// Constructor.
   ///
   /// @param[in]  start_level  The initial value.
   /// @since  1.10.0, 11.08.2018
   explicit LevelCounter( int start_level = 0):
      mLevel( start_level)
   {
   } // LevelCounter::LevelCounter

   /// Allow default copy constructor and assignment.
   LevelCounter( const LevelCounter&) = default;
   LevelCounter& operator =( const LevelCounter&) = default;

   /// Returns the current value of the level counter.
   ///
   /// @return  The current value.
   /// @since  1.10.0, 11.08.2018
   int value() const
   {
      return mLevel;
   } // LevelCounter::value

   /// Prefix increment operator, increments the internal value.
   ///
   /// @return  This object with the new, incremented value.
   /// @since  1.10.0, 11.08.2018
   LevelCounter& operator ++( std::prefix)
   {
      ++mLevel;
      return *this;
   } // LevelCounter::operator ++

   /// Postfix increment operator, increments the internal value.
   ///
   /// @return  New level counter with the previous value.
   /// @since  1.10.0, 11.08.2018
   LevelCounter operator ++( std::postfix)
   {
      auto  copy( *this);
      ++mLevel;
      return copy;
   } // LevelCounter::operator ++

   /// Assignment operator, assigns a new value.
   ///
   /// @param[in]  new_level  The new level to assign.
   /// @return  This object with the new value.
   /// @since  1.10.0, 13.08.2018
   LevelCounter& operator =( int new_level)
   {
      mLevel = new_level;
      return *this;
   } // LevelCounter::operator =

   /// Less comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this object/level is less than the other.
   /// @since  1.10.0, 11.08.2018
   bool operator <( int other) const
   {
      return mLevel < other;
   } // LevelCounter::operator <

private:
   /// The value of the level counter.
   int  mLevel;

}; // LevelCounter


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_LEVEL_COUNTER_HPP


// =====  END OF level_counter.hpp  =====

