
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::FirstPass.


#ifndef CELMA_COMMON_FIRST_PASS_HPP
#define CELMA_COMMON_FIRST_PASS_HPP


#include <iomanip>
#include <iostream>


namespace celma { namespace common {


/// Very simple and small class which implements a 'first pass' detector.<br>
/// Simply create an object of this class, and use the bool or ! operator to
/// check if it is the first time or not.
/// @since  0.2, 04.04.2016
class FirstPass
{
public:
   /// Constructor, initialises internal variables.
   /// @since  0.2, 04.04.2016
   FirstPass();

   /// Returns if this function is called for the first time, i.e. the very
   /// first time this function returns \c true, always \c false afterwards.
   /// @return  \c true if this was the first call of this function.
   /// @since  0.2, 04.04.2016
   operator bool();

   /// Returns if this function is called for at least the second time, i.e. the
   /// very first time this function returns \c false, always \c true afterwards.
   /// @return  \c true if this was at least the second call of this function.
   /// @since  0.2, 04.04.2016
   bool operator !();

   /// Writes the current value of the flag to the stream.
   /// @param[in,out]  os  The stream to write to.
   /// @param[in]      fp  The object to dump the value of the flag from.
   /// @return  The stream as passed in.
   /// @since  0.2, 04.04.2016
   friend std::ostream& operator <<( std::ostream& os, const FirstPass& fp);

   /// Resets the internal flag to \c true.
   /// @since  0.2, 04.04.2016
   void reset();

private:
   /// The internal flag, used to detect if the bool or ! operator are called
   /// for the first time or not.
   bool  mFirstPass;

}; // FirstPass


// inlined methods
// ===============


inline FirstPass::FirstPass():
   mFirstPass( true)
{
} // end FirstPass::FirstPass


inline FirstPass::operator bool()
{
   const bool  oldVal = mFirstPass;
   mFirstPass = false;
   return oldVal;
} // end FirstPass::operator bool


inline bool FirstPass::operator !()
{
   const bool  oldVal = !mFirstPass;
   mFirstPass = false;
   return oldVal;
} // end FirstPass::operator !


inline void FirstPass::reset()
{
   mFirstPass = true;
} // end FirstPass::reset


inline std::ostream& operator <<( std::ostream& os, const FirstPass& fp)
{
   return os << std::boolalpha << fp.mFirstPass;
} // end FirstPass::operator <<


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_FIRST_PASS_HPP


// =========================  END OF first_pass.hpp  =========================

