
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "custom argument type" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>
#include <bitset>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCustomConversion
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;


// module definitions

/// Custom type: set flags in a bitset.
/// @since  0.2, 10.04.2016
class TypedArgBitset: public prog_args::detail::TypedArgBase
{
public:
   /// The type of the destination variable.
   typedef bitset< 1024>  type;

   /// Constructor.
   /// @param[in]  arg_spec  The argument specification, i.e. short and/or long
   ///                       argument.
   /// @param[in]  dest      The destination variable to store the values in.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @since  0.2, 10.04.2016
   TypedArgBitset( const string& arg_spec, type& dest, const string& vname);

   /// Stores the value in the destination variable.
   /// @param[in]  value  The value to store in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const string& value);

   /// Returns if the destination has (at least) one value set.
   /// @return  \c true if the destination variable contains (at least) one
   ///          value, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual prog_args::detail::TypedArgBase* setListSep( char sep);

private:
   /// Reference of the destination variable to store the value(s) in.
   type&  mDestVar;
   /// The character to use a list separator, default: ,
   char   mListSep;

}; // TypedArgBitset


// inlined methods
// ===============


TypedArgBitset::TypedArgBitset( const string& arg_spec, type& dest,
                                const string& vname):
   prog_args::detail::TypedArgBase( arg_spec, vname, vmRequired, false),
   mDestVar( dest),
   mListSep( ',')
{
} // end TypedArgBitset::TypedArgBitset


void TypedArgBitset::assign( const string& value)
{

   common::Tokenizer  tok( value, mListSep);


   for (auto it : tok)
   {
      check( it);

      if (!mFormats.empty())
      {
         string  valCopy( it);
         format( valCopy);
         mDestVar.set( boost::lexical_cast< int>( valCopy));
      } else
      {
         mDestVar.set( boost::lexical_cast< int>( it));
      } // end if
   } // end for
} // end TypedArgBitset::assign


bool TypedArgBitset::hasValue() const
{
   return mDestVar.count() > 0;
} // end TypedArgBitset::hasValue


prog_args::detail::TypedArgBase* TypedArgBitset::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // end TypedArgBitset::setListSep



/// Check if adding a custom destination type for argument handling works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( custom_bitset)
{

   prog_args::Handler    ah( 0);
   TypedArgBitset::type  kilobits;


   BOOST_REQUIRE_NO_THROW( ah.addCustomArgument< TypedArgBitset>( "b,bitset", DEST_VAR( kilobits), "bitset")
                                                                ->setIsMandatory());

   common::ArgString2Array  as2a( "-b 1,2,3,5,7,11", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( kilobits.count(), 6);
   BOOST_REQUIRE( kilobits[  1]);
   BOOST_REQUIRE( kilobits[  2]);
   BOOST_REQUIRE( kilobits[  3]);
   BOOST_REQUIRE( kilobits[  5]);
   BOOST_REQUIRE( kilobits[  7]);
   BOOST_REQUIRE( kilobits[ 11]);

} // end custom_bitset



// =========================  END OF test_argh_custom_type.cpp  =========================

