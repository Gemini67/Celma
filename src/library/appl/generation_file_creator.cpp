
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


#include "celma/appl/generation_file_creator.hpp"


namespace celma { namespace appl {



GenerationFileCreator::GenerationFileCreator( GenerationFileDefinition& dest_def):
   mDefs( dest_def)
{
} // GenerationFileCreator::GenerationFileCreator



void GenerationFileCreator::field( GenerationFileDefinition::ElementTypes field_type)
{

   GenerationFileDefinition::Field  field;


   field.mType       = field_type;
   field.mFixedWidth = mFixedWidth;
   field.mFillChar   = mFillChar;

   mDefs.mFields.push_back( field);

   mFixedWidth = 0;
   mFillChar   = '\0';

} // GenerationFileCreator::field



void GenerationFileCreator::setFixedWidth( int fixed_width)
{

   mFixedWidth = fixed_width;

} // end if



void GenerationFileCreator::setFillChar( char fill_char)
{

   mFillChar = fill_char;

} // 



void GenerationFileCreator::setEnv( const std::string& env_var_name)
{

   GenerationFileDefinition::Field  env_field;


   env_field.mType       = GenerationFileDefinition::ElementTypes::env;
   env_field.mParamInfo  = env_var_name;

   mDefs.mFields.push_back( env_field);

   mFixedWidth = 0;
   mFillChar   = '\0';

} // 



GenerationFileCreator& operator <<( GenerationFileCreator& c, const std::string& const_text)
{

   c.addConstantText( const_text);

   return c;
} // GenerationFileCreator::operator <<



GenerationFileCreator& operator <<( GenerationFileCreator& c, int fixed_width)
{

   c.setFixedWidth( fixed_width);

   return c;
} // GenerationFileCreator::operator <<



void GenerationFileCreator::addConstantText( const std::string& const_text)
{

   GenerationFileDefinition::Field  constant_field;


   constant_field.mType       = GenerationFileDefinition::ElementTypes::constant;
   constant_field.mParamInfo  = const_text;
   constant_field.mFixedWidth = mFixedWidth;

   mDefs.mFields.push_back( constant_field);

   mFixedWidth = 0;
   mFillChar   = '\0';

} // GenerationFileCreator::addConstantText



void GenerationFileCreator::customProperty( const std::string& property_name)
{

   GenerationFileDefinition::Field  constant_field;


   constant_field.mType       = GenerationFileDefinition::ElementTypes::customProperty;
   constant_field.mParamInfo  = property_name;
   constant_field.mFixedWidth = mFixedWidth;

   mDefs.mFields.push_back( constant_field);

   mFixedWidth = 0;
   mFillChar   = '\0';

} // GenerationFileCreator::customProperty



} // namespace appl
} // namespace celma


// ===================  END OF generation_file_creator.cpp  ===================

