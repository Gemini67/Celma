
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogDestData.


#pragma once


#include <iosfwd>
#include <memory>
#include <string>
#include "celma/log/detail/i_log_dest.hpp"


namespace celma::log::detail {


/// Stores the properties of a log destination.
///
/// @since  1.0.0, 19.06.2016
class LogDestData
{
public:
   /// Constructor.
   ///
   /// @param[in]  name
   ///    The symbolic name of the log destination.
   /// @param[in]  ldo
   ///    The object handling the log destination.
   /// @since  1.0.0, 19.06.2016
   LogDestData( const std::string& name, ILogDest* ldo):
      mName( name),
      mpLogger( ldo)
   {
   } // LogDestData::LogDestData

   /// Writes information about a log destination.
   ///
   /// @param[in]  os
   ///    The stream to write into.
   /// @param[in]  l
   ///    The log destination to dump the information of.
   /// @return  The stream as passed in.
   /// @since  1.0.0, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const LogDestData& l);
   
   /// The symbolic name of the log destination.
   std::string                 mName;
   /// Pointer to the object handling the log destination.
   std::shared_ptr< ILogDest>  mpLogger;

}; // LogDestData


} // namespace celma::log::detail


// =====  END OF log_dest_data.hpp  =====

