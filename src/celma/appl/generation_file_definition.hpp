
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
/// See documentation of class celma::appl::GenerationFileDefinition.


#ifndef CELMA_APPL_GENERATION_FILE_DEFINITION_HPP
#define CELMA_APPL_GENERATION_FILE_DEFINITION_HPP


#include <string>
#include <vector>


namespace celma { namespace appl {


/// In various places in an application, files with generation information are
/// used/needed: Log Files, data files etc.with date/timestamp, log file number
/// etc.<br>
/// Use this class to store the different parts of the path and file name that
/// compose the fully qualified filename.
/// @since  0.12, 11.01.2017
class GenerationFileDefinition
{
public:
   /// List of the element types that can be used to define a generation file
   /// path and name:
   enum class ElementTypes
   {
      constant,         //!< Inserts a constant text.
      dateTime,         //!< Inserts a timestamp into the file name.
      env,              //!< Inserts the value of the specified environment
                        //!< variable.
      projectPath,      //!< Inserts the current value of the project path.
      fileNbr,          //!< The number of the file.
      customProperty,   //!< A custom property, i.e. an element whose value is
                        //!< specified at runtime.
      separator         //!< Makes sure that there is exactly one path separator
                        //!< between two elements of the path.
   };

   GenerationFileDefinition() = default;
   GenerationFileDefinition( const GenerationFileDefinition&) = default;
   GenerationFileDefinition( GenerationFileDefinition&&) = default;
   ~GenerationFileDefinition() = default;

   GenerationFileDefinition& operator =( const GenerationFileDefinition&) = default;
   GenerationFileDefinition& operator =( GenerationFileDefinition&&) = default;

protected:
   friend class GenerationFileCreator;

   struct Field
   {
      ElementTypes  mType;
      std::string   mParamInfo = "";
      int           mFixedWidth = 0;
      char          mFillChar = '\0';
   };

   typedef std::vector< Field>  vector_t;

   vector_t  mFields;

}; // GenerationFileDefinition


} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_GENERATION_FILE_DEFINITION_HPP


// ==================  END OF generation_file_definition.hpp  ==================

