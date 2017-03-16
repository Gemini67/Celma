
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
/// See documentation of class celma::prog_args::detail::@@@.


// module header file include
#include "celma/prog_args/detail/value_storage.hpp"


namespace celma { namespace prog_args { namespace detail {



ValueStorage::ValueStorage( const std::string& type_name):
   mTypeName( type_name)
{
} // 



bool ValueStorage::isSameType( const std::string& other_type_name) const noexcept
{
   return mTypeName == other_type_name;
} // 



} // namespace detail
} // namespace prog_args
} // namespace celma


// ========================  END OF value_storage.cpp  ========================

