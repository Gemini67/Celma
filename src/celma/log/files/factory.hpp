
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
/// See documentation of functions celma::log::files::factory().


#ifndef CELMA_LOG_FILES_FACTORY_HPP
#define CELMA_LOG_FILES_FACTORY_HPP


#include <stdexcept>
#include <utility>
#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/files/handler.hpp"
#include "celma/log/files/max_size.hpp"
#include "celma/log/files/simple.hpp"
#include "celma/log/files/timestamped.hpp"


namespace celma { namespace log { namespace files {


/// List of log file types supported by the factory functions:
enum class LogFileTypes
{
   maxSize,      //!< Files with a maximum size.
   simple,       //!< Files without generations/roll-over.
   timestamped   //!< Files with timestamp in the path/name.
};


/// Base template function for creating a log file object.
///
/// @tparam  LogFileTypes
///    Template parameter is of type enum value and determines the type of the
///    log file to create.
/// @param[in]  name_def
///    The object that provides the path and name for the logfiles.
/// @return
///    Pointer to the newly created object with the requested log file type.
/// @since  1.26.0, 13.03.2018
template< LogFileTypes> detail::ILogDest*
   factory( filename::Definition& name_def);


/// Creates a log file with type "simple": No generations, no automatic
/// roll-over.
///
/// @param[in]  name_def
///    The object that provides the path and name for the logfiles.
/// @return  Pointer to the newly created object for a simple log file.
/// @since  1.26.0, 13.03.2018
template<>
   detail::ILogDest*
      factory< LogFileTypes::simple>( filename::Definition& name_def)
{
   return new Handler< Simple>( new Simple( name_def));
} // factory


/// Creates a log file with type "timestamped": Automatically open a new file
/// depending on the timestamp of the log messages.
///
/// @param[in]  name_def
///    The object that provides the path and name for the logfiles.
/// @return  Pointer to the newly created object for a "timestamped" log file.
/// @since  1.26.0, 13.03.2018
template<>
   detail::ILogDest*
      factory< LogFileTypes::timestamped>( filename::Definition& name_def)
{
   return new Handler< Timestamped>( new Timestamped( name_def));
} // factory



/// Not partial specialization but overload due to different number of
/// parameters:<br>
/// Creates a log file with type "maximum size": Automatically renumber existing
/// files and open a new file when the maximum size is reached.
///
/// @param[in]  name_def
///    The object that provides the path and name for the logfiles.
/// @param[in]  max_file_size
///    Maximum allowed log file size.
/// @param[in]  max_gen
///    Maximum number of generations of log files to keep.
/// @return  Pointer to the newly created object for a "maximum size" log file.
/// @since  1.26.0, 13.03.2018
detail::ILogDest* factory( filename::Definition& name_def,
   size_t max_file_size, int max_gen)
{
   return new Handler< MaxSize>( new MaxSize( name_def, max_file_size, max_gen));
} // factory


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_FACTORY_HPP


// =====  END OF factory.hpp  =====

