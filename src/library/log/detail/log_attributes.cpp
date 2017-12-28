
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
#include "celma/log/detail/log_attributes.hpp"


namespace celma { namespace log { namespace detail {



LogAttributes::LogAttributes():
   mAttributes()
{
}



void LogAttributes::addAttribute( const std::string& attr_name,
                                  const std::string& attr_value)
{

   mAttributes.push_back( AttrPair( attr_name, attr_value));

}



void LogAttributes::removeAttribute( const std::string& attr_name)
{

   for (AttrCont::iterator it = mAttributes.begin(); it != mAttributes.end(); ++it)
   {
      if (it->first == attr_name)
      {
         mAttributes.erase( it);
         return;
      } // end if
   } // end for

}



} // namespace detail
} // namespace log
} // namespace celma


// ========================  END OF log_attributes.cpp  ========================

