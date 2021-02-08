
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
/// See documentation of template class celma::common::FixedString<>.


#pragma once


#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include "celma/common/length_type.hpp"
#include "celma/common/detail/fixed_string_iterator.hpp"
#include "celma/common/detail/fixed_string_reverse_iterator.hpp"


namespace celma::common {


/// Class to handle a string with a fixed length.
/// The interface of this class corresponds to the interface of std::string,
/// hence the function names that differ from the usual naming scheme.<br>
/// All functions of this class make sure that the string is terminated with a
/// trailing zero. If an operation would exceed the maximum string length, the
/// surplus characters are silently ignored.<br>
/// The only methods that may throw in this class are those where their
/// counterpart in the std::string class throws.<br>
/// The design of this class e.g. also allows to store the fixed string in
/// shared memory.
/// @tparam  L  The length of the string to handle, without the trailing zero.
/// @since  x.y.z, 13.01.2021
/// @todo  Every append(), insert() or replace() method that takes iterator(s)
///        as parameter should also be implemented accepting iterators from a
///        fixed string with a different length.
/// @todo  Every append(), insert() or replace() method that takes iterator(s)
///        as parameter should also be implemented accepting std::string
///        iterators.
/// @todo  Add sprintf() method, internally implemented using snprintf().
/// @todo  Add stream interface (separate class).
template< size_t L> class FixedString
{
public:
   using iterator = detail::FixedStringIterator< char, FixedString< L>>;
   using const_iterator = detail::FixedStringIterator< const char,
      const FixedString< L>>;
   using reverse_iterator = detail::FixedStringReverseIterator< char,
      FixedString< L>>;
   using const_reverse_iterator =
      detail::FixedStringReverseIterator< const char, const FixedString< L>>;

   /// Default constructor for an empty string.
   /// @since  x.y.z, 13.01.2021
   FixedString() = default;

   /// Copies the given C string.
   /// @param[in]  str  The string to copy.
   /// @since  x.y.z, 13.01.2021
   explicit FixedString( const char* str) noexcept;

   /// Copies the given std::string.
   /// @param[in]  str  The string to copy.
   /// @since  x.y.z, 13.01.2021
   explicit FixedString( const std::string& str) noexcept;

   /// Default copy constructor is fine.
   FixedString( const FixedString&) = default;

   /// Copies the string from another fixed string object with a different
   /// maximum length.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  other  The other fixed string object to copy the string from.
   /// @since  x.y.z, 13.01.2021
   template< size_t S> FixedString( const FixedString< S>& other) noexcept;

   /// Move constructor.
   /// @param[in]  other The other string object to copy from.
   /// @since  x.y.z, 13.01.2021
   FixedString( FixedString&& other) noexcept;

   /// Default destructor is fine.
   /// @since  x.y.z, 13.01.2021
   ~FixedString() = default;

   /// Returns the internal string in an std::string object.
   /// @return  std::string with a copy of the internal string.
   /// @since  x.y.z, 13.01.2021
   std::string str() const noexcept;

   /// Returns a pointer to the internal C string.
   /// @return  The internal C string.
   /// @since  x.y.z, 13.01.2021
   const char* c_str() const noexcept;

   /// Returns the length of the string.
   /// This is the number of characters currently stored in the string, without
   /// the trailing zero.
   /// @return  The length of the string.
   /// @since  x.y.z, 13.01.2021
   size_t length() const noexcept;

   /// Returns if the string is currently empty.
   /// @return  \c true if the string is empty.
   /// @since  x.y.z, 15.01.2021
   bool empty() const noexcept;

   /// Assigns the given C string.
   /// @param[in]  str  Pointer to the C string to assign.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   FixedString& assign( const char* str) noexcept;

   /// Assigns the contents of the given std::string.
   /// @param[in]  str  The std::string to copy the string from.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   FixedString& assign( const std::string& str) noexcept;

   /// Assigns the contents from another fixed string object.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string object to copy the string from.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   template< size_t S> FixedString& assign( const FixedString< S>& str) noexcept;

   /// Clears the string.
   /// @since  x.y.z, 13.01.2021
   void clear() noexcept;

   /// Returns the character at the given position, with range checking.
   /// @param[in]  idx  The position/index of the character to return.
   /// @return  The character at the given position.
   /// @throws
   ///    std::out_of_range if the given index is after the end of the string.
   /// @since  x.y.z, 14.01.2021
   char& at( size_t idx) noexcept( false);

   /// Returns the character at the given position, with range checking.
   /// @param[in]  idx  The position/index of the character to return.
   /// @return  The non-modifyable character at the given position.
   /// @throws
   ///    std::out_of_range if the given index is after the end of the string.
   /// @since  x.y.z, 14.01.2021
   const char& at( size_t idx) const noexcept( false);

   /// Returns the character at the given position, without any range checking.
   /// If the given index is invalid, i.e. after the end of the string or even
   /// after the end of the buffer, the behaviour is undefined.
   /// @param[in]  idx  The position/index of the character to return.
   /// @return  The character at the given position.
   /// @since  x.y.z, 14.01.2021
   char& operator []( size_t idx) noexcept;

   /// Returns the character at the given position, without any range checking.
   /// If the given index is invalid, i.e. after the end of the string or even
   /// after the end of the buffer, the behaviour is undefined.
   /// @param[in]  idx  The position/index of the character to return.
   /// @return  The character at the given position.
   /// @since  x.y.z, 14.01.2021
   const char& operator []( size_t idx) const noexcept;

   /// Returns the first character of the string.
   /// If the string buffer is empty, this returns the zero character.
   /// @return  The first character of the string.
   /// @since  x.y.z, 14.01.2021
   char& front() noexcept;

   /// Returns the first character of the string.
   /// If the string buffer is empty, this returns the zero character.
   /// @return  The first character of the string.
   /// @since  x.y.z, 14.01.2021
   const char& front() const noexcept;

   /// Returns the last character of the string.
   /// If the string buffer is empty, this returns the zero character.
   /// @return  The last character of the string.
   /// @since  x.y.z, 14.01.2021
   char& back() noexcept;

   /// Returns the last character of the string.
   /// If the string buffer is empty, this returns the zero character.
   /// @return  The last character of the string.
   /// @since  x.y.z, 14.01.2021
   const char& back() const noexcept;

   /// Returns the internal C string.
   /// @return  Pointer to the internal C string.
   /// @since  x.y.z, 14.01.2021
   char* data() noexcept;

   /// Returns the internal C string.
   /// @return  Pointer to the internal C string.
   /// @since  x.y.z, 14.01.2021
   const char* data() const noexcept;

   /// Returns an iterator pointing to the first character of the string.
   /// @return  Iterator pointing to the beginning of the string.
   /// @since  x.y.z, 22.01.2021
   iterator begin() noexcept;

   /// Returns a const iterator pointing to the first character of the string.
   /// @return  Const iterator pointing to the beginning of the string.
   /// @since  x.y.z, 22.01.2021
   const_iterator begin() const noexcept;

   /// Returns a const iterator pointing to the first character of the string.
   /// @return  Const iterator pointing to the beginning of the string.
   /// @since  x.y.z, 22.01.2021
   const_iterator cbegin() const noexcept;

   /// Returns an iterator pointing behind the last character of the string.
   /// @return  Iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   iterator end() noexcept;

   /// Returns a const iterator pointing behind the last character of the string.
   /// @return  Const iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   const_iterator end() const noexcept;

   /// Returns a const iterator pointing behind the last character of the string.
   /// @return  Const iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   const_iterator cend() const noexcept;

   /// Returns a reverse iterator pointing to the last character of the string.
   /// @return  Reverse iterator pointing to the last character of the string.
   /// @since  x.y.z, 22.01.2021
   reverse_iterator rbegin() noexcept;

   /// Returns a const reverse iterator pointing to the last character of the
   /// string.
   /// @return  Const reverse iterator pointing to the last character of the
   ///         string.
   /// @since  x.y.z, 22.01.2021
   const_reverse_iterator rbegin() const noexcept;

   /// Returns a const reverse iterator pointing to the last character of the
   /// string.
   /// @return  Const reverse iterator pointing to the last character of the
   ///         string.
   /// @since  x.y.z, 22.01.2021
   const_reverse_iterator crbegin() const noexcept;

   /// Returns a reverse iterator pointing behind the end of the string.
   /// @return  Reverse iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   reverse_iterator rend() noexcept;

   /// Returns a const reverse iterator pointing behind the end of the string.
   /// @return  Const reverse iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   const_reverse_iterator rend() const noexcept;

   /// Returns a const reverse iterator pointing behind the end of the string.
   /// @return  Const reverse iterator pointing behind the end of the string.
   /// @since  x.y.z, 22.01.2021
   const_reverse_iterator crend() const noexcept;

   /// Insert \a count repetitions of the character \a ch at the given position.
   /// @param[in]  index  The position to insert the repeated characters at.
   /// @param[in]  count  Number of times to insert the character.
   /// @param[in]  ch     The character to insert.
   /// @return  This object.
   /// @since  x.y.z, 14.01.2021
   FixedString& insert( size_t index, size_t count, char ch) noexcept;

   /// Inserts \a count characters of the given C string at the given position.
   /// @param[in]  index  The position/index to insert the part of the C string.
   /// @param[in]  str    Pointer to the string to insert.
   /// @param[in]  count  Number of characters from the C string to insert.
   /// @return  This object.
   /// @since  x.y.z, 14.01.2021
   FixedString& insert( size_t index, const char* str, size_t count) noexcept;

   /// Inserts a C string.
   /// @param[in]  index  The position/index to insert the C string.
   /// @param[in]  str    The C string to insert.
   /// @return  This object.
   /// @since  x.y.z, 14.01.2021
   FixedString& insert( size_t index, const char* str) noexcept;

   /// Inserts a std::string.
   /// @param[in]  index  The position/index to insert the std::string.
   /// @param[in]  str    The std::string with the text to insert.
   /// @return  This object.
   /// @since  x.y.z, 14.01.2021
   FixedString& insert( size_t index, const std::string& str) noexcept;

   /// Inserts the substring (\a index_str, \a count) from the std::string.
   /// @param[in]  index      The position/index to insert the part from the
   ///                        std::string.
   /// @param[in]  str        The std::string to insert a part from.
   /// @param[in]  index_str  Start position in the std::string to copy from.
   /// @param[in]  count      Number of characters to copy from the std::string.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& insert( size_t index, const std::string& str, size_t index_str,
      size_t count = std::string::npos) noexcept;

   /// Inserts a fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  index  The position/index to insert the fixed string.
   /// @param[in]  str    The other fixed string object to copy the text from.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   template< size_t S>
      FixedString& insert( size_t index, const FixedString< S>& str) noexcept;

   /// Inserts a part of a fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  index      The position/index to insert the part of the fixed
   ///                        string.
   /// @param[in]  str        The other fixed string object to copy the text
   ///                        from.
   /// @param[in]  index_str  Start position in the fixed string to copy from.
   /// @param[in]  count      Number of characters to copy from the other fixed
   ///                        string.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   template< size_t S>
      FixedString& insert( size_t index, const FixedString< S>& str,
         size_t index_str, size_t count = std::string::npos) noexcept;

