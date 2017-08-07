
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ArgumentContainer.


// module header file include
#include "celma/prog_args/detail/argument_container.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/format/to_string.hpp"
#include "celma/prog_args/handler.hpp"


using std::endl;
using std::invalid_argument;
using std::runtime_error;
using std::string;


namespace celma { namespace prog_args { namespace detail {


/// Constructor.
/// @since  0.2, 10.04.2016
ArgumentContainer::ArgumentContainer():
   mArguments()
{
} // ArgumentContainer::ArgumentContainer



/// Adds a new argument.
/// @param[in]  arg_handler  The object used to handle this argument.
/// @param[in]  key          The argument character, string or both.
/// @since  0.2, 10.04.2016
void ArgumentContainer::addArgument( TypedArgBase* arg_handler,
                                     const ArgumentKey& key)
{

   shared_handler_t  sa( arg_handler);


   mArguments.addArgument( sa, key);

} // ArgumentContainer::addArgument



/// After argument evaluating: Check that all mandatory arguments were set,
/// and check that the cardinality requirements (if set) were met.
/// @since  0.2, 10.04.2016
void ArgumentContainer::checkMandatoryCardinality() const
{

   for (auto const& argi : mArguments)
   {
      if (argi.data()->isMandatory() && !argi.data()->hasValue())
         throw runtime_error( "Mandatory argument '"
                              + format::toString( argi.key())
                              + "' was not set");
      argi.data()->checkCardinality();
   } // end for

} // ArgumentContainer::checkMandatoryCardinality



/// Check this object and \a otherAH don't share any arguments.
/// @param[in]  ownName    The symbolic name of this argument group.
/// @param[in]  otherName  The symbolic name of the other object's argument
///                        group.
/// @param[in]  otherAH    The other object to check the argument against.
/// @since  0.2, 10.04.2016
void ArgumentContainer::checkArgMix( const string& ownName,
                                     const string& otherName,
                                     const ArgumentContainer& otherAH) const
{

   for (auto const& other_argi : otherAH.mArguments)
   {
      for (auto const& argi : mArguments)
      {
         if (argi.key() == other_argi.key())
            throw invalid_argument( "Argument '-"
                                    + format::toString( argi.key())
                                    + " from group '" + otherName
                                    + "' is already used by '" + ownName + "'");

         if (argi.key().mismatch( other_argi.key()))
            throw invalid_argument( "Argument '-"
                                    + format::toString( other_argi.key())
                                    + " from group '" + otherName
                                    + "' has a mismatch with '"
                                    + format::toString( argi.key())
                                    + "' in group '" + ownName + "'");
      } // end for
   } // end for

} // ArgumentContainer::checkArgMix



/// Searches if this short or long argument is defined.<br>
/// If a long argument name was used, also search for partial matches.
/// @param[in]  key  The short and/or long argument name to check.
/// @return  Pointer to the argument handler object if the argument is
///          defined, NULL otherwise.
/// @since  0.15.0, 12.07.2017  (take ArgumentKey as parameter)
/// @since  0.2, 10.04.2016
TypedArgBase* ArgumentContainer::findArg( const ArgumentKey& key) const
{


   TypedArgBase*  part_match = nullptr;


   for (auto const& argi : mArguments)
   {
      if (argi == key)
         return argi.data().get();

      if (argi.key().startsWith( key))
      {
         // found a match using the long argument as abbreviation
         if (part_match == nullptr)
            part_match = argi.data().get();
         else
            throw runtime_error( "Long argument abbreviation '"
                                 + format::toString( key)
                                 + "' matches more than one argument");
      } // end if
   } // end for

   return part_match;
} // ArgumentContainer::findArg



/// Specifies the line length to use when printing the usage.<br>
/// Used when this container is used to store te sub-group arguments.
/// @param[in]  useLen  The new line length to use.<br>
///                     The value must be in the range 60 <= useLen < 240.
/// @since  0.2, 10.04.2016
void ArgumentContainer::setUsageLineLength( int useLen)
{

   for (auto & arg : mArguments)
   {
      TypedArgSubGroup*  tasg = static_cast< TypedArgSubGroup*>( arg.data().get());
      if ((tasg != nullptr) && (tasg->obj() != nullptr))
      {
         tasg->obj()->setUsageLineLength( useLen);
      } // end if
   } // end for

} // ArgumentContainer::setUsageLineLength



/// Prints the contents of the container == list of all arguments.
/// @param[out]  os  The stream to write to.
/// @param[in]   ac  The object to dump the data of.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, const ArgumentContainer& ac)
{

   os << "Arguments:" << endl;

   for (auto const& arg : ac.mArguments)
   {
      os << '\'' << format::toString( arg.key()) << "' " << arg.data() << endl;
   } // end for

   return os;
} // operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// ======================  END OF argument_container.cpp  ======================

