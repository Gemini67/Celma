
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


/// @file
/// See documentation of class celma::log::detail::@@@.


#ifndef CELMA_LOG_DETAIL_LOG_ATTRIBUTES_HPP
#define CELMA_LOG_DETAIL_LOG_ATTRIBUTES_HPP


#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>


namespace celma { namespace log { namespace detail {


class LogAttributes
{
public:
   LogAttributes();

   /// 
   /// @param[in]  attr_name   .
   /// @param[in]  attr_value  .
   /// @since  0.3, 19.06.2016
   void addAttribute( const std::string& attr_name, const std::string& attr_value);

   template< typename T> void addAttribute( const std::string& attr_name, T value);

   void removeAttribute( const std::string& attr_name);

private:
   typedef std::pair< std::string, std::string>  AttrPair;
   typedef std::vector< AttrPair>  AttrCont;

   AttrCont  mAttributes;
};


// inlined methods
// ===============


template< typename T>
   void LogAttributes::addAttribute( const std::string& attr_name, T value)
{
   addAttribute( attr_name, boost::lexical_cast< std::string>( value));
}


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_ATTRIBUTES_HPP


// ========================  END OF log_attributes.hpp  ========================