   /// Inserts the given character at the given position.
   /// @param[in]  pos  Iterator pointing to the position to insert the
   ///                  character.
   /// @param[in]  ch   The character to insert.
   /// @return  Iterator pointing to the position where the character was
   ///          inserted, pointing to end if the given position was invalid.
   /// @since  x.y.z, 25.01.2021
   iterator insert( const_iterator pos, char ch) noexcept;

   /// Inserts \a count repetitions of the given character at the given position.
   /// @param[in]  pos    Iterator pointing to the position to insert the
   ///                    character(s>.
   /// @param[in]  count  Number of repetitions of the character to insert.
   /// @param[in]  ch     The character to insert.
   /// @return  Iterator pointing to the position of the first character that
   ///          was inserted, pointing to the if the given position was invalid.
   /// @since  x.y.z, 25.01.2021
   iterator insert( const_iterator pos, size_t count, char ch) noexcept;

   /// Inserts the string from the initializer list at the given position.
   /// @param[in]  pos    The position to insert.
   /// @param[in]  ilist  The list of characters to insert.
   /// @return  Iterator pointing to the position of the first character that
   ///          was inserted, pointing to the if the given position was invalid.
   /// @since  x.y.z, 25.01.2021
   iterator insert( const_iterator pos, std::initializer_list< char> ilist)
      noexcept;

   /// Erases \a count characters from the string, starting at position \a index.
   /// If no count is given, everything starting from a index is deleted.
   /// @param[in]  index  The index of the first character to delete.
   /// @param[in]  count  Number of characters to delete, when not set
   ///                    everything to the end of the string is deleted.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& erase( size_t index = 0, size_t count = std::string::npos)
      noexcept;

   /// Erases the character at the given position.
   /// @param[in]  position  Iterator poiting to the character to erase.
   /// @return  Iterator pointing to the position where the character was
   ///          erased, poiting to end if the position was invalid.
   /// @since  x.y.z, 25.01.2021
   iterator erase( const_iterator position) noexcept;

   /// Erases all characters in the range [first, last).
   /// @param[in]  first  Iterator pointing to the first character to erase.
   /// @param[in]  last   Iterator pointing behind the last character to erase.
   /// @return  Iterator pointing to the position where the first character was
   ///          erased, poiting to end if the position was invalid.
   /// @since  x.y.z, 25.01.2021
   iterator erase( const_iterator first, const_iterator last) noexcept;

   /// Pushes the given character to the end of the string.
   /// @param[in]  ch  The character to push to the end of the string.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& push_back( char ch) noexcept;

   /// Pops the last character from the end of the string.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& pop_back() noexcept;

   /// Appends \a count repetitions of the given character to the string.
   /// @param[in]  count  Number of repetitions of the character to append.
   /// @param[in]  ch     The character to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& append( size_t count, char ch) noexcept;

   /// Appends a std::string.
   /// @param[in]  str  The std::string with the text to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& append( const std::string& str) noexcept;

   /// Appends the contents of another fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  fs  The other fixed string to append the contents of.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   template< size_t S> FixedString& append( const FixedString< S>& fs) noexcept;

   /// Appends a part of a std::string.
   /// @param[in]  str    The std::string with the text to append.
   /// @param[in]  pos    The position of the first character in \a str to
   ///                    append.
   /// @param[in]  count  Number of characters from \a str to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& append( const std::string& str, size_t pos,
      size_t count = std::string::npos) noexcept;

   /// Appends a part of another fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str    The other fixed string to append a part of its text
   ///                    from.
   /// @param[in]  pos    Start position of the substring in \a str to append.
   /// @param[in]  count  Number of characters from \a str to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   template< size_t S> FixedString& append( const FixedString< S>& str,
      size_t pos, size_t count = std::string::npos) noexcept;

   /// Appends a C string.
   /// @param[in]  str    Pointer to the C string (character array) to append.
   /// @param[in]  count  Number of characters from \a str to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& append( const char* str, size_t count) noexcept;

   /// Appends a C string.
   /// @param[in]  str  Pointer to the C string (character array) to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& append( const char* str) noexcept;

   /// Appends the characters from the range [first, last).
   /// @param[in]  first  Iterator pointing to the first character to append.
   /// @param[in]  last   Iterator pointing behind the last character to append.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& append( const_iterator first, const_iterator last) noexcept;

/*
   template< size_t S>
      FixedString& append( typename FixedString< S>::const_iterator first,
         typename FixedString< S>::const_iterator last) noexcept;
*/

   /// Appends the contents from another fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string to append the text from.
   /// @return  This object.
   /// @since  x.y.z, 18.01.2021
   template< size_t S> FixedString& operator +=( const FixedString< S>& str)
      noexcept;

   /// Appends to contents from a std::string.
   /// @param[in]  str  The std::string to append the contents from.
   /// @return  This object.
   /// @since  x.y.z, 18.01.2021
   FixedString& operator +=( const std::string& str) noexcept;

   /// Appends a C string.
   /// @param[in]  str  The C string to append.
   /// @return  This object.
   /// @since  x.y.z, 18.01.2021
   FixedString& operator +=( const char* str) noexcept;

   /// Appends a single character.
   /// @param[in]  ch  The character to append.
   /// @return  This object.
   /// @since  x.y.z, 18.01.2021
   FixedString& operator +=( char ch) noexcept;

   /// Compares the string against the one of another fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  fs  The other fixed string object to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   template< size_t S> int compare( const FixedString< S>& fs) const noexcept;

   /// Compares the string against the one of a std::string.
   /// @param[in]  fs  The std::string object to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( const std::string& str) const noexcept;

   /// Compares the string against a C string.
   /// @param[in]  fs  The C string object to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( const char* str) const noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) against the
   /// other fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The other fixed string to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   template< size_t S>
      int compare( size_t pos1, size_t count1, const FixedString< S>& str) const
         noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) against the
   /// std::string.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The std::string to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( size_t pos1, size_t count1, const std::string& str) const
      noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) against the C
   /// string.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The C string to compare against.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( size_t pos1, size_t count1, const char* str) const noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) of this string
   /// against the range [pos2, pos2+count2) of the other fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The other fixed string to compare against.
   /// @param[in]  pos2    The position of the first character in the other
   ///                     fixed string to start the comparison with.
   /// @param[in]  count2  Number of characters from the other fixed string to
   ///                     compare.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   template< size_t S>
      int compare( size_t pos1, size_t count1, const FixedString< S>& str,
         size_t pos2, size_t count2) const noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) of this string
   /// against the range [pos2, pos2+count2) of the std::string.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The other fixed string to compare against.
   /// @param[in]  pos2    The position of the first character in the std::fixed
   ///                     string to start the comparison with.
   /// @param[in]  count2  Number of characters from the std::string to compare.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( size_t pos1, size_t count1, const std::string& str,
      size_t pos2, size_t count2) const noexcept;

   /// Compares the characters in the range [pos1, pos1+count1) of this string
   /// against the \a count2 characters of the C string.
   /// @param[in]  pos1    The position of the first character to start the
   ///                     comparison with.
   /// @param[in]  count1  Number of characters to compare.
   /// @param[in]  str     The C string to compare against.
   /// @param[in]  count2  Number of characters from the C to compare.
   /// @return
   ///    - value &lt; 0: this string is smaller than the other.
   ///    - value = 0: both strings are equal.
   ///    - value &gt; 0: the other string is smaller than this.
   /// @since  x.y.z, 18.01.2021
   int compare( size_t pos1, size_t count1, const char* str, size_t count2)
      const noexcept;

   /// Returns if the first characters of this string match those in the other
   /// fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string object to compare against.
   /// @return  \c true if the first characters of this string match those in
   ///          the other fixed string.
   /// @since  x.y.z, 18.01.2021
   template< size_t S> bool starts_with( const FixedString< S>& str) const
      noexcept;

   /// Returns if the first characters of this string match those in the
   /// std::string.
   /// @param[in]  str  The std::string object to compare against.
   /// @return  \c true if the first characters of this string match those in
   ///          the std::string.
   /// @since  x.y.z, 20.01.2021
   bool starts_with( const std::string& str) const noexcept;

   /// Returns if the first characters of this string match those in the C
   /// string.
   /// @param[in]  str  The C string to compare against.
   /// @return  \c true if the first characters of this string match those in
   ///          the C string.
   /// @since  x.y.z, 20.01.2021
   bool starts_with( const char* str) const noexcept;

   /// Returns if the string starts with the given character.
   /// @param[in]  ch  The character to compare against.
   /// @return  \c true if the string starts with this character.
   /// @since  x.y.z, 20.01.2021
   bool starts_with( char ch) const noexcept;

   /// Returns if the last characters of this string match those in the other
   /// fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string object to compare against.
   /// @return  \c true if the last characters of this string match those in the
   ///          other fixed string.
   /// @since  x.y.z, 20.01.2021
   template< size_t S> bool ends_with( const FixedString< S>& str) const
      noexcept;

   /// Returns if the last characters of this string match those in the
   /// std::string.
   /// @param[in]  str  The std::string object to compare against.
   /// @return  \c true if the last characters of this string match those in the
   ///          std::string.
   /// @since  x.y.z, 20.01.2021
   bool ends_with( const std::string& str) const noexcept;

   /// Returns if the last characters of this string match those in the C
   /// string.
   /// @param[in]  str  The C string to compare against.
   /// @return  \c true if the last characters of this string match those in the
   ///          C string.
   /// @since  x.y.z, 20.01.2021
   bool ends_with( const char* str) const noexcept;

   /// Returns if the string ends with the given character.
   /// @param[in]  ch  The character to compare against.
   /// @return  \c true if the string ends with this character.
   /// @since  x.y.z, 20.01.2021
   bool ends_with( char ch) const noexcept;

   /// Returns if this string contains a sub-string equal to that in the other
   /// fixed string object.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string object with the sub-string to
   ///                  search.
   /// @return  \c true if this string contains a sub-string equal to that in
   ///          \a str.
   /// @since  x.y.z, 20.01.2021
   template< size_t S> bool contains( const FixedString< S>& str) const noexcept;

   /// Returns if this string contains a sub-string equal to that in the
   /// std::string.
   /// @param[in]  str  The std::string object with the sub-string to search.
   /// @return  \c true if this string contains a sub-string equal to that in
   ///          \a str.
   /// @since  x.y.z, 20.01.2021
   bool contains( const std::string& str) const noexcept;

   /// Returns if this string contains a sub-string equal to that in the C
   /// string.
   /// @param[in]  str  The C string to search.
   /// @return  \c true if this string contains a sub-string equal to that in
   ///          \a str.
   /// @since  x.y.z, 20.01.2021
   bool contains( const char* str) const noexcept;

   /// Returns if the string contains the given character.
   /// @param[in]  ch  The character to search for.
   /// @return  \c true if this string contains the given character.
   /// @since  x.y.z, 20.01.2021
   bool contains( char ch) const noexcept;

   /// Replaces the sub-string in the range [pos, pos+count) with the contents
   /// of the other fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  pos    The position of the first character to replace.
   /// @param[in]  count  Number of characters in this string to replace.
   /// @param[in]  str    Another fixed string with the string to insert here.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   template< size_t S> FixedString& replace( size_t pos, size_t count,
      const FixedString< S>& str) noexcept;

   /// Replaces the sub-string in the range [pos, pos+count) with the contents
   /// of the std::string.
   /// @param[in]  pos    The position of the first character to replace.
   /// @param[in]  count  Number of characters in this string to replace.
   /// @param[in]  str    A std::string with the string to insert here.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedString& replace( size_t pos, size_t count, const std::string& str)
      noexcept;

   /// Replaces the sub-string in the range [pos1, pos1+count1) with the
   /// sub-string in the range [pos2, pos2+count2) from the other fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  pos1    The position of the first character to replace.
   /// @param[in]  count1  Number of characters in this string to replace.
   /// @param[in]  str     Another fixed string with the string to insert here.
   /// @param[in]  pos2    The position of the first character in the other
   ///                     fixed string to use for replacement.
   /// @param[in]  count2  Number of characters from the other fixed string to
   ///                     use for replacement.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   template< size_t S>
      FixedString& replace( size_t pos1, size_t count1,
         const FixedString< S>& str, size_t pos2,
         size_t count2 = std::string::npos) noexcept;

   /// Replaces the sub-string in the range [pos1, pos1+count1) with the
   /// sub-string in the range [pos2, pos2+count2) from the std::string.
   /// @param[in]  pos1    The position of the first character to replace.
   /// @param[in]  count1  Number of characters in this string to replace.
   /// @param[in]  str     A std::string with the string to insert here.
   /// @param[in]  pos2    The position of the first character in the
   ///                     std::string to use for replacement.
   /// @param[in]  count2  Number of characters from the std::string to use for
   ///                     replacement.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedString& replace( size_t pos1, size_t count1, const std::string& str,
      size_t pos2, size_t count2 = std::string::npos) noexcept;

   /// Replaces the sub-string in the range [first, last) with the sub-string in
   /// the range [first2, last2).
   /// @param[in]  first   Iterator pointing to the first character to replace.
   /// @param[in]  last    Iterator pointing behind the last character to
   ///                     replace.
   /// @param[in]  first2  Iterator pointing to the first character to use for
   ///                     replacement.
   /// @param[in]  last2   Iterator pointing behind the last character to use
   ///                     for replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      iterator first2, iterator last2) noexcept;

   /// Replaces the sub-string in the range [first, last) with the sub-string in
   /// the range [first2, last2).
   /// @param[in]  first   Iterator pointing to the first character to replace.
   /// @param[in]  last    Iterator pointing behind the last character to
   ///                     replace.
   /// @param[in]  first2  Iterator pointing to the first character to use for
   ///                     replacement.
   /// @param[in]  last2   Iterator pointing behind the last character to use
   ///                     for replacement.
   /// @return  This object.
   /// @since  x.y.z, 28.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      std::string::iterator first2, std::string::iterator last2) noexcept;

   /// Replaces the sub-string in the range [first, last) with the characters
   /// from the beginning of the C string.
   /// @param[in]  first   Iterator pointing to the first character to replace.
   /// @param[in]  last    Iterator pointing behind the last character to
   ///                     replace.
   /// @param[in]  str     Pointer to the C string to use for the replacement.
   /// @param[in]  count2  Number of characters from the C string to use for the
   ///                     replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      const char* str, size_t count2) noexcept;

   /// Replaces the sub-string in the range [pos1, pos1+count1) with the
   /// contents of the C string.
   /// @param[in]  pos1    The position of the first character to replace.
   /// @param[in]  count1  Number of characters in this string to replace.
   /// @param[in]  str     Pointer to the C string to use for the replacement.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedString& replace( size_t pos1, size_t count1, const char* str) noexcept;

   /// Replaces the sub-string in the range [pos1, pos1+count1) with the
   /// characters from the beginning of the C string.
   /// @param[in]  pos1    The position of the first character to replace.
   /// @param[in]  count1  Number of characters in this string to replace.
   /// @param[in]  str     Pointer to the C string to use for the replacement.
   /// @param[in]  count2  Number of characters from the C string to use for the
   ///                     replacement.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedString& replace( size_t pos1, size_t count1, const char* str,
      size_t count2) noexcept;

   /// Replaces the sub-string in the range [first, last) with the contents of
   /// the C string.
   /// @param[in]  first   Iterator pointing to the first character to replace.
   /// @param[in]  last    Iterator pointing behind the last character to
   ///                     replace.
   /// @param[in]  str     Pointer to the C string to use for the replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      const char* str) noexcept;

   /// Replaces the sub-string in the range [pos, pos+count) with \a count2
   /// repetitions of the given character.
   /// @param[in]  pos     The position of the first character to replace.
   /// @param[in]  count   Number of characters in this string to replace.
   /// @param[in]  count2  Number of repetitions of the character to use for the
   ///                     replacement.
   /// @param[in]  ch      The character to use for the replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( size_t pos, size_t count, size_t count2, char ch)
      noexcept;

   /// Replaces the sub-string in the range [first, last) with \a count2
   /// repetitions of the given character.
   /// @param[in]  first   Iterator pointing to the first character to replace.
   /// @param[in]  last    Iterator pointing behind the last character to
   ///                     replace.
   /// @param[in]  count2  Number of repetitions of the character to use for the
   ///                     replacement.
   /// @param[in]  ch      The character to use for the replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      size_t count2, char ch) noexcept;

   /// Replaces the sub-string in the range [first, last) with the contents of
   /// the initializer list.
   /// @param[in]  first  Iterator pointing to the first character to replace.
   /// @param[in]  last   Iterator pointing behind the last character to
   ///                    replace.
   /// @param[in]  ilist  The initializer list with the characters to use for
   ///                    the replacement.
   /// @return  This object.
   /// @since  x.y.z, 25.01.2021
   FixedString& replace( const_iterator first, const_iterator last,
      std::initializer_list< char> ilist) noexcept;

