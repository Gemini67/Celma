
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::TestIDirList.


#ifndef CELMA_LOG_TEST_I_DIR_LIST_HPP
#define CELMA_LOG_TEST_I_DIR_LIST_HPP


#include <string>


namespace celma { namespace log {


/// Helper class used to clean up the temporary directories created during the
/// log tests.<br>
/// This class defines the interface of a function that is called when a new
/// directory is created.
///
/// @since  1.26.0, 08.03.2018
class TestIDirList
{
public:
   /// Default empty, virtual destructor.
   ///
   /// @since  1.26.0, 08.03.2018
   virtual ~TestIDirList() = default;

   /// Interface of the callback functions. Called when a new directory was
   /// created.
   ///
   /// @param[in]  dir_name  The name of the directory that was created.
   /// @since  1.26.0, 08.03.2018
   virtual void dirCreated( const std::string&) = 0;

}; // TestIDirList


} // namespace log
} // namespace celma


#endif   // CELMA_LOG_TEST_I_DIR_LIST_HPP


// =====  END OF test_i_dir_list.hpp  =====

