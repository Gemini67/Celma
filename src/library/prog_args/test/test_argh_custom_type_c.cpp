
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "custom argument type" in the module
**    celma::prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <bitset>
#include <iostream>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCustomConversion
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/common/tokenizer.hpp"


using std::string;
using celma::prog_args::detail::ArgumentKey;
using celma::prog_args::detail::TypedArgBase;
using celma::prog_args::Handler;


// module definitions


namespace {


/// Custom type: set flags in a bitset.
/// @since  0.2, 10.04.2016
class TypedArgBitset final : public TypedArgBase
{
public:
   /// The type of the destination variable.
   using type = std::bitset< 1024>;

   /// Constructor.
   /// @param[in]  dest   The destination variable to store the values in.
   /// @param[in]  vname  The name of the destination variable to store the
   ///                    value in.
   /// @since  0.16.0, 13.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArgBitset( type& dest, const string& vname);

   /// Returns the name of the destination type as string.
   ///
   /// @return  String with the name of the destination type.
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Stores the value in the destination variable.
   ///
   /// @param[in]  value
   ///    The value to store in string format.
   /// @param[in]  inverted
   ///    Ignored.
   /// @since  0.2, 10.04.2016
   void assign( const string& value, bool inverted) override;

   /// Returns if the destination has (at least) one value set.
   /// @return  \c true if the destination variable contains (at least) one
   ///          value, \c false otherwise.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Writes the contents of the destination variable into the stream.
   /// @param[in]  os
   ///    The stream to write into.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 05.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   TypedArgBase* setListSep( char sep) override;

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


const std::string TypedArgBitset::varTypeName() const
{
   return "custom";
} // TypedArgBitset::varTypeName


void TypedArgBitset::assign( const string& value, bool)
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
} // TypedArgBitset::hasValue


void TypedArgBitset::printValue( std::ostream& os, bool) const
{
   os << "[custom]";
} // TypedArgBitset::printValue


TypedArgBase* TypedArgBitset::setListSep( char sep)
{
   mListSep = sep;
   return this;
} // TypedArgBitset::setListSep


} // namespace



/// Check if adding a custom destination type for argument handling works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( custom_bitset)
{

   Handler               ah( 0);
   TypedArgBitset::type  kilobits;


   BOOST_REQUIRE_NO_THROW(
      ah.addArgument( "b,bitset", new TypedArgBitset( kilobits, "bitset"),
                      "a bit set")->setIsMandatory());

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 1,2,3,5,7,11"));
   BOOST_REQUIRE_EQUAL( kilobits.count(), 6);
   BOOST_REQUIRE( kilobits[  1]);
   BOOST_REQUIRE( kilobits[  2]);
   BOOST_REQUIRE( kilobits[  3]);
   BOOST_REQUIRE( kilobits[  5]);
   BOOST_REQUIRE( kilobits[  7]);
   BOOST_REQUIRE( kilobits[ 11]);

} // custom_bitset



// =====  END OF test_argh_custom_type_c.cpp  =====

