
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::Properties.


// module header file include
#include "celma/common/properties.hpp"


// C++ Standard Library includes
#include <iostream>


namespace celma { namespace common {



/// Constructor.
/// @param[in]  separator  The spearator to use for this instance.
/// @since  1.2, 19.10.2016
Properties::Properties( char separator):
   mSeparator( separator),
   mProperties( "")
{
} // Properties::Properties



/// Insertion operator for a Properties object.
/// @param[out]  os     The stream to write to.
/// @param[in]   props  The object to dump the contents of.
/// @return  The stream as passed in.
/// @since  1.2, 19.10.2016
std::ostream& operator <<( std::ostream& os, const Properties& props)
{

   props.mProperties.dump( os);

   return os;
} // operator <<



} // namespace common
} // namespace celma


// ==========================  END OF properties.cpp  ==========================

