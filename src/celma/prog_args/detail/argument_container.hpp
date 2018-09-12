
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
/// See documentation of class celma::prog_args::detail::ArgumentContainer.


#ifndef CELMA_PROG_ARGS_DETAIL_ARGUMENT_CONTAINER_HPP
#define CELMA_PROG_ARGS_DETAIL_ARGUMENT_CONTAINER_HPP


#include <iosfwd>
#include <string>
#include <memory>
#include "celma/prog_args/detail/typed_arg_base.hpp"
#include "celma/prog_args/detail/storage.hpp"
#include "celma/prog_args/summary_options.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Extracted from ArgumentHandler: Store an argument which may use the short
/// argument format (character), the long format (string/name) or name.
///
/// @since  0.15.0, 05.07.2017  (use container Storage)
/// @since  0.2, 10.04.2016
class ArgumentContainer
{
public:
   /// Constructor.
   ///
   /// @param[in]  stores_sub_args
   ///    Set if the object is used to store sub-arguments, i.e. arguments that
   ///    are related to another (parent) argument.
   /// @since
   ///    1.8.0, 12.07.2018  (parameter stores_sub_args added)
   /// @since
   ///    0.2, 10.04.2016
   ArgumentContainer( bool stores_sub_args = false);

   /// Adds a new argument.
   /// @param[in]  argHandler  The object used to handle this argument.
   /// @param[in]  key         The argument character, string or both.
   /// @since  0.2, 10.04.2016
   void addArgument( TypedArgBase* argHandler, const ArgumentKey& key);

   /// After argument evaluating: Check that all mandatory arguments were set,
   /// and check that the cardinality requirements (if set) were met.
   /// @since  0.2, 10.04.2016
   void checkMandatoryCardinality() const;

   /// Check this object and \a otherAH don't share any arguments.
   /// @param[in]  ownName    The symbolic name of this argument group.
   /// @param[in]  otherName  The symbolic name of the other object's argument
   ///                        group.
   /// @param[in]  otherAH    The other object to check the argument against.
   /// @since  0.2, 10.04.2016
   void checkArgMix( const std::string& ownName, const std::string& otherName,
                     const ArgumentContainer& otherAH) const;

   /// Searches if this short or long argument is defined.<br>
   /// If a long argument name was used, also search for partial matches.
   /// @param[in]  key  The short and/or long argument name to check.
   /// @return  Pointer to the argument handler object if the argument is
   ///          defined, NULL otherwise.
   /// @since  0.15.0, 12.07.2017  (take ArgumentKey as parameter)
   /// @since  0.2, 10.04.2016
   TypedArgBase* findArg( const ArgumentKey& key) const;

   /// Specifies the line length to use when printing the usage.<br>
   /// Used when this container is used to store te sub-group arguments.
   /// @param[in]  useLen  The new line length to use.<br>
   ///                     The value must be in the range 60 <= useLen < 240.
   /// @since  0.2, 10.04.2016
   void setUsageLineLength( int useLen);

   /// Returns if the class contains at least one argument.
   /// @return  \c true if the class doesn't contain any argument(s).
   /// @since  0.2, 10.04.2016
   bool empty() const;

   /// After the arguments from the command line were evaluated, prints the list
   /// of arguments that were used and the values that were aet.
   /// 
   /// @param[in]  contents_set
   ///    Set of flags that specify the contents of the summary to print.
   /// @param[out]  os
   ///    The stream to write the summary to.
   /// @param[in]   arg_prefix
   ///    Specifies the prefix for the arguments of this handler. Used when the
   ///    argument handler handles the arguments of a sub-group.
   /// @since  1.8.0, 03.07.2018
   void printSummary( sumoptset_t contents_set, std::ostream& os,
      const char* arg_prefix) const;

   /// Prints the contents of the container == list of all arguments.
   /// @param[out]  os  The stream to write to.
   /// @param[in]   ac  The object to dump the data of.
   /// @return  The stream as passed in.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os,
                                     const ArgumentContainer& ac);

private:
   /// Store shared pointers to the handler objects.
   using shared_handler_t = std::shared_ptr< TypedArgBase>;

   /// All arguments set.
   Storage< shared_handler_t>  mArguments;
   /// Flag, set by the constructor, specifies if this container stores sub-
   /// arguments or not.
   const bool  mStoreSubArgs;

}; // ArgumentContainer


// inlined methods
// ===============


inline bool ArgumentContainer::empty() const
{
   return mArguments.empty();
} // ArgumentContainer::empty


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_CONTAINER_HPP


// =====  END OF argument_container.hpp  =====

