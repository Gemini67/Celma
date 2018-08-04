
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of enum class celma::prog_args::SummaryOptions;


#ifndef CELMA_PROG_ARGS_SUMMARY_OPTIONS_HPP
#define CELMA_PROG_ARGS_SUMMARY_OPTIONS_HPP


#include "celma/common/enum_flags.hpp"


namespace celma { namespace prog_args {


/// List of additional contents that can be activated in the summary output:
enum class SummaryOptions
{
   with_type,   //!< Also prints the type of the destination variable.
   with_key     //!< Also prints the key of the argument that was used.
}; // SummaryOptions


/// Summary options set: Stores the flags that are set for the summary
/// options.
using sumoptset_t = common::EnumFlags< SummaryOptions>;


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_SUMMARY_OPTIONS_HPP


// =====  END OF summary_options.hpp  =====

