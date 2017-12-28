
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
/// See documentation of class celma::log::formatting::Definition.


#ifndef CELMA_LOG_FORMATTING_DEFINITION_HPP
#define CELMA_LOG_FORMATTING_DEFINITION_HPP


#include <string>
#include <vector>


namespace celma { namespace log { namespace formatting {


/// Use this class to create a log message format definition using stream
/// syntax.
/// @since  1.0.0, 07.12.2016
class Definition
{
public:
   /// List of the fields/columns that can be used in a log message.
   enum class FieldTypes
   {
      constant,        //!< Constant text.
      date,            //!< The date of the log message.
      time,            //!< The time when the message was created.
      dateTime,        //!< The timestamp of the message.
      pid,             //!< The id of the process that created the message.
      threadId,        //!< The if od the thread that created this message.
      lineNbr,         //!< The line number in the file.
      functionName,    //!< The name of the method/function in which the log
                       //!< message was created.
      fileName,        //!< The name of the file from which the log message was
                       //!< created.
      msgLevel,        //!< The severity/level of the log message.
      msgClass,        //!< The log class that the message belongs to. 
      errorNbr,        //!< The error number.
      text,            //!< The text of the og message.
      customProperty   //!< A custom property.
   };

   // Default constructor, copy constructor and destructor are fine.
   Definition() = default;
   Definition( const Definition&) = default;
   ~Definition() = default;

   // Also use default copy assignment.
   Definition& operator =( const Definition&) = default;

protected:
   friend class Creator;

   /// The data that is stored for each field.
   /// @since  1.0.0, 07.12.2016
   struct Field
   {
      /// The type of the field.
      FieldTypes   mType;
      /// Constant text or format string for date, time, ...
      std::string  mConstant;
      /// The fixed width of the field, if set.
      int          mFixedWidth;
      /// Set if the data in the field should be left-aligned.
      bool         mAlignLeft;
   };

   /// Type of the container to store the fields of the format definition.
   typedef std::vector< Field>  vector_t;

   /// The fields of the format definition.
   vector_t  mFields;

}; // Definition


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_DEFINITION_HPP


// ==========================  END OF definition.hpp  ==========================

