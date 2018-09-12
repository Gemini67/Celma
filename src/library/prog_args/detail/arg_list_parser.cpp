
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ArgListParser.


// module header file include
#include "celma/prog_args/detail/arg_list_parser.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
///
/// @param[in]  argc    Number of argument strings in the array.
/// @param[in]  argv[]  Array of argument strings.
/// @since  0.2, 09.04.2016
ArgListParser::ArgListParser( int argc, char* argv[]):
   mArgCount( argc),
   mpArgV( argv)
{
} // ArgListParser::ArgListParser



/// Returns the iterator pointing to the first argument.
///
/// @return  Iterator pointing to the first argument.
/// @since  0.2, 09.04.2016
ArgListParser::const_iterator ArgListParser::begin() const
{
   return const_iterator( *this);
} // ArgListParser::begin



/// Returns the iterator pointing behind the last argument.
///
/// @return  Iterator pointing behind the last argument.
/// @since  0.2, 09.04.2016
ArgListParser::const_iterator ArgListParser::end() const
{
   return const_iterator( *this, true);
} // ArgListParser::end



/// Returns the iterator pointing to the first argument.
///
/// @return  Iterator pointing to the first argument.
/// @since  0.2, 09.04.2016
ArgListParser::const_iterator ArgListParser::cbegin() const
{
   return const_iterator( *this);
} // ArgListParser::cbegin



/// Returns the iterator pointing behind the last argument.
///
/// @return  Iterator pointing behind the last argument.
/// @since  0.2, 09.04.2016
ArgListParser::const_iterator ArgListParser::cend() const
{
   return const_iterator( *this, true);
} // ArgListParser::cend



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF arg_list_parser.cpp  =====

