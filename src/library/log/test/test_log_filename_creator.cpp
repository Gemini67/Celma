
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module filename::Creator, using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/log/filename/creator.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFilenameCreatorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/project_path.hpp"
#include "celma/appl/project_root.hpp"


using celma::log::filename::Creator;


/// Helper class used to check the contents of the created format.
/// @since  x.y.z, 16.10.2017
class DefinitionAccess: public celma::log::filename::Definition
{
public:
   /// Returns the stored size, i.e. number of format entries.
   /// @return  The number of format entries stored.
   /// @since  x.y.z, 16.10.2017
   size_t size() const
   {
      return mParts.size();
   } // DefinitionAccess::size

   /// Returns the type of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the type of.
   /// @return  The type of the field at the given position.
   /// @since  x.y.z, 16.10.2017
   PartTypes partType( int part_idx) const
   {
      return mParts[ part_idx].mType;
   } // DefinitionAccess::partType

   /// Returns the constant value of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the constant
   ///                        value of.
   /// @return  The constant value of the field at the given position.
   /// @since  x.y.z, 16.10.2017
   const std::string& constant( int field_idx) const
   {
      return mParts[ field_idx].mConstant;
   } // DefinitionAccess::constant

   /// Returns the fixed width of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the fixed width
   ///                        of.
   /// @return  The fixed width of the field at the given position.
   /// @since  x.y.z, 16.10.2017
   int fixedWidth( int field_idx) const
   {
      return mParts[ field_idx].mFixedWidth;
   } // DefinitionAccess::fixedWidth

   /// Returns if left alignment should be used for the field at the given
   /// position.
   /// @param[in]  field_idx  The number of the field to return the alignment
   ///                        mode of.
   /// @return  \c true if left alignment should be used for the field at the
   ///          given position.
   /// @since  x.y.z, 16.10.2017
   char fillChar( int field_idx) const
   {
      return mParts[ field_idx].mFillChar;
   } // DefinitionAccess::alignLeft

}; // DefinitionAccess


BOOST_TEST_DONT_PRINT_LOG_VALUE( DefinitionAccess)
BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::log::filename::Definition::PartTypes)


/// First simple tests.
/// @since  x.y.z, 16.10.2017
BOOST_AUTO_TEST_CASE( test_one)
{

   namespace clf = celma::log::filename;

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::date;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << "/var/log/logfile." << clf::number;

      BOOST_REQUIRE_EQUAL( my_def.size(), 2);
   } // end scope

} // test_one



/// Check that multiple constant text parts are concatenated to one element.
/// @since  x.y.z, 16.10.2017
BOOST_AUTO_TEST_CASE( test_combine)
{

   namespace clf = celma::log::filename;

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << "/var" << "/log";

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "/var/log");
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << "/var" << "/log/" << "myfile.log";

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "/var/log/myfile.log");
   } // end scope

} // test_combine



/// Check that multiple path parts are correctly separated by a slash.
/// @since  x.y.z, 16.10.2017
BOOST_AUTO_TEST_CASE( test_check_path_sep)
{

   namespace clf = celma::log::filename;

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << "/var" << clf::path_sep << "/log";

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "/var/log");
   } // end scope

} // test_check_path_sep



/// Check usage of class ProjectPath.
/// @since  x.y.z, 16.10.2017
BOOST_AUTO_TEST_CASE( test_project_path)
{

   namespace clf = celma::log::filename;

   {
      static char  dir[] = "DIR=/opt/appl";
      ::putenv( dir);

      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      celma::appl::ProjectRoot::instance().setProjectRoot(
         celma::appl::ProjectRoot::ProjRootSrc::env, "DIR");
      celma::appl::ProjectPath  logdir( "log");

      format_creator << logdir << clf::path_sep << "myfile.log";

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "/opt/appl/log/myfile.log");
   } // end scope

} // test_project_path



// ===================  END OF test_log_filename_creator.cpp  ===================
