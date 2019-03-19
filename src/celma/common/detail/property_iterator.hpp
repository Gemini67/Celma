
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::PropertyIterator.


#ifndef CELMA_COMMON_DETAIL_PROPERTY_ITERATOR_HPP
#define CELMA_COMMON_DETAIL_PROPERTY_ITERATOR_HPP


#include <cassert>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include "celma/common/detail/property_entry.hpp"
#include "celma/common/detail/property_map.hpp"
#include "celma/common/pre_postfix.hpp"


namespace celma { namespace common { namespace detail {


/// Iterator for properties.<br>
/// Unlike standard iterators, this iterator provides specific methods to
/// retrieve the data of the current property. This is partly to hide
/// implementation details, partly because the required information is built in
/// the iterator only and finally to handle the values with different types.<br>
/// Since properties are not stored in one container, but in containers stored
/// in containers, it is not possible to e.g. have just one internal iterator
/// object. Instead, when a sub-map is encountered, the current iterator must be
/// stored, then an interator is created for the sub-map, and when we finished
/// processing the sub-map we return and continue with the previous iterator.
///
/// @since  x.y.z, 12.03.2019
class PropertyIterator
{
public:
   using iterator_tag = std::forward_iterator_tag;

   /// Default constructor, can be used for end() iterators.
   ///
   /// @since  x.y.z, 13.03.2019
   PropertyIterator() = default;

   /// Creates an iterator that points to the first value of all properties.<br>
   /// If the first element of the top property map is a map itself, create an
   /// iterator for the sub-map and search there for the first value.
   ///
   /// @param[in]  properties
   ///    The top-level property map.
   /// @param[in]  path_sep
   ///    The character to use as separator when building a property path.
   /// @since  x.y.z, 12.03.2019
   explicit PropertyIterator( PropertyMap& properties, char path_sep);

   /// Default copy constructor and destructor should be okay.
   PropertyIterator( const PropertyIterator&) = default;
   ~PropertyIterator() = default;

   /// Prefix increment operator.
   ///
   /// @param[in]  std::prefix  Actually void == no parameter for prefix.
   /// @return
   ///    Reference to this object which just moved the internal iterator to the
   ///    next value.
   /// @since  x.y.z, 13.03.2019
   PropertyIterator& operator ++( std::prefix);

   /// Postfix increment operator.
   ///
   /// @param[in]  std::postfix
   ///    Dummy parameter used to distinguish from the prefix operator.
   /// @return
   ///    The old value of this object.
   /// @since  x.y.z, 13.03.2019
   PropertyIterator operator ++( std::postfix);

   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return
   ///    \c true if this object and the other point to the same entry, or both
   ///    equal to end().
   /// @since  x.y.z, 13.03.2019
   bool operator ==( const PropertyIterator& other) const;

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  The other object to compare against.
   /// @return
   ///    \c true if this object and the other do not point to the same entry.
   /// @since  x.y.z, 13.03.2019
   bool operator !=( const PropertyIterator& other) const;

   /// Returns the path of the current entry (without the name of the entry
   /// itself).
   ///
   /// @return
   ///    The path of the current entry, may be an empty string for top-level
   ///    properties.
   /// @since  x.y.z, 12.03.2019
   const std::string& path() const;

   /// Returns the name of the current entry (without the path to the entry).
   ///
   /// @return
   ///    The name of the current entry.
   /// @since  x.y.z, 12.03.2019
   const std::string& name() const;

   /// Returns the complete path and name of the current entry.
   ///
   /// @return  The complete path plus name of the current entry.
   /// @since  x.y.z, 19.03.2019
   std::string pathAndName() const;

   /// Returns the value of the current entry.
   ///
   /// @return
   ///    The value of the current entry.
   /// @since  x.y.z, 12.03.2019
   template< typename T> const T& value() const noexcept( false);

private:
   /// Helper class to manage the entries needed to store the current position
   /// in a property map.
   ///
   /// @since  x.y.z, 12.03.2019
   class CurrentEntry
   {
   public:
      /// Default construction of objects is fine.
      CurrentEntry() = default;

