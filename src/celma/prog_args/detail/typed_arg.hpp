
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArg<>.<br>
/// This file contains the base template plus all specialisations:
/// - TypedArg< bool>
/// - TypedArg< celma::common::CheckAssign< T>>
/// - TypedArg< celma::common::CheckAssign< bool>>
/// - TypedArg< LevelCounter>
/// - TypedArg< ContainerAdapter< T>><br>
///   This one is used for STL containers like std::set<>, std::vector<> etc.
/// - TypedArg< KeyValueContainerAdapter< K, V>>
/// - TypedArg< T[ N]>
/// - TypedArg< std::array< T, N>>
/// - TypedArg< std::tuple< T...>>
/// - TypedArg< std::bitset< T...>>
/// - TypedArg< std::vector< bool>>
/// - TypedArg< celma::container::DynamicBitset>
/// - TypedArg< celma::common::ValueFilter< T>>


#pragma once


#include <cstring>
#include <algorithm>
#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <boost/lexical_cast.hpp>
#include "celma/common/check_assign.hpp"
#include "celma/common/contains.hpp"
#include "celma/common/parse_filter_string.hpp"
#include "celma/common/string_util.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/common/type_name.hpp"
#include "celma/common/value_filter.hpp"
#include "celma/container/dynamic_bitset.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/container_adapter.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/container_adapter.hpp"
#include "celma/prog_args/detail/key_value_container_adapter.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"
#include "celma/prog_args/level_counter.hpp"


