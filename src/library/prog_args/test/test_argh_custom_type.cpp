
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "custom argument type" in the module
**    celma::prog_args::Handler, using the Boost.Test module.
**
--*/


// C++ Standard Library includes
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


using std::string;
using celma::prog_args::detail::ArgumentKey;
using celma::prog_args::detail::TypedArgBase;
using celma::prog_args::Handler;


// module definitions

/// Custom type: set flags in a bitset.
/// @since  0.2, 10.04.2016
class TypedArgBitset: public TypedArgBase
{
public:
   /// The type of the destination variable.
   typedef std::bitset< 1024>  type;

   /// Constructor.
   /// @param[in]  dest   The destination variable to store the values in.
   /// @param[in]  vname  The name of the destination variable to store the
   ///                    value in.
   /// @since  0.16.0, 13.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArgBitset( type& dest, const string& vname);

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
   virtual TypedArgBase* setListSep( char sep);

private:
   /// Reference of the destination variable to store the value(s) in.
   type&  mDestVar;
   /// The character to use a list separator, default: ,
   char   mListSep;

}; // TypedArgBitset


// inlined methods
// ===============


TypedArgBitset::TypedArgBitset( type& dest, const string& vname):
   TypedArgBase( vname, Handler::ValueMode::required, false),
   mDestVar( dest),
   mListSep( ',')
{
} // TypedArgBitset::TypedArgBitset


void TypedArgBitset::assign( const string& value)
{

   celma::common::Tokenizer  tok( value, mListSep);


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
} // TypedArgBitset::assign


bool TypedArgBitset::hasValue() const
{
   return mDestVar.count() > 0;
} // end TypedArgBitset::hasValue


TypedArgBase* TypedArgBitset::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArgBitset::setListSep



/// Check if adding a custom destination type for argument handling works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( custom_bitset)
{

   Handler               ah( 0);
   TypedArgBitset::type  kilobits;


   BOOST_REQUIRE_NO_THROW(
      ah.addArgument( "b,bitset", new TypedArgBitset( kilobits, "bitset"),
                      "a bit set")->setIsMandatory());

   const celma::common::ArgString2Array  as2a( "-b 1,2,3,5,7,11", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( kilobits.count(), 6);
   BOOST_REQUIRE( kilobits[  1]);
   BOOST_REQUIRE( kilobits[  2]);
   BOOST_REQUIRE( kilobits[  3]);
   BOOST_REQUIRE( kilobits[  5]);
   BOOST_REQUIRE( kilobits[  7]);
   BOOST_REQUIRE( kilobits[ 11]);

} // custom_bitset



// ====================  END OF test_argh_custom_type.cpp  ====================

