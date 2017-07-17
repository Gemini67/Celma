
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
/// See documentation of class celma::log::formatting::Definition.


#ifndef CELMA_LOG_FORMATTING_DEFINITION_HPP
#define CELMA_LOG_FORMATTING_DEFINITION_HPP


#include <string>
#include <vector>


namespace celma { namespace log { namespace formatting {


/// @since  0.11, 07.12.2016
class Definition
{
public:
   enum class FieldTypes
   {
      constant,
      date,
      time,
      dateTime,
      pid,
      lineNbr,
      functionName,
      fileName,
      msgLevel,
      msgClass,
      errorNbr,
      text,
      customProperty
   };

   Definition() = default;
   Definition( const Definition&) = default;
   ~Definition() = default;

   Definition& operator =( const Definition&) = default;

protected:
   friend class Creator;

   struct Field
   {
      FieldTypes   mType;
      std::string  mConstant;
      int          mFixedWidth;
      bool         mAlignRight;
   };

   typedef std::vector< Field>  vector_t;

   vector_t  mFields;

}; // Definition


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_DEFINITION_HPP


// ==========================  END OF definition.hpp  ==========================

