
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
/// See documentation of class celma::log::detail::@@@.


// module header file include
#include "celma/log/detail/no_generation_policy.hpp"


// C++ Standard Library includes
#include <fstream>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/common/string_util.hpp"


namespace celma { namespace log { namespace detail {



NoGenerationPolicy::NoGenerationPolicy( const std::string& path,
                                        const std::string& filename):
   mFullPathFilename( path)
{

   common::ensure_last( mFullPathFilename);

   mFullPathFilename.append( filename);

}



void NoGenerationPolicy::openLogfile( std::ofstream& outfile)
{

   if (outfile.is_open())
      return;

   outfile.open( mFullPathFilename.c_str(), std::ios_base::out | std::ios_base::app);

   if (!outfile)
      throw CELMA_RuntimeError( "could not create/open logfile");

}



} // namespace detail
} // namespace log
} // namespace celma


// =====================  END OF no_generation_policy.cpp  =====================

