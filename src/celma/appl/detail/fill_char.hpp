
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


#ifndef CELMA_APPL_DETAIL_FILL_CHAR_HPP
#define CELMA_APPL_DETAIL_FILL_CHAR_HPP


namespace celma { namespace appl { namespace detail {


class fill_char
{
public:
   /// Constructor. Stores name of the property.
   /// @param[in]  name  The name of the property.
   /// @since  x.y, 31.01.2017
   explicit fill_char( char use_fill_char):
      mFillChar( use_fill_char)
   {
   } // 

   /// Returns the internally stored name of the custom property.
   /// @return  The name of the property.
   /// @since  x.y, 31.01.2017
   char getFillChar() const
   {
      return mFillChar;
   } // 
   
private:
   /// The name of the property.
   const char  mFillChar;
   
}; // 


} // namespace detail
} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_DETAIL_FILL_CHAR_HPP


// ==========================  END OF fill_char.hpp  ==========================

