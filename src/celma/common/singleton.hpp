
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


#ifndef CELMA_COMMON_SINGLETON_HPP
#define CELMA_COMMON_SINGLETON_HPP


// hide the fact that the singleton implementation is a bit more complex
#include "celma/common/detail/singleton.hpp"


namespace celma { namespace common {


using detail::Singleton;


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SINGLETON_HPP


// =========================  END OF singleton.hpp  =========================