namespace celma::prog_args::detail {


// Template TypedArg
// =================


/// Helper class to store a destination variable with its native type.
///
/// @tparam  T  The type of the value.
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the value in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017 (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArg( T& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the type of the destination variable as string.
   ///
   /// @return  String with the type of the destination variable.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Checks that the value mode 'command' is only set for destination types
   /// "std::string".
   /// For all other value modes and types, the method of the base clase is
   /// called.
   ///
   /// @param[in]  vm  The value mode to set.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::invalid_argument if the value mode "command" should have been set
   ///    on another destination than string.
   /// @since  0.14.2, 12.05.2017
   TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Adds the value of the destination variable to the string.
   ///
   /// @param[out]  dest  The string to append the default value to.
   /// @since  0.2, 10.04.2016
   void defaultValue( std::string& dest) const override;

   /// Needed to evaulate constraints.
   ///
   /// @param[in]  arg
   ///    Pointer to the other argument with the value to compare against.
   /// @return
   ///    - Value less than zero if this value is less than the other value.
   ///    - 0 if the values are equal.
   ///    - Value greater than zero if the other value is greater.
   /// @since  1.34.1, 14.01.2020
   int compareValue( const TypedArgBase* arg) const override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   void assign( const std::string& value, bool inverted) override;

   /// Reference of the destination variable to store the value in.
   T&    mDestVar;
   /// Flag, set when the argument was found/the value is set.
   bool  mHasValueSet = false;

}; // TypedArg< T>


// inlined methods
// ===============


template< typename T>
   TypedArg< T>::TypedArg( T& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::required, true),
      mDestVar( dest)
{
} // TypedArg< T>::TypedArg


template< typename T> const std::string TypedArg< T>::varTypeName() const
{
   return type< T>::name();
} // TypedArg< T>::varTypeName


template< typename T> bool TypedArg< T>::hasValue() const
{
   return mHasValueSet;
} // TypedArg< T>::hasValue


template< typename T> void TypedArg< T>::printValue( std::ostream& os,
   bool print_type) const
{
   os << format::toString( mDestVar);
   if (print_type)
      os  << " [" << type< T>::name() << "]";
} // TypedArg< T>::printValue


template< typename T>
   TypedArgBase* TypedArg< T>::setValueMode( ValueMode vm) noexcept( false)
{
   if (vm == ValueMode::command)
   {
      if (::strcmp( type< T>::name(), "std::string") != 0)
         throw std::invalid_argument( std::string( "may not set value mode '") +
                                      valueMode2str( vm) + "' on variable '" +
                                      mVarName + "'");
      // cannot call method of base class (would throw), have to handle it myself
      mValueMode = vm;
      return this;
   } // end if

   return TypedArgBase::setValueMode( vm);
} // TypedArg< T>::setValueMode


template< typename T> void TypedArg< T>::defaultValue( std::string& dest) const
{
   dest.append( format::toString( mDestVar));
} // TypedArg< T>::defaultValue


template< typename T> int TypedArg< T>::compareValue( const TypedArgBase* arg) const
{
  auto  other = static_cast< const TypedArg< T>*>( arg);
  if (mDestVar < other->mDestVar)
     return -1;
  return (other->mDestVar < mDestVar) ? 1 : 0;
} // TypedArg< T>::compareValue


template< typename T> void TypedArg< T>::dump( std::ostream& os) const
{
   os << "value type '" << type< T>::name() << "', destination '"
      << mVarName << "', ";
   if (mHasValueSet)
      os << "value = " << format::toString( mDestVar) << "." << std::endl;
   else 
      os << "value not set." << std::endl;
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< T>::dump


template< typename T>
   void TypedArg< T>::assign( const std::string& value, bool)
{
   check( value);
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      mDestVar = boost::lexical_cast< T>( valCopy);
   } else
   {
      mDestVar = boost::lexical_cast< T>( value);
   } // end if
   mHasValueSet = true;
} // TypedArg< T>::assign


// Template TypedArg< bool>
// ========================


/// Specialisation of template TypedArg<> for boolean variables.
///
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// since  6.0, 18.09.2013
template<> class TypedArg< bool>: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the value in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArg( bool& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::none, false),
      mDestVar( dest),
      mValue2Set( !mDestVar)
   {
   } // TypedArg< bool>::TypedArg

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns "bool".
   /// @return  The string "bool".
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override
   {
      return "bool";
   } // TypedArg< bool>::varTypeName

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override
   {
      return mHasValueSet;
   } // TypedArg< bool>::hasValue

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   void printValue( std::ostream& os, bool print_type) const override
   {
      os << std::boolalpha << mDestVar;
      if (print_type)
         os << " [bool]";
   } // TypedArg< bool>::printValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   ///
   /// @return  Nothing, always throws.
   /// @throw  std::logic_error whenever called.
   /// @since  0.2, 10.04.2016
   TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< bool>::setIsMandatory

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override
   {
      os << "boolean flag, destination '" << mVarName << "', "
         << (mHasValueSet ? "set." : "not set.") << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< bool>::dump

   /// Stores the value in the destination variable.
   ///
   /// @param  Ignored.
   /// @since  0.2, 10.04.2016
   void assign( const std::string&, bool) override
   {
      mDestVar     = mValue2Set;
      mHasValueSet = true;
   } // TypedArg< bool>::assign

private:
   /// Reference of the destination variable to store the value in.
   bool&  mDestVar;
   /// Flag set when a value was assigned through an argument.
   bool   mHasValueSet = false;
   /// The value to set when assign is called.
   bool   mValue2Set;

}; // TypedArg< bool>


// Template TypedArg< common::CheckAssign< T>>
// ===========================================


/// Specialisation of TypedArg<> for values wrapped in CheckAssign<>.
///
/// @tparam  T  The native type of the value.
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg< common::CheckAssign< T>>:
   public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the value in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArg( common::CheckAssign< T>& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the name of the type of the variable handled by the CheckAssign<>
   /// object.
   ///
   /// @return  The name of the type of the destination variable.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   ///
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   void assign( const std::string& value, bool inverted) override;

   /// Reference of the destination variable to store the value in.
   common::CheckAssign< T>&  mDestVar;

}; // TypedArg< CheckAssign< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< common::CheckAssign< T>>::TypedArg( common::CheckAssign< T>& dest,
                                                 const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
{
} // TypedArg< common::CheckAssign< T>>::TypedArg


template< typename T>
   const std::string TypedArg< common::CheckAssign< T>>::varTypeName() const
{
   return type< T>::name();
} // TypedArg< common::CheckAssign< T>>::varTypeName


template< typename T> bool TypedArg< common::CheckAssign< T>>::hasValue() const
{
   return mDestVar.hasValue();
} // TypedArg< common::CheckAssign< T>>::hasValue


template< typename T>
   void TypedArg< common::CheckAssign< T>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( static_cast< T>( mDestVar));
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< common::CheckAssign< T>>::printValue


template< typename T> void TypedArg< common::CheckAssign< T>>::dump( std::ostream& os) const
{
   os << "value type '" << type< T>::name()
      << "', destination 'CheckAssign< " << mVarName << ">', value ";
   if (mDestVar.hasValue())
      os << "= " << static_cast< T>( mDestVar) << "." << std::endl;
   else
      os << "not set." << std::endl;
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< common::CheckAssign< T>>::dump


template< typename T>
   void TypedArg< common::CheckAssign< T>>::assign( const std::string& value,
      bool)
{
   check( value);
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      mDestVar = boost::lexical_cast< T>( valCopy);
   } else
   {
      mDestVar = boost::lexical_cast< T>( value);
   } // end if
} // TypedArg< CheckAssign< T>>::assign


// Template TypedArg< common::CheckAssign< bool>>
// ==============================================


/// Specialization of the TypedArg< CheckAssign< T>> template for boolean flags.
///
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// @since  0.2, 10.04.2016
template<> class TypedArg< common::CheckAssign< bool>>: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the value in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArg( common::CheckAssign< bool>& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::none, false),
      mDestVar( dest)
   {
   } // TypedArg< common::CheckAssign< bool>>::TypedArg

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Always returns "bool".
   /// @return  The string "bool".
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override
   {
      return "bool";
   } // TypedArg< common::CheckAssign< bool>>::varTypeName

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override
   {
      return mDestVar.hasValue();
   } // TypedArg< common::CheckAssign< bool>>::hasValue

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 05.07.2018
   void printValue( std::ostream& os, bool print_type) const override
   {
      os << std::boolalpha << static_cast< bool>( mDestVar);
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< common::CheckAssign< bool>>::printValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   ///
   /// @return  Nothing, always throws.
   /// @throw  std::logic_error whenever called.
   /// @since  0.2, 10.04.2016
   TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< common::CheckAssign< bool>>::setIsMandatory

   /// Unset the flag (set to \c false) when the argument is detected, instead
   /// of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   TypedArgBase* unsetFlag() override
   {
      mValue2Set = false;
      return this;
   } // TypedArg< common::CheckAssign< bool>>::unsetFlag

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override
   {
      os << "sets boolean flag on 'CheckAssign< " << mVarName << ">'." << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< common::CheckAssign< bool>>::dump

private:
   /// Stores the value in the destination variable.
   ///
   /// @since  0.2, 10.04.2016
   void assign( const std::string& /* value */, bool /* inverted */) override
   {
      mDestVar = mValue2Set;
   } // TypedArg< common::CheckAssign< bool>>::assign

   /// Reference of the destination variable to store the value in.
   common::CheckAssign< bool>&  mDestVar;
   /// The value to set when assign is called. Default = \c true.
   bool                         mValue2Set = true;

}; // TypedArg< common::CheckAssign< bool>>



// Template TypedArg< LevelCounter>
// ================================


/// Specialisation of TypedArg<> for a level counter.
/// It is possible/allowed to increment a level counter multiple times, or a
/// value can be assigned to it.<br>
/// Those two features are mutually exclusive: Once the level counter was
/// incremented, it is not possible to assign a value anymore, and vice versa.
///
/// @since  1.10.0, 11.08.2018
template<> class TypedArg< LevelCounter>: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.10.0, 11.08.2018
   TypedArg( LevelCounter& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::optional, true),
      mDestVar( dest)
   {
      mpCardinality.reset();
   } // TypedArg< LevelCounter>::TypedArg

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Always returns "LevelCounter".
   /// @return  The string "LevelCounter".
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override
   {
      return "LevelCounter";
   } // TypedArg< LevelCounter>::varTypeName

   /// Returns if the destination variable was incremented at least once.
   ///
   /// @return
   ///    \c true if the destination variable was incremented at least once.
   /// @since  1.10.0, 11.08.2018
   bool hasValue() const override
   {
      return mHasValueSet || mIncremented;
   } // TypedArg< LevelCounter>::hasValue

   /// Overwrites the 'value mode' which specifies if a value is needed for this
   /// argument or not.
   /// Here in the base class, the only value mode that can be set is
   /// 'required'.
   ///
   /// @param[in]  vm  The new value mode.
   /// @return  Pointer to this object.
   /// @throw  std::invalid_argument if the value mode cannot be set.
   /// @since  1.10.0, 13.08.2018
   TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override
   {

      if (vm == ValueMode::command)
         throw std::invalid_argument( std::string( "may not set value mode '")
            + valueMode2str( vm) + "' on variable '" + mVarName + "'");

      mValueMode = vm;
      return this;
   } // TypedArg< LevelCounter>::setValueMode

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.10.0, 11.08.2018
   void printValue( std::ostream& os, bool print_type) const override
   {
      os << mDestVar.value();
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< LevelCounter>::printValue

   /// Special feature for destination variable type level counter:
   /// Allow mixing of increment and assignment on the command line.
   ///
   /// @since  1.11.0, 20.08.2018
   TypedArgBase* setAllowMixIncSet() noexcept( true) override
   {
      mAllowMixIncSet = true;
      return this;
   } // TypedArg< LevelCounter>::setAllowMixIncSet

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.10.0, 11.08.2018
   void dump( std::ostream& os) const override
   {
      os << "value type 'LevelCounter', destination variable '" << mVarName
         << "', current value " << mDestVar.value() << "." << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< LevelCounter>::dump

   /// Either increments the level counter, or assigns a value to it.
   ///
   /// @param[in]  value
   ///    Either an empty string, in which case the current value is
   ///    incremented, otherwise value to store/assign.
   /// @since  1.10.0, 11.08.2018
   void assign( const std::string& value, bool /* inverted */) noexcept( false)
      override
   {
      if (value.empty())
      {
         if (mHasValueSet && !mAllowMixIncSet)
            throw std::runtime_error( "already have a value assigned to "
               "variable '" + mVarName + "'");

         const int          new_level = mDestVar.value() + 1;
         const std::string  testval( std::to_string( new_level));
         check( testval);

         // when we get here, the new value is within the limits
         ++mDestVar;
         mIncremented = true;
      } else
      {
         if (!mAllowMixIncSet && (mHasValueSet || mIncremented))
            throw std::runtime_error( "already have a value assigned to "
               "variable '" + mVarName + "'");
         check( value);
         if (!mFormats.empty())
         {
            std::string  valCopy( value);
            format( valCopy);
            mDestVar = boost::lexical_cast< int>( valCopy);
         } else
         {
            mDestVar = boost::lexical_cast< int>( value);
         } // end if
         mHasValueSet = true;
      } // end if
   } // TypedArg< LevelCounter>::assign

private:
   /// Reference of the destination variable to store the value(s) in.
   LevelCounter&  mDestVar;
   /// Flag that is set when the level counter was incremented at least once.
   bool           mIncremented = false;
   /// Flag that is set when a vlaue was assigned to the level counter.
   bool           mHasValueSet = false;
   /// If this flag is set, mixing increment and setting the argument on the
   /// command line is allowed.
   bool           mAllowMixIncSet = false;


}; // TypedArg< LevelCounter>


// Template TypedArg< detail::ContainerAdapter< T>>
// ================================================


/// Specialisation of TypedArg<> for destination variables that are of type
/// container, wrapped in a detail::ContainerAdapter<>.
///
/// @tparam  T  The type of container.
/// @since  1.34.0, 22.11.2019  (generalisation for all containers)
template< typename T> class TypedArg< ContainerAdapter< T>>: public TypedArgBase
{
public:
   /// The type of the destination variable/container adapter.
   using dest_type_t = ContainerAdapter< T>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.34.0, 22.11.2019
   TypedArg( dest_type_t dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.34.0, 22.11.2019
   ~TypedArg() override = default;

   /// By default, the value mode for containers is set to "required". Here it
   /// can be changed to "optional" if "clear before assign" has been set before
   /// and the destination container contains (default) values.<br>
   /// This allows the following scenario:
   /// - Assign default values to the destination container.
   /// - Define the argument with "clear before assign" and value mode
   ///   "optional".
   /// - If the argument is not used: Default values are used.
   /// - If the argument is used without value(s): The container is cleared.
   /// - Argument used with values: Only the values are stored in the container.
   /// .
   /// Can only be set on container types that support clearing.
   ///
   /// @param[in]  vm
   ///    The new value mode, only allowed value is actually "optional".
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error if the value mode is not "optional", or "clear before
   ///    assign" is not set.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Returns the name of the type of the destination variable (container of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/container.
   /// @since  1.34.0, 22.11.2019
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.34.0, 22.11.2019
   void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   ///
   /// @return  Pointer to this object.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setTakesMultiValue() override;

   /// Adds a value formatter for the value at the given position: The value
   /// from the argument list (command line) is formatted before it is checked
   /// and/or stored.
   /// The "value index" refers to the position of the new/additional value in
   /// the destination container, i.e. if the container contains some default
   /// values these ust be taken into account.<br>
   /// Since the numbers of values that will be passed on the command line is
   /// not necessarily known, the range of the value index is not checked
   /// against any upper bound.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format to.<br>
   ///    A value of -1 means that the format should be applied to all values,
   ///    index 0 means the first value etc.
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw  std::invalid_argument when the given object pointer is NULL.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* addFormatPos( int val_idx, IFormat* f) noexcept( false)
      override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type container:
   /// Clear the contents of the container before assigning the value(s) from
   /// the command line. If the feature is off (the default), the value(s) from
   /// the command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination variable that should be overwritten by the argument's
   /// values.<br>
   /// Can only be set on containers that support clearing.
   ///
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error if the destination container type does not support
   ///    clearing.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setClearBeforeAssign() noexcept( false) override;

   /// Special feature for destination variable type container:
   /// Sort the contents of the container.<br>
   /// Can only be set on containers that can be sorted, i.e. support iterators.
   ///
   /// @throw
   ///    std::logic_error if the destination container type does not support
   ///    sorting.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setSortData() noexcept( false) override;

   /// Special feature for destination variable type container:
   /// Make sure only unique values are stored in the container.<br>
   /// Can only be set on containers that support iterators. When not set, the
   /// resulting behaviour depends on the type of the container that is used:
   /// Either multiple, equal values are simply added (e.g. vector, multiset),
   /// or multiple values are silently discarded (e.g. set).
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @throw
   ///    std::logic_error if the destination container type does not support
   ///    iterators.
   /// @since  1.34.0, 22.11.2019
   TypedArgBase* setUniqueData( bool duplicates_are_errors = false)
      noexcept( false) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.34.0, 22.11.2019
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value  The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  1.34.0, 22.11.2019
   void assign( const std::string& value, bool inverted) override;

   /// Returns if this object/container and the other container intersect, i.e.
   /// have at least one element in common.
   ///
   /// @return  \c true if the values in the two containers intersect.
   /// @since  1.34.1, 12.01.2020
   bool hasIntersection( TypedArgBase* arg) const noexcept( false) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   dest_type_t  mDestVar;
   /// The character to use as a list separator, default: ,
   char         mListSep = ',';
   /// If set, the contents of the container are cleared before the first
   /// value(s) from the command line are assigned.
   bool         mClearB4Assign = false;
   /// If set, the contents of the container are sorted.
   bool         mSortData = false;
   /// If set, makes sure that the data in the container contains no duplicates.
   bool         mUniqueData = false;
   /// If set, trying to add a duplicate value to the container is treated as an
   /// error, otherwise (the default) it is silently discarded.
   bool         mTreatDuplicatesAsErrors = false;

}; // TypedArg< ContainerAdapter< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< ContainerAdapter< T>>::TypedArg( dest_type_t dest,
      const std::string& vname):
         TypedArgBase( vname, ValueMode::required, false),
         mDestVar( dest)
{
   mpCardinality.reset();
} // TypedArg< ContainerAdapter< T>>::TypedArg


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::setValueMode( ValueMode vm)
{
   if (vm == mValueMode)
      return this;
   if ((vm != ValueMode::optional) || !mClearB4Assign || mDestVar.empty())
      throw std::logic_error( "can only set value mode 'optional' for "
         "container, and ony if 'clear before assign' is set and the container "
         "is not empty");
   mValueMode = vm;
   return this;
} // TypedArg< ContainerAdapter< T>>::setValueMode


template< typename T>
   const std::string TypedArg< ContainerAdapter< T>>::varTypeName() const
{
   // application should not need or want to know that we are using an adapter
   return type< T>::name();
} // TypedArg< ContainerAdapter< T>>::varTypeName


template< typename T> bool TypedArg< ContainerAdapter< T>>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArg< ContainerAdapter< T>>::hasValue


template< typename T>
   void TypedArg< ContainerAdapter< T>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << mDestVar.toString();
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< ContainerAdapter< T>>::printValue


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< ContainerAdapter< T>>::setTakesMultiValue


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::addFormatPos( int val_idx,
      IFormat* f)
{
   if (dest_type_t::AllowsPositionFormat)
      return internAddFormat( val_idx + 1, f);
   return TypedArgBase::addFormatPos( val_idx, f);
} // TypedArg< ContainerAdapter< T>>::addFormatPos


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< ContainerAdapter< T>>::setListSep


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::setClearBeforeAssign()
{
   mClearB4Assign = true;
   return this;
} // TypedArg< ContainerAdapter< T>>::setClearBeforeAssign


template< typename T>
   TypedArgBase* TypedArg< ContainerAdapter< T>>::setSortData()
{
   if (!dest_type_t::IsSorted && dest_type_t::IsSortable)
   {
      mSortData = true;
      return this;
   } // end if
   return TypedArgBase::setSortData();
} // TypedArg< ContainerAdapter< T>>::setSortData


template< typename T>
   TypedArgBase*
      TypedArg< ContainerAdapter< T>>::setUniqueData( bool duplicates_are_errors)
         noexcept( false)
{
   if (dest_type_t::HasIterators)
   {
     mUniqueData = true;
     mTreatDuplicatesAsErrors = duplicates_are_errors;
     return this;
   } // end if
   return TypedArgBase::setUniqueData( duplicates_are_errors);
} // TypedArg< ContainerAdapter< T>>::setUniqueData


template< typename T>
   void TypedArg< ContainerAdapter< T>>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName() << "', destination container '"
      << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : std::to_string( mDestVar.size()))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< ContainerAdapter< T>>::dump


template< typename T>
   void TypedArg< ContainerAdapter< T>>::assign( const std::string& value, bool)
{
   if (mClearB4Assign)
   {
      mDestVar.clear();
      // clear only once
      mClearB4Assign = false;
   } // end if

   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if ((it != tok.begin()) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      auto  list_val( *it);

      check( list_val);

      if (!mFormats.empty())
      {
         format( list_val);
         // we use the position of the new value in the destination container to
         // determine which formatter should be used
         // this works with multiple, separate values as well as a container
         /// with default values
         if (dest_type_t::AllowsPositionFormat)
            format( list_val, mDestVar.size());
      } // end if

      auto const  dest_value = boost::lexical_cast< typename dest_type_t::value_type_t>( list_val);
      if (mUniqueData && mDestVar.contains( dest_value))
      {
         if (mTreatDuplicatesAsErrors)
            throw std::runtime_error( "refuse to store duplicate values in"
               " variable '" + mVarName + "'");
         continue; // for
      } // end if

      mDestVar.addValue( dest_value);
   } // end for

   if (mSortData)
      mDestVar.sort();

} // TypedArg< ContainerAdapter< T>>::assign


template< typename T>
   bool TypedArg< ContainerAdapter< T>>::hasIntersection( TypedArgBase* arg)
      const noexcept( false)
{
   return mDestVar.hasIntersection( static_cast< const TypedArg< dest_type_t>*>( arg)->mDestVar);
} // TypedArg< ContainerAdapter< T>>::hasIntersection


// Template TypedArg< detail::KeyValueContainerAdapter< T>>
// ========================================================


/// Specialisation of TypedArg<> for destination variables that are of type
/// container, wrapped in a detail::KeyValueContainerAdapter<>.
///
/// @tparam  T  The type of the key-value-pair container.
/// @since  1.41.0, 09.02.2020
template< typename T>
   class TypedArg< KeyValueContainerAdapter< T>>: public TypedArgBase
{
public:
   /// The type of the destination variable/container adapter.
   using dest_type_t = KeyValueContainerAdapter< T>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.41.0, 09.02.2020
   TypedArg( dest_type_t dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.41.0, 09.02.2020
   ~TypedArg() override = default;

   /// By default, the value mode for containers is set to "required". Here it
   /// can be changed to "optional" if "clear before assign" has been set before
   /// and the destination container contains (default) values.<br>
   /// This allows the following scenario:
   /// - Assign default values to the destination container.
   /// - Define the argument with "clear before assign" and value mode
   ///   "optional".
   /// - If the argument is not used: Default values are used.
   /// - If the argument is used without value(s): The container is cleared.
   /// - Argument used with values: Only the values are stored in the container.
   /// .
   /// Can only be set on container types that support clearing.
   ///
   /// @param[in]  vm
   ///    The new value mode, only allowed value is actually "optional".
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error if the value mode is not "optional", or "clear before
   ///    assign" is not set.
   /// @since  1.41.0, 09.02.2020
   TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Returns the name of the type of the destination variable (container of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/container.
   /// @since  1.41.0, 09.02.2020
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.41.0, 09.02.2020
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.41.0, 09.02.2020
   void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   ///
   /// @return  Pointer to this object.
   /// @since  1.41.0, 09.02.2020
   TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// Default for key-value pairs is set to ";".
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::invalid_argument if the given list separator is already set as
   ///    part of the pair separator string.
   /// @since  1.41.0, 09.02.2020
   TypedArgBase* setListSep( char sep) noexcept( false) override;

   /// Allows to set the separators to use to split key-value-pair.
   /// The string must contain at least one character, which is then used to
   /// separate. Example with separator = ";" (and list separator = ","):<br>
   /// 1;2,3;4,5;6  --> key 1, value 2; key 3, value 4; key 5; value 6.<br>
   /// Switching the separators would be a more common example (and that is the
   /// default that is set): list separator = ";", separator here = ",":<br>
   /// 1,2;3,4;5,6  --> key 1, value 2; key 3, value 4; key 5; value 6.<br>
   /// If the string is 3 characters long, the 2 additional characters are
   /// expected around a key-value-pair. Example: separator = ",{}", list
   /// separator = ";":<br>
   /// {1,2};{3,4};{5,6}  --> key 1, value 2; key 3, value 4; key 5; value 6.
   ///
   /// @param[in]  separators
   ///    The string with the separator(s) as described above.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::runtime_error if the length of the given pair separator string is
   ///    invalid, must be one (1) or three.
   /// @throw
   ///    std::invalid_argument if the pair separator string contains the list
   ///    separator character.
   /// @since  1.41.0, 13.02.2020
   TypedArgBase* setPairFormat( const std::string& separators) noexcept( false)
      override;

   /// Special feature for destination variable type container:
   /// Clear the contents of the container before assigning the value(s) from
   /// the command line. If the feature is off (the default), the value(s) from
   /// the command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination variable that should be overwritten by the argument's
   /// values.<br>
   /// Can only be set on containers that support clearing.
   ///
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error if the destination container type does not support
   ///    clearing.
   /// @since  1.41.0, 09.02.2020
   TypedArgBase* setClearBeforeAssign() noexcept( false) override;

   /// Key-value-pair containers either support duplicate key values like
   /// std::multimap, or attempts to insert an already exiosting key are simply
   /// ignored.
   /// With this method it can be controlled that e.g. in a multi-map only
   /// unique key values can be inserted, or that the attempt to insert an
   /// already existing key value results in an error.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate key values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @return  This object.
   /// @since  1.41.0, 20.02.2020
   TypedArgBase* setUniqueData( bool duplicates_are_errors) override;

   /// Special method for key-value pair container: Set the formatter to use
   /// for the key.
   ///
   /// @param[in]  f  Pointer to the formatter function to use for the key.
   /// @return   This object.
   /// @since  1.41.0, 18.02.2020
   TypedArgBase* addFormatKey( IFormat* f) override;

   /// Special method for key-value pair container: Set the formatter to use
   /// for the value.
   ///
   /// @param[in]  f  Pointer to the formatter function to use for the value.
   /// @return   This object.
   /// @since  1.41.0, 18.02.2020
   TypedArgBase* addFormatValue( IFormat* f) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.41.0, 09.02.2020
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value  The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.41.0, 09.02.2020
   void assign( const std::string& value, bool inverted) override;

   /// Returns if this object/container and the other container intersect, i.e.
   /// have at least one element in common.
   ///
   /// @return  \c true if the values in the two containers intersect.
   /// @since  1.41.0, 09.02.2020
   bool hasIntersection( TypedArgBase* arg) const noexcept( false) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   dest_type_t  mDestVar;
   /// The separator(s) to use to split a pair into key and value.
   std::string  mPairSeparator;
   /// The character to use as a list separator, default: ,
   char         mListSep = ';';
   /// If set, the contents of the container are cleared before the first
   /// value(s) from the command line are assigned.
   bool         mClearB4Assign = false;
   /// If set, makes sure that the data in the container contains no duplicates.
   bool         mUniqueData = false;
   /// If set, trying to add a duplicate value to the container is treated as an
   /// error, otherwise (the default) it is silently discarded.
   bool         mTreatDuplicatesAsErrors = false;

}; // TypedArg< KeyValueContainerAdapter< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< KeyValueContainerAdapter< T>>::TypedArg( dest_type_t dest,
      const std::string& vname):
         TypedArgBase( vname, ValueMode::required, false),
         mDestVar( dest)
{
   mpCardinality.reset();
   mPairSeparator = ",";
} // TypedArg< KeyValueContainerAdapter< T>>::TypedArg


template< typename T>
   TypedArgBase* TypedArg< KeyValueContainerAdapter< T>>::setValueMode( ValueMode vm)
{
   if (vm == mValueMode)
      return this;
   if ((vm != ValueMode::optional) || !mClearB4Assign || mDestVar.empty())
      throw std::logic_error( "can only set value mode 'optional' for "
         "container, and ony if 'clear before assign' is set and the container "
         "is not empty");
   mValueMode = vm;
   return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setValueMode


template< typename T>
   const std::string TypedArg< KeyValueContainerAdapter< T>>::varTypeName() const
{
   // application should not need or want to know that we are using an adapter
   return type< T>::name();
} // TypedArg< KeyValueContainerAdapter< T>>::varTypeName


template< typename T> bool TypedArg< KeyValueContainerAdapter< T>>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArg< KeyValueContainerAdapter< T>>::hasValue


template< typename T>
   void TypedArg< KeyValueContainerAdapter< T>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << mDestVar.toString();
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< KeyValueContainerAdapter< T>>::printValue


template< typename T>
   TypedArgBase* TypedArg< KeyValueContainerAdapter< T>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setTakesMultiValue


template< typename T>
   TypedArgBase* TypedArg< KeyValueContainerAdapter< T>>::setListSep( char sep)
{
   if (!mPairSeparator.empty()
       && (mPairSeparator.find( sep) != std::string::npos))
      throw std::invalid_argument( "list-separator must not be set as pair-"
         "separator too");
   mListSep = sep;
   return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setListSep


template< typename T>
   TypedArgBase*
      TypedArg< KeyValueContainerAdapter< T>>::setPairFormat(
         const std::string& separators) noexcept( false)
{
   if ((separators.length() != 1) && (separators.length() != 3))
      throw std::invalid_argument( "length of pair-separator string must be "
         "either 1 or 3");
   if (separators.find( mListSep) != std::string::npos)
      throw std::invalid_argument( "pair-separator string must not contain the "
         "list separator character");
   mPairSeparator = separators;
   return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setPairFormat


template< typename T>
   TypedArgBase* TypedArg< KeyValueContainerAdapter< T>>::setClearBeforeAssign()
{
   mClearB4Assign = true;
   return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setClearBeforeAssign


template< typename T>
   TypedArgBase*
      TypedArg< KeyValueContainerAdapter< T>>::setUniqueData( bool duplicates_are_errors)
{
  mUniqueData = true;
  mTreatDuplicatesAsErrors = duplicates_are_errors;
  return this;
} // TypedArg< KeyValueContainerAdapter< T>>::setUniqueData


template< typename T>
   TypedArgBase*
      TypedArg< KeyValueContainerAdapter< T>>::addFormatKey( IFormat* f)
{
   return internAddFormat( 1, f);
} // TypedArg< KeyValueContainerAdapter< T>>::addFormatKey


template< typename T>
   TypedArgBase*
      TypedArg< KeyValueContainerAdapter< T>>::addFormatValue( IFormat* f)
{
   return internAddFormat( 2, f);
} // TypedArg< KeyValueContainerAdapter< T>>::addFormatValue


template< typename T>
   void TypedArg< KeyValueContainerAdapter< T>>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName() << "', destination container '"
      << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : std::to_string( mDestVar.size()))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< KeyValueContainerAdapter< T>>::dump


template< typename T>
   void TypedArg< KeyValueContainerAdapter< T>>::assign( const std::string& value, bool)
{
   if (mClearB4Assign)
   {
      mDestVar.clear();
      // clear only once
      mClearB4Assign = false;
   } // end if

   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if ((it != tok.begin()) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      auto  list_val( *it);

      check( list_val);

      // split the string into key and value
      if (mPairSeparator.length() == 3)
      {
         if ((list_val.front() == mPairSeparator[ 1])
             && (list_val.back() == mPairSeparator[ 2]))
            list_val = list_val.substr( 1, list_val.length() - 2);
         else
            throw std::runtime_error( "pair format not as expected");
      } // end if

      auto  key_value = common::split2( list_val, mPairSeparator[ 0]);

      if (key_value.first.empty() || key_value.second.empty())
            throw std::runtime_error( "pair format not as expected");

      if (!mFormats.empty())
      {
         format( key_value.first, 0);
         format( key_value.second, 1);
      } // end if

      auto const  dest_key   =
         boost::lexical_cast< typename dest_type_t::key_type_t>(
            key_value.first);

      if (mUniqueData && mDestVar.contains( dest_key))
      {
         if (mTreatDuplicatesAsErrors)
            throw std::runtime_error( "refuse to store duplicate values in"
               " variable '" + mVarName + "'");
         continue; // for
      } // end if

      auto const  dest_value =
         boost::lexical_cast< typename dest_type_t::value_type_t>(
            key_value.second);

      mDestVar.addValue( dest_key, dest_value);
   } // end for

} // TypedArg< KeyValueContainerAdapter< T>>::assign


template< typename T>
   bool TypedArg< KeyValueContainerAdapter< T>>::hasIntersection( TypedArgBase* arg)
      const noexcept( false)
{
   return mDestVar.hasIntersection( static_cast< const TypedArg< dest_type_t>*>( arg)->mDestVar);
} // TypedArg< KeyValueContainerAdapter< T>>::hasIntersection


// Template TypedArg< T[ N]>
// =========================


/// Specialisation of TypedArg<> for values wrapped in an POD array.
/// Arrays are always filled from the first element up to the maximum number of
/// elements that the array can store.
///
/// @tparam  T
///    The type of the value(s) stored in the array.
/// @tparam  N
///    Number of elements the array can hold.
/// @since  1.26.0, 29.04.2019
template< typename T, size_t N> class TypedArg< T[ N]>: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  aname
   ///    The name of the destination variable to store the values in.
   /// @since  1.26.0, 29.04.2019
   TypedArg( T (&dest)[ N], const std::string& aname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the name of the type of the destination variable (array of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/array.
   /// @since  1.26.0, 29.04.2019
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.26.0, 29.04.2019
   bool hasValue() const override;

   /// Prints the current values of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the values to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.26.0, 29.04.2019
   void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For arrays it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.26.0, 29.04.2019
   TypedArgBase* setTakesMultiValue() override;

   /// Adds a value formatter for the value at the given position: The value
   /// from the argument list (command line) is formatted before it is checked
   /// and/or stored.
   /// The "value index" refers to the position of the new/additional value in
   /// the destination array.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format to.<br>
   ///    A value of -1 means that the format should be applied to all values,
   ///    index 0 means the first value etc.
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw  std::invalid_argument when the given object pointer is NULL.
   /// @since  1.32.0, 20.08.2019
   TypedArgBase* addFormatPos( int val_idx, IFormat* f) noexcept( false)
      override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.26.0, 29.04.2019
   TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type array:
   /// Sort the contents of the array.
   ///
   /// @since  1.26.0, 29.04.2019
   TypedArgBase* setSortData() override;

   /// Special feature for destination variable type array:
   /// Make sure only unique values are stored in the array.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since  1.26.0, 29.04.2019
   TypedArgBase* setUniqueData( bool duplicates_are_errors = false) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.26.0, 29.04.2019
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  1.26.0, 29.04.2019
   void assign( const std::string& value, bool inverted) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   T            (&mDestVar)[ N];
   /// The index of the next value to store in the array.
   size_t       mIndex = 0;
   /// The character to use as a list separator, default: ,
   char         mListSep = ',';
   /// If set, the contents of the array are sorted.
   bool         mSortData = false;
   /// If set, makes sure that the data in the array contains no duplicates.
   bool         mUniqueData = false;
   /// If set, trying to add a duplicate value to the array is treated as an
   /// error, otherwise (the default) it is silently discarded.
   bool         mTreatDuplicatesAsErrors = false;

}; // TypedArg< T[ N]>


// inlined methods
// ===============


template< typename T, size_t N>
   TypedArg< T[ N]>::TypedArg( T (&dest)[N], const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
{
   mpCardinality.reset();
} // TypedArg< T[ N]>::TypedArg


template< typename T, size_t N>
   const std::string TypedArg< T[ N]>::varTypeName() const
{
   return type< T[ N]>::name();
} // TypedArg< T[ N]>::varTypeName


template< typename T, size_t N> bool TypedArg< T[ N]>::hasValue() const
{
   return mIndex > 0;
} // TypedArg< T[ N]>::hasValue


template< typename T, size_t N>
   void TypedArg< T[ N]>::printValue( std::ostream& os, bool print_type) const
{
   os << format::toString( mDestVar, mDestVar + mIndex);
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< T[ N]>::printValue


template< typename T, size_t N>
   TypedArgBase* TypedArg< T[ N]>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< T[ N]>::setTakesMultiValue


template< typename T, size_t N>
   TypedArgBase* TypedArg< T[ N]>::addFormatPos( int val_idx, IFormat* f)
{
   if (val_idx >= static_cast< int>( N))
      throw std::range_error( "formatter value index is out of range");
   return internAddFormat( val_idx + 1, f);
} // TypedArg< T[ N]>::addFormatPos


template< typename T, size_t N>
   TypedArgBase* TypedArg< T[ N]>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< T[ N]>::setListSep


template< typename T, size_t N> TypedArgBase* TypedArg< T[ N]>::setSortData()
{
   mSortData = true;
   return this;
} // TypedArg< T[ N]>::setSortData


template< typename T, size_t N>
   TypedArgBase* TypedArg< T[ N]>::setUniqueData( bool duplicates_are_errors)
{
   mUniqueData = true;
   mTreatDuplicatesAsErrors = duplicates_are_errors;
   return this;
} // TypedArg< T[ N]>::setUniqueData


template< typename T, size_t N>
   void TypedArg< T[ N]>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName()
      << "', destination array '" << mVarName << "', currently "
      << ((mIndex == 0) ? "no" : std::to_string( mIndex))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< T[ N]>::dump


template< typename T, size_t N>
   void TypedArg< T[ N]>::assign( const std::string& value, bool)
{
   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if ((it != tok.begin()) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      if (mIndex == N)
         throw std::runtime_error( "too many values for fixed-size array "
            "variable '" + mVarName + "'");

      auto  list_val( *it);

      check( list_val);

      if (!mFormats.empty())
      {
         format( list_val);
         format( list_val, mIndex);
      } // end if

      auto const  dest_value = boost::lexical_cast< T>( list_val);
      if (mUniqueData)
      {
         if (common::contains( mDestVar, dest_value))
         {
            if (mTreatDuplicatesAsErrors)
               throw std::runtime_error( "refuse to store duplicate values in"
                  " variable '" + mVarName + "'");
            continue; // for
         } // end if
      } // end if

      mDestVar[ mIndex++] = dest_value;
   } // end for

   if (mSortData)
      std::sort( mDestVar, mDestVar + mIndex);

} // TypedArg< T[ N]>::assign


// Template TypedArg< std::array< T, N>>
// =====================================


/// Specialisation of TypedArg<> for values wrapped in an std::array.
/// Arrays are always filled from the first element up to the maximum number of
/// elements that the array can store.
///
/// @tparam  T
///    The type of the value(s) stored in the array.
/// @tparam  N
///    Number of elements the array can hold.
/// @since  1.26.0, 26.04.2019
template< typename T, size_t N>
   class TypedArg< std::array< T, N>>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using array_type = typename std::array< T, N>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  aname
   ///    The name of the destination variable to store the values in.
   /// @since  1.26.0, 26.04.2019
   TypedArg( array_type& dest, const std::string& aname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the name of the type of the destination variable (array of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/array.
   /// @since  1.26.0, 26.04.2019
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.26.0, 26.04.2019
   bool hasValue() const override;

   /// Prints the current values of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the values to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.26.0, 26.04.2019
   void printValue( std::ostream& os, bool print_type) const override;

   /// Adds a value formatter for the value at the given position: The value
   /// from the argument list (command line) is formatted before it is checked
   /// and/or stored.
   /// The "value index" refers to the position of the new/additional value in
   /// the destination array.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format to.<br>
   ///    A value of -1 means that the format should be applied to all values,
   ///    index 0 means the first value etc.
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw  std::invalid_argument when the given object pointer is NULL.
   /// @since  1.32.0, 26.08.2019
   TypedArgBase* addFormatPos( int val_idx, IFormat* f) noexcept( false)
      override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For arrays it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.26.0, 26.04.2019
   TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.26.0, 26.04.2019
   TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type array:
   /// Sort the contents of the array.
   ///
   /// @since  1.26.0, 26.04.2019
   TypedArgBase* setSortData() override;

   /// Special feature for destination variable type array:
   /// Make sure only unique values are stored in the array.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since  1.26.0, 26.04.2019
   TypedArgBase* setUniqueData( bool duplicates_are_errors = false) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.26.0, 26.04.2019
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  1.26.0, 26.04.2019
   void assign( const std::string& value, bool inverted) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   array_type&  mDestVar;
   /// The index of the next value to store in the array.
   size_t       mIndex = 0;
   /// The character to use as a list separator, default: ,
   char         mListSep = ',';
   /// If set, the contents of the array are sorted.
   bool         mSortData = false;
   /// If set, makes sure that the data in the array contains no duplicates.
   bool         mUniqueData = false;
   /// If set, trying to add a duplicate value to the array is treated as an
   /// error, otherwise (the default) it is silently discarded.
   bool         mTreatDuplicatesAsErrors = false;

}; // TypedArg< std::array< T, N>>


// inlined methods
// ===============


template< typename T, size_t N>
   TypedArg< std::array< T, N>>::TypedArg( array_type& dest,
      const std::string& vname):
         TypedArgBase( vname, ValueMode::required, false),
         mDestVar( dest)
{
   mpCardinality.reset();
} // TypedArg< std::array< T, N>>::TypedArg


template< typename T, size_t N>
   const std::string TypedArg< std::array< T, N>>::varTypeName() const
{
   return type< std::array< T, N>>::name();
} // TypedArg< std::array< T, N>>::varTypeName


template< typename T, size_t N>
   bool TypedArg< std::array< T, N>>::hasValue() const
{
   return mIndex > 0;
} // TypedArg< std::array< T, N>>::hasValue


template< typename T, size_t N>
   void TypedArg< std::array< T, N>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar.begin(), mDestVar.end());
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< std::array< T, N>>::printValue


template< typename T, size_t N>
   TypedArgBase* TypedArg< std::array< T, N>>::addFormatPos( int val_idx,
      IFormat* f)
{
   if (val_idx >= static_cast< int>( N))
      throw std::range_error( "formatter value index is out of range");
   return internAddFormat( val_idx + 1, f);
} // TypedArg< std::array< T, N>>::addFormatPos


template< typename T, size_t N>
   TypedArgBase* TypedArg< std::array< T, N>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< std::array< T, N>>::setTakesMultiValue


template< typename T, size_t N>
   TypedArgBase* TypedArg< std::array< T, N>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< std::array< T, N>>::setListSep


template< typename T, size_t N>
   TypedArgBase* TypedArg< std::array< T, N>>::setSortData()
{
   mSortData = true;
   return this;
} // TypedArg< std::array< T, N>>::setSortData


template< typename T, size_t N>
   TypedArgBase*
      TypedArg< std::array< T, N>>::setUniqueData( bool duplicates_are_errors)
{
   mUniqueData = true;
   mTreatDuplicatesAsErrors = duplicates_are_errors;
   return this;
} // TypedArg< std::array< T, N>>::setUniqueData


template< typename T, size_t N>
   void TypedArg< std::array< T, N>>::dump( std::ostream& os) const
{
   os << "value type '" << type< array_type>::name()
      << "', destination array '" << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : std::to_string( mIndex))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< std::array< T, N>>::dump


template< typename T, size_t N>
   void TypedArg< std::array< T, N>>::assign( const std::string& value, bool)
{
   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if ((it != tok.begin()) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      if (mIndex == N)
         throw std::runtime_error( "too many values for fixed-size array "
            "variable '" + mVarName + "'");

      auto  list_val( *it);

      check( list_val);

      if (!mFormats.empty())
      {
         format( list_val);
         format( list_val, mIndex);
      } // end if

      auto const  dest_value = boost::lexical_cast< T>( list_val);
      if (mUniqueData)
      {
         if (common::contains( mDestVar, dest_value))
         {
            if (mTreatDuplicatesAsErrors)
               throw std::runtime_error( "refuse to store duplicate values in"
                  " variable '" + mVarName + "'");
            continue; // for
         } // end if
      } // end if

      mDestVar[ mIndex++] = dest_value;
   } // end for

   if (mSortData)
      std::sort( mDestVar.begin(), mDestVar.begin() + mIndex);

} // TypedArg< std::array< T, N>>::assign


namespace internal {


// Class TupleElementValueAssign
// =============================


/// Helper class used to assign a value to a tuple element with type
/// conversion.
/// Can be replaced by a lambda, once the decltype works for boost::lexical_cast.
class TupleElementValueAssign
{
public:
   /// Constructor.
   ///
   /// @param[in]  value  The value to assign to the tuple element.
   /// @since  0.11, 04.01.2017
   explicit TupleElementValueAssign( const std::string& value):
      mValue( value)
   {
   } // TupleElementValueAssign::TupleElementValueAssign

   /// Empty default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   virtual ~TupleElementValueAssign() = default;

   /// Operator called for the tuple element. Converts the value from #mValue to
   /// the required destination type and assigns it to \a tuple_value, i.e. the
   /// tuple element.
   ///
   /// @param[out]  tuple_element  The element of the the tuple to assign the
   ///                             value to.
   /// @since  6.0, 04.01.2017
   template< typename T> void operator ()( T& tuple_element)
   {
      tuple_element = boost::lexical_cast< T>( mValue);
   } // TupleElementValueAssign::operator ()

private:
   /// The value to assign in the operator.
   const std::string  mValue;

}; // TupleElementValueAssign


} // namespace internal


// Template TypedArg< std::tuple< T...>>
// =====================================


/// Helper class to store a destination variable of type tuple with its native
/// element types.
///
/// @tparam  T  The types of the values.
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// @since  0.11, 07.01.2017
///    (converted from TypedArgTuple into specialisation)
/// @since  0.11, 19.12.2016
template< typename... T> class TypedArg< std::tuple< T...>>: public TypedArgBase
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the value in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.11, 19.12.2016
   TypedArg( std::tuple< T...>& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the name of the type of the destination variable, the tuple.
   ///
   /// @return  String with the name of the complete type.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.11, 19.12.2016
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Adds the value of the destination variable to the string.
   ///
   /// @param[out]  dest  The string to append the default value to.
   /// @since  0.11, 19.12.2016
   void defaultValue( std::string& dest) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For tuples it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   TypedArgBase* setTakesMultiValue() override;

   /// Overload for destination tuple: Format not allowed.
   ///
   /// @param[in]  f  Pointer to the format to add, the object is deleted.
   /// @return  Never returns anything.
   /// @throw
   ///    std::logic_error when called since setting a single formatter for a
   ///    tuple is  never allowed.
   /// @since  1.23.0, 09.04.2019
   TypedArgBase* addFormat( IFormat* f) noexcept( false) override;

   /// Adds a value formatter for the value at the given position: The value
   /// from the argument list (command line) is formatted before it is checked
   /// and/or stored.
   /// The "value index" refers to the position of the new/additional value in
   /// the destination tuple.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format to.
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error when the given value index is 0 (would mean:
   ///    formatter for all values).
   /// @throw
   ///    std::invalid_argument when the given object pointer is NULL.
   /// @throw
   ///    std::range_error when the given value index is too big for this tuple.
   /// @since  1.32.0, 10.04.2019
   TypedArgBase* addFormatPos( int val_idx, IFormat* f) noexcept( false)
      override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   TypedArgBase* setListSep( char sep) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.11, 19.12.2016
   void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter \a inverted)
   /// @since  0.11, 19.12.2016
   void assign( const std::string& value, bool inverted) override;

   /// Reference of the destination variable to store the value in.
   std::tuple< T...>&  mDestVar;
   /// The length, i.e. the number of elements, of the tuple.
   const size_t        mTupleLength;
   /// Counter for the number of values set.
   size_t              mNumValuesSet = 0;
   /// The character to use a list separator, default: ,
   char                mListSep = ',';

}; // TypedArg< std::tuple< T...>>


// inlined methods
// ===============


template< typename... T>
   TypedArg< std::tuple< T...>>::TypedArg( std::tuple< T...>& dest,
                                           const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest),
      mTupleLength( common::tuple_length( dest))
{
   mpCardinality.reset( new CardinalityExact( mTupleLength));
} // TypedArg< std::tuple< T...>>::TypedArg


template< typename... T>
   const std::string TypedArg< std::tuple< T...>>::varTypeName() const
{
   return type< std::tuple< T...>>::name();
} // TypedArg< std::tuple< T...>>::varTypeName


template< typename... T> bool TypedArg< std::tuple< T...>>::hasValue() const
{
   return mNumValuesSet == mTupleLength;
} // TypedArg< std::tuple< T...>>::hasValue


template< typename... T>
   void TypedArg< std::tuple< T...>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar);
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< std::tuple< T...>>::printValue


template< typename... T>
   void TypedArg< std::tuple< T...>>::defaultValue( std::string& dest) const
{
   dest.append( "<").append( format::toString( mDestVar)).append( ">");
} // TypedArg< std::tuple< T...>>::defaultValue


template< typename... T>
   TypedArgBase* TypedArg< std::tuple< T...>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< std::tuple< T...>>::setTakesMultiValue


template< typename... T>
   TypedArgBase* TypedArg< std::tuple< T...>>::addFormat( IFormat* f)
{
   delete f;
   throw std::logic_error( "not allowed to add a single format for a tuple");
} // TypedArg< std::tuple< T...>>::addFormat


template< typename... T>
   TypedArgBase* TypedArg< std::tuple< T...>>::addFormatPos( int val_idx,
      IFormat* f)
{
   if (val_idx == -1)
   {
      // reject? or test if all elements of the tuple have the same type?
      // if all elements had the same type, it would be easier to use a vector
      // or an array or ...
      // so, reject
      throw std::logic_error( "general formatter for all values not allowed "
         "with tuples");
   } // end if

   if (val_idx >= static_cast< int>( mTupleLength))
      throw std::range_error( "cannot add a formatter for position "
         + format::toString( val_idx) + " for a tuple with only "
         + format::toString( mTupleLength) + " elements");

   return internAddFormat( val_idx + 1, f);
} // TypedArg< std::tuple< T...>>::addFormatPos


template< typename... T>
   TypedArgBase* TypedArg< std::tuple< T...>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< std::tuple< T...>>::setListSep


template< typename... T>
   void TypedArg< std::tuple< T...>>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName() << "', destination '" << mVarName
      << "', ";
   if (hasValue())
   {
      os << "value = <" << format::toString( mDestVar) << ">." << std::endl;
   } else
   { 
      os << "value not set." << std::endl;
   } // end if
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< std::tuple< T...>>::dump


template< typename... T>
   void TypedArg< std::tuple< T...>>::assign( const std::string& value, bool)
{
   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin_counting(); it != tok.end_counting(); ++it)
   {
      if ((it.currentNum() > 0) && (mpCardinality.get() != nullptr))
         mpCardinality->gotValue();

      std::string  list_val( *it);

      check( list_val);

      if (!mFormats.empty())
      {
         format( list_val, mNumValuesSet);
      } // end if

      internal::TupleElementValueAssign  teva( list_val);
      common::tuple_at_index( mNumValuesSet, mDestVar, teva);

#if 0
      // this should work ...
      common::tuple_at_index( mNumValuesSet, mDestVar,
                              [&list_val]( auto& tuple_value)
        {
           tuple_value = boost::lexical_cast< std::decltype( tuple_value)>( list_val);
        });
#endif
      ++mNumValuesSet;
   } // end for
} // TypedArg< std::tuple< T...>>::assign


// Template TypedArg< std::bitset< T>>
// ===================================


/// Specialisation of TypedArg<> for destination value type std::bitset<>.
///
/// @tparam  N  The size of the bitset.
/// @since  1.4.3, 29.04.2018
template< size_t N> class TypedArg< std::bitset< N>>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using bitset_type = typename std::bitset< N>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.4.3, 29.04.2018
   TypedArg( bitset_type& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   ~TypedArg() override = default;

   /// Returns the type of the destination variable.
   ///
   /// @return  The name of the destination variable's type.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.4.3, 29.04.2018
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For bitsets it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type bitset:
   /// Clear the contents of the bitset before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination bitset that should be overwritten by the argument's values.
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   TypedArgBase* setClearBeforeAssign() override;

   /// Unset the flags (reset in the bitset) when the argument is detected,
   /// instead of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   TypedArgBase* unsetFlag() override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  1.4.3, 29.04.2018
   void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  1.4.3, 29.04.2018
   void assign( const std::string& value, bool inverted) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   bitset_type&  mDestVar;
   /// The character to use as a list separator, default: ,
   char          mListSep = ',';
   /// If set, the contents of the bitset are cleared before the first value(s)
   /// from the command line are assigned.
   bool          mClearB4Assign = false;
   /// Specifies if the flags in the bitset should set (the default) or reset.
   bool          mResetFlags = false;


}; // TypedArg< std::bitset< N>>


// inlined methods
// ===============


template< size_t N>
   TypedArg< std::bitset< N>>::TypedArg( bitset_type& dest,
                                         const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
{
   mpCardinality.reset();
} // TypedArg< std::bitset< N>>::TypedArg


template< size_t N>
   const std::string TypedArg< std::bitset< N>>::varTypeName() const
{
   return type< bitset_type>::name();
} // TypedArg< std::bitset< N>>::varTypeName


template< size_t N> bool TypedArg< std::bitset< N>>::hasValue() const
{
   return mDestVar.any();
} // TypedArg< std::bitset< N>>::hasValue


template< size_t N>
   void TypedArg< std::bitset< N>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar);
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< std::bitset< N>>::printValue


template< size_t N>
   TypedArgBase* TypedArg< std::bitset< N>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< std::bitset< N>>::setTakesMultiValue


template< size_t N>
   TypedArgBase* TypedArg< std::bitset< N>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< std::bitset< N>>::setListSep


template< size_t N>
   TypedArgBase* TypedArg< std::bitset< N>>::setClearBeforeAssign()
{
   mClearB4Assign = true;
   return this;
} // TypedArg< std::bitset< N>>::setClearBeforeAssign


template< size_t N> TypedArgBase* TypedArg< std::bitset< N>>::unsetFlag()
{
   mResetFlags = true;
   return this;
} // TypedArg< std::bitset< N>>::unsetFlag


template< size_t N>
   void TypedArg< std::bitset< N>>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName()
      << "', destination bitset '" << mVarName << "', currently "
      << (mDestVar.none() ? "no" : std::to_string( mDestVar.count()))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< std::bitset< N>>::dump


template< size_t N>
   void TypedArg< std::bitset< N>>::assign( const std::string& value, bool)
{
   if (mClearB4Assign)
   {
      mDestVar.reset();
      // clear only once
      mClearB4Assign = false;
   } // end if

   common::Tokenizer  tok( value, mListSep);
   for (auto it = tok.begin(); it != tok.end(); ++it)
   {
      if (mpCardinality && (it != tok.begin()))
         mpCardinality->gotValue();

      auto const&  list_val( *it);

      check( list_val);

      if (!mFormats.empty())
      {
         auto  valCopy( list_val);
         format( valCopy);
         auto const  pos = boost::lexical_cast< size_t>( valCopy);
         if (pos >= N)
            throw std::runtime_error( "position " + std::to_string( pos)
               + " is outside the range of the bitset");
         mDestVar[ pos] = !mResetFlags;
      } else
      {
         auto const  pos = boost::lexical_cast< size_t>( list_val);
         if (pos >= N)
            throw std::runtime_error( "position " + std::to_string( pos)
               + " is outside the range of the bitset");
         mDestVar[ pos] = !mResetFlags;
      } // end if
   } // end for
} // TypedArg< std::bitset< N>>::assign


// Template TypedArg< std::vector< bool>>
// ======================================


/// Specialisation of TypedArg<> for destination value type std::vector< bool>.
///
/// @since  1.40.0. 28.05.2020
template<> class TypedArg< std::vector< bool>>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using vector_type = typename std::vector< bool>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.40.0. 28.05.2020
   TypedArg( vector_type& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
   {
      mpCardinality.reset();
   } // TypedArg< std::vector< bool>>::TypedArg

   /// Empty, virtual default destructor.
   ///
   /// @since  1.40.0. 28.05.2020
   ~TypedArg() override = default;

   /// Returns the type of the destination variable.
   ///
   /// @return  The name of the destination variable's type.
   /// @since  1.40.0. 28.05.2020
   const std::string varTypeName() const override
   {
      return type< vector_type>::name();
   } // TypedArg< std::vector< bool>>::varTypeName

   /// Returns if the destination has (at least) one value set.
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.40.0. 28.05.2020
   bool hasValue() const override
   {
      return common::contains( mDestVar, true);
   } // TypedArg< std::vector< bool>>::hasValue

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.40.0. 28.05.2020
   void printValue( std::ostream& os, bool print_type) const override
   {
      os << format::toString( mDestVar);
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< std::vector< bool>>::printValue

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For vector< bool> it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.40.0. 28.05.2020
   TypedArgBase* setTakesMultiValue() override
   {
      mTakeMultipleValues = true;
      return this;
   } // TypedArg< std::vector< bool>>::setTakesMultiValue

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.40.0. 28.05.2020
   TypedArgBase* setListSep( char sep) override
   {
      mListSep = sep;
      return this;
   } // TypedArg< std::vector< bool>>::setListSep

   /// Special feature for destination variable type vector< bool>:
   /// Clear the contents of the vector before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination vector that should be overwritten by the argument's values.
   ///
   /// @return  Pointer to this object.
   /// @since  1.40.0. 28.05.2020
   TypedArgBase* setClearBeforeAssign() override
   {
      mClearB4Assign = true;
      return this;
   } // TypedArg< std::vector< bool>>::setClearBeforeAssign

   /// Unset the flags (set to \c false the vector) when the argument is detected,
   /// instead of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  1.40.0. 28.05.2020
   TypedArgBase* unsetFlag() override
   {
      mResetFlags = true;
      return this;
   } // TypedArg< std::vector< bool>>::unsetFlag

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  1.40.0. 28.05.2020
   void dump( std::ostream& os) const override
   {
      os << "value type '" << varTypeName()
         << "', destination vector '" << mVarName << "', currently "
         << (none() ? "no" : std::to_string( count()))
         << " values." << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< std::vector< bool>>::dump

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.40.0. 28.05.2020
   void assign( const std::string& value, bool) override
   {
      if (mClearB4Assign)
      {
         mDestVar.clear();
         // clear only once
         mClearB4Assign = false;
      } // end if

      if (mDestVar.size() == 0)
         mDestVar.resize( 10);

      common::Tokenizer  tok( value, mListSep);
      for (auto it = tok.begin(); it != tok.end(); ++it)
      {
         if (mpCardinality && (it != tok.begin()))
            mpCardinality->gotValue();

         auto const&  listVal( *it);

         check( listVal);

         if (!mFormats.empty())
         {
            auto  valCopy( listVal);
            format( valCopy);
            auto const  pos = boost::lexical_cast< size_t>( valCopy);
            if (pos >= mDestVar.size())
               mDestVar.resize( pos * 1.5);
            mDestVar[ pos] = !mResetFlags;
         } else
         {
            auto const  pos = boost::lexical_cast< size_t>( listVal);
            if (pos >= mDestVar.size())
               mDestVar.resize( pos * 1.5);
            mDestVar[ pos] = !mResetFlags;
         } // end if
      } // end for
   } // TypedArg< std::vector< bool>>::assign

private:
   /// Returns if no bit is set.
   ///
   /// @return  \c true if no bit is set.
   /// @since  1.40.0, 02.06.2020
   bool none() const
   {
      return !common::contains( mDestVar, true);
   } // TypedArg< std::vector< bool>>::none

   /// Returns the number of bits that are set.
   ///
   /// @return  Number of bits set.
   /// @since  1.40.0, 02.06.2020
   size_t count() const
   {
      return std::count( mDestVar.begin(), mDestVar.end(), true);
   } // TypedArg< std::vector< bool>>::count

   /// Reference of the destination variable to store the value(s) in.
   vector_type&  mDestVar;
   /// The character to use as a list separator, default: ,
   char          mListSep = ',';
   /// If set, the contents of the vector are cleared before the first value(s)
   /// from the command line are assigned.
   bool          mClearB4Assign = false;
   /// Specifies if the flags in the vector should set (the default) or reset.
   bool          mResetFlags = false;


}; // TypedArg< std::vector< bool>>


// Template TypedArg< container::DynamicBitset>
// ============================================


/// Specialisation of TypedArg<> for destination value type
/// container::DynamicBitset.
///
/// @since  1.37.0, 28.06.2020
template<> class TypedArg< container::DynamicBitset>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using bitset_type = container::DynamicBitset;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  1.37.0, 28.06.2020
   TypedArg( bitset_type& dest, const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
   {
      mpCardinality.reset();
   } // TypedArg< container::DynamicBitset>::TypedArg

   /// Empty, virtual default destructor.
   ///
   /// @since  1.37.0, 28.06.2020
   ~TypedArg() override = default;

   /// Returns the type of the destination variable.
   ///
   /// @return  The name of the destination variable's type.
   /// @since  1.37.0, 28.06.2020
   const std::string varTypeName() const override
   {
      return type< bitset_type>::name();
   } // TypedArg< container::DynamicBitset>::varTypeName

   /// Returns if the destination has (at least) one value set.
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.37.0, 28.06.2020
   bool hasValue() const override
   {
      return mDestVar.any();
   } // TypedArg< container::DynamicBitset>::hasValue

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.37.0, 28.06.2020
   void printValue( std::ostream& os, bool print_type) const override
   {
      os << format::toString( mDestVar);
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< container::DynamicBitset>::printValue

   /// Overloads TypedArgBase::setTakesMultiValue().
   /// For dynamic bitsets it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.37.0, 28.06.2020
   TypedArgBase* setTakesMultiValue() override
   {
      mTakeMultipleValues = true;
      return this;
   } // TypedArg< container::DynamicBitset>::setTakesMultiValue

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.37.0, 28.06.2020
   TypedArgBase* setListSep( char sep) override
   {
      mListSep = sep;
      return this;
   } // TypedArg< container::DynamicBitset>::setListSep

   /// Special feature for destination variable type bitset:
   /// Clear the contents of the bitset before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination bitset that should be overwritten by the argument's values.
   ///
   /// @return  Pointer to this object.
   /// @since  1.37.0, 28.06.2020
   TypedArgBase* setClearBeforeAssign() override
   {
      mClearB4Assign = true;
      return this;
   } // TypedArg< container::DynamicBitset>::setClearBeforeAssign

   /// Unset the flags (reset in the bitset) when the argument is detected,
   /// instead of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  1.37.0, 28.06.2020
   TypedArgBase* unsetFlag() override
   {
      mResetFlags = true;
      return this;
   } // TypedArg< container::DynamicBitset>::unsetFlag

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  1.37.0, 28.06.2020
   void dump( std::ostream& os) const override
   {
      os << "value type '" << varTypeName()
         << "', destination bitset '" << mVarName << "', currently "
         << (mDestVar.none() ? "no" : boost::lexical_cast< std::string>( mDestVar.count()))
         << " values." << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< container::DynamicBitset>::dump

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.37.0, 28.06.2020
   void assign( const std::string& value, bool) override
   {
      if (mClearB4Assign)
      {
         mDestVar.reset();
         // clear only once
         mClearB4Assign = false;
      } // end if

      common::Tokenizer  tok( value, mListSep);
      for (auto it = tok.begin(); it != tok.end(); ++it)
      {
         if (mpCardinality && (it != tok.begin()))
            mpCardinality->gotValue();

         auto const&  listVal( *it);

         check( listVal);

         if (!mFormats.empty())
         {
            auto  valCopy( listVal);
            format( valCopy);
            auto const  pos = boost::lexical_cast< size_t>( valCopy);
            mDestVar.set( pos, !mResetFlags);
         } else
         {
            auto const  pos = boost::lexical_cast< size_t>( listVal);
            mDestVar.set( pos, !mResetFlags);
         } // end if
      } // end for
   } // TypedArg< container::DynamicBitset>::assign

private:
   /// Reference of the destination variable to store the value(s) in.
   bitset_type&  mDestVar;
   /// The character to use as a list separator, default: ,
   char          mListSep = ',';
   /// If set, the contents of the bitset are cleared before the first value(s)
   /// from the command line are assigned.
   bool          mClearB4Assign = false;
   /// Specifies if the flags in the bitset should set (the default) or reset.
   bool          mResetFlags = false;


}; // TypedArg< container::DynamicBitset>


// Template TypedArg< ValueFilter< T>>
// ===================================


/// Specialisation of TypedArg<> for an argument string that specifies the
/// filters to create.
///
/// @tparam  T  The type of the value(s) to create the filter(s) for.
/// @since  1.31.0, 17.10.2019
template< typename T> class TypedArg< common::ValueFilter< T>>:
   public TypedArgBase
{
public:
   /// The type of the destination variable.
   using valfilter_type = typename common::ValueFilter< T>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the filter(s) in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the filter(s) in.
   /// @since  1.31.0, 17.10.2019
   TypedArg( valfilter_type& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 23.10.2019
   ~TypedArg() override = default;

   /// Returns the name of the type of the destination variable (ValueFilter of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/value filter.
   /// @since  1.31.0, 17.10.2019
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one filter set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one filter.
   /// @since  1.31.0, 17.10.2019
   bool hasValue() const override;

   /// Prints the current value of the destination variable.
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.31.0, 17.10.2019
   void printValue( std::ostream& os, bool print_type) const override;

   /// Always throws for this class.
   ///
   /// @param[in]  c  Check object is deleted.
   /// @return  Nothing.
   /// @throw
   ///    std::logic_error because checking a value filter string is not
   ///    supported.
   /// @since  1.31.0, 18.10.2019
   TypedArgBase* addCheck( ICheck* c) noexcept( false) override;

   /// Always throws for this class.
   ///
   /// @param[in]  f  Format object is deleted.
   /// @return  Nothing.
   /// @throw
   ///    std::logic_error because formatting a value filter string is not
   ///    supported.
   /// @since  1.31.0, 18.10.2019
   TypedArgBase* addFormat( IFormat* f) noexcept( false) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.31.0, 17.10.2019
   void dump( std::ostream& os) const override;

   /// Parses the given string, creates and stores the filters defined therein
   /// in the destination value fiter.
   ///
   /// @param[in]  value
   ///    The string with the filter definitions.
   /// @param[in]  inverted
   ///    Not supported for this argument.
   /// @since  1.31.0, 17.10.2019
   void assign( const std::string& value, bool inverted) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   valfilter_type&  mDestVar;

}; // TypedArg< common::ValueFilter< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< common::ValueFilter< T>>::TypedArg( valfilter_type& dest,
      const std::string& vname):
         TypedArgBase( vname, ValueMode::required, false),
         mDestVar( dest)
{
} // TypedArg< common::ValueFilter< T>>::TypedArg


template< typename T>
   const std::string TypedArg< common::ValueFilter< T>>::varTypeName() const
{
   return type< common::ValueFilter< T>>::name();
} // TypedArg< common::ValueFilter< T>>::varTypeName


template< typename T> bool TypedArg< common::ValueFilter< T>>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArg< common::ValueFilter< T>>::hasValue


template< typename T>
   void TypedArg< common::ValueFilter< T>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar);
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< common::ValueFilter< T>>::printValue


template< typename T>
   TypedArgBase* TypedArg< common::ValueFilter< T>>::addCheck( ICheck* c)
{
   delete c;
   throw std::logic_error( "calling addCheck() not allowed for variable '"
      + mVarName + "'");
} // TypedArg< common::ValueFilter< T>>::addCheck


template< typename T>
   TypedArgBase* TypedArg< common::ValueFilter< T>>::addFormat( IFormat* f)
{
   delete f;
   throw std::logic_error( "calling addFormat() not allowed for variable '"
      + mVarName + "'");
} // TypedArg< common::ValueFilter< T>>::addFormat


template< typename T>
   void TypedArg< common::ValueFilter< T>>::dump( std::ostream& os) const
{
   os << "value type '" << varTypeName() << "', destination value filter '"
      << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : std::to_string( mDestVar.size()))
      << " filters." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< common::ValueFilter< T>>::dump


template< typename T>
   void TypedArg< common::ValueFilter< T>>::assign( const std::string& value,
      bool)
{
   mDestVar = common::parseFilterString< T>( value) ;
} // TypedArg< common::ValueFilter< T>>::assign


} // namespace celma::prog_args::detail


// =====  END OF typed_arg.hpp  =====