      /// Constructor with the iterator position to store.
      /// 
      /// @param[in]  properties  The property map to start iterating over.
      /// @since  x.y.z, 12.03.2019
      CurrentEntry( PropertyMap::map_t& properties):
         mPathPrefix(),
         mpProperties( &properties),
         mEntryIter( properties.begin())
      {
      } // PropertyIterator::CurrentEntry::CurrentEntry

      /// Clears the current entry (clear path and set the iterator to end).
      ///
      /// @since  x.y.z, 13.03.2019
      void reset()
      {
         mPathPrefix.clear();
         mpProperties = nullptr;
      } // PropertyIterator::CurrentEntry::reset

      /// Resets this object to iterate over the given map.
      ///
      /// @param[in]  properties  The map to start iterating over.
      /// @since  x.y.z, 15.03.2019
      void reset( PropertyMap::map_t& properties)
      {
         mpProperties = &properties;
         mEntryIter = properties.begin();
      } // PropertyIterator::CurrentEntry::reset

      /// Append the given path to the current path prefix.<br>
      /// If the path prefix already contains a path, add a separator first.
      ///
      /// @param[in]  path
      ///    The path to append to the current path prefix.
      /// @param[in]  path_sep
      ///    Separator character to use.
      /// @since  x.y.z, 13.03.2019
      void append( const std::string& path, char path_sep)
      {
         if (!mPathPrefix.empty())
         {
            mPathPrefix.append( 1, path_sep);
         } // end if
         mPathPrefix.append( path);
      } // PropertyIterator::CurrentEntry::append

      /// Returns if the internal entry iterator equals the map's end()
      /// iterator.
      ///
      /// @return  \c true if the internal iterator equals end().
      /// @since  x.y.z, 15.03.2019
      bool atEnd() const
      {
         return (mpProperties == nullptr) || (mEntryIter == mpProperties->end());
      } // PropertyIterator::CurrentEntry::atEnd

      /// Shortcut to get the type of the property entry to which the iterator
      /// currently points.
      ///
      /// @return
      ///    The type of the property entry to which the stored iterator
      ///    currently points.
      /// @since  x.y.z, 15.03.2019
      PropertyEntry::Types entryType() const
      {
         return mEntryIter->second->entryType();
      } // PropertyIterator::CurrentEntry::entryType

      /// Equality comparison operator.
      ///
      /// @param[in]  other  The other object to compare against.
      /// @return
      ///    \c true if this object and the other point to the same property map
      ///    entry.
      /// @since  x.y.z, 13.03.2019
      bool operator ==( const CurrentEntry& other) const
      {
         return ((mpProperties == nullptr) && (other.mpProperties == nullptr))
                || ((mPathPrefix == other.mPathPrefix)
                    && (mpProperties == other.mpProperties)
                    && (mEntryIter == other.mEntryIter));
      } // PropertyIterator::CurrentEntry::operator ==

      /// The path prefix of the current entry.
      std::string                   mPathPrefix;
      /// The property map to which the iterator belongs.
      PropertyMap::map_t*           mpProperties = nullptr;
      /// The property map iterator pointing to the current value.
      PropertyMap::map_t::iterator  mEntryIter;
   }; // PropertyIterator::CurrentEntry

   /// Container used to store the path of parent maps that led to the current
   /// entry.
   using entry_stack_t = std::stack< CurrentEntry>;

   /// Tries to find the next value, i.e. the next entry that contains a
   /// value.<br>
   /// The iterator of the current entry must have been prepared before, i.e.
   /// set to the start point or incremented aready.<br>
   /// If the next map entry contains a sub-map, the current entry is pushed to
   /// the stack, the first entry of the sub-map is made the current entry and
   /// then findNextValue() is called to find the first value in the
   /// sub-map.<br>
   /// When the function returns, the current entry either points to the next
   /// value, or has been reset to end() if no more value existed.
   ///
   /// @since  x.y.z, 13.03.2019
   void findNextValue();

