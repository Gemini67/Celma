
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
/// See documentation of class celma::appl::detail::@@@.


#ifndef CELMA_APPL_DETAIL_DATE_TIME_HPP
#define CELMA_APPL_DETAIL_DATE_TIME_HPP


namespace celma { namespace appl { namespace detail {


/// @since  x.y.z, 22.03.2017
class date_time
{
public:
   /// Constructor. Stores the format string for the timestamp.
   /// @param[in]  format  The format string.
   /// @since  x.y.z, 22.03.2017
   explicit date_time( const std::string& format):
      mFormatString( format)
   {
   } // 

   /// Returns the internally stored format string.
   /// @return  The format string.
   /// @since  x.y.z, 22.03.2017
   const std::string& getFormatString() const
   {
      return mFormatString;
   } // 
   
private:
   /// The format string to use for the timestamp.
   const std::string  mFormatString;
   
}; // date_time


} // namespace detail
} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_DETAIL_DATE_TIME_HPP


// ==========================  END OF date_time.hpp  ==========================

