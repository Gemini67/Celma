
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArg.<br>
/// This file contains the base template plus all specialisations:
/// - TypedArg< bool>
/// - TypedArg< CheckAssign< T>>
/// - TypedArg< CheckAssign< bool>>
/// - TypedArg< T[ N]>
/// - TypedArg< std::array< T, N>>
/// - TypedArg< std::bitset< T...>>
/// - TypedArg< std::tuple< T...>>
/// - TypedArg< std::vector< T>>
/// - TypedArg< common::ValueFilter< T>>


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP


#include <cstring>
#include <algorithm>
#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "celma/common/check_assign.hpp"
#include "celma/common/contains.hpp"
#include "celma/common/parse_filter_string.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/common/type_name.hpp"
#include "celma/common/value_filter.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"
#include "celma/prog_args/level_counter.hpp"


namespace celma { namespace prog_args { namespace detail {


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

   /// Returns the type of the destination variable as string.
   ///
   /// @return  String with the type of the destination variable.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Checks that the value mode 'command' is only set for destination types
   /// "std::string".<br>
   /// For all other value modes and types, the metzhod of the base clase is
   /// called.
   ///
   /// @param[in]  vm  The value mode to set.
   /// @return  Pointer to this object.
   /// @since  0.14.2, 12.05.2017
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Adds the value of the destination variable to the string.
   ///
   /// @param[out]  dest  The string to append the default value to.
   /// @since  0.2, 10.04.2016
   virtual void defaultValue( std::string& dest) const override;

   /// 
   /// @param[in]  dest
   ///    .
   /// @since
   ///    x.y.z, 23.10.2019
   void getValue( T& dest) const;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

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
   virtual void assign( const std::string& value, bool inverted) override;

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


template< typename T> void TypedArg< T>::getValue( T& dest) const
{
   if (mHasValueSet)
      dest = mDestVar;
} // TypedArg< T>::getValue


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

   /// Returns "bool".
   /// @return  The string "bool".
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override
   {
      return "bool";
   } // TypedArg< bool>::varTypeName

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override
   {
      return mHasValueSet;
   } // TypedArg< bool>::hasValue

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override
   {
      os << std::boolalpha << mDestVar;
      if (print_type)
         os << " [bool]";
   } // TypedArg< bool>::printValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   ///
   /// @return  Nothing, always throws.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< bool>::setIsMandatory

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override
   {
      os << "boolean flag, destination '" << mVarName << "', "
         << (mHasValueSet ? "set." : "not set.") << std::endl
         << "   " << static_cast< const TypedArgBase&>( *this);
   } // TypedArg< bool>::dump

   /// Stores the value in the destination variable.
   ///
   /// @param  Ignored.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string&, bool) override
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

   /// Returns the name of the type of the variable handled by the CheckAssign<>
   /// object.
   ///
   /// @return  The name of the type of the destination variable.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   ///
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value, bool inverted) override;

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

