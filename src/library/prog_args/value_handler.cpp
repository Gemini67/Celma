
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
/// See documentation of class celma::prog_args::ValueHandler.


// module header file include
#include "celma/prog_args/value_handler.hpp"


// C++ Standard Library includes
#include <iostream>


namespace celma { namespace prog_args {



/// Constructor.
/// @param[in]  flagSet  The set of flags. See enum HandleFlags for a list of
///                      possible values.
/// @param[in]  txt1     Optional pointer to the object to provide additional
///                      text for the usage.
/// @param[in]  txt2     Optional pointer to the object to provide additional
///                      text for the usage.
/// @since  0.14.0, 09.02.2017
ValueHandler::ValueHandler( int flagSet, IUsageText* txt1, IUsageText* txt2):
   ValueHandler( std::cout, std::cerr, flagSet, txt1, txt2)
{
} // ValueHandler::ValueHandler



/// Constructor that allows to specify the output streams to write to.
/// @param[in]  os        The stream to write normal output to.
/// @param[in]  error_os  The stream to write error output to.
/// @param[in]  flag_set  The set of flags. See enum HandleFlags for a list
///                       of possible values.
/// @param[in]  txt1      Optional pointer to the object to provide
///                       additional text for the usage.
/// @param[in]  txt2      Optional pointer to the object to provide
///                       additional text for the usage.
/// @since  0.14.0, 09.02.2017
ValueHandler::ValueHandler( std::ostream& os, std::ostream& error_os,
                            int flag_set, IUsageText* txt1, IUsageText* txt2):
   Handler( os, error_os, flag_set, txt1, txt2),
   mValues()
{
} // ValueHandler::ValueHandler



/// Returns if this object is a value handler.
/// @return  In this class, always \c true.
/// @since  0.14.0, 21.02.2017
bool ValueHandler::isValueHandler() const
{
   return true;
} // ValueHandler::isValueHandler



/// Returns this object.
/// @return  This object.
/// @since  0.14.0, 15.03.2017
ValueHandler* ValueHandler::getValueHandlerObj()
{
   return this;
} // ValueHandler::getValueHandlerObj



} // namespace prog_args
} // namespace celma


// ========================  END OF value_handler.cpp  ========================

