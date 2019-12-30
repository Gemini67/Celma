
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions celma::prog_args::destination.<br>
/// Instead of having multiple addArgument() methods in the
/// celma::prog_args::Handler class, the destination functions are provided to
/// create the corresponding typed arg classes/objects.<br>
/// List of the macros provided by this module:
/// - \c DEST_VAR: Destination is a 'normal' int, string etc., but also a
///   bitset, an array or a vector.
/// - \c DEST_VAR_VALUE: Value for the destination variable is provided with
///   the argument, not on the command line.
/// - \c DEST_PAIR: Pair of destination variables, the value for the second
///   variable is specified with the argument.
/// - \c DEST_RANGE: The argument value is a range string, whose values are
///   stored in the destination variable.
/// - \c DEST_RANGE_BITSET: Again, the argument is a range string, but here the
///   corresponding bits are set in the bitset.
/// - \c DEST_FUNCTION: The specified function is called when the argument is
///   used. The function does not accept a valur.
/// - \c DEST_FUNCTION_VALUE: Here also the specified function is called when
///   the argument is used, but this time the function requires a value.
/// - \c DEST_MEMBER_METHOD: Calls a member function of the current object.
/// - \c DEST_METHOD: Calls a member function of the given object.
/// - \c DEST_MEMBER_METHOD_VALUE: Calls the member function of the current
///   object. Passes the value from the cmmand line.
/// - \c DEST_METHOD_VALUE: Calls the member function of the given object.
///   Passes the value from the command line.


#ifndef CELMA_PROG_ARGS_DESTINATION_HPP
#define CELMA_PROG_ARGS_DESTINATION_HPP


#include <type_traits>
#include "celma/common/range_dest.hpp"
#include "celma/prog_args/detail/arg_handler_callable.hpp"
#include "celma/prog_args/detail/container_adapter.hpp"
#include "celma/prog_args/detail/typed_arg_callable.hpp"
#include "celma/prog_args/detail/typed_arg_callable_value.hpp"
#include "celma/prog_args/detail/typed_arg.hpp"
#include "celma/prog_args/detail/typed_arg_pair.hpp"
#include "celma/prog_args/detail/typed_arg_range.hpp"
#include "celma/prog_args/detail/typed_arg_value.hpp"