   /// Always returns "bool".
   /// @return  The string "bool".
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override
   {
      return "bool";
   } // TypedArg< common::CheckAssign< bool>>::varTypeName

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override
   {
      return mDestVar.hasValue();
   } // TypedArg< common::CheckAssign< bool>>::hasValue

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 05.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override
   {
      os << std::boolalpha << static_cast< bool>( mDestVar);
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< common::CheckAssign< bool>>::printValue

   /// Would specify that the argument is mandatory (required). This does not
   /// make sense for a flag/boolean value: Throw exception.
   ///
   /// @return  Nothing, always throws.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory() noexcept( false) override
   {
      throw std::logic_error( "Cannot make boolean argument for variable '" +
                              mVarName + "' mandatory");
   } // TypedArg< common::CheckAssign< bool>>::setIsMandatory

   /// Unset the flag (set to \c false) when the argument is detected, instead
   /// of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* unsetFlag() override
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
   virtual void assign( const std::string& /* value */, bool /* inverted */)
      override
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


/// Specialisation of TypedArg<> for a level counter.<br>
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

   /// Always returns "LevelCounter".
   /// @return  The string "LevelCounter".
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override
   {
      return "LevelCounter";
   } // TypedArg< LevelCounter>::varTypeName

   /// Returns if the destination variable was incremented at least once.
   ///
   /// @return
   ///    \c true if the destination variable was incremented at least once.
   /// @since  1.10.0, 11.08.2018
   virtual bool hasValue() const override
   {
      return mHasValueSet || mIncremented;
   } // TypedArg< LevelCounter>::hasValue

   /// Overwrites the 'value mode' which specifies if a value is needed for this
   /// argument or not.<br>
   /// Here in the base class, the only value mode that can be set is
   /// 'required'.
   ///
   /// @param[in]  vm  The new value mode.
   /// @return  Pointer to this object.
   /// @since  1.10.0, 13.08.2018
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override
   {

      if ((vm == ValueMode::command) || (vm == ValueMode::unknown))
         throw std::invalid_argument( std::string( "may not set value mode '") +
                                      valueMode2str( vm) + "' on variable '" +
                                      mVarName + "'");

      mValueMode = vm;
      return this;
   } // TypedArg< LevelCounter>::setValueMode

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.10.0, 11.08.2018
   virtual void printValue( std::ostream& os, bool print_type) const override
   {
      os << mDestVar.value();
      if (print_type)
         os << " [" << varTypeName() << "]";
   } // TypedArg< LevelCounter>::printValue

   /// Special feature for destination variable type level counter:<br>
   /// Allow mixing of increment and assignment on the command line.
   ///
   /// @since  1.11.0, 20.08.2018
   virtual TypedArgBase* setAllowMixIncSet() noexcept( true) override
   {
      mAllowMixIncSet = true;
      return this;
   } // TypedArg< LevelCounter>::setAllowMixIncSet

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.10.0, 11.08.2018
   virtual void dump( std::ostream& os) const override
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
   virtual void assign( const std::string& value, bool /* inverted */)
      noexcept( false) override
   {
      if (value.empty())
      {
         if (mHasValueSet && !mAllowMixIncSet)
            throw std::runtime_error( "already have a value assigned to "
               "variable '" + mVarName + "'");

         const int          new_level = mDestVar.value() + 1;
         const std::string  testval( boost::lexical_cast< std::string>( new_level));
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


// Template TypedArg< std::vector< T>>
// ===================================


/// Specialisation of TypedArg<> for values wrapped in a vector.
///
/// @tparam  T  The type of the value(s) stored in the vector.
/// @since  1.24.2, 23.04.2019
///    (allow to change value mode to optional when "clear before assign" is
///     already set)
/// @since  0.15.0, 17.07.2017
///    (use type ArgumentKey instead of string for arguments)
/// @since  0.2, 10.04.2016
template< typename T> class TypedArg< std::vector< T>>: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using vector_type = typename std::vector< T>;

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    The destination variable to store the values in.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArg( vector_type& dest, const std::string& vname);

   /// By default, the value mode for vectors is set to "required". Here it can
   /// be changed to "optional" if "clear before assign" has been set before and
   /// the destination vector contains (default) values.<br>
   /// This allows the following scenario:
   /// - Assign default values to the destination vector.
   /// - Define the argument with "clear before assign" and value mode
   ///   "optional".
   /// - If the argument is not used: Default values are used.
   /// - If the argument is used without value(s): The vector is cleared.
   /// - Argument used with values: Only the values are stored in the vector.
   ///
   /// @param[in]  vm
   ///    The new value mode, only allowed value is actually "optional".
   /// @return  Pointer to this object.
   /// @throws
   ///    "logic error" if the value mode is not "optional", or "clear before
   ///    assign" is not set.
   /// @since  1.24.2, 23.04.2019
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false);

   /// Returns the name of the type of the destination variable (vector of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/vector.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For vectors it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type vector:<br>
   /// Clear the contents of the vector before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination vector that should be overwritten by the argument's values.
   ///
   /// @return  Pointer to this object.
   /// @since  1.2.0, 28.12.2017
   virtual TypedArgBase* setClearBeforeAssign() override;

   /// Special feature for destination variable type vector:<br>
   /// Sort the contents of the vector.
   ///
   /// @since  1.9.0, 04.08.2018
   virtual TypedArgBase* setSortData() override;

   /// Special feature for destination variable type vector:<br>
   /// Make sure only unique values are stored in the vector.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since
   ///    1.9.0, 04.08.2018
   virtual TypedArgBase* setUniqueData( bool duplicates_are_errors = false)
      override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value  The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value, bool inverted) override;

private:
   /// Reference of the destination variable to store the value(s) in.
   vector_type&  mDestVar;
   /// The character to use as a list separator, default: ,
   char          mListSep = ',';
   /// If set, the contents of the vector are cleared before the first value(s)
   /// from the command line are assigned.
   bool          mClearB4Assign = false;
   /// If set, the contents of the vector are sorted.
   bool          mSortData = false;
   /// If set, makes sure that the data in the vector contains no duplicates.
   bool          mUniqueData = false;
   /// If set, trying to add a duplicate value to the vector is treated as an
   /// error, otherwise (the default) it is silently discarded.
   bool          mTreatDuplicatesAsErrors = false;

}; // TypedArg< std::vector< T>>


// inlined methods
// ===============


template< typename T>
   TypedArg< std::vector< T>>::TypedArg( vector_type& dest,
                                         const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
{
   mpCardinality.reset();
} // TypedArg< std::vector< T>>::TypedArg


template< typename T>
   TypedArgBase* TypedArg< std::vector< T>>::setValueMode( ValueMode vm)
{
   if (vm == mValueMode)
      return this;
   if ((vm != ValueMode::optional) || !mClearB4Assign || mDestVar.empty())
      throw std::logic_error( "can only set value mode 'optional' for vector, "
         "and ony if 'clear before assign' is set and the vector is not empty");
   mValueMode = vm;
   return this;
} // TypedArg< std::vector< T>>::setValueMode


template< typename T>
   const std::string TypedArg< std::vector< T>>::varTypeName() const
{
   return type< std::vector< T>>::name();
} // TypedArg< std::vector< T>>::varTypeName


template< typename T> bool TypedArg< std::vector< T>>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArg< std::vector< T>>::hasValue


template< typename T>
   void TypedArg< std::vector< T>>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar.begin(), mDestVar.end());
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArg< std::vector< T>>::printValue


template< typename T>
   TypedArgBase* TypedArg< std::vector< T>>::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArg< std::vector< T>>::setTakesMultiValue


template< typename T>
   TypedArgBase* TypedArg< std::vector< T>>::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArg< std::vector< T>>::setListSep


template< typename T>
   TypedArgBase* TypedArg< std::vector< T>>::setClearBeforeAssign()
{
   mClearB4Assign = true;
   return this;
} // TypedArg< std::vector< T>>::setClearBeforeAssign


template< typename T>
   TypedArgBase* TypedArg< std::vector< T>>::setSortData()
{
   mSortData = true;
   return this;
} // TypedArg< std::vector< T>>::setSortData


template< typename T>
   TypedArgBase*
      TypedArg< std::vector< T>>::setUniqueData( bool duplicates_are_errors)
{
   mUniqueData = true;
   mTreatDuplicatesAsErrors = duplicates_are_errors;
   return this;
} // TypedArg< std::vector< T>>::setUniqueData


template< typename T>
   void TypedArg< std::vector< T>>::dump( std::ostream& os) const
{
   os << "value type '" << type< vector_type>::name()
      << "', destination vector '" << mVarName << "', currently "
      << (mDestVar.empty() ? "no" : std::to_string( mDestVar.size()))
      << " values." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArg< std::vector< T>>::dump


template< typename T>
   void TypedArg< std::vector< T>>::assign( const std::string& value, bool)
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

      auto  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         format( listVal);
      } // end if

