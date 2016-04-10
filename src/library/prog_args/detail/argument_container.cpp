
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


// module header file include
#include "celma/prog_args/detail/argument_container.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/prog_args/handler.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {


/// Constructor.
/// @since  0.2, 10.04.2016
ArgumentContainer::ArgumentContainer():
   mCharArgs(),
   mLongArgs()
{
} // end ArgumentContainer::ArgumentContainer



/// Adds a new argument.
/// @param[in]  argHandler  The object used to handle this argument.
/// @param[in]  argSpec     The argument character, string or both.
/// @since  0.2, 10.04.2016
void ArgumentContainer::addArgument( TypedArgBase* argHandler,
                                     const string& argSpec)
{

   SharedArg  sa( argHandler);


   splitArgSpec( argSpec, sa);

} // end ArgumentContainer::addArgument



/// After argument evaluating: Check that all mandatory arguments were set,
/// and check that the cardinality requirements (if set) were met.
/// @since  0.2, 10.04.2016
void ArgumentContainer::checkMandatoryCardinality() const
{

   for (CharArgCont::const_iterator caci = mCharArgs.begin(); caci != mCharArgs.end(); ++caci)
   {
      if (caci->second->isMandatory() && !caci->second->hasValue())
         throw invalid_argument( "Mandatory argument '" + string( 1, caci->first) + "' was not set");
      caci->second->checkCardinality();
   } // end for

   for (LongArgCont::const_iterator laci = mLongArgs.begin(); laci != mLongArgs.end(); ++laci)
   {
      if (laci->second->isMandatory() && !laci->second->hasValue())
         throw invalid_argument( "Mandatory argument '" + laci->first + "' was not set");
      laci->second->checkCardinality();
   } // end for

} // end ArgumentContainer::checkMandatoryCardinality



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

   for (CharArgCont::const_iterator caci = otherAH.mCharArgs.begin();
        caci != otherAH.mCharArgs.end(); ++caci)
   {
      if (mCharArgs.find( caci->first) != mCharArgs.end())
         throw runtime_error( "Argument '-" + string( 1, caci->first)
                              + " from group '" + otherName
                              + "' is already used by '" + ownName + "'");
   } // end for

   for (LongArgCont::const_iterator laci = otherAH.mLongArgs.begin();
        laci != otherAH.mLongArgs.end(); ++laci)
   {
      if (mLongArgs.find( laci->first) != mLongArgs.end())
         throw runtime_error( "Argument '--" + laci->first + " from group '"
                              + otherName + "' is already used by '"
                              + ownName + "'");
   } // end for

} // end ArgumentContainer::checkArgMix



/// Searches if this single character argument is defined.
/// @param[in]  charArg  The argument character to check.
/// @return  Pointer to the argument handler object if the argument is
///          defined, NULL otherwise.
/// @since  0.2, 10.04.2016
TypedArgBase* ArgumentContainer::findArg( char charArg) const
{

   CharArgCont::const_iterator  caci = mCharArgs.find( charArg);


   return (caci == mCharArgs.end()) ? nullptr : caci->second.get();
} // end ArgumentContainer::findArg



/// Searches if this argument name is defined.
/// @param[in]  longArg  The argument name to check.
/// @return  Pointer to the argument handler object if the argument is
///          defined, NULL otherwise.
/// @since  0.2, 10.04.2016
TypedArgBase* ArgumentContainer::findArg( const string& longArg) const
{


   LongArgCont::const_iterator  laci = mLongArgs.find( longArg);


   if (laci == mLongArgs.end())
   {
      // check if an abbreviation was used
      LongArgCont::const_iterator  laci2 = mLongArgs.lower_bound( longArg);
      while (laci2 != mLongArgs.end())
      {
         const int  compRes = laci2->first.compare( 0, longArg.length(), longArg);
         if (compRes == 0)
         {
            // found a match using the long argument as abbreviation
            if (laci == mLongArgs.end())
               laci = laci2;
            else
               throw invalid_argument( "Long argument abbreviation '" + longArg +
                                       "' matches more than one argument");
         } else if (compRes > 0)
         {
            break;   // while
         } // end if
         ++laci2;
      } // end while
   } // end if

   return (laci == mLongArgs.end()) ? nullptr : laci->second.get();
} // end ArgumentContainer::findArg



