
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::detail::PropertyIterator.


// module header file include
#include "celma/container/detail/property_iterator.hpp"


namespace celma::container::detail {



/// Creates an iterator that points to the first value of all properties.<br>
/// If the first element of the top property map is a map itself, create an
/// iterator for the sub-map and search there for the first value.
///
/// @param[in]  properties
///    The top-level property map.
/// @param[in]  path_sep
///    The character to use as separator when building a property path.
/// @since  1.22.0, 12.03.2019
PropertyIterator::PropertyIterator( PropertyCont& properties, char path_sep):
   mPathSeparator( path_sep),
   mEntriesStack(),
   mCurrentEntry( properties.map())
{

   findNextValue();

} // PropertyIterator::PropertyIterator



/// Returns the complete path and name of the current entry.
///
/// @return  The complete path plus name of the current entry.
/// @since  1.22.0, 19.03.2019
std::string PropertyIterator::pathAndName() const
{

   if (mCurrentEntry.atEnd())
      return mCurrentEntry.mPathPrefix;

   std::string  full( mCurrentEntry.mPathPrefix);

   if (!full.empty())
      full.append( 1, mPathSeparator);

   full.append( mCurrentEntry.mEntryIter->first);

   return full;
} // PropertyIterator::pathAndName



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
/// @since  1.22.0, 13.03.2019
void PropertyIterator::findNextValue()
{

   assert( mCurrentEntry.mpProperties != nullptr);

   while (!mCurrentEntry.atEnd())
   {
      if (mCurrentEntry.entryType() == PropertyEntry::Types::map)
      {
         mEntriesStack.push( mCurrentEntry);
         mCurrentEntry.append( mCurrentEntry.mEntryIter->first, mPathSeparator);
         auto  sub_map = static_cast< PropertyCont*>( mCurrentEntry.mEntryIter->second);
         mCurrentEntry.reset( sub_map->map());
      } else if (mCurrentEntry.entryType() == PropertyEntry::Types::link)
      {
         auto  link_dest = mCurrentEntry.linkDest();
         if (link_dest->entryType() == PropertyEntry::Types::value)
         {
            // link to single value, treat like direct value
            break;
         } // end if

         mEntriesStack.push( mCurrentEntry);
         mCurrentEntry.append( mCurrentEntry.mEntryIter->first, mPathSeparator);
         auto  sub_map = static_cast< PropertyCont*>( link_dest);
         mCurrentEntry.reset( sub_map->map());
      } else // entry type == value
      {
         break;
      } // end if
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



} // namespace celma::container::detail


// =====  END OF property_iterator.cpp  =====