      auto const  dest_value = boost::lexical_cast< T>( listVal);
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

      mDestVar.push_back( dest_value);
   } // end for

   if (mSortData)
      std::sort( mDestVar.begin(), mDestVar.end());

} // TypedArg< std::vector< T>>::assign


// Template TypedArg< T[ N]>
// =========================


/// Specialisation of TypedArg<> for values wrapped in an POD array.<br>
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

   /// Returns the name of the type of the destination variable (array of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/array.
   /// @since  1.26.0, 29.04.2019
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.26.0, 29.04.2019
   virtual bool hasValue() const override;

   /// Prints the current values of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the values to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.26.0, 29.04.2019
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For arrays it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.26.0, 29.04.2019
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.26.0, 29.04.2019
   virtual TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type array:<br>
   /// Sort the contents of the array.
   ///
   /// @since  1.26.0, 29.04.2019
   virtual TypedArgBase* setSortData() override;

   /// Special feature for destination variable type array:<br>
   /// Make sure only unique values are stored in the array.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since  1.26.0, 29.04.2019
   virtual TypedArgBase* setUniqueData( bool duplicates_are_errors = false)
      override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.26.0, 29.04.2019
   virtual void dump( std::ostream& os) const override;

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
   virtual void assign( const std::string& value, bool inverted) override;

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

      auto  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         format( listVal);
      } // end if

      auto const  dest_value = boost::lexical_cast< T>( listVal);
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


