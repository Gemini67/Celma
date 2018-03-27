
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
/// See documentation of template functions celma::prog_args::destination.<br>
/// Instead of having multiple addArgument() methods in the
/// celma::prog_args::Handler class, the destination functions are provided to
/// create the corresponding typed arg classes/objects.


#ifndef CELMA_PROG_ARGS_DESTINATION_HPP
#define CELMA_PROG_ARGS_DESTINATION_HPP


#include "celma/common/check_assign.hpp"
#include "celma/common/range_dest.hpp"
#include "celma/prog_args/detail/arg_handler_callable.hpp"
#include "celma/prog_args/detail/typed_arg_callable.hpp"
#include "celma/prog_args/detail/typed_arg_callable_value.hpp"
#include "celma/prog_args/detail/typed_arg.hpp"
#include "celma/prog_args/detail/typed_arg_pair.hpp"
#include "celma/prog_args/detail/typed_arg_range.hpp"
#include "celma/prog_args/detail/typed_arg_value.hpp"


namespace celma { namespace prog_args {


/// Returns the typed argument object corresponding to the type of the
/// destination variable.
/// @tparam  T  The type of the destination variable.
/// @param[in]  dest_var  The destination variable of an argument.
/// @param[in]  vname     The name of the destination variable.
/// @return  The typed arg object for the type of the \a dest_var.
/// @since  0.16.0, 09.11.2017
template< typename T>
   detail::TypedArgBase* destination( T& dest_var, const std::string vname)
{
   return new detail::TypedArg< T>( dest_var, vname);
} // destination


/// Returns the typed argument object corresponding to the type of the
/// destination variable.
/// @tparam  T  The type of the destination variable.
/// @param[in]  dest_var  The destination variable of an argument.
/// @param[in]  vname     The name of the destination variable.
/// @param[in]  value     The value to set on the destination variable when the
///                       argument is used.
/// @return  The typed arg object for the type of the \a dest_var.
/// @since  1.1.0, 15.11.2017
template< typename T>
   detail::TypedArgBase* destination( T& dest_var, const std::string vname,
      const T& value)
{
   return new detail::TypedArgValue< T>( dest_var, vname, value);
} // destination


/// Overload for creating the typed argument object for a pair of variables.
/// @tparam  T1  The type of the first destination variable.
/// @tparam  T2  The type of the second destination variable.
/// @param[in]  dest_var1  The first destination variable for the value of the
///                        argument.
/// @param[in]  vname1     The name of the first destination variable.
/// @param[in]  dest_var2  The second variable for the argument.
/// @param[in]  vname2     The name of the second variable.
/// @param[in]  value2     The value to assign to the second variable.
/// @return  The typed argument object for the pair of variables.
/// @since  0.16.0, 10.11.2017
template< typename T1, typename T2>
   detail::TypedArgBase*
      destination( T1& dest_var1, const std::string vname1,
                   T2& dest_var2, const std::string vname2, const T2& value2)
{
   return new detail::TypedArgPair< T1, T2>( dest_var1, vname1,
                                             dest_var2, vname2, value2);
} // destination


/// Overload for creating a typed argument object to handle a range string.
/// @tparam  T  The type of the values to create by the range string.
/// @tparam  C  The type of the container to store the values created by the
///             range.
/// @param[in]  dest   The object that takes the range string and stores the
///                    values in the container.
/// @param[in]  vname  The name of the destination variable.
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
/// @param[in]  fun    The function to call for this argument.<br>
///                    Use the macros DEST_FUNCTION or DEST_METHOD to easily
///                    set up the correct call.
/// @param[in]  fname  The name of the function to call.<br>
///                    Used for error reporting.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.16.0, 10.11.2017
inline detail::TypedArgBase* destination( detail::ArgHandlerCallable fun,
                                          const std::string fname)
{
   return new detail::TypedArgCallable( fun, fname);
} // destination


/// Overload for creating a typed argument object to handle a callable that may
/// accept or require a value parameter.
/// @param[in]  fun          The function to call for this argument.<br>
///                          This function must take an std::string as
///                          parameter.<br>
///                          Use the macros DEST_FUNCTION_VALUE or
///                          DEST_METHOD_VALUE to easily set up the correct
///                          call.
/// @param[in]  fname        The name of the function to call.<br>
///                          Used for error reporting.
/// @param[in]  takes_value  Dummy parameter used to distinguish from the
///                          non-value variant.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.16.0, 10.11.2017
inline detail::TypedArgBase* destination( detail::ArgHandlerCallableValue fun,
                                          const std::string fname,
                                          bool)
{
   return new detail::TypedArgCallableValue( fun, fname);
} // destination


} // namespace prog_args
} // namespace celma


