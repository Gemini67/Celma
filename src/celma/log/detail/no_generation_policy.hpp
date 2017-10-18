
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


#ifndef CELMA_LOG_DETAIL_NO_GENERATION_POLICY_HPP
#define CELMA_LOG_DETAIL_NO_GENERATION_POLICY_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace log { namespace detail {


/// @since  x.y.z, 19.06.2016
class NoGenerationPolicy
{
public:
   NoGenerationPolicy( const std::string& path, const std::string& filename);

   void openLogfile( std::ofstream& outfile);

private:
   std::string  mFullPathFilename;

};


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_NO_GENERATION_POLICY_HPP


// =====================  END OF no_generation_policy.hpp  =====================

