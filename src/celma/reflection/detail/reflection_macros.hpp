
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/** @file
    Internal macro definitions for generating a reflection-like field access.
*/


#ifndef CELMA_REFLECTION_DETAIL_REFLECTION_MACROS_HPP
#define CELMA_REFLECTION_DETAIL_REFLECTION_MACROS_HPP


#include <iosfwd>
#include "celma/reflection/detail/reflected_base.hpp"


/// One field == member variable of the 'normal' structure.
/// @param  t  The type of the field.
/// @param  n  The name of the field == variable.
#define  STRUCT_FIELD( t, n)  t  m ## n;


/// Print the name and the value of one field of the structure.
/// @param  t  The type of the field, not used here.
/// @param  n  The name of the field == variable.
#define  PRINT_STRUCT_FIELD( t, n)  os << #n " = " << record.m ## n << '\n';


/// Creates the structure definition and the insertion operator to print the
/// contents of an object.
/// @param  n  The name of the structure to create.
/// @param  l  The list of fields/variables and their types.
#define STRUCT( n, l) \
   struct n \
   { \
      l(STRUCT_FIELD) \
   }; \
   std::ostream& operator <<( std::ostream& os, const n& record) \
   { \
      l(PRINT_STRUCT_FIELD) \
      return os; \
   }
   

/// Creates setter and getter methods for one field == member variable in
/// 'normal' structure.
/// @param  t  The type of the field.
/// @param  n  The name of the field == variable.
#define  CLASS_FIELD( t, n)  \
   void set ## n( const t& new ## n) \
   { \
      mDestination.m ## n = new ## n; \
   } \
   const t& get ## n() const \
   { \
      return mDestination.m ## n; \
   }


/// Creates the function call to add a field to the id/name containers.
/// @param  t  The type of the field.
/// @param  n  The name of the field == variable.
#define  ADD_MEMBER( t, n) \
   addField( #n , mDestination.m ## n);


/// Creates the class that provides reflection-like access to the variables in
/// the 'normal' structure.
/// @param  n  The name of the class to create.
/// @param  l  The list of fields/variables and their types.
#define REFLECTED( n, l) \
   class Reflected ## n : public celma::reflection::detail::ReflectedBase \
   { \
   public: \
      Reflected ## n( n& dest): \
         ReflectedBase(), \
         mDestination( dest) \
      { \
         l(ADD_MEMBER)\
      } \
      l(CLASS_FIELD) \
      const n& data() const noexcept( false) \
      { \
         return mDestination; \
      } \
      n& data() noexcept( false) \
      { \
         return mDestination; \
      } \
   private: \
      n&  mDestination; \
   }


#endif   // CELMA_REFLECTION_DETAIL_REFLECTION_MACROS_HPP


// ======================  END OF reflection_macros.hpp  ======================
