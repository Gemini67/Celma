
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
    Macro definitions for generating a reflection-like field access.<br>
    First you have to define the list of fields and their types that you want to
    be handled.<br>
    Example:
    <pre>
    \#define  ADDRESS_RECORD_FIELDS(FIELD) \
       FIELD( std::string, Name) \
       FIELD( std::string, FirstName) \
       FIELD( int,         PostalCode)
    </pre>
    Important is the structure of the definition, the names
    (here \c ADDRESS_RECORD_FIELDS and \c FIELD) you can choose yourself.<br>
    Afterwards, you call the REFLECT() macro with the name of the structure to
    create and your list definition. This will generate you
    - A structure with the specified name and the member variables as specified
      in the list.
    - A class named \c Reflected<structname> which will provide getter and
      setter methods to access the members of a structure object by name or by
      id.
*/


#ifndef CELMA_REFLECTION_REFLECTION_MACROS_HPP
#define CELMA_REFLECTION_REFLECTION_MACROS_HPP


#include "celma/reflection/detail/reflected_base.hpp"


/// One field == member variable of the 'normal' structure.
/// @param  t  The type of the field.
/// @param  n  The name of the field == variable.
#define  STRUCT_FIELD( t, n)  t  m ## n;


/// Creates the structure definition.
/// @param  n  The name of the structure to create.
/// @param  l  The list of fields/variables and their types.
#define STRUCT( n, l) \
   struct n \
   { \
      l(STRUCT_FIELD) \
   };


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


/// The main macro, the only one that should actually be used by the
/// application.
/// @param  n  The name of the structure to create.
/// @param  l  The list of fields/variables and their types.
#define REFLECT( n, l) \
   STRUCT( n, l) \
   REFLECTED( n, l)


// must NOT undefine the additional macros STRUCT_FIELD or CLASS_FIELD here
// otherwise macro expansion does not work


#endif   // CELMA_REFLECTION_REFLECTION_MACROS_HPP


// ======================  END OF reflection_macros.hpp  ======================
