
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::NamePathRemain.


// module header file include
#include "celma/common/detail/name_path_remain.hpp"


namespace celma { namespace common { namespace detail {



/// Constructor.<br>
/// Tries to split the \a name into the first name and the remaining path.
///
/// @param[in]  name
///    The property path to handle.
/// @param[in]  separator
///    The separator character.
/// @since  1.22.0, 19.10.2016
NamePathRemain::NamePathRemain( const std::string& name, char separator):
   mFirstName(),
   mRemain()
{

   auto const  sep_pos = name.find( separator);


   if (sep_pos == std::string::npos)
   {
      mFirstName = name;
   } else
   {
      mFirstName.assign( name, 0, sep_pos);
      mRemain.assign( name, sep_pos + 1, std::string::npos);
   } // end if

} // NamePathRemain::NamePathRemain



} // namespace detail
} // namespace common
} // namespace celma


// =====  END OF name_path_remain.cpp  =====

