
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
/// See documentation of template celma::prog_args::detail::TypedArgRange.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_RANGE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_RANGE_HPP


#include <iostream>
#include <boost/lexical_cast.hpp>
#include "celma/common/range_dest.hpp"
#include "celma/common/range_string.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Helper class to store a destination variable that is a container in which a
/// range of values can be stored.
///
/// @tparam  T  The type of the value(s) to be stored in the container.
/// @tparam  C  The type of the container to store the values in.
/// @since  0.2, 10.04.2016
template< typename T, typename C> class TypedArgRange: public TypedArgBase
{
public:
   /// The type of the destination variable.
   using dest_type = common::RangeDest< T, C>;

   /// Constructor.
   /// @param[in]  dest   The destination variable to store the values in.
   /// @param[in]  vname  The name of the destination variable to store the
   ///                       value in.
   /// @since  0.16.0, 13.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArgRange( const dest_type& dest, const std::string& vname);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   virtual ~TypedArgRange() = default;

   /// Returns the name of the type of the destination container.
   ///
   /// @return  The destination container's type name.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Returns if the destination has (at least) one value set.
   /// @return  \c true if the destination variable contains (at least) one
   ///          value, \c false otherwise.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 05.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Adding checks is not allowed for a range.
   ///
   /// @param[in]  c  Pointer to the check to add, is deleted.
   /// @return  Nothing, always throws.
   /// @throw  std::logic_error since checks are not allowed for ranges.
   /// @since  0.2, 10.04.2016
   TypedArgBase* addCheck( ICheck* c) noexcept( false) override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Ignored.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   void assign( const std::string& value, bool inverted) override;

   /// Actually evaluates the range string.
   /// @param[in]  value  The value string to evaluate.
   /// @since  0.2, 10.04.2016
   void evalRange( const std::string& value);

   /// Copy of the RangeDest object which contains a reference of the final
   /// destination variable to store the value(s) in.
   dest_type  mDestVar;

}; // TypedArgRange< T, C>


// inlined methods
// ===============


template< typename T, typename C>
   TypedArgRange< T, C>::TypedArgRange( const dest_type& dest,
                                        const std::string& vname):
      TypedArgBase( vname, ValueMode::required, false),
      mDestVar( dest)
{
} // TypedArgRange< T, C>::TypedArgRange


template< typename T, typename C>
   const std::string TypedArgRange< T, C>::varTypeName() const
{
   return type< C>::name();
} // TypedArgRange< T, C>::varTypeName


template< typename T, typename C> bool TypedArgRange< T, C>::hasValue() const
{
   return !mDestVar.empty();
} // TypedArgRange< T, C>::hasValue


template< typename T, typename C>
   void TypedArgRange< T, C>::printValue( std::ostream& os,
      bool print_type) const
{
   os << format::toString( mDestVar);
   if (print_type)
      os << " [" << varTypeName() << "]";
} // TypedArgRange< T, C>::printValue


template< typename T, typename C> TypedArgBase*
   TypedArgRange< T, C>::addCheck( ICheck* c) noexcept( false)
{
   delete c;
   throw std::logic_error( "cannot add value-check to destination type 'range'");
} // TypedArgRange< T, C>::addCheck


template< typename T, typename C>
   void TypedArgRange< T, C>::dump( std::ostream& os) const
{
   os << "stores value(s) with type '" << type< T>::name()
      << "' in range-container '" << mVarName << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgRange< T, C>::dump


template< typename T, typename C>
   void TypedArgRange< T, C>::assign( const std::string& value, bool)
{
   if (!mFormats.empty())
   {
      std::string  valCopy( value);
      format( valCopy);
      evalRange( valCopy);
   } else
   {
      evalRange( value);
   } // end if
} // TypedArgRange< T, C>::assign


template< typename T, typename C>
   void TypedArgRange< T, C>::evalRange( const std::string& value)
{

   common::RangeString< T>  rs( value);
   for (auto cit = rs.cbegin(); cit != rs.cend(); ++cit)
   {
      mDestVar.set( boost::lexical_cast< T>( cit));
   } // end for

} // TypedArgRange< T, C>::evalRange


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_RANGE_HPP


// =====  END OF typed_arg_range.hpp  =====

