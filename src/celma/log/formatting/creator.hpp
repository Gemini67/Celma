
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
/// See documentation of class celma::log::formatting::Creator.


#ifndef CELMA_LOG_FORMATTING_CREATOR_HPP
#define CELMA_LOG_FORMATTING_CREATOR_HPP


#include <string>
#include "celma/log/formatting/definition.hpp"
#include "celma/log/detail/custom_property.hpp"


namespace celma { namespace log { namespace formatting {


// bring helper class customProperty into the same namespace
using detail::customProperty;


class Creator
{
public:
   Creator( Definition& dest_def);

   void field( Definition::FieldTypes field_type);
   void setFixedWidth( int fixed_width);
   void alignRight();

   Creator& operator <<( Creator&( *m)( Creator&))
   {
      m( *this);
      return *this;
   }

   /// 
   /// @param[in]  c   .
   /// @param[in]  cp  .
   /// @return  .
   /// @since  0.11, 13.12.2016
   friend Creator& operator <<( Creator& c, const customProperty& cp)
   {
      c.customProperty( cp.name());
      return c;
   } // end operator <<

   friend Creator& operator <<( Creator& c, const std::string& const_text);

   friend Creator& operator <<( Creator& c, int fixed_width);

private:
   void addConstantText( const std::string& const_text);

   void customProperty( const std::string& proprty_name);

   Definition&  mDefs;
   int          mFixedWidth;
   bool         mAlignRight;

}; // Creator


inline Creator& date( Creator& in)
{

   in.field( Definition::FieldTypes::date);

   return in;
} // date


inline Creator& date_time( Creator& in)
{

   in.field( Definition::FieldTypes::dateTime);

   return in;
} // date_time


inline Creator& line_nbr( Creator& in)
{

   in.field( Definition::FieldTypes::lineNbr);

   return in;
} // line_nbr


inline Creator& right( Creator& in)
{

   in.alignRight();

   return in;
} // right


inline Creator& text( Creator& in)
{

   in.field( Definition::FieldTypes::text);

   return in;
} // text


inline Creator& time( Creator& in)
{

   in.field( Definition::FieldTypes::time);

   return in;
} // time


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_CREATOR_HPP


// ===========================  END OF creator.hpp  ===========================