namespace celma { namespace prog_args {


/// Returns the typed argument object corresponding to the type of the
/// destination variable, which may be a simple POD, a std::string, but also a
/// std::vector or a std::bitset.
/// Additional precaution was taken to make sure that destinations of type
/// container are not handled here.
///
/// @tparam  T  The type of the destination variable.
/// @param[in]  dest_var
///    The destination variable of an argument.
/// @param[in]  vname
///    The name of the destination variable.
/// @return  The typed arg object for the type of the \a dest_var.
/// @since  0.16.0, 09.11.2017
template< typename T>
   typename std::enable_if< !detail::ContainerAdapter< T>::HasAdapter,
      detail::TypedArgBase*>::type
   destination( T& dest_var, const std::string vname)
{
   return new detail::TypedArg< T>( dest_var, vname);
} // destination


/// Returns the typed argument object corresponding to the type of the
/// destination variable.
/// This overload handles the case when the value to set is given when the
/// argument is defined.
///
/// @tparam  T  The type of the destination variable.
/// @param[in]  dest_var
///    The destination variable of an argument.
/// @param[in]  vname
///    The name of the destination variable.
/// @param[in]  value
///    The value to set on the destination variable when the argument is used.
/// @return  The typed arg object for the type of the \a dest_var.
/// @since  1.1.0, 15.11.2017
template< typename T>
   detail::TypedArgBase* destination( T& dest_var, const std::string vname,
      const T& value)
{
   return new detail::TypedArgValue< T>( dest_var, vname, value);
} // destination


/// Returns the typed argument object corresponding to the type of the
/// destination variable.
/// This overload handles the case when the destination variable is a
/// container.<br>
/// Additional precaution was taken to make sure that this overload is only
/// chosen for supported container types.
/// 
/// @tparam  T  The type of the destination variable, container of something.
/// @param[in]  dest_cont
///    The destination variable/container, in which the values from the command
///    line should be stored.
/// @param[in]  cname
///    The name of the variable/container.
/// @return  The typed arg object for the type of the \a dest_cont.
/// @since  x.y.z, 22.11.2019
template< typename T>
   typename std::enable_if< detail::ContainerAdapter< T>::HasAdapter,
      detail::TypedArgBase*>::type
   destination( T& dest_cont, const std::string cname)
{
   return new detail::TypedArg< detail::ContainerAdapter< T>>(
     detail::ContainerAdapter< T>( dest_cont), cname);
} // destination


/// Overload for creating the typed argument object for a pair of variables.
/// This ovrload is used when the first destination variable is a single-value
/// type like int, std::string etc.
///
/// @tparam  T1
///    The type of the first destination variable.
/// @tparam  T2
///    The type of the second destination variable.
/// @param[in]  dest_var1
///    The first destination variable for the value of the argument.
/// @param[in]  vname1
///    The name of the first destination variable.
/// @param[in]  dest_var2
///    The second variable for the argument.
/// @param[in]  vname2
///    The name of the second variable.
/// @param[in]  value2
///    The value to assign to the second variable.
/// @return  The typed argument object for the pair of variables.
/// @since  0.16.0, 10.11.2017
template< typename T1, typename T2>
   typename std::enable_if< !detail::ContainerAdapter< T1>::HasAdapter,
      detail::TypedArgBase*>::type
   destination( T1& dest_var1, const std::string vname1,
      T2& dest_var2, const std::string vname2, const T2& value2)
{
   return new detail::TypedArgPair< T1, T2>( dest_var1, vname1,
      dest_var2, vname2, value2);
} // destination


/// Overload for creating the typed argument object for a pair of variables.
/// This ovrload is used when the first destination variable is a container.
///
/// @tparam  T1
///    The type of the first destination variable.
/// @tparam  T2
///    The type of the second destination variable.
/// @param[in]  dest_var1
///    The first destination variable for the value of the argument.
/// @param[in]  vname1
///    The name of the first destination variable.
/// @param[in]  dest_var2
///    The second variable for the argument.
/// @param[in]  vname2
///    The name of the second variable.
/// @param[in]  value2
///    The value to assign to the second variable.
/// @return  The typed argument object for the pair of variables.
/// @since  x.y.z, 28.11.2019
template< typename T1, typename T2>
   typename std::enable_if< detail::ContainerAdapter< T1>::HasAdapter,
      detail::TypedArgBase*>::type
   destination( T1& dest_var1, const std::string vname1,
      T2& dest_var2, const std::string vname2, const T2& value2)
{
   detail::ContainerAdapter< T1>  wrapper( dest_var1);
   return new detail::TypedArgPair< detail::ContainerAdapter< T1>, T2>(
      wrapper, vname1, dest_var2, vname2, value2);
} // destination


/// Overload for creating a typed argument object to handle a range string.
///
/// @tparam  T
///    The type of the values to create by the range string.
/// @tparam  C
///    The type of the container to store the values created by the range.
/// @param[in]  dest
///    The object that takes the range string and stores the values in the
///    container.
/// @param[in]  vname
///    The name of the destination variable.
/// @return  The typed argument object for range strings.
/// @since  0.16.0, 10.11.2017
template< typename T, typename C>
   detail::TypedArgBase*
      destination( const common::RangeDest< T, C>& dest,
         const std::string vname)
{
   return new detail::TypedArgRange< T, C>( dest, vname);
} // destination


/// Overload for creating a typed argument object to handle a callable.
///
/// @param[in]  fun
///    The function to call for this argument.<br>
///    Use the macros DEST_FUNCTION or DEST_METHOD to easily set up the correct
///    call.
/// @param[in]  fname
///    The name of the function to call.<br>
///    Used for error reporting.
/// @return
///    The object managing this argument, may be used to apply further settings.
/// @since  0.16.0, 10.11.2017
inline detail::TypedArgBase* destination( detail::ArgHandlerCallable fun,
   const std::string fname)
{
   return new detail::TypedArgCallable( fun, fname);
} // destination


/// Overload for creating a typed argument object to handle a callable that may
/// accept or require a value parameter.
///
/// @param[in]  fun
///    The function to call for this argument.<br>
///    This function must take an std::string as parameter.<br>
///    Use the macros DEST_FUNCTION_VALUE or DEST_METHOD_VALUE to easily set up
///    the correct call.
/// @param[in]  fname
///    The name of the function to call.<br>
///    Used for error reporting.
/// @param[in]  takes_value
///    Dummy parameter used to distinguish from the non-value variant.
/// @return
///    The object managing this argument, may be used to apply further settings.
/// @since  0.16.0, 10.11.2017
inline detail::TypedArgBase* destination( detail::ArgHandlerCallableValue fun,
   const std::string fname, bool)
{
   return new detail::TypedArgCallableValue( fun, fname);
} // destination


} // namespace prog_args
} // namespace celma


