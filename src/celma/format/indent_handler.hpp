
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of classes celma::format::IndentHandler and
/// celma::format::ScopedIndent.


#pragma once


#include <iostream>
#include <string>


namespace celma::format {



/// Helper class to handle the spaces used for indention in formatted text like
/// XML.
/// There are two ways to use this class:
/// - Create an object and specify the initial indent level plus the size of the
///   indention, i.e. the number of spaces to increase the indention for each
///   level.
/// - To get the indention/spaces, simply pass the object into a stream.
/// - To increase the indention, create a copy of the object and use the new
///   object.<br>
///   This is best used with functions calling other functions or calling itself
///   recursively.
/// - Or you create a "scoped indent" object which increased the indention, and
///   delete this object again when the indention should be decreased again.
/// @since  1.45.0, 02.03.2021
class IndentHandler
{
public:
   /// Constructor.
   /// @param[in]  level  The level of indention to start with.
   /// @param[in]  size   Number of spaces to indent for each level.
   /// @since  1.45.0, 02.03.2021
   IndentHandler( int level, int size);

   /// Copy constructor, increases the indention by one level.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  1.45.0, 02.03.2021
   IndentHandler( const IndentHandler& other);

   /// Prefix increment operator, increases the level of indention.
   /// @return  This object.
   /// @since  1.45.0, 02.03.2021
   IndentHandler& operator ++();

   /// Prefix decrement operator, decreases the level of indention.
   /// @return  This object.
   /// @since  1.45.0, 02.03.2021
   IndentHandler& operator --();

   /// Insertion operator, prints the spaces for indention.
   /// @param[in]  os  The stream to write into.
   /// @param[in]  ih  The object with the current level of indention.
   /// @return  The stream as passed in.
   /// @since  1.45.0, 02.03.2021
   friend std::ostream& operator <<( std::ostream& os, const IndentHandler& ih);

private:
   /// The string with the spaces to currently use for indention.
   std::string  mIndention;
   /// The current level of indention.
   int          mLevel;
   /// Number of spaces to use per level of indention.
   int          mSize;

}; // IndentHandler


// inlined methods
// ===============


inline IndentHandler::IndentHandler( int level, int size):
   mIndention( level * size, ' '),
   mLevel( level),
   mSize( size)
{
} // IndentHandler::IndentHandler


IndentHandler::IndentHandler( const IndentHandler& other):
   mIndention( (other.mLevel + 1) * other.mSize, ' '),
   mLevel( other.mLevel + 1),
   mSize( other.mSize)
{
} // IndentHandler::IndentHandler


inline IndentHandler& IndentHandler::operator ++()
{
   ++mLevel;
   mIndention.assign( mLevel * mSize, ' ');
   return *this;
} // IndentHandler::operator ++


inline IndentHandler& IndentHandler::operator --()
{
   --mLevel;
   mIndention.assign( mLevel * mSize, ' ');
   return *this;
} // IndentHandler::operator --


inline std::ostream& operator <<( std::ostream& os, const IndentHandler& ih)
{
   return os << ih.mIndention;
} // operator <<


// Class ScopedIndent
// ==================


/// Increases the level of indention within a scope.
/// @since  1.45.0, 02.03.2021
class ScopedIndent
{
public:
   /// Constructor.
   /// @param[in]  ih  The object to increase the indention level on.
   /// @since  1.45.0, 02.03.2021
   ScopedIndent( IndentHandler& ih);

   /// Destructor, decreases the indention level again.
   /// @since  1.45.0, 02.03.2021
   ~ScopedIndent();

private:
   /// The object on which the indention level is increased/decreased.
   IndentHandler&  mIndentHandler;

};  // ScopedIndent


// inlined methods
// ===============


inline ScopedIndent::ScopedIndent( IndentHandler& ih):
   mIndentHandler( ih)
{
   ++ih;
} // ScopedIndent::ScopedIndent


inline ScopedIndent::~ScopedIndent()
{
   --mIndentHandler;
} // ScopedIndent::~ScopedIndent


} // namespace celma::format


// =====  END OF indent_handler.hpp  =====