   /// The path separator to be used.
   const char     mPathSeparator = '-';
   /// Stack of the property entries with maps that brought use here.
   entry_stack_t  mEntriesStack;
   /// Data of the current entry.
   CurrentEntry   mCurrentEntry;

}; // PropertyIterator


// inlined methods
// ===============


inline
   PropertyIterator::PropertyIterator( PropertyMap& properties, char path_sep):
      mPathSeparator( path_sep),
      mEntriesStack(),
      mCurrentEntry( properties.mProperties)
{
   findNextValue();
} // PropertyIterator::PropertyIterator


inline PropertyIterator& PropertyIterator::operator ++( std::prefix)
{
   if (mCurrentEntry.atEnd())
      return *this;
   ++mCurrentEntry.mEntryIter;
   findNextValue();
   return *this;
} // PropertyIterator::operator ++


inline PropertyIterator PropertyIterator::operator ++( std::postfix)
{
   if (mCurrentEntry.atEnd())
      return *this;
   auto  copy( *this);
   ++mCurrentEntry.mEntryIter;
   findNextValue();
   return copy;
} // PropertyIterator::operator ++


inline bool PropertyIterator::operator ==( const PropertyIterator& other) const
{
   return mCurrentEntry == other.mCurrentEntry;
} // PropertyIterator::operator ==


inline bool PropertyIterator::operator !=( const PropertyIterator& other) const
{
   return !(mCurrentEntry == other.mCurrentEntry);
} // PropertyIterator::operator !=


inline const std::string& PropertyIterator::path() const
{
   return mCurrentEntry.mPathPrefix;
} // PropertyIterator::path


inline const std::string& PropertyIterator::name() const
{
   if (mCurrentEntry.atEnd())
      return mCurrentEntry.mPathPrefix;
   return mCurrentEntry.mEntryIter->first;
} // PropertyIterator::name


inline std::string PropertyIterator::pathAndName() const
{
   if (mCurrentEntry.atEnd())
      return mCurrentEntry.mPathPrefix;
   std::string  full( mCurrentEntry.mPathPrefix);
   if (!full.empty())
      full.append( 1, mPathSeparator);
   full.append( mCurrentEntry.mEntryIter->first);
   return full;
} // PropertyIterator::pathAndName


template< typename T> inline const T& PropertyIterator::value() const
{
   if (mCurrentEntry.mpProperties == nullptr)
      throw std::runtime_error( "no current element");
   auto  entry = static_cast< PropertyValue< T>*>( mCurrentEntry.mEntryIter->second);
   return entry->getValue();
} // PropertyIterator::value


inline void PropertyIterator::findNextValue()
{
   assert( mCurrentEntry.mpProperties != nullptr);
   while (!mCurrentEntry.atEnd()
          && (mCurrentEntry.entryType() == PropertyEntry::Types::map))
   {
      mEntriesStack.push( mCurrentEntry);
      mCurrentEntry.append( mCurrentEntry.mEntryIter->first, mPathSeparator);
      auto  sub_map = static_cast< PropertyMap*>( mCurrentEntry.mEntryIter->second);
      mCurrentEntry.reset( sub_map->mProperties);
   } // end while

   if (mCurrentEntry.atEnd())
   {
      if (!mEntriesStack.empty())
      {
         mCurrentEntry = mEntriesStack.top();
         mEntriesStack.pop();
         // the iterator in the current entry from the stack still points to the
         // map that we just returned from
         // have to increment the iterator now
         ++mCurrentEntry.mEntryIter;
         findNextValue();
         return;
      } // end if

      mCurrentEntry.reset();
   } // end if

} // PropertyIterator::findNextValue


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PROPERTY_ITERATOR_HPP


// =====  END OF property_iterator.hpp  =====

