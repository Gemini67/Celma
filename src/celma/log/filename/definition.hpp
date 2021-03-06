
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filename::Definition.


#ifndef CELMA_LOG_FILENAME_DEFINITION_HPP
#define CELMA_LOG_FILENAME_DEFINITION_HPP


#include <algorithm>
#include <string>
#include <vector>


namespace celma { namespace log { namespace filename {


/// Stores the definition of the format of a log filename.
/// @since  1.26.0, 21.02.2018  (pid added)
/// @since  1.0.0, 11.10.2017
class Definition
{
public:
   /// List of the parts which a log filename definition can contain:
   enum class PartTypes
   {
      constant,   //!< Constant part of the path and/or filename.
      env,        //!< An environment variable whose value is evaluated only
                  //!< when a logfile name is created.
      date,       //!< Date as part of the path/filename.
      number,     //!< Log file number.
      pid         //!< Process-id as part of the path/filename.
   };

   // Default constructor, copy constructor and destructor are fine.
   Definition() = default;
   Definition( const Definition&) = default;
   ~Definition() = default;

   // Also use default copy assignment.
   Definition& operator =( const Definition&) = default;

   /// Returns if this file name definition includes a log file generation
   /// number.
   ///
   /// @return  \c true if the definition includes a (generation) number.
   /// @since  1.0.0, 20.12.2017
   bool hasGenerationNbr() const;

   /// Returns if this file name definition includes a date field.
   ///
   /// @return  \c true if the definition includes a date field.
   /// @since  1.0.0, 21.12.2017
   bool hasDateField() const;

   /// Returns if the current filename definition is empty, i.e. contains no
   /// parts yet.
   ///
   /// @return  \c true if the current definition is (still) empty.
   /// @since  1.25.0, 03.05.2019
   bool empty() const;

protected:
   friend class Creator;

   /// The data that is stored for each part.
   ///
   /// @since  1.0.0, 11.10.2017
   struct Part
   {
      /// The type of the field.
      PartTypes    mType;
      /// Constant text or format string for date, time, ...
      std::string  mConstant;
      /// The fixed width of the number field, if set.
      int          mFixedWidth;
      /// The fill character for the number field, if set.
      char         mFillChar;
   };

   /// Type of the container to store the fields of the format definition.
   using vector_t = std::vector< Part>;

   /// The parts of the filename definition.
   vector_t  mParts;

}; // Definition


// inlined methods
// ===============


inline bool Definition::hasGenerationNbr() const
{
   return std::find_if( mParts.begin(), mParts.end(), []( auto const& part)
      {
         return part.mType == PartTypes::number;
      }) != mParts.end();
} // Definition::hasGenerationNbr


inline bool Definition::hasDateField() const
{
   return std::find_if( mParts.begin(), mParts.end(), []( auto const& part)
      {
         return part.mType == PartTypes::date;
      }) != mParts.end();
} // Definition::hasDateField


inline bool Definition::empty() const
{
   return mParts.empty();
} // Definition::empty


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_DEFINITION_HPP


// =====  END OF definition.hpp  =====