// macros
// ======


/// Macro used to call the celma::prog_args::destination() function for a single
/// destination variable.
///
/// @param  n  The destination variable.
/// @since  0.16.0, 09.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_VAR( n)  celma::prog_args::destination( n, #n)

/// Macro used to call the celma::prog_args::destination() function for a single
/// destination variable, where the value to set is also specified.
/// @param  n
///
///    The destination variable.
/// @param  v
///    The value to set on the destinaion variable when the argument is used.
/// @since  1.1.0, 15.11.2017
#define  DEST_VAR_VALUE( n, v)  celma::prog_args::destination( n, #n, v)

/// Macro used to call the celma::prog_args::destination() function for a pair
/// of destination variables.
///
/// @param  dv1
///    The first destination variable.
/// @param  dv2
///    The second destination variable.
/// @param  val2
///    The value to set on the second destination variable when the argument is
///    used.
/// @since  0.16.0, 10.11.2017
#define  DEST_PAIR( dv1, dv2, val2)  \
   celma::prog_args::destination( dv1, #dv1, dv2, #dv2, val2)

/// Macro used to call the celma::prog_args::destination() function for a
/// destination variable that accepts a range string as value.
///
/// @param  n
///    The destination variable.
/// @param  t
///    The value type of the destination variable.
/// @param  c
///    The type of the container/the destination variable.
/// @todo  Try to change this (and the class RangeDest?) so that the type of
///        the destination variable (container type) does not need to be
///        set separately.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_RANGE( n, t, c)  \
   celma::prog_args::destination( \
      celma::common::RangeDest< t, c < t > >( n), #n)

/// Macro used to call the celma::prog_args::destination() function for a
/// destination variable that accepts a range string as value and stores the
/// resulting values in a bitset.
///
/// @param  n
///    The destination variable.
/// @param  s
///    The size of the bitset.
/// @since  1.8.0, 10.07.2018
///    (renamed from DEST_BITSET)
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_RANGE_BITSET( n, s)  \
   celma::prog_args::destination( \
      celma::common::RangeDest< size_t, std::bitset< s> >( n), #n)

/// Macro used to call the celma::prog_args::destination() function for a
/// function that takes no value as argument handler.
///
/// @param  f  The name of the function.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION( f)  \
   celma::prog_args::destination( std::bind( &f, std::placeholders::_1), #f)

/// Macro used to call the celma::prog_args::destination() function for a
/// function that accepts a value.
///
/// @param  f  The name of the function.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION_VALUE( f)  \
   celma::prog_args::destination( \
      std::bind( &f, std::placeholders::_1, std::placeholders::_2), #f, true)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) of the current object that takes no value.
///
/// @param  c
///    The name of the class.
/// @param  m  The name of the method.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD( c, m)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, this, std::placeholders::_1), #c "::" #m)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) that takes no value.
///
/// @param  c
///    The name of the class.
/// @param  m
///    The name of the method.
/// @param  o
///    The object to call the method for.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_METHOD( c, m, o)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, &o, std::placeholders::_1), #c "::" #m)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) of the current object, that accepts a value.
///
/// @param  c
///    The name of the class.
/// @param  m
///    The name of the method.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD_VALUE( c, m)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, this, std::placeholders::_1, std::placeholders::_2), \
         #c "::" #m, true)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) that accepts a value.
///
/// @param  c
///    The name of the class.
/// @param  m
///    The name of the method.
/// @param  o
///    The object to call the method for.
/// @since  0.16.0, 10.11.2017
///    (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_METHOD_VALUE( c, m, o)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, &o, std::placeholders::_1, std::placeholders::_2), \
         #c "::" #m, true)


#endif   // CELMA_PROG_ARGS_DESTINATION_HPP


// =====  END OF destination.hpp  =====

