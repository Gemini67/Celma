
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of enum class celma::prog_args::SummaryOptions;


#pragma once


#include <cstdint>
#include "celma/common/enum_flags.hpp"


namespace celma::prog_args {


/// List of additional contents that can be activated in the summary output:
enum class SummaryOptions : uint8_t
{
   with_type,   //!< Also prints the type of the destination variable.
   with_key     //!< Also prints the key of the argument that was used.
}; // SummaryOptions


/// Summary options set: Stores the flags that are set for the summary
/// options.
using sumoptset_t = common::EnumFlags< SummaryOptions>;


} // namespace celma::prog_ags


// =====  END OF summary_options.hpp  =====

