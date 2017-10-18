
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
/// See documentation of class celma::log::filename::Definition.


#ifndef CELMA_LOG_FILENAME_DEFINITION_HPP
#define CELMA_LOG_FILENAME_DEFINITION_HPP


#include <string>
#include <vector>


namespace celma { namespace log { namespace filename {


/// Stores the definition of a the format of a filename.
/// @since  x.y.z, 11.10.2017
class Definition
{
public:
   /// List of the parts which a log filename definition can contain:
   enum class PartTypes
   {
      constant,   //!< Constant part of the path and/or filename.
      date,       //!< Date as part of the path/filename.
      number      //!< Log file number.
   };

   // Default constructor, copy constructor and destructor are fine.
   Definition() = default;
   Definition( const Definition&) = default;
   ~Definition() = default;

   // Also use default copy assignment.
   Definition& operator =( const Definition&) = default;

protected:
   friend class Creator;

   /// The data that is stored for each part.
   /// @since  x.y.z, 11.10.2017
   struct Part
   {
      /// The type of the field.
      PartTypes    mType;
      /// Constant text or format string for date, time, ...
      std::string  mConstant;
      /// The fixed width of the number field, if set.
      int          mFixedWidth;
      /// The fill character for the number field, if set.
      int          mFillChar;
   };

   /// Type of the container to store the fields of the format definition.
   typedef std::vector< Part>  vector_t;

   /// The parts of the filename definition.
   vector_t  mParts;

}; // Definition


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_DEFINITION_HPP


// ==========================  END OF definition.hpp  ==========================

