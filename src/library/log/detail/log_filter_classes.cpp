
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
/// See documentation of class celma::log::detail::LogFilterClasses.


// module header file include
#include "celma/log/detail/log_filter_classes.hpp"


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/common/celma_exception.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor, initialises the set of log classes to accept.
/// @param[in]  class_list  The list of log class names to filter for.
/// @since  0.3, 19.06.2016
LogFilterClasses::LogFilterClasses( const std::string& class_list):
   ILogFilter( ftClasses),
   mClassSelection()
{

   common::Tokenizer  token( class_list, ',');


   for (auto it : token)
   {
      const LogClass  lc = text2logClass( it.c_str());
      if (lc == LogClass::undefined)
         throw CELMA_RuntimeError( std::string( "log class '").append( it).append( "' invalid"));

      mClassSelection.set( static_cast< size_t>( lc));
   } // end for

   if (mClassSelection.none())
      throw CELMA_RuntimeError( "no log classes selected in filter");

} // end LogFilterClasses::LogFilterClasses



} // namespace detail
} // namespace log
} // namespace celma


// ======================  END OF log_filter_classes.cpp  ======================

