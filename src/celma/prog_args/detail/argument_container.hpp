
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
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
#include <map>
#include <string>
#include <memory>
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Extracted from ArgumentHandler: Store an argument which may use the short
/// argument format (character), the long format (string/name) or name.
/// @since  0.2, 10.04.2016
class ArgumentContainer
{
public:
   /// Constructor.
   /// @since  0.2, 10.04.2016
   ArgumentContainer();

   /// Adds a new argument.
   /// @param[in]  argHandler  The object used to handle this argument.
   /// @param[in]  argSpec     The argument character, string or both.
   /// @since  0.2, 10.04.2016
   void addArgument( TypedArgBase* argHandler, const std::string& argSpec);

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

   /// Searches if this single character argument is defined.
   /// @param[in]  charArg  The argument character to check.
   /// @return  Pointer to the argument handler object if the argument is
   ///          defined, NULL otherwise.
   /// @since  0.2, 10.04.2016
   TypedArgBase* findArg( char charArg) const;

   /// Searches if this argument name is defined.
   /// @param[in]  longArg  The argument name to check.
   /// @return  Pointer to the argument handler object if the argument is
   ///          defined, NULL otherwise.
   /// @since  0.2, 10.04.2016
   TypedArgBase* findArg( const std::string& longArg) const;

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

   /// Prints the contents of the container == list of all arguments.
   /// @param[out]  os  The stream to write to.
   /// @param[in]   ac  The object to dump the data of.
   /// @return  The stream as passed in.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const ArgumentContainer& ac);

private:
   /// Store shared pointers to the handler objects.
   typedef std::shared_ptr< TypedArgBase>  SharedArg;

   /// Used to store the single character arguments and the corresponding
   /// handler objects.
   typedef std::map< char, SharedArg>   CharArgCont;
   /// Used to store the multi character (long) arguments and the corresponding
   /// handler objects.
   typedef std::map< std::string, SharedArg>  LongArgCont;

   /// Splits the argument specifyer string into single and long argument and
   /// stores it accordingly.
   /// @param[in]  argSpec  The string with the short, long or both arguments.
   /// @param[in]  sa       The object to handle these argument(s).
   /// @since  0.2, 10.04.2016
   void splitArgSpec( const std::string& argSpec, const SharedArg& sa);

   /// Adds an object to either the single or multi character containers.
   /// @param[in]  singleArgSpec  The string with the single or multi-character
   ///                            argument.
   /// @param[in]  sa             The object to handle this argument.
   /// @since  0.2, 10.04.2016
   void addArgObj( const std::string& singleArgSpec, const SharedArg& sa);

   /// Single character arguments.
   CharArgCont  mCharArgs;
   /// Multi-character (long) arguments.
   LongArgCont  mLongArgs;

}; // ArgumentContainer


// inlined methods
// ===============


inline bool ArgumentContainer::empty() const
{
   return mCharArgs.empty() && mLongArgs.empty();
} // end ArgumentContainer::empty


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARGUMENT_CONTAINER_HPP


// =========================  END OF argument_container.hpp  =========================

