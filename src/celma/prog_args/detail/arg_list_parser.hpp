
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


#ifndef CELMA_PROG_ARGS_DETAIL_ARG_LIST_PARSER_HPP
#define CELMA_PROG_ARGS_DETAIL_ARG_LIST_PARSER_HPP


#include "celma/prog_args/detail/arg_list_iterator.hpp"
#include "celma/prog_args/detail/arg_list_element.hpp"


namespace celma { namespace prog_args { namespace detail {


/// This class allows to handle an argument list one element after the other.<br>
/// Here we don't know which arguments are mandatory, or if a value belongs to
/// the previous argument or if it is a positional value. We just parse the
/// argument list, separate groups of multiple single character arguments and
/// separate long arguments from their values.
///
/// @since  0.2, 09.04.2016
class ArgListParser
{
public:
   /// Constructor.
   /// @param[in]  argc    Number of argument strings in the array.
   /// @param[in]  argv[]  Array of argument strings.
   /// @since  0.2, 09.04.2016
   ArgListParser( int argc, char* argv[]);

   /// Returns the number of argument strings (as passed to the constructor).
   /// @return  Number of argument strings.
   /// @since  0.2, 09.04.2016
   int argCount() const;

   /// Returns pointer to the array of argument strings (as passed to the
   /// constructor).
   /// @return  Pointer to the beginning of the array of argument strings.
   /// @since  0.2, 09.04.2016
   char** argVector() const;

   /// The type of the iterator.
   using const_iterator = ArgListIterator< ArgListParser, ArgListElement>;

   /// Returns the iterator pointing to the first argument.
   /// @return  Iterator pointing to the first argument.
   /// @since  0.2, 09.04.2016
   const_iterator begin() const;

   /// Returns the iterator pointing behind the last argument.
   /// @return  Iterator pointing behind the last argument.
   /// @since  0.2, 09.04.2016
   const_iterator end() const;

   /// Returns the iterator pointing to the first argument.
   /// @return  Iterator pointing to the first argument.
   /// @since  0.2, 09.04.2016
   const_iterator cbegin() const;

   /// Returns the iterator pointing behind the last argument.
   /// @return  Iterator pointing behind the last argument.
   /// @since  0.2, 09.04.2016
   const_iterator cend() const;

private:
   /// Number of argument strings.
   int     mArgCount;
   /// Array of argument strings.
   char**  mpArgV;   

}; // ArgListParser


// inlined methods
// ===============


inline int ArgListParser::argCount() const
{
   return mArgCount;
} // end ArgListParser::argCount


inline char** ArgListParser::argVector() const
{
   return mpArgV;
} // end ArgListParser::argVector


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARG_LIST_PARSER_HPP


// =====  END OF arg_list_parser.hpp  =====

