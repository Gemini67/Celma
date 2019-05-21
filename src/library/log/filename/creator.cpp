
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
/// See documentation of class celma::log::filename::Creator.


#include "celma/log/filename/creator.hpp"


namespace celma { namespace log { namespace filename {



/// Constructor.
/// @param[in]  dest_def  The filename definition object to store the log
///                       filename format definition in.
/// @since  1.0.0, 11.10.2017
Creator::Creator( Definition& dest_def):
   mDefs( dest_def),
   mString()
{
} // Creator::Creator



/// Adds a path/filename part with the given type. Remaining parameters must
/// be set before and are stored in the member variables.
/// @param[in]  part_type  The type of the part to add.
/// @since  1.0.0, 11.10.2017
void Creator::part( Definition::PartTypes part_type)
{

   Definition::Part  part;


   part.mType       = part_type;
   part.mConstant   = mString;
   part.mFixedWidth = mFixedWidth;
   part.mFillChar   = mFillChar;

   addPart( part);

} // Creator::part



/// Sets a fixed width for the next part, the log file number.
/// @param[in]  fixed_width  The fixed width to use for log file number.
/// @since  1.0.0, 11.10.2017
void Creator::setFixedWidth( int fixed_width)
{

   mFixedWidth = fixed_width;

} // Creator::setFixedWidth



/// Sets the fill-character to use when adding the log file number.
/// @param[in]  fill_char  The fill-character to use.
/// @since  1.0.0, 16.10.2017
void Creator::setFillChar( char fill_char)
{

   mFillChar = fill_char;

} // Creator::setFillChar



/// 
/// @since  1.0.0, 16.10.2017
void Creator::setCheckPathSeparator()
{

   mCheckPathSep = true;

} // Creator::setCheckPathSeparator()



/// Operator to handle manipulators.
/// @param[in]  m  The manipulator to call.
/// @return  This object.
/// @since  1.0.0, 11.10.2017
Creator& Creator::operator <<( Creator&( *m)( Creator&))
{

   m( *this);

   return *this;
} // operator <<



/// Operator to pass a constant string to a creator object.
/// @param[in]  c           The object to pass the constant string to.
/// @param[in]  const_text  The text part to add.<br>
///                         If the previous part was a constant text too,
///                         this text will be appended to it.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 11.10.2017
Creator& operator <<( Creator& c, const std::string& const_text)
{

   c.addConstantText( const_text);

   return c;
} // operator <<



/// Operator to pass a fixed width setting for the log file number to a
/// creator object.
/// @param[in]  c            The object to pass the fixed width to.
/// @param[in]  fixed_width  The fixed width to store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 11.10.2017
Creator& operator <<( Creator& c, int fixed_width)
{

   c.setFixedWidth( fixed_width);

   return c;
} // operator <<



/// Operator to pass the data of a 'format string' to a creator object.
/// @param[in]  c   The object to pass the format string to.
/// @param[in]  fs  The format string to store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 11.10.2017
Creator& operator <<( Creator& c, const formatString& fs)
{

   c.formatString( fs.value());

   return c;
} // operator <<



/// Operator to change the fill character to use for a fixed width log file
/// number.
/// @param[in]  c    The object to change the eparator string in.
/// @param[in]  sep  The separator string to set.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 11.10.2017
Creator& operator <<( Creator& c, char fill_char)
{

   c.setFillChar( fill_char);

   return c;
} // operator <<



/// Operator to store a path part that adds the value of the given
/// environment variable.
/// @param[in]  c   The object to pass the name of the environment variable
///                 to.
/// @param[in]  ev  The objct with the name of the environment variable to
///                 store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 19.10.2017
Creator& operator <<( Creator& c, const env_var& ev)
{

   c.addEnvVar( ev.value());

   return c;
} // operator <<



/// Called by the operator to actually store the constant text.<br>
/// Also adds the part to the log file format definition.
/// @param[in]  const_text  The constant text to store.
/// @since  1.0.0, 11.10.2017
void Creator::addConstantText( const std::string& const_text)
{

   Definition::Part  constant_part;


   constant_part.mType       = Definition::PartTypes::constant;
   constant_part.mConstant   = const_text;
   constant_part.mFixedWidth = 0;
   constant_part.mFillChar   = '\0';

   addPart( constant_part);

} // Creator::addConstantText



/// Stores a format string that should be used by the next date part.
/// @param[in]  fmt  The format string to store.
/// @since  1.0.0, 11.10.2017
void Creator::formatString( const std::string& fmt)
{

   mString = fmt;

} // Creator::formatString



/// Called by the operator to actually store the name of an environment
/// variable.<br>
/// Also adds the part to the log file format definition.
/// @param[in]  env_var_name  The name of the environment variable.
/// @since  1.0.0, 19.10.2017
void Creator::addEnvVar( const std::string& env_var_name)
{

   Definition::Part  env_var_part;


   env_var_part.mType       = Definition::PartTypes::env;
   env_var_part.mConstant   = env_var_name;
   env_var_part.mFixedWidth = 0;
   env_var_part.mFillChar   = '\0';

   addPart( env_var_part);

} // Creator::addEnvVar



/// Checks if two constant text parts can be concatenated, and if
/// #mCheckPathSep is set, checks if a path separator must be added in
/// between. Otherwise the part is added as-is to the log filename
/// definition.<br>
/// And while we're at it, prepare for the next part.
/// @param[in]  part  The part to add.
/// @since  1.0.0, 11.10.2017
void Creator::addPart( const Definition::Part& part)
{

   bool  done = false;


   if ((part.mType == Definition::PartTypes::constant) && !mDefs.mParts.empty())
   {
      auto  last = --mDefs.mParts.end();
      if (last->mType == Definition::PartTypes::constant)
      {
         if (mCheckPathSep)
         {
            const int  num_sep =
               (last->mConstant[ last->mConstant.length() - 1] == '/')
               + (part.mConstant[ 0] == '/');

            if (num_sep == 0)
               last->mConstant.append( "/");
            else if (num_sep == 2)
               last->mConstant.erase( last->mConstant.length() - 1);
         } // end if

         last->mConstant.append( part.mConstant);
         done = true;
      } // end if
   } // end if

   if (!done)
      mDefs.mParts.push_back( part);

   mString.clear();
   mFixedWidth = 0;
   mFillChar = '0';
   mCheckPathSep = false;

} // Creator::addPart



} // namespace filename
} // namespace log
} // namespace celma


// =====  END OF creator.cpp  =====