// macros
// ======


/// Macro used to call the celma::prog_args::destination() function for a single
/// destination variable.
/// @param  n  The destination variable.
/// @since  0.16.0, 09.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define DEST_VAR( n)  celma::prog_args::destination( n, #n)

/// Macro used to call the celma::prog_args::destination() function for a single
/// destination variable, where the value to set is also specified.
/// @param  n  The destination variable.
/// @param  v  The value to set on the destinaion variable when the argument is
///            used.
/// @since  1.1.0, 15.11.2017
#define DEST_VAR_VALUE( n, v)  celma::prog_args::destination( n, #n, v)

/// Macro used to call the celma::prog_args::destination() function for a pair
/// of destination variables.
/// @param  dv1   The first destination variable.
/// @param  dv2   The second destination variable.
/// @param  val2  The value to set on the second destination variable when the
///               argument is used.
/// @since  0.16.0, 10.11.2017
#define DEST_PAIR( dv1, dv2, val2)  \
   celma::prog_args::destination( dv1, #dv1, dv2, #dv2, val2)

/// Macro used to call the celma::prog_args::destination() function for a
/// destination variable that accepts a range string as value.
/// @param  n  The destination variable.
/// @param  t  The value type of the destination variable.
/// @param  c  The type of the container/the destination variable.
/// @todo  Try to change this (and the class RangeDest?) so that the type of
///        the destination variable (container type) does not need to be
///        set separately.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define DEST_RANGE( n, t, c)  \
   celma::prog_args::destination( \
      celma::common::RangeDest< t, c < t > >( n), #n)

/// Macro used to call the celma::prog_args::destination() function for a
/// destination variable that accepts a range string as value and stores the
/// resulting values in a bitset.
/// @param  n  The destination variable.
/// @param  s  The size of the bitset.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define DEST_BITSET( n, s)  \
   celma::prog_args::destination( \
      celma::common::RangeDest< size_t, std::bitset< s> >( n), #n)

/// Macro used to call the celma::prog_args::destination() function for a
/// function that takes no value as argument handler.
/// @param[in]  f  The name of the function.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION( f)  celma::prog_args::destination( std::bind( &f), #f)

/// Macro used to call the celma::prog_args::destination() function for a
/// function that accepts a value.
/// @param[in]  f  The name of the function.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION_VALUE( f)  \
   celma::prog_args::destination( \
      std::bind( &f, std::placeholders::_1), #f, true)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) of the current object that takes no value.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD( c, m)  \
   celma::prog_args::destination( std::bind( & c :: m, this), #c "::" #m)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) that takes no value.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @param[in]  o  The object to call the method for.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_METHOD( c, m, o)  \
   celma::prog_args::destination( std::bind( & c :: m, &o), #c "::" #m)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) of the current object, that accepts a value.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD_VALUE( c, m)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, this, std::placeholders::_1), #c "::" #m, \
         true)

/// Macro used to call the celma::prog_args::destination() function for a
/// method (class member function) that accepts a value.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @param[in]  o  The object to call the method for.
/// @since  0.16.0, 10.11.2017  (adapted for new destination concept)
/// @since  0.2, 10.04.2016
#define  DEST_METHOD_VALUE( c, m, o)  \
   celma::prog_args::destination( \
      std::bind( & c :: m, &o, std::placeholders::_1), #c "::" #m, \
         true)


#endif   // CELMA_PROG_ARGS_DESTINATION_HPP


// =========================  END OF destination.hpp  =========================

