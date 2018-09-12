
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogMsgProperty.


#ifndef CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP
#define CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP


#include <string>
#include <tuple>
#include <vector>


namespace celma { namespace log { namespace detail {


/// @since 0.11, 11.12.2016
class LogMsgProperty
{
public:
   void addProperty( const std::string& property_name,
                     const std::string& property_value);

   /// 
   /// @param[in]  property_name  .
   /// @return  .
   /// @since  0.11, 12.12.2016
   const std::string getPropertyValue( const std::string& property_name) const;

private:
   using property_t = std::tuple< std::string, std::string>;
   using property_cont_t = std::vector< property_t>;

   property_cont_t  mProperties;

}; // LogMsgProperty


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_MSG_PROPERTY_HPP


// =====  END OF log_msg_property.hpp  =====