/// Specialisation of TypedArg<> for values wrapped in an std::array.<br>
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

   /// Returns the name of the type of the destination variable (array of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/array.
   /// @since  1.26.0, 26.04.2019
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.26.0, 26.04.2019
   virtual bool hasValue() const override;

   /// Prints the current values of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the values to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.26.0, 26.04.2019
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For arrays it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.26.0, 26.04.2019
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.26.0, 26.04.2019
   virtual TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type array:<br>
   /// Sort the contents of the array.
   ///
   /// @since  1.26.0, 26.04.2019
   virtual TypedArgBase* setSortData() override;

   /// Special feature for destination variable type array:<br>
   /// Make sure only unique values are stored in the array.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since  1.26.0, 26.04.2019
   virtual TypedArgBase* setUniqueData( bool duplicates_are_errors = false)
      override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.26.0, 26.04.2019
   virtual void dump( std::ostream& os) const override;

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
   virtual void assign( const std::string& value, bool inverted) override;

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


template< typename T, size_t N> bool TypedArg< std::array< T, N>>::hasValue() const
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

      auto  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         format( listVal);
      } // end if

      auto const  dest_value = boost::lexical_cast< T>( listVal);
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


namespace {


// Class TupleElementValueAssign
// =============================


/// Helper class used to assign a value to a tuple element with type
/// conversion.<br>
/// Can be replaced by a lambda, once the decltype works for boost::lexical_cast.
class TupleElementValueAssign
{
public:
   /// Constructor.
   ///
   /// @param[in]  value  The value to assign to the tuple element.
   /// @since  0.11, 04.01.2017
   TupleElementValueAssign( const std::string& value):
      mValue( value)
   {
   } // TupleElementValueAssign::TupleElementValueAssign

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


} // namespace


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

   /// Returns the name of the type of the destination variable, the tuple.
   ///
   /// @return  String with the name of the complete type.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has a value set.
   ///
   /// @return  \c true if the destination variable contains a value.
   /// @since  0.11, 19.12.2016
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Adds the value of the destination variable to the string.
   ///
   /// @param[out]  dest  The string to append the default value to.
   /// @since  0.11, 19.12.2016
   virtual void defaultValue( std::string& dest) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For tuples it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Overload for destination tuple: Format not allowed.
   /// @param[in]  f  Pointer to the format to add, the object is deleted.
   /// @return  Never returns anything.
   /// @throws
   ///    "logic error" when called since setting a format for a tuple is never
   ///    allowed.
   /// @since  1.23.0, 09.04.2019
   virtual TypedArgBase* addFormat( IFormat* f) noexcept( false) override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.11, 04.01.2017
   virtual TypedArgBase* setListSep( char sep) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  0.11, 19.12.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.11, 19.12.2016
   virtual void assign( const std::string& value, bool inverted) override;

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
   throw std::logic_error( "not allowed to add a format for a tuple");
} // TypedArgBase* TypedArg< std::tuple< T...>>::addFormat


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

      const std::string&  listVal( *it);

      check( listVal);

      TupleElementValueAssign  teva( listVal);
      common::tuple_at_index( mNumValuesSet, mDestVar, teva);

