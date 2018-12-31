
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::IFormatBase.


#ifndef CELMA_LOG_DETAIL_I_FORMAT_BASE_HPP
#define CELMA_LOG_DETAIL_I_FORMAT_BASE_HPP


namespace celma { namespace log { namespace detail {


/// Base class for all output formatters. Needed to define the interface.<br>
/// Actually there are specific interfaces for each output destination type.
/// Because the output destination type is not known yet, this class contains
/// no methods at all.
/// @since  1.0.0, 19.06.2016
class IFormatBase
{
public:
   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   virtual ~IFormatBase() = default;

}; // IFormatBase


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_I_FORMAT_BASE_HPP


// ========================  END OF i_format_base.hpp  ========================

