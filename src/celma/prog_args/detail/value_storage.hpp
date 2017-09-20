
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


#ifndef CELMA_PROG_ARGS_DETAIL_VALUE_STORAGE_HPP
#define CELMA_PROG_ARGS_DETAIL_VALUE_STORAGE_HPP


#include <string>


namespace celma { namespace prog_args { namespace detail {


/// @since  0.15.0, 09.02.2017
class ValueStorage
{
public:
   /// @since  0.15.0, 10.02.2017
   ValueStorage( const std::string& type_name);

   ~ValueStorage() = default;

   /// @since  0.15.0, 10.02.2017
   bool isSameType( const std::string& other_type_name) const noexcept;

protected:
   const std::string  mTypeName;

}; // ValueStorage


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_VALUE_STORAGE_HPP


// ========================  END OF value_storage.hpp  ========================