/*
   template< typename S> FixedString& replace( const S& orig, const S& subst);
*/

   /// Returns the substring with the range[pos, pos+count).
   /// @param[in]  pos    The starting position of the substring to return.
   /// @param[in]  count  Number of characters to return with the substring,
   ///                    if not set everything after the start position is
   ///                    returned.
   /// @return  A std::string object with the specified substring.
   /// @since  x.y.z, 25.01.2021
   std::string substr( size_t pos, size_t count = std::string::npos) noexcept;

   /// Copies \a count characters into the given C string.
   /// @param[in]  dest   The C string to copy the string into.
   /// @param[in]  count  Number of characters to copy.
   /// @param[in]  pos    Starting position for copying, if not set copying
   ///                    starts at the beginning of the string.
   /// @return  Number of characters that were actually copied.
   /// @since  x.y.z, 25.01.2021
   size_t copy( char* dest, size_t count, size_t pos = 0) noexcept;

   /// Swaps the contents == string between this object and the other fixed
   /// string.
   /// @param[in]  other  The other fixed string to swap the contents with.
   /// @since  x.y.z, 25.01.2021
   void swap( FixedString& other) noexcept;

/*
   template< size_t S> void swap( FixedString< S>& other) noexcept;
*/

   /// Searches for the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Start position for searching, if not set searching
   ///                  starts at the beginning of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t find( const FixedString& str, size_t pos = 0) const noexcept;

   /// Searches for the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Start position for searching, if not set searching
   ///                  starts at the beginning of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t find( const std::string& str, size_t pos = 0) const noexcept;

   /// Searches for the given string.
   /// @param[in]  str    The string to search for.
   /// @param[in]  pos    Start position for searching, if not set searching
   ///                    starts at the beginning of the string.
   /// @param[in]  count  Length of the string to search for.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t find( const char* str, size_t pos, size_t count) const noexcept;

   /// Searches for the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Start position for searching, if not set searching
   ///                  starts at the beginning of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t find( const char* str, size_t pos = 0) const noexcept;

   /// Searches for the given character.
   /// @param[in]  ch   The single character to search for.
   /// @param[in]  pos  Start position for searching, if not set searching
   ///                  starts at the beginning of the string.
   /// @return  The index of the position where the character was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t find( char ch, size_t pos = 0) const noexcept;

   /// Searches backwards from the end of the string to find the last occurrence
   /// of the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Starting position for searching the string, if not set
   ///                  searching starts at the end of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t rfind( const FixedString& str, size_t pos = std::string::npos) const
      noexcept;

   /// Searches backwards from the end of the string to find the last occurrence
   /// of the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Starting position for searching the string, if not set
   ///                  searching starts at the end of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t rfind( const std::string& str, size_t pos = std::string::npos) const
      noexcept;

   /// Searches backwards from the end of the string to find the last occurrence
   /// of the given string.
   /// @param[in]  str    The string to search for.
   /// @param[in]  pos    Starting position for searching the string, if not set
   ///                    searching starts at the end of the string.
   /// @param[in]  count  Number of characters of the given string to search for.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t rfind( const char* str, size_t pos, size_t count) const noexcept;

   /// Searches backwards from the end of the string to find the last occurrence
   /// of the given string.
   /// @param[in]  str  The string to search for.
   /// @param[in]  pos  Starting position for searching the string, if not set
   ///                  searching starts at the end of the string.
   /// @return  The index of the position where the string was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t rfind( const char* str, size_t pos = std::string::npos) const noexcept;

   /// Searches backwards from the end of the string to find the last occurrence
   /// of the given character.
   /// @param[in]  ch   The single character to search for.
   /// @param[in]  pos  Starting position for searching the character, if not
   ///                  set searching starts at the end of the string.
   /// @return  The index of the position where the character was found,
   ///          std::string::npos if the string was not found.
   /// @since  x.y.z, 26.01.2021
   size_t rfind( char ch, size_t pos = std::string::npos) const noexcept;

   /// Searches for the first occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the beginning of the string.
   /// @return  The index of the position where one of the characters was found,
   ///          std::string::npos if none of those characters were found.
   /// @since  x.y.z, 26.01.2021
   size_t find_first_of( const FixedString& str, size_t pos = 0) const noexcept;

   /// Searches for the first occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the beginning of the string.
   /// @return  The index of the position where one of the characters was found,
   ///          std::string::npos if none of those characters were found.
   /// @since  x.y.z, 26.01.2021
   size_t find_first_of( const std::string& str, size_t pos = 0) const noexcept;

   /// Searches for the first occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str    The string with the characters to search for.
   /// @param[in]  pos    Starting position for searching the characters, if not
   ///                    set searching starts at the beginning of the string.
   /// @param[in]  count  Number of characters in the string to actually use for
   ///                    searching. The range [0,count) may even contain null
   ///                    characters.
   /// @return  The index of the position where one of the characters was found,
   ///          std::string::npos if none of those characters were found.
   /// @since  x.y.z, 26.01.2021
   size_t find_first_of( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Searches for the first occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the beginning of the string.
   /// @return  The index of the position where one of the characters was found,
   ///          std::string::npos if none of those characters were found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_of( const char* str, size_t pos = 0) const noexcept;

   /// Searches for the first occurrence of the given character.
   /// @param[in]  ch   The single character to search for.
   /// @param[in]  pos  Starting position for searching the character, if not
   ///                  set searching starts at the beginning of the string.
   /// @return  The index of the position where the character was found for the
   ///          first time, std::string::npos if the character was not found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_of( char ch, size_t pos = 0) const noexcept;

   /// Searches for the first occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the beginning
   ///                  of the string.
   /// @return  The index of the first position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_not_of( const FixedString& str, size_t pos = 0) const
      noexcept;

   /// Searches for the first occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the beginning
   ///                  of the string.
   /// @return  The index of the first position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_not_of( const std::string& str, size_t pos = 0) const
      noexcept;

   /// Searches for the first occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str    The string with the characters to ignore.
   /// @param[in]  pos    Starting position for searching the non-matching
   ///                    characters, if not set searching starts at the
   ///                    beginning of the string.
   /// @param[in]  count  Number of characters in the string to actually use for
   ///                    searching. The range [0,count) may even contain null
   ///                    characters.
   /// @return  The index of the first position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_not_of( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Searches for the first occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the beginning
   ///                  of the string.
   /// @return  The index of the first position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_not_of( const char* str, size_t pos = 0) const noexcept;

   /// Searches for the first occurrence of another character than the given
   /// one.
   /// @param[in]  ch   The single character to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  character, if not set searching starts at the beginning
   ///                  of the string.
   /// @return  The index of the first position where another character was
   ///          found, std::string::npos if no such character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_first_not_of( char ch, size_t pos = 0) const noexcept;

   /// Searches for the last occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the end of the string.
   /// @return  The index of the position where the last of these characters was
   ///          found, std::string::npos if none of those characters were found.
   /// @since  x.y.z, 27.01.2021
   size_t find_last_of( const FixedString& str, size_t pos = std::string::npos)
      const noexcept;

   /// Searches for the last occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the end of the string.
   /// @return  The index of the position where the last of these characters was
   ///          found, std::string::npos if none of those characters were found.
   /// @since  x.y.z, 27.01.2021
   size_t find_last_of( const std::string& str, size_t pos = std::string::npos)
      const noexcept;

   /// Searches for the last occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str    The string with the characters to search for.
   /// @param[in]  pos    Starting position for searching the characters, if not
   ///                    set searching starts at the end of the string.
   /// @param[in]  count  Number of characters in the string to actually use for
   ///                    searching. The range [0,count) may even contain null
   ///                    characters.
   /// @return  The index of the position where the last of these characters was
   ///          found, std::string::npos if none of those characters were found.
   /// @since  x.y.z, 27.01.2021
   size_t find_last_of( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Searches for the last occurrence of one of the characters in the given
   /// string.
   /// @param[in]  str  The string with the characters to search for.
   /// @param[in]  pos  Starting position for searching the characters, if not
   ///                  set searching starts at the end of the string.
   /// @return  The index of the position where the last of these characters was
   ///          found, std::string::npos if none of those characters were found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_of( const char* str, size_t pos = std::string::npos) const
      noexcept;

   /// Searches for the last occurrence of a character.
   /// @param[in]  ch   The single character to search for.
   /// @param[in]  pos  Starting position for searching the character, if not
   ///                  set searching starts at the end of the string.
   /// @return  The index of the last position where this character was found,
   ///          std::string::npos if no such character was found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_of( char ch, size_t pos = std::string::npos) const noexcept;

   /// Searches for the last occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the end of
   ///                  the string.
   /// @return  The index of the last position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 27.01.2021
   size_t find_last_not_of( const FixedString& str,
      size_t pos = std::string::npos) const noexcept;

   /// Searches for the last occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the end of
   ///                  the string.
   /// @return  The index of the last position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_not_of( const std::string& str,
      size_t pos = std::string::npos) const noexcept;

   /// Searches for the last occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str    The string with the characters to ignore.
   /// @param[in]  pos    Starting position for searching the non-matching
   ///                    characters, if not set searching starts at the end of
   ///                    the string.
   /// @param[in]  count  Number of characters in the string to actually use for
   ///                    searching. The range [0,count) may even contain null
   ///                    characters.
   /// @return  The index of the last position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_not_of( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Searches for the last occurrence of a character that is not part of the
   /// given search string.
   /// @param[in]  str  The string with the characters to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  characters, if not set searching starts at the end of
   ///                  the string.
   /// @return  The index of the last position where a character was found that
   ///          was not part of the given string, std::string::npos if no such
   ///          character was found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_not_of( const char* str, size_t pos = std::string::npos)
      const noexcept;

   /// Searches for the last occurrence of another character than the given one.
   /// @param[in]  ch   The single character to ignore.
   /// @param[in]  pos  Starting position for searching the non-matching
   ///                  character, if not set searching starts at the end of the
   ///                  string.
   /// @return  The index of the last position where this character was found,
   ///          std::string::npos if no such character was found.
   /// @since  x.y.z, 28.01.2021
   size_t find_last_not_of( char ch, size_t pos = std::string::npos) const
      noexcept;

   /// Copies a C string into the internal buffer.
   /// @param[in]  str  The C string to copy.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   FixedString& operator =( const char* str) noexcept;

   /// Copies a std::string into the internal buffer.
   /// @param[in]  str  The std::string to copy from.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   FixedString& operator =( const std::string& str) noexcept;

   /// Default assignment operator is fine.
   /// @param[in]  str  The other fixed string object with the same size.
   /// @return  This object.
   /// @since  x.y.z, 14.01.2021
   FixedString& operator =( const FixedString& str) = default;

   /// Copies the contents of another fixed string.
   /// @tparam  S  The maximum length of the other fixed string class.
   /// @param[in]  str  The other fixed string object to copy from.
   /// @return  This object.
   /// @since  x.y.z, 13.01.2021
   template< size_t S> FixedString& operator =( const FixedString< S>& str)
      noexcept;

private:
   /// Internal type used to store the length of the string.
   /// Uses the smallest type that fits for the length.
   using size_type = typename LengthType< L>::type;

   /// Copies #mLength bytes from the given string pointer.
   /// So, obviously #mLength must be set before correctly.
   /// @param[in]  src  Pointer to the string buffer to copy from.
   /// @since  x.y.z, 13.01.2021
   void internalCopy( const char* src) noexcept;

   /// Actual implementation of appending a string.
   /// The calling function must ensure that pos + count is within the given
   /// string.
   /// @param[in]  str    Pointer to the string to append.
   /// @param[in]  pos    Start position in the string to append from.
   /// @param[in]  count  Number of characters from the string to append.
   /// @return  This object.
   /// @since  x.y.z, 15.01.2021
   FixedString& appendImpl( const char* str, size_t pos, size_t count) noexcept;

   /// Compares the string of this object with the given, other string.
   /// @param[in]  str  The other string to compare against.
   /// @param[in]  len  Length of the other string.
   /// @return
   /// - &lt; 0 if this string is smaller (or shorter) than the other string.
   /// - 0 if both strings are equal and have the same length.
   /// - &gt; 0 if the other string is greater (or longer) than this string.
   /// @since  x.y.z, 18.01.2021
   int fullCompareImpl( const char* str, size_t len) const noexcept;

   /// Compares the range [pos1, pos1+count1) of this string with the given
   /// string.
   /// @param[in]  pos1    The start position within this string for the
   ///                     comparison.
   /// @param[in]  count1  Number of characters of this string to use for the
   ///                     comparison.
   /// @param[in]  str     The other string to compare against.
   /// @param[in]  len2    Number of characters of the other string to use for
   ///                     the comparison.
   /// @return
   /// - &lt; 0 if this string is smaller (or shorter) than the other string.
   /// - 0 if both strings are equal and have the same length.
   /// - &gt; 0 if the other string is greater (or longer) than this string.
   /// @since  x.y.z, 18.01.2021
   int partCompareImpl( size_t pos1, size_t count1, const char* str,
      size_t len2) const noexcept;

   /// Compares the range [pos1, pos1+count1) of this string with the range
   /// [pos2, pos2+count2) of the other string.
   /// @param[in]  pos1    The start position within this string for the
   ///                     comparison.
   /// @param[in]  count1  Number of characters of this string to use for the
   ///                     comparison.
   /// @param[in]  str     The other string to compare against.
   /// @param[in]  len2    The full length of the other string.
   /// @param[in]  pos2    The start position within the other string.
   /// @param[in]  count2  Number of characters of the other string to use for
   ///                     the comparison.
   /// @return
   /// - &lt; 0 if this string is smaller (or shorter) than the other string.
   /// - 0 if both strings are equal and have the same length.
   /// - &gt; 0 if the other string is greater (or longer) than this string.
   /// @since  x.y.z, 18.01.2021
   int partPartCompareImpl( size_t pos1, size_t count1, const char* str,
      size_t len2, size_t pos2, size_t count2) const noexcept;

   /// Checks if the first part of this string equals the given string.
   /// @param[in]  str      The string to compare against.
   /// @param[in]  str_len  The length of the string to compare against.
   /// @return  \c true if this string starts with the given string.
   /// @since  x.y.z, 20.01.2021
   bool startsWithImpl( const char* str, size_t str_len) const noexcept;

   /// Checks if the last part of this string equals the given string.
   /// @param[in]  str      The string to compare against.
   /// @param[in]  str_len  The length of the string to compare against.
   /// @return  \c true if this string ends with the given string.
   /// @since  x.y.z, 20.01.2021
   bool endsWithImpl( const char* str, size_t str_len) const noexcept;

   /// Checks if this string contains the given string.
   /// @param[in]  str      The string to search for.
   /// @param[in]  str_len  The length of the string to search for.
   /// @return  \c true if this string contains the given string.
   /// @since  x.y.z, 20.01.2021
   bool containsImpl( const char* str, size_t str_len) const noexcept;

   /// Replaces the characters in the range [pos1, pos1+count1) with the
   /// characters from the given string in the range [pos2, pos2+count2).
   /// @param[in]  pos1    The position of the first character to replace.
   /// @param[in]  count1  Number of characters to replace from this string.
   /// @param[in]  str     Pointer to the string with the new contents.
   /// @param[in]  pos2    Start position of the range to use for the
   ///                     replacement.
   /// @param[in]  count2  Number of characters to take from the other string.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedString& replaceImpl( size_t pos1, size_t count1, const char* str,
      size_t pos2, size_t count2) noexcept;

   /// Returns the position of the first occurrence of any character from the
   /// given search string.
   /// @param[in]  str    The string with the characters to search for.
   /// @param[in]  pos    Start position for searching.
   /// @param[in]  count  Length of the string with the search characters, only
   ///                    used to ensure it is not 0.
   /// @return  The index of the first character from this string that was found
   ///          in the search string.
   /// @since  x.y.z, 27.01.2021
   size_t findFirstOfImpl( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Returns the position of the first occurrence of any character from this
   /// string that does not occur in the given search string.
   /// @param[in]  str    The string with the characters to ignore.
   /// @param[in]  pos    Start position for searching.
   /// @param[in]  count  Length of the string with the search characters, only
   ///                    used to ensure it is not 0.
   /// @return  The index of the first character from this string that was not
   ///          found in the search string.
   /// @since  x.y.z, 27.01.2021
   size_t findFirstNotOfImpl( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Returns the position of the last occurrence of any character from the
   /// given search string.
   /// @param[in]  str    The string with the characters to search for.
   /// @param[in]  pos    Start position for searching.
   /// @param[in]  count  Length of the string with the search characters, only
   ///                    used to ensure it is not 0.
   /// @return  The index of the last character from this string that was found
   ///          in the search string.
   /// @since  x.y.z, 27.01.2021
   size_t findLastOfImpl( const char* str, size_t pos, size_t count) const
      noexcept;

   /// Returns the position of the last occurrence of any character from this
   /// string that does not occur in the given search string.
   /// @param[in]  str    The string with the characters to ignore.
   /// @param[in]  pos    Start position for searching.
   /// @param[in]  count  Length of the string with the search characters, only
   ///                    used to ensure it is not 0.
   /// @return  The index of the last character from this string that was not
   ///          found in the search string.
   /// @since  x.y.z, 28.01.2021
   size_t findLastNotOfImpl( const char* str, size_t pos, size_t count) const
      noexcept;

   /// The string buffer, with the given length + 1 for the trailing zero.
   char       mString[ L + 1] = { '\0' };
   /// The actual length of the string in the buffer.
   /// Use a variable with the minimum size.
   size_type  mLength = 0;

}; // FixedString


// inlined methods
// ===============


template< size_t L> inline void FixedString< L>::internalCopy( const char* src)
   noexcept
{
   if (mLength > 0)
   {
      ::memcpy( mString, src, mLength);
   } // end if
   mString[ mLength] = '\0';
} // FixedString< L>::internalCopy


template< size_t L> template< size_t S>
   FixedString< L>::FixedString( const FixedString< S>& other) noexcept:
      mLength( std::min( L, other.length()))
{
   // need to use the functions of the other object instead of accessing the
   // member variables directly, since this is another class
   internalCopy( other.c_str());
} // FixedString< L>::FixedString


template< size_t L> FixedString< L>::FixedString( const char* str) noexcept:
   mLength( std::min( L, ::strlen( str)))
{
   internalCopy( str);
} // FixedString< L>::FixedString


template< size_t L> FixedString< L>::FixedString( const std::string& str)
   noexcept:
      mLength( std::min( L, str.length()))
{
   internalCopy( str.c_str());
} // FixedString< L>::FixedString


template< size_t L> FixedString< L>::FixedString( FixedString&& other) noexcept:
   mLength( other.mLength)
{
   if (mLength > 0)
   {
      internalCopy( other.mString);
   } // end if
} // FixedString< L>::FixedString


template< size_t L> std::string FixedString< L>::str() const noexcept
{
   return (mLength > 0) ? std::string( mString, mLength) : std::string();
} // FixedString< L>::str


template< size_t L> const char* FixedString< L>::c_str() const noexcept
{
   return mString;
} // FixedString< L>::c_str


template< size_t L> size_t FixedString< L>::length() const noexcept
{
   return mLength;
} // FixedString< L>::length


template< size_t L> bool FixedString< L>::empty() const noexcept
{
   return mLength == 0;
} // FixedString< L>::empty


template< size_t L> FixedString< L>& FixedString< L>::assign( const char* str)
   noexcept
{
   mLength = std::min( L, ::strlen( str));
   internalCopy( str);
   return *this;
} // FixedString< L>::assign


template< size_t L>
   FixedString< L>& FixedString< L>::assign( const std::string& str) noexcept
{
   mLength = std::min( L, str.length());
   internalCopy( str.c_str());
   return *this;
} // FixedString< L>::assign


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::assign( const FixedString< S>& str)
      noexcept
{
   mLength = std::min( L, str.length());
   internalCopy( str.c_str());
   return *this;
} // FixedString< L>::assign


template< size_t L> char& FixedString< L>::at( size_t idx) noexcept( false)
{
   if (idx > mLength)
      throw std::out_of_range( "index " + std::to_string( idx)
         + " is after end of string");
   return mString[ idx];
} // FixedString< L>::at


template< size_t L>
   const char& FixedString< L>::at( size_t idx) const noexcept( false)
{
   if (idx > mLength)
      throw std::out_of_range( "index " + std::to_string( idx)
         + " is after end of string");
   return mString[ idx];
} // FixedString< L>::at


template< size_t L> char& FixedString< L>::operator []( size_t idx) noexcept
{
   return mString[ idx];
} // FixedString< L>::operator []


template< size_t L>
   const char& FixedString< L>::operator []( size_t idx) const noexcept
{
   return mString[ idx];
} // FixedString< L>::operator []


template< size_t L> char& FixedString< L>::front() noexcept
{
   return mString[ 0];
} // FixedString< L>::front


template< size_t L> const char& FixedString< L>::front() const noexcept
{
   return mString[ 0];
} // FixedString< L>::front


template< size_t L> char& FixedString< L>::back() noexcept
{
   return mString[ (mLength == 0) ? 0 : (mLength - 1)];
} // FixedString< L>::back


template< size_t L> const char& FixedString< L>::back() const noexcept
{
   return mString[ (mLength == 0) ? 0 : (mLength - 1)];
} // FixedString< L>::back


template< size_t L> char* FixedString< L>::data() noexcept
{
   return mString;
} // FixedString< L>::data


template< size_t L> const char* FixedString< L>::data() const noexcept
{
   return mString;
} // FixedString< L>::data


template< size_t L>
   typename FixedString< L>::iterator FixedString< L>::begin() noexcept
{
   return iterator( this);
} // FixedString< L>::begin


template< size_t L>
   typename FixedString< L>::const_iterator FixedString< L>::begin() const
      noexcept
{
   return const_iterator( this);
} // FixedString< L>::begin


template< size_t L>
   typename FixedString< L>::const_iterator FixedString< L>::cbegin() const
      noexcept
{
   return const_iterator( this);
} // FixedString< L>::cbegin


template< size_t L>
   typename FixedString< L>::iterator FixedString< L>::end() noexcept
{
   return iterator( true, this);
} // FixedString< L>::end


template< size_t L>
   typename FixedString< L>::const_iterator FixedString< L>::end() const
      noexcept
{
   return const_iterator( true, this);
} // FixedString< L>::end


template< size_t L>
   typename FixedString< L>::const_iterator FixedString< L>::cend() const
      noexcept
{
   return const_iterator( true, this);
} // FixedString< L>::cend


template< size_t L>
   typename FixedString< L>::reverse_iterator FixedString< L>::rbegin() noexcept
{
   return reverse_iterator( this);
} // FixedString< L>::rbegin


template< size_t L>
   typename FixedString< L>::const_reverse_iterator FixedString< L>::rbegin()
      const noexcept
{
   return const_reverse_iterator( this);
} // FixedString< L>::rbegin


template< size_t L>
   typename FixedString< L>::const_reverse_iterator FixedString< L>::crbegin()
      const noexcept
{
   return const_reverse_iterator( this);
} // FixedString< L>::crbegin


template< size_t L>
   typename FixedString< L>::reverse_iterator FixedString< L>::rend() noexcept
{
   return reverse_iterator( true, this);
} // FixedString< L>::rend


template< size_t L>
   typename FixedString< L>::const_reverse_iterator FixedString< L>::rend()
      const noexcept
{
   return const_reverse_iterator( true, this);
} // FixedString< L>::rend


template< size_t L>
   typename FixedString< L>::const_reverse_iterator FixedString< L>::crend()
      const noexcept
{
   return const_reverse_iterator( true, this);
} // FixedString< L>::crend


template< size_t L>
   FixedString< L>&
      FixedString< L>::insert( size_t index, size_t count, char ch) noexcept
{

   if (index < mLength)
   {
      if (mLength + count <= L)
      {
         // aaaccccc\0, insert( 3, 4, 'b')
         // length = 8, L > 11
         // --> aaa____ccccc\0
         ::memmove( &mString[ index + count], &mString[ index], mLength - index + 1);
         // --> aaabbbbccccc\0
         ::memset( &mString[ index], ch, count);
         mLength += count;
      } else if (index + count <= L)
      {
         // aaaccccc\0, insert( 3, 4, 'b')
         // length = 8, L = 10
         // --> aaa____ccc\0
         ::memmove( &mString[ index + count], &mString[ index], mLength - index + 1);
         // --> aaabbbbccc\0
         ::memset( &mString[ index], ch, count);
         mLength = L;
      } else // index + count > L
      {
         // aaaccccc\0, insert( 3, 6, 'b')
         // length = 8, L = 8
         // --> aaabbbbb\0
         ::memset( &mString[ index], ch, L - index);
         mLength = L;
      } // end if
   } else
   {
      // append at the end
      if (mLength + count > L)
         count = L - mLength;

      ::memset( &mString[ mLength], ch, count);
      mLength += count;
   } // end if

   mString[ mLength] = '\0';
   return *this;
} // FixedString< L>::insert


template< size_t L>
   FixedString< L>& FixedString< L>::insert( size_t index, const char* str,
      size_t count) noexcept
{

   if (index < mLength)
   {
      if (mLength + count <= L)
      {
         // aaaccccc\0, insert( 3, "bbbb")
         // length = 8, L > 11
         // --> aaa____ccccc\0
         ::memmove( &mString[ index + count], &mString[ index],
            mLength - index + 1);
         // --> aaabbbbccccc\0
         ::memcpy( &mString[ index], str, count);
         mLength += count;
      } else if (index + count <= L)
      {
         // aaaccccc\0, insert( 3, "bbbb")
         // length = 8, L = 10
         // --> aaa____ccc\0
         ::memmove( &mString[ index + count], &mString[ index],
            mLength - index + 1);
         // --> aaabbbbccc\0
         ::memcpy( &mString[ index], str, count);
         mLength = L;
      } else // index + count > L
      {
         // aaaccccc\0, insert( 3, "bbbbbb")
         // length = 8, L = 8
         // --> aaabbbbb\0
         ::memcpy( &mString[ index], str, L - index);
         mLength = L;
      } // end if
   } else
   {
      // append at the end
      if (mLength + count > L)
         count = L - mLength;

      ::memcpy( &mString[ mLength], str, count);
      mLength += count;
   } // end if

   mString[ mLength] = '\0';
   return *this;
} // FixedString< L>::insert


template< size_t L>
   FixedString< L>& FixedString< L>::insert( size_t index, const char* str)
      noexcept
{
   return insert( index, str, ::strlen( str));
} // FixedString< L>::insert


template< size_t L>
   FixedString< L>& FixedString< L>::insert( size_t index,
      const std::string& str) noexcept
{
   return insert( index, str.c_str(), str.length());
} // FixedString< L>::insert


template< size_t L>
   FixedString< L>& FixedString< L>::insert( size_t index,
      const std::string& str, size_t index_str, size_t count) noexcept
{
   return insert( index, str.substr( index_str, count));
} // FixedString< L>::insert


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::insert( size_t index,
      const FixedString< S>& str) noexcept
{
   // need to use the functions of the other object instead of accessing the
   // member variables directly, since this is another class
   return insert( index, str.c_str(), str.length());
} // FixedString< L>::insert


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::insert( size_t index,
      const FixedString< S>& str, size_t index_str, size_t count) noexcept
{
   if (index_str > str.length())
      return *this;
   return insert( index, &str[ index_str],
      std::min( str.length() - index_str, count));
} // FixedString< L>::insert


template< size_t L>
   typename FixedString< L>::iterator
      FixedString< L>::insert( const_iterator pos, char ch) noexcept
{
   if (pos == cend())
      return end();
   const size_t  idx = pos - cbegin();
   insert( idx, 1, ch);
   return iterator( this, idx);
} // FixedString< L>::insert


template< size_t L>
   typename FixedString< L>::iterator
      FixedString< L>::insert( const_iterator pos, size_t count, char ch)
         noexcept
{
   if (pos == cend())
      return end();
   const size_t  idx = pos - cbegin();
   insert( idx, count, ch);
   return iterator( this, idx);
} // FixedString< L>::insert


template< size_t L>
   typename FixedString< L>::iterator
      FixedString< L>::insert( const_iterator pos,
         std::initializer_list< char> ilist) noexcept
{
   if (pos == cend())
      return end();
   const size_t  idx = pos - cbegin();
   const size_t  insert_size = ilist.size();
   if (insert_size == 0)
      return iterator( this, idx);
   insert( idx, ilist.begin(), insert_size);
   return iterator( this, idx);
} // FixedString L>::insert


template< size_t L>
   FixedString< L>& FixedString< L>::erase( size_t index, size_t count) noexcept
{
   if (index > mLength)
      return *this;
   // count can be max(64bit), so we cannot calc index + count
   if (count >= mLength - index)
   {
      mString[ index] = '\0';
      mLength = index;
      return *this;
   } // end if

   // really delete a part from within the string
   // aaabbbbccccc, erase( 3, 4)
   // length = 12
   ::memmove( &mString[ index], &mString[ index + count],
      mLength - index - count);
   mLength -= count;
   mString[ mLength] = '\0';
   return *this;
} // FixedString< L>::erase


template< size_t L>
   typename FixedString< L>::iterator
      FixedString< L>::erase( const_iterator position) noexcept
{
   if (position == cend())
      return end();
   const size_t  idx = position - cbegin();
   erase( idx, 1);
   return iterator( this, idx);
} // FixedString< L>::erase


template< size_t L>
   typename FixedString< L>::iterator
      FixedString< L>::erase( const_iterator first, const_iterator last)
         noexcept
{
   if ((first == cend()) || (first == last))
      return end();
   const size_t  idx = first - cbegin();
   const size_t  count = (last == cend()) ? std::string::npos : (last - first);
   erase( idx, count);
   return iterator( this, idx);
} // FixedString< L>::erase


template< size_t L> FixedString< L>& FixedString< L>::push_back( char ch)
   noexcept
{
   if (mLength < L)
   {
      mString[ mLength++] = ch;
      mString[ mLength] = '\0';
   } // end if
   return *this;
} // FixedString< L>::push_back


template< size_t L> FixedString< L>& FixedString< L>::pop_back() noexcept
{
   if (mLength > 0)
   {
      mString[ --mLength] = '\0';
   } // end if
   return *this;
} // FixedString< L>::pop_back


template< size_t L> inline
   FixedString< L>& FixedString< L>::appendImpl( const char* str, size_t pos,
      size_t count) noexcept
{
   if (count > 0)
   {
      const size_t  append_len = std::min( L - mLength, count);
      ::memcpy( &mString[ mLength], &str[ pos], append_len);
      mLength += append_len;
      mString[ mLength] = '\0';
   } // end if
   return *this;
} // FixedString< L>::appendImpl


template< size_t L>
   FixedString< L>& FixedString< L>::append( size_t count, char ch) noexcept
{
   // test if string is already full
   if (mLength == L)
      return *this;
   return append( std::string( count, ch));
} // FixedString< L>::append


template< size_t L>
   FixedString< L>& FixedString< L>::append( const std::string& str) noexcept
{
   return appendImpl( str.c_str(), 0, str.length());
} // FixedString< L>::append


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::append( const FixedString< S>& fs) noexcept
{
   return appendImpl( fs.c_str(), 0, fs.length());
} // FixedString< L>::append


template< size_t L>
   FixedString< L>& FixedString< L>::append( const std::string& str, size_t pos,
      size_t count) noexcept
{
   return appendImpl( str.c_str(), pos, count);
} // FixedString< L>::append


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::append( const FixedString< S>& str,
      size_t pos, size_t count) noexcept
{
   return appendImpl( str.c_str(), pos, count);
} // FixedString< L>::append


template< size_t L>
   FixedString< L>& FixedString< L>::append( const char* str, size_t count)
      noexcept
{
   return appendImpl( str, 0, std::min( count, ::strlen( str)));
} // FixedString< L>::append


template< size_t L>
   FixedString< L>& FixedString< L>::append( const char* str) noexcept
{
   return appendImpl( str, 0, ::strlen( str));
} // FixedString< L>::append


template< size_t L>
   FixedString< L>&
      FixedString< L>::append( const_iterator first, const_iterator last)
         noexcept
{
   if ((first == last) || (mLength == L))
      return *this;
   const size_t  count = last - first;
   return appendImpl( &(*first), 0, count);
} // FixedString< L>::append


/*
template< size_t L> template< size_t S>
   FixedString< L>&
      FixedString< L>::append( typename FixedString< S>::const_iterator first,
         typename FixedString< S>::const_iterator last) noexcept
{
   if ((first == last) || (mLength == L))
      return *this;
   const size_t  count = last - first;
   if (count == 0)
      return *this;
   return appendImpl( &(*first), 0, count);
} // FixedString< L>::append
*/

template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::operator +=( const FixedString< S>& str)
      noexcept
{
   return append(str);
} // FixedString< L>::operator +=


template< size_t L>
   FixedString< L>& FixedString< L>::operator +=( const std::string& str)
      noexcept
{
   return append( str);
} // FixedString< L>::operator +=


template< size_t L>
   FixedString< L>& FixedString< L>::operator +=( const char* str) noexcept
{
   return append( str);
} // FixedString< L>::operator +=


template< size_t L>
   FixedString< L>& FixedString< L>::operator +=( char ch) noexcept
{
   return append( 1, ch);
} // FixedString< L>::operator +=


template< size_t L>
   int FixedString< L>::fullCompareImpl( const char* str, size_t len) const
      noexcept
{
   const size_t  max_cmp_len = std::min( static_cast< size_t>( mLength), len);
   const int     cmp_result = ::memcmp( mString, str, max_cmp_len);

   if (cmp_result == 0)
   {
      return (mLength > len) ? 1 : (mLength < len) ? -1 : 0;
   } // end if

   return cmp_result;
} // FixedString< L>::fullCompareImpl


template< size_t L> template< size_t S>
   int FixedString< L>::compare( const FixedString< S>& fs) const noexcept
{
   return fullCompareImpl( fs.c_str(), fs.length());
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( const std::string& str) const noexcept
{
   return fullCompareImpl( str.c_str(), str.length());
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( const char* str) const noexcept
{
   return fullCompareImpl( str, ::strlen( str));
} // FixedString< L>::compare


template< size_t L> inline
   int FixedString< L>::partCompareImpl( size_t pos1, size_t count1,
      const char* str, size_t len2) const noexcept
{
   if (pos1 >= mLength)
      return (len2 == 0) ? 0 : 1;

   const size_t  use_len = (pos1 + count1 > mLength) ? (mLength - pos1) : count1;
   const size_t  max_cmp_len = std::min( use_len, len2);
   const int     cmp_result = ::memcmp( &mString[ pos1], str, max_cmp_len);

   if (cmp_result == 0)
   {
      return (use_len > len2) ? 1 : (use_len < len2) ? -1 : 0;
   } // end if

   return cmp_result;
} // FixedString< L>::partCompareImpl


template< size_t L> template< size_t S>
   int FixedString< L>::compare( size_t pos1, size_t count1,
      const FixedString< S>& str) const noexcept
{
   return partCompareImpl( pos1, count1, str.c_str(), str.length());
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( size_t pos1, size_t count1,
      const std::string& str) const noexcept
{
   return partCompareImpl( pos1, count1, str.c_str(), str.length());
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( size_t pos1, size_t count1, const char* str)
      const noexcept
{
   return partCompareImpl( pos1, count1, str, ::strlen( str));
} // FixedString< L>::compare


template< size_t L> inline
   int FixedString< L>::partPartCompareImpl( size_t pos1, size_t count1,
      const char* str, size_t len2, size_t pos2, size_t count2) const noexcept
{
   if (pos1 >= mLength)
      return (pos2 >= len2) ? 0 : 1;
   if (pos2 >= len2)
      return -1;

   const size_t  str_len1 = (count1 > mLength - pos1) ? (mLength - pos1) : count1;
   const size_t  str_len2 = (count2 > len2 - pos2) ? (len2 - pos2) : count2;
   const size_t  max_cmp_len = std::min( str_len1, str_len2);
   const int     cmp_result = ::memcmp( &mString[ pos1], &str[ pos2], max_cmp_len);

   if (cmp_result == 0)
   {
      return (str_len1 > str_len2) ? 1 : (str_len1 < str_len2) ? -1 : 0;
   } // end if

   return cmp_result;
} // FixedString< L>::partPartCompareImpl


template< size_t L> template< size_t S>
   int FixedString< L>::compare( size_t pos1, size_t count1,
      const FixedString< S>& str, size_t pos2, size_t count2) const noexcept
{
   return partPartCompareImpl( pos1, count1, str.c_str(), str.length(), pos2,
      count2);
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( size_t pos1, size_t count1,
      const std::string& str, size_t pos2, size_t count2) const noexcept
{
   return partPartCompareImpl( pos1, count1, str.c_str(), str.length(), pos2,
      count2);
} // FixedString< L>::compare


template< size_t L>
   int FixedString< L>::compare( size_t pos1, size_t count1, const char* str,
      size_t count2) const noexcept
{
   return partPartCompareImpl( pos1, count1, str, ::strlen( str), 0, count2);
} // FixedString< L>::compare


template< size_t L> inline
   bool FixedString< L>::startsWithImpl( const char* str, size_t str_len) const
      noexcept
{
   if ((str_len == 0) && (mLength == 0))
      return true;
   if (str_len > mLength)
      return false;
   return ::memcmp( mString, str, str_len) == 0;
} // FixedString< L>::startsWithImpl


template< size_t L> template< size_t S>
   bool FixedString< L>::starts_with( const FixedString< S>& str) const noexcept
{
   return startsWithImpl( str.c_str(), str.length());
} // FixedString< L>::starts_with


template< size_t L>
   bool FixedString< L>::starts_with( const std::string& str) const noexcept
{
   return startsWithImpl( str.c_str(), str.length());
} // FixedString< L>::starts_with


template< size_t L>
   bool FixedString< L>::starts_with( const char* str) const noexcept
{
   return startsWithImpl( str, ::strlen( str));
} // FixedString< L>::starts_with


template< size_t L> bool FixedString< L>::starts_with( char ch) const noexcept
{
   return (mLength > 0) && (mString[ 0] == ch);
} // FixedString< L>::starts_with


template< size_t L> inline
   bool FixedString< L>::endsWithImpl( const char* str, size_t str_len) const
      noexcept
{
   if ((str_len == 0) && (mLength == 0))
      return true;
   if (str_len > mLength)
      return false;
   return ::memcmp( &mString[ mLength - str_len], str, str_len) == 0;
} // FixedString< L>::startsWithImpl


template< size_t L> template< size_t S>
   bool FixedString< L>::ends_with( const FixedString< S>& str) const noexcept
{
   return endsWithImpl( str.c_str(), str.length());
} // FixedString< L>::ends_with

template< size_t L>
   bool FixedString< L>::ends_with( const std::string& str) const noexcept
{
   return endsWithImpl( str.c_str(), str.length());
} // FixedString< L>::ends_with


template< size_t L> bool FixedString< L>::ends_with( const char* str) const
   noexcept
{
   return endsWithImpl( str, ::strlen( str));
} // FixedString< L>::ends_with


template< size_t L> bool FixedString< L>::ends_with( char ch) const noexcept
{
   return (mLength > 0) && (mString[ mLength - 1] == ch);
} // FixedString< L>::ends_with


template< size_t L> inline
   bool FixedString< L>::containsImpl( const char* str, size_t str_len) const
      noexcept
{
   if ((str_len == 0) || (mLength == 0) || (str_len > mLength))
      return false;
   for (size_type idx = 0; idx + str_len <= mLength; ++idx)
   {
      if ((mString[ idx] == str[ 0])
          && (::memcmp( &mString[ idx], str, str_len) == 0))
         return true;
   } // end for
   return false;
} // FixedString< L>::containsImpl


template< size_t L> template< size_t S>
   bool FixedString< L>::contains( const FixedString< S>& str) const noexcept
{
   return containsImpl( str.c_str(), str.length());
} // FixedString< L>::contains


template< size_t L>
   bool FixedString< L>::contains( const std::string& str) const noexcept
{
   return containsImpl( str.c_str(), str.length());
} // FixedString< L>::contains


template< size_t L>
   bool FixedString< L>::contains( const char* str) const noexcept
{
   return containsImpl( str, ::strlen( str));
} // FixedString< L>::contains


template< size_t L> bool FixedString< L>::contains( char ch) const noexcept
{
   for (size_type idx = 0; idx < mLength; ++idx)
   {
      if (mString[ idx] == ch)
         return true;
   } // end for
   return false;
} // FixedString< L>::contains


template< size_t L> inline
   FixedString< L>& FixedString< L>::replaceImpl( size_t pos1, size_t count1,
      const char* str, size_t pos2, size_t count2) noexcept
{
   if (pos1 >= mLength)
      return *this;
   size_t  copy_len = count2;
   if (pos1 + count1 >= mLength)
   {
      // replace from pos until the end of the string
      if (pos1 + copy_len > L)
         copy_len = L - pos1;
      ::memcpy( &mString[ pos1], &str[ pos2], copy_len);
      mLength = pos1 + copy_len;
      mString[ mLength] = '\0';
   } else if (count1 == copy_len)
   {
      ::memcpy( &mString[ pos1], &str[ pos2], copy_len);
   } else if (count1 < copy_len)
   {
      // goodbyexfarewell
      // replace x by ' and ':  replace( 7, 1, " and ");
      // str.length() == 5
      // make space:  goodbyex....farewell
      // copy:        goodbye and farewell
      ::memmove( &mString[ pos1 + copy_len - count1 + 1],
         &mString[ pos1 + count1],
         mLength - pos1 - count1);
      ::memcpy( &mString[ pos1], &str[ pos2], copy_len);
      mLength = mLength - count1 + copy_len;
      mString[ mLength] = '\0';
   } else // count1 > copy_len
   {
      // goodbyexxxxxxxxfarewell
      // replace xxxxxxxx by ' and ':  replace( 7, 8, " and ");
      // str.length() == 5
      // adjust end of string:  goodbyexxxxxfarewell
      // copy:                  goodbye and farewell
      ::memmove( &mString[ pos1 + copy_len], &mString[ pos1 + count1],
         mLength - pos1 - count1);
      ::memcpy( &mString[ pos1], &str[ pos2], copy_len);
      mLength -= (count1 - copy_len);
      mString[ mLength] = '\0';
   } // end if
   return *this;
} // FixedString< L>::replaceImpl


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::replace( size_t pos, size_t count,
      const FixedString< S>& str) noexcept
{
   return replaceImpl( pos, count, str.c_str(), 0, str.length());
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>& FixedString< L>::replace( size_t pos, size_t count,
      const std::string& str) noexcept
{
   return replaceImpl( pos, count, str.c_str(), 0, str.length());
} // FixedString< L>::replace


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::replace( size_t pos1, size_t count1,
      const FixedString< S>& str, size_t pos2, size_t count2) noexcept
{
   if (pos2 > str.length())
      return *this;
   return replaceImpl( pos1, count1, str.c_str(), pos2,
      std::min( count2, str.length() - pos2));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>& FixedString< L>::replace( size_t pos1, size_t count1,
      const std::string& str, size_t pos2, size_t count2) noexcept
{
   if (pos2 > str.length())
      return *this;
   return replaceImpl( pos1, count1, str.c_str(), pos2,
      std::min( count2, str.length() - pos2));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>& FixedString< L>::replace( size_t pos1, size_t count1,
      const char* str) noexcept
{
   return replaceImpl( pos1, count1, str, 0, ::strlen( str));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>& FixedString< L>::replace( size_t pos1, size_t count1,
      const char* str, size_t count2) noexcept
{
   return replaceImpl( pos1, count1, str, 0, std::min( count2, ::strlen( str)));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         iterator first2, iterator last2) noexcept
{
   if ((first == cend()) || (first == last) || (first2 == last2))
      return *this;
   const size_t  idx = first - cbegin();
   const size_t  count1 = (last == cend()) ? (mLength - idx) : (last - first);
   const size_t  count2 = (last2 == end()) ? ::strlen( &(*first2))
      : (last2 - first2);
   return replaceImpl( idx, count1, &(*first2), 0, count2);
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         std::string::iterator first2, std::string::iterator last2) noexcept
{
   if ((first == cend()) || (first == last) || (first2 == last2))
      return *this;
   const size_t  idx = first - cbegin();
   const size_t  count1 = (last == cend()) ? (mLength - idx) : (last - first);
   const size_t  count2 = last2 - first2;
   return replaceImpl( idx, count1, &(*first2), 0, count2);
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         const char* str, size_t count2) noexcept
{
   if ((first == last) || (str == nullptr) || (count2 == 0))
      return *this;
   const size_t  idx = first - cbegin();
   const size_t  count1 = (last == cend()) ? (mLength - idx) : (last - first);
   return replaceImpl( idx, count1, str, 0, count2);
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         const char* str) noexcept
{
   return (str == nullptr) ? *this : replace( first, last, str, ::strlen( str));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( size_t pos, size_t count, size_t count2,
         char ch) noexcept
{
   return replace( pos, count, std::string( count2, ch));
} // FixedString< L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         size_t count2, char ch) noexcept
{
   if ((first == cend()) || (last == first) || (count2 == 0))
      return *this;
   return replace( first - cbegin(), last - first, count2, ch);
} // FixedString L>::replace


template< size_t L>
   FixedString< L>&
      FixedString< L>::replace( const_iterator first, const_iterator last,
         std::initializer_list< char> ilist) noexcept
{
   if (ilist.size() == 0)
      return *this;
   return replace( first, last, ilist.begin(), ilist.size());
} // FixedString< L>::replace


template< size_t L>
   std::string FixedString< L>::substr( size_t pos, size_t count) noexcept
{
   if ((pos >= mLength) || (count == 0))
      return std::string();
   if ((count == std::string::npos) || (pos + count >= mLength))
      count = mLength - pos;
   return std::string( &mString[ pos], count);
} // FixedString< L>::substr


template< size_t L>
   size_t FixedString< L>::copy( char* dest, size_t count, size_t pos) noexcept
{
   if ((pos >= mLength) || (dest == nullptr))
      return 0;
   if (pos + count >= mLength)
      count = mLength - pos;
   ::memcpy( dest, &mString[ pos], count);
   return count;
} // FixedString< L>::copy


template< size_t L> void FixedString< L>::swap( FixedString& other) noexcept
{
   if (mLength == 0)
   {
      if (other.mLength > 0)
      {
         ::memcpy( mString, other.mString, other.mLength);
         mLength = other.mLength;
         other.mString[ 0] = '\0';
         other.mLength = 0;
      } // end if
   } else if (other.mLength == 0)
   {
      ::memcpy( other.mString, mString, mLength);
      other.mLength = mLength;
      mString[ 0] = '\0';
      mLength = 0;
   } else
   {
      // copy my data into buffer
      // then copy from other into this
      // finally copy buffer into other
      char          buffer[ L];
      const size_t  length = mLength;
      ::memcpy( buffer, mString, mLength + 1);
      ::memcpy( mString, other.mString, other.mLength + 1);
      mLength = other.mLength;
      ::memcpy( other.mString, buffer, length + 1);
      other.mLength = length;
   } // end if
} // FixedString< L>::swap


template< size_t L>
   size_t FixedString< L>::find( const FixedString& str, size_t pos) const
      noexcept
{
   if ((pos + str.mLength > mLength) || (mLength == 0) || (str.mLength == 0))
      return std::string::npos;
   for (size_t idx = pos; idx <= (mLength - str.length()); ++idx)
   {
      if (::memcmp( &mString[ idx], str.mString, str.mLength) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find


template< size_t L>
   size_t FixedString< L>::find( const std::string& str, size_t pos) const
      noexcept
{
   if ((pos + str.length() > mLength) || (mLength == 0) || str.empty())
      return std::string::npos;
   for (size_t idx = pos; idx <= (mLength - str.length()); ++idx)
   {
      if (::memcmp( &mString[ idx], str.c_str(), str.length()) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find


template< size_t L>
   size_t FixedString< L>::find( const char* str, size_t pos, size_t count)
      const noexcept
{
   if ((pos + count > mLength) || (mLength == 0) || (count == 0)
       || (str == nullptr))
      return std::string::npos;
   for (size_t idx = pos; idx <= (mLength - count); ++idx)
   {
      if (::memcmp( &mString[ idx], str, count) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find


template< size_t L>
   size_t FixedString< L>::find( const char* str, size_t pos) const noexcept
{
   return find( str, pos, ::strlen( str));
} // FixedString< L>::find


template< size_t L>
   size_t FixedString< L>::find( char ch, size_t pos) const noexcept
{
   if ((pos + 1 > mLength) || (mLength == 0))
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      if (mString[ idx] == ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find


template< size_t L>
   size_t FixedString< L>::rfind( const FixedString& str, size_t pos) const
      noexcept
{
   if ((mLength == 0) || (str.mLength == 0) || (str.mLength > mLength))
      return std::string::npos;
   if ((pos == std::string::npos) || (pos + str.mLength > mLength))
      pos = mLength - str.mLength;
   // have to add 1 in the assignment because of the decrement in the condition
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      if (::memcmp( &mString[ idx], str.mString, str.mLength) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::rfind


template< size_t L>
   size_t FixedString< L>::rfind( const std::string& str, size_t pos) const
      noexcept
{
   if ((mLength == 0) || str.empty() || (str.length() > mLength))
      return std::string::npos;
   if ((pos == std::string::npos) || (pos + str.length() > mLength))
      pos = mLength - str.length();
   // have to add 1 in the assignment because of the decrement in the condition
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      if (::memcmp( &mString[ idx], str.c_str(), str.length()) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::rfind


template< size_t L>
   size_t FixedString< L>::rfind( const char* str, size_t pos, size_t count)
      const noexcept
{
   if ((mLength == 0) || (str == nullptr))
      return std::string::npos;
   const size_t  str_len = ::strlen( str);
   if (str_len == 0)
      return std::string::npos;
   if (count > str_len)
      count = str_len;
   if (count > mLength)
      return std::string::npos;
   if ((pos == std::string::npos) || (pos + count > mLength))
      pos = mLength - count;
   // have to add 1 in the assignment because of the decrement in the condition
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      if (::memcmp( &mString[ idx], str, count) == 0)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::rfind


template< size_t L>
   size_t FixedString< L>::rfind( const char* str, size_t pos) const noexcept
{
   return rfind( str, pos, ::strlen( str));
} // FixedString< L>::rfind


template< size_t L>
   size_t FixedString< L>::rfind( char ch, size_t pos) const noexcept
{
   if ((pos + 1 > mLength) || (mLength == 0))
      return std::string::npos;
   if (pos == std::string::npos)
      pos = mLength;
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      if (mString[ idx] == ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::rfind


template< size_t L>
   size_t FixedString< L>::findFirstOfImpl( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      if (::strchr( str, mString[ idx]) != nullptr)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::findFirstOfImpl


template< size_t L>
   size_t FixedString< L>::find_first_of( const FixedString& str, size_t pos)
      const noexcept
{
   return findFirstOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_first_of


template< size_t L>
   size_t FixedString< L>::find_first_of( const std::string& str, size_t pos)
      const noexcept
{
   return findFirstOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_first_of


template< size_t L>
   size_t FixedString< L>::find_first_of( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      // since str is allowed to contain 0 characters, we iterate ourselves
      for (size_t str_idx = 0; str_idx < count; ++str_idx)
      {
         if (str[ str_idx] == mString[ idx])
            return idx;
      } // end for
   } // end for
   return std::string::npos;
} // FixedString< L>::find_first_of


template< size_t L>
   size_t FixedString< L>::find_first_of( const char* str, size_t pos) const
      noexcept
{
   return findFirstOfImpl( str, pos, ::strlen( str));
} // FixedString< L>::find_first_of


template< size_t L>
   size_t FixedString< L>::find_first_of( char ch, size_t pos) const noexcept
{
   if (pos >= mLength)
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      if (mString[ idx] == ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_first_of


template< size_t L>
   size_t FixedString< L>::findFirstNotOfImpl( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      if (::strchr( str, mString[ idx]) == nullptr)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::findFirstNotOfImpl


template< size_t L>
   size_t FixedString< L>::find_first_not_of( const FixedString& str,
      size_t pos) const noexcept
{
   return findFirstNotOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_first_not_of


template< size_t L>
   size_t FixedString< L>::find_first_not_of( const std::string& str,
      size_t pos) const noexcept
{
   return findFirstNotOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_first_not_of


template< size_t L>
   size_t FixedString< L>::find_first_not_of( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      // since str is allowed to contain 0 characters, we iterate ourselves
      bool  matches = false;
      for (size_t str_idx = 0; str_idx < count; ++str_idx)
      {
         if (str[ str_idx] == mString[ idx])
         {
            matches = true;
            break;
         } // end if
      } // end for
      if (!matches)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_first_not_of


template< size_t L>
   size_t FixedString< L>::find_first_not_of( char ch, size_t pos) const
      noexcept
{
   if (pos >= mLength)
      return std::string::npos;
   for (size_t idx = pos; idx < mLength; ++idx)
   {
      if (mString[ idx] != ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_first_not_of


template< size_t L>
   size_t FixedString< L>::find_first_not_of( const char* str, size_t pos) const
      noexcept
{
   return findFirstNotOfImpl( str, pos, ::strlen( str));
} // FixedString< L>::find_first_not_of


template< size_t L>
   size_t FixedString< L>::findLastOfImpl( const char* str, size_t pos,
      size_t count) const noexcept
{
   if (pos == std::string::npos)
      pos = mLength;
   else
      ++pos;
   if ((pos - 1 >= mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx-- > 0; )
   {
      if (::strchr( str, mString[ idx]) != nullptr)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::findLastOfImpl


template< size_t L>
   size_t FixedString< L>::find_last_of( const FixedString& str, size_t pos)
      const noexcept
{
   return findLastOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_last_of


template< size_t L>
   size_t FixedString< L>::find_last_of( const std::string& str, size_t pos)
      const noexcept
{
   return findLastOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_last_of


template< size_t L>
   size_t FixedString< L>::find_last_of( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      // since str is allowed to contain 0 characters, we iterate ourselves
      for (size_t str_idx = 0; str_idx < count; ++str_idx)
      {
         if (str[ str_idx] == mString[ idx])
            return idx;
      } // end for
   } // end for
   return std::string::npos;
} // FixedString< L>::find_last_of


template< size_t L>
   size_t FixedString< L>::find_last_of( const char* str, size_t pos) const
      noexcept
{
   return findLastOfImpl( str, pos, ::strlen( str));
} // FixedString< L>::find_last_of


template< size_t L>
   size_t FixedString< L>::find_last_of( char ch, size_t pos) const noexcept
{
   if (pos == std::string::npos)
      pos = mLength;
   else if (pos >= mLength)
      return std::string::npos;
   else
      ++pos;
   for (size_t idx = pos; idx-- > 0; )
   {
      if (mString[ idx] == ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_last_of


template< size_t L>
   size_t FixedString< L>::findLastNotOfImpl( const char* str, size_t pos,
      size_t count) const noexcept
{
   if (pos == std::string::npos)
      pos = mLength;
   else
      ++pos;
   if ((pos - 1 >= mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos; idx-- > 0; )
   {
      if (::strchr( str, mString[ idx]) == nullptr)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::findLastNotOfImpl


template< size_t L>
   size_t FixedString< L>::find_last_not_of( const FixedString& str, size_t pos)
      const noexcept
{
   return findLastNotOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_last_not_of


template< size_t L>
   size_t FixedString< L>::find_last_not_of( const std::string& str, size_t pos)
      const noexcept
{
   return findLastNotOfImpl( str.c_str(), pos, str.length());
} // FixedString< L>::find_last_not_of


template< size_t L>
   size_t FixedString< L>::find_last_not_of( const char* str, size_t pos,
      size_t count) const noexcept
{
   if ((pos > mLength) || (str == nullptr) || (count == 0))
      return std::string::npos;
   for (size_t idx = pos + 1; idx-- > 0; )
   {
      // since str is allowed to contain 0 characters, we iterate ourselves
      bool  matches = false;
      for (size_t str_idx = 0; str_idx < count; ++str_idx)
      {
         if (str[ str_idx] == mString[ idx])
         {
            matches = true;
            break;
         } // end if
      } // end for
      if (!matches)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_last_not_of


template< size_t L>
   size_t FixedString< L>::find_last_not_of( const char* str, size_t pos) const
      noexcept
{
   return findLastNotOfImpl( str, pos, ::strlen( str));
} // FixedString< L>::find_last_not_of


template< size_t L>
   size_t FixedString< L>::find_last_not_of( char ch, size_t pos) const noexcept
{
   if (pos == std::string::npos)
      pos = mLength;
   else if (pos >= mLength)
      return std::string::npos;
   else
      ++pos;
   for (size_t idx = pos; idx-- > 0; )
   {
      if (mString[ idx] != ch)
         return idx;
   } // end for
   return std::string::npos;
} // FixedString< L>::find_last_not_of


template< size_t L>
   FixedString< L>& FixedString< L>::operator =( const char* str) noexcept
{
   return assign( str);
} // FixedString< L>::operator =


template< size_t L>
   FixedString< L>& FixedString< L>::operator =( const std::string& str)
      noexcept
{
   return assign( str);
} // FixedString< L>::operator =


template< size_t L> template< size_t S>
   FixedString< L>& FixedString< L>::operator =( const FixedString< S>& str)
      noexcept
{
   return assign( str);
} // FixedString< L>::operator =


template< size_t L> void FixedString< L>::clear() noexcept
{
   mString[ 0] = '\0';
   mLength = 0;
} // FixedString< L>::clear


/// Insertion operator for fixed strings.
/// @tparam  L  The size of the fixed string buffer.
/// @param[in]  os  The stream to write into.
/// @param[in]  fs  The fixed string object to dump the contents of.
/// @return  The stream as passed in.
/// @since  x.y.z, 13.01.2021
template< size_t L>
   std::ostream& operator <<( std::ostream& os, const FixedString< L>& fs)
      noexcept
{
   return os << '\'' << fs.c_str() << '\'';
} // operator <<


/// Equality comparison operator as free function, is capable of comparing two
/// fixed strings with different sizes.
/// Objects are considered equal if the strings they store are equal.
/// tparam  L  The buffer size of the first fixed string object.
/// tparam  S  The buffer size of the second fixed string object.
/// @param[in]  lhs  The first fixed string object.
/// @param[in]  rhs  The second fixed string object.
/// @return  \c true if the strings in the two objects are identical.
/// @since  x.y.z, 13.01.2021
template< size_t L, size_t S>
   bool operator ==( const FixedString< L>& lhs, const FixedString< S>& rhs)
      noexcept
{
   return (lhs.length() == rhs.length())
          && (::memcmp( lhs.c_str(), rhs.c_str(), lhs.length()) == 0);
} // operator ==


/// Inequality comparison operator as free function, is capable of comparing two
/// fixed strings with different sizes.
/// Objects are considered not equal if the strings they store are not equal.
/// tparam  L  The buffer size of the first fixed string object.
/// tparam  S  The buffer size of the second fixed string object.
/// @param[in]  lhs  The first fixed string object.
/// @param[in]  rhs  The second fixed string object.
/// @return  \c true if the strings in the two objects are diferent.
/// @since  x.y.z, 13.01.2021
template< size_t L, size_t S>
   bool operator !=( const FixedString< L>& lhs, const FixedString< S>& rhs)
      noexcept
{
   return (lhs.length() != rhs.length())
          && (::memcmp( lhs.c_str(), rhs.c_str(), lhs.length()) != 0);
} // operator !=


} // namespace celma::common


// =====  END OF fixed_string.hpp  =====

