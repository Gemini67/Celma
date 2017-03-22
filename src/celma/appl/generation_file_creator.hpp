
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
/// See documentation of class celma::appl::GenerationFileCreator.


#ifndef CELMA_APPL_GENERATION_FILE_CREATOR_HPP
#define CELMA_APPL_GENERATION_FILE_CREATOR_HPP


#include <string>
#include "celma/appl/detail/env.hpp"
#include "celma/appl/detail/fill_char.hpp"
#include "celma/appl/detail/width.hpp"
#include "celma/appl/generation_file_definition.hpp"
#include "celma/common/custom_property.hpp"


namespace celma { namespace appl {


// bring helper classes into the same namespace
using common::customProperty;
using detail::env;
using detail::fill_char;
using detail::width;


/// Use this class to specify the elements of a generation file. Afterwards call
/// GenerationFileStringBuilder with the necessary parameters/values to actually
/// create the path and filename.<br>
/// Examples:
/// - gfc << projectPath << "/log/application_errors.log" << fileNbr( notNull, @@@
/// .
/// @since  0.12, 11.01.2017
class GenerationFileCreator
{
public:
   GenerationFileCreator( GenerationFileDefinition& dest_def);

   GenerationFileCreator&
      operator <<( GenerationFileCreator&( *m)( GenerationFileCreator&))
   {
      m( *this);
      return *this;
   }

   void field( GenerationFileDefinition::ElementTypes field_type);

   /// 
   /// @param[in]  c   .
   /// @param[in]  cp  .
   /// @return  .
   /// @since  0.12, 11.01.2017
   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              const customProperty& cp)
   {
      c.customProperty( cp.name());
      return c;
   } // end operator <<

   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              const width& w)
   {
      c.setFixedWidth( w.getWidth());
      return c;
   } // end operator <<

   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              const fill_char& fc)
   {
      c.setFillChar( fc.getFillChar());
      return c;
   } // end operator <<

   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              const env& e)
   {
      c.setEnv( e.getVarName());
      return c;
   } // end operator <<

   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              const std::string& const_text);

   friend GenerationFileCreator& operator <<( GenerationFileCreator& c,
                                              int fixed_width);

private:
   void setFixedWidth( int fixed_width);
   void setFillChar( char fill_char);
   void setEnv( const std::string& env_var_name);
   void addConstantText( const std::string& const_text);
   void customProperty( const std::string& proprty_name);

   GenerationFileDefinition&  mDefs;
   int                        mFixedWidth = 0;
   char                       mFillChar = '\0';

}; // GenerationFileCreator


inline GenerationFileCreator& date_time( GenerationFileCreator& in)
{

   in.field( GenerationFileDefinition::ElementTypes::dateTime);

   return in;
} // date_time


/// 
/// @param[in]  in  .
/// @return  .
/// @since  6.0, 30.01.2017
inline GenerationFileCreator& project_path( GenerationFileCreator& in)
{

   in.field( GenerationFileDefinition::ElementTypes::projectPath);

   return in;
} // project_path


/// 
/// @param[in]  in  .
/// @return  .
/// @since  x.y, 31.01.2017
inline GenerationFileCreator& file_nbr( GenerationFileCreator& in)
{

   in.field( GenerationFileDefinition::ElementTypes::fileNbr);

   return in;
} // file_nbr


/// 
/// @param[in]  in  .
/// @return  .
/// @since  x.y, 31.01.2017
inline GenerationFileCreator& sep( GenerationFileCreator& in)
{

   in.field( GenerationFileDefinition::ElementTypes::separator);

   return in;
} // sep


} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_GENERATION_FILE_CREATOR_HPP


// ===================  END OF generation_file_creator.hpp  ===================