/// Specifies the line length to use when printing the usage.<br>
/// Used when this container is used to store te sub-group arguments.
/// @param[in]  useLen  The new line length to use.<br>
///                     The value must be in the range 60 <= useLen < 240.
/// @since  0.2, 10.04.2016
void ArgumentContainer::setUsageLineLength( int useLen)
{

   for (CharArgCont::const_iterator caci = mCharArgs.begin(); caci != mCharArgs.end(); ++caci)
   {
      TypedArgSubGroup*  tasg = static_cast< TypedArgSubGroup*>( caci->second.get());
      if ((tasg != nullptr) && (tasg->obj() != nullptr))
      {
         tasg->obj()->setUsageLineLength( useLen);
      } // end if
   } // end for

   for (LongArgCont::const_iterator laci = mLongArgs.begin(); laci != mLongArgs.end(); ++laci)
   {
      TypedArgSubGroup*  tasg = static_cast< TypedArgSubGroup*>( laci->second.get());
      if ((tasg != nullptr) && (tasg->obj() != nullptr))
      {
         tasg->obj()->setUsageLineLength( useLen);
      } // end if
   } // end for

} // end ArgumentContainer::setUsageLineLength



/// Splits the argument specifyer string into single and long argument and
/// stores it accordingly.
/// @param[in]  argSpec  The string with the short, long or both arguments.
/// @param[in]  sa       The object to handle these argument(s).
/// @since  0.2, 10.04.2016
void ArgumentContainer::splitArgSpec( const string& argSpec, const SharedArg& sa)
{

   string::size_type  pos = argSpec.find_first_of( ',');


   if (pos == string::npos)
   {
      addArgObj( argSpec, sa);
   } else
   {
      string  part( argSpec.substr( 0, pos));
      addArgObj( part, sa);
      part = argSpec.substr( pos + 1);
      addArgObj( part, sa);
   } // end if

} // end ArgumentContainer::splitArgSpec



/// Adds an object to either the single or multi character containers.
/// @param[in]  singleArgSpec  The string with the single or multi-character
///                            argument.
/// @param[in]  sa             The object to handle this argument.
/// @since  0.2, 10.04.2016
void ArgumentContainer::addArgObj( const string& singleArgSpec,
                                   const SharedArg& sa)
{

   if (singleArgSpec.length() == 0)
   {
      addArgObj( "-", sa);
   } else if (singleArgSpec.length() == 1)
   {
      CharArgCont::const_iterator  caci = mCharArgs.find( singleArgSpec[ 0]);
      if (caci != mCharArgs.end())
         throw invalid_argument( "Destination '" + sa->varName()
                                 + "': Argument '" + singleArgSpec +
                                 "' already used for destination '" +
                                 caci->second->varName() + "'!");

      mCharArgs.insert( CharArgCont::value_type( singleArgSpec[ 0], sa));
   } else
   {
      LongArgCont::const_iterator  laci = mLongArgs.find( singleArgSpec);
      if (laci != mLongArgs.end())
         throw invalid_argument( "Destination '" + sa->varName()
                                   + "': Argument '" + singleArgSpec
                                   + "' already used for destination '" +
                                  laci->second->varName() + "'!");

      mLongArgs.insert( LongArgCont::value_type( singleArgSpec, sa));
   } // end if

} // end ArgumentContainer::addArgObj



/// Prints the contents of the container == list of all arguments.
/// @param[out]  os  The stream to write to.
/// @param[in]   ac  The object to dump the data of.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
ostream& operator <<( ostream& os, const ArgumentContainer& ac)
{

   cout << "Short (character) arguments:" << endl;

   for (ArgumentContainer::CharArgCont::const_iterator cit = ac.mCharArgs.begin();
        cit != ac.mCharArgs.end(); ++cit)
   {
      os << "'-" << cit->first << "' " << cit->second << endl;
   } // end for

   cout << endl << "Long (string) arguments:" << endl;

   for (ArgumentContainer::LongArgCont::const_iterator cit = ac.mLongArgs.begin();
        cit != ac.mLongArgs.end(); ++cit)
   {
      os << "'--" << cit->first << "' " << cit->second << endl;
   } // end for

   return os;
} // end operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF argument_container.cpp  =========================