#if 0
      // this should work ...
      common::tuple_at_index( mNumValuesSet, mDestVar,
                              [&listVal]( auto& tuple_value)
        {
           tuple_value = boost::lexical_cast< std::decltype( tuple_value)>( listVal);
        });
#endif
      ++mNumValuesSet;
   } // end for
} // TypedArg< std::tuple< T...>>::assign


// Template TypedArg< std::bitset< T>>
// ===================================


/// Specialisation of TypedArg<> for destination value type bitset.
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

   /// Returns the type of the destination variable.
   ///
   /// @return  The name of the destination variable's type.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   /// @return
   ///    \c true if the destination variable contains (at least) one value.
   /// @since  1.4.3, 29.04.2018
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Overloads TypedArgBase::setTakesMultiValue().<br>
   /// For bitsets it is possible/allowed to activate this feature.
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   virtual TypedArgBase* setTakesMultiValue() override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   virtual TypedArgBase* setListSep( char sep) override;

   /// Special feature for destination variable type bitset:<br>
   /// Clear the contents of the bitset before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination bitset that should be overwritten by the argument's values.
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   virtual TypedArgBase* setClearBeforeAssign() override;

   /// Unset the flags (reset in the bitset) when the argument is detected,
   /// instead of setting it (the default).
   ///
   /// @return  Pointer to this object.
   /// @since  1.4.3, 29.04.2018
   virtual TypedArgBase* unsetFlag() override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  1.4.3, 29.04.2018
   virtual void dump( std::ostream& os) const override;

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
   virtual void assign( const std::string& value, bool inverted) override;

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
      << (mDestVar.none() ? "no" : boost::lexical_cast< std::string>( mDestVar.count()))
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

      auto const&  listVal( *it);

      check( listVal);

      if (!mFormats.empty())
      {
         auto  valCopy( listVal);
         format( valCopy);
         auto const  pos = boost::lexical_cast< size_t>( valCopy);
         if (pos >= N)
            throw std::runtime_error( "position " + std::to_string( pos)
               + " is outside the range of the bitset");
         mDestVar[ pos] = !mResetFlags;
      } else
      {
         auto const  pos = boost::lexical_cast< size_t>( listVal);
         if (pos >= N)
            throw std::runtime_error( "position " + std::to_string( pos)
               + " is outside the range of the bitset");
         mDestVar[ pos] = !mResetFlags;
      } // end if
   } // end for
} // TypedArg< std::bitset< N>>::assign


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

   /// Returns the name of the type of the destination variable (ValueFilter of
   /// something).
   ///
   /// @return  The name of the type of the destination variable/vector.
   /// @since  1.31.0, 17.10.2019
   virtual const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one filter set.
   ///
   /// @return
   ///    \c true if the destination variable contains (at least) one filter.
   /// @since  1.31.0, 17.10.2019
   virtual bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   ///
   /// @param[out]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since  1.31.0, 17.10.2019
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Always throws for this class.
   ///
   /// @param[in]  c  Check object is deleted.
   /// @return  Nothing.
   /// @throw
   ///    std::logic_error because checking a value filter string is not
   ///    supported.
   /// @since  1.31.0, 18.10.2019
   virtual TypedArgBase* addCheck( ICheck* c) noexcept( false) override;

   /// Always throws for this class.
   ///
   /// @param[in]  f  Format object is deleted.
   /// @return  Nothing.
   /// @throw
   ///    std::logic_error because formatting a value filter string is not
   ///    supported.
   /// @since  1.31.0, 18.10.2019
   virtual TypedArgBase* addFormat( IFormat* f) noexcept( false) override;

protected:
   /// Used for printing an argument and its destination variable.
   ///
   /// @param[out]  os  The stream to print to.
   /// @since  1.31.0, 17.10.2019
   virtual void dump( std::ostream& os) const override;

   /// Parses the given string, creates and stores the filters defined therein
   /// in the destination value fiter.
   ///
   /// @param[in]  value
   ///    The string with the filter definitions.
   /// @param[in]  inverted
   ///    Not supported for this argument.
   /// @since  1.31.0, 17.10.2019
   virtual void assign( const std::string& value, bool inverted) override;

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


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_HPP


// =====  END OF typed_arg.hpp  =====

