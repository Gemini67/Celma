
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


#ifndef CELMA_APPL_DETAIL_WIDTH_HPP
#define CELMA_APPL_DETAIL_WIDTH_HPP


namespace celma { namespace appl { namespace detail {


class width
{
public:
   /// Constructor. Stores name of the property.
   /// @param[in]  name  The name of the property.
   /// @since  x.y, 31.01.2017
   explicit width( int fixed_width):
      mWidth( fixed_width)
   {
   } // 

   /// Returns the internally stored name of the custom property.
   /// @return  The name of the property.
   /// @since  x.y, 31.01.2017
   int getWidth() const
   {
      return mWidth;
   } // 
   
private:
   /// The name of the property.
   const int  mWidth;
   
}; // 


} // namespace detail
} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_DETAIL_WIDTH_HPP


// ============================  END OF width.hpp  ============================

