
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// This file containsd a collection of classes that can be used to handle
/// arbitrary values types in STL containers etc.<br>
/// All classes take the (final) base class as parameter, allowing to build a
/// class hierarchy based on the application base class.<br>
/// The following classes are defined here:
/// - TypeNameBase<br>
///   The base class for all other classes. Is not dependent on the value type,
///   so it is possible to easily cast the class pointer to this type and then
///   access the type string of the value type.
/// - TypeName<br>
///   Stores the name of a type.
/// - Reference<br>
///   Stores a reference to a variable.
/// - Value<br>
///   Provides a variable of the specified type.
/// - VarName
///   Stores a reference to a variable, plus stores the name of the variable.


#ifndef CELMA_COMMON_ANY_TYPE_BASE_HPP
#define CELMA_COMMON_ANY_TYPE_BASE_HPP


#include <string>
#include "celma/common/type_name.hpp"


namespace celma { namespace common {


// forward declaration
template< typename B> class TypeNameBase;


// AnyBase
// =======


/// If no special base class with virtual methods, members or anything the like
/// is needed, this base class can be used as the (final) base for this class
/// hierarchy.
/// @since  0.14.0, 18.02.2017
class AnyBase
{
public:
   ~AnyBase() = default;

   const TypeNameBase< AnyBase>* getTypeNameBase() const;

private:
   friend class TypeNameBase< AnyBase>;

   /// Private constructor to make sure that objects of this class can only be
   /// created from TypeNameBase.
   AnyBase() = default;

}; // AnyBase


// TypeNameBase
// ============


/// Base class for all, needs only the base class as template parameter, so the
/// methods of this class can be accessed even while the value type is unknown.
/// @tparam  B  The type of the base class.
/// @since  0.13.3, 15.02.2017
template< typename B> class TypeNameBase: public B
{
public:
   ~TypeNameBase() = default;

   /// Returns the stored type name.
   /// @return  The type name stored internally.
   /// @since  0.13.3, 15.02.2017
   const std::string& getTypeName() const
   {
      return mTypeName;
   } // TypeNameBase< B>::getTypeName

protected:
   /// Constructor, stores the specified type name.
   /// @param[in]  type_name  The type name to store.
   /// @since  0.13.3, 15.02.2017
   TypeNameBase( const std::string& type_name):
      mTypeName( type_name)
   {
   } // TypeNameBase< B>::TypeNameBase

private:
   /// The type name.
   const std::string  mTypeName;

}; // TypeNameBase< B>


// TypeName
// ========


/// Basically the same as TypeNameBase, but takes the type to store the name of
/// as template parameter.
/// @tparam  T  The type to store the name of.
/// @tparam  B  The type of the base class.
/// @since  0.13.3, 13.02.2017
template< typename T, typename B> class TypeName: public TypeNameBase< B>
{
public:
   ~TypeName() = default;

protected:
   /// Constructor.
   /// @since  0.13.3, 13.02.2017
   TypeName():
      TypeNameBase< B>( type< T>::name())
   {
   } // TypeName< T, B>::TypeName

}; // TypeName< T, B>


// Reference
// =========


/// Based on class TypeName, but also stores the reference of a variable of the
/// specified type.
/// @tparam  T  The type of the variable to store the reference (and type name)
///             of.
/// @tparam  B  The type of the base class.
/// @since  0.13.3, 13.02.2017
template< typename T, typename B> class Reference: public TypeName< T, B>
{
public:
   /// Constructor.
   /// @param[in]  dest  The variable to store the reference to.
   /// @since  0.13.3, 13.02.2017
   Reference( T& dest):
      TypeName< T, B>(),
      mDestination( dest)
   {
   } // Reference< T, B>::Reference

   ~Reference() = default;

protected:
   /// Reference of the specified variable.
   T&  mDestination;
  
}; // Reference< T, B>


// Value
// =====


/// Also based on TypeName, but also contains an internal variable of the
/// specified type.
/// @tparam  T  The type of the variable to create internally.
/// @tparam  B  The type of the base class.
/// @since  0.13.3, 13.02.2017
template< typename T, typename B> class Value: public TypeName< T, B>
{
public:
   /// Constructor.
   /// @param[in]  init_val  Initial value to set on the internal variable.
   /// @since  0.13.3, 13.02.2017
   Value( const T& init_val = T()):
      TypeName< T, B>(),
      mValue( init_val)
   {
   } // Value< T, B>::Value

   ~Value() = default;

protected:
   /// Internal variable of the specified type.
   T  mValue;
  
}; // Value< T, B>


// VarName
// =======


/// As Reference, stores the reference to a variable, but plus the name of the
/// variable.
/// @tparam  T  The type of the variable.
/// @tparam  B  The type of the base class.
/// @since  0.13.3, 13.02.2017
template< typename T, typename B> class VarName: public Reference< T, B>
{
public:
   /// Constructor.
   /// @param[in]  dest      The variable to store the reference to.
   /// @param[in]  var_name  The name of the original variable.
   /// @since  0.13.3, 13.02.2017
   VarName( T& dest, const std::string& var_name):
      Reference< T, B>( dest),
      mVarName( var_name)
   {
   } // VarName< T, B>::VarName

   ~VarName() = default;

   /// Returns the name of the original variable.
   /// @return  The name of the original variable as specified in the
   ///          constructor.
   /// @since  0.13.3, 16.02.2017
   const std::string& getVarName() const
   {
      return mVarName;
   } // 
   
protected:
   /// The name of the original variable.
   const std::string  mVarName;
  
}; // VarName< T, B>


#define VAR_NAME( n)  n, #n


inline const TypeNameBase< AnyBase>* AnyBase::getTypeNameBase() const
{
   return static_cast< const TypeNameBase< AnyBase>*>( this);
} // AnyBase::getTypeNameBase


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_ANY_TYPE_BASE_HPP


// ========================  END OF any_type_base.hpp  ========================

