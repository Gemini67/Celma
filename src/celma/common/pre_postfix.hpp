
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// Defines special values for defining pre- and postfix operators.


#pragma once


namespace std
{


// Yeah, I know, you should not define stuff in namespace std::, but since the
// following two usings are something like standard, I did it anyway. Sue me.
// And besides, it would look strange to define
//    operator ++( celma::common::postfix)
// Wouldn't it?


/// Use this keyword for defining the prefix --/++ operator.
using prefix = void;

/// Use this keyword for defining the postfix --/++ operator.
using postfix = int;


} // namespace std


// =====  END OF pre_postfix.hpp  =====

