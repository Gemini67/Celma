
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::Storage.


#ifndef CELMA_PROG_ARGS_DETAIL_STORAGE_HPP
#define CELMA_PROG_ARGS_DETAIL_STORAGE_HPP


#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/summary_options.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Type of the data entries that are actually stored.
/// @tparam  U  The type of the objects to store.
/// @since  0.15.0, 21.06.2017
template< typename U> class Data
{
public:
   /// Constructor.
   /// @param[in]  key   The key == short and/or long argument.
   /// @param[in]  data  The data to store with the key.
   /// @since  0.15.0, 21.06.2017
   Data( const ArgumentKey& key, U data):
      mKey( key),
      mData( data)
   {
   } // Data< U>::Data

   // defaults suit me fine
   Data( const Data&) = default;
   ~Data() = default;
   Data& operator =( const Data&) = default; 

   /// Equality comparison operator.<br>
   /// Checks only the key == the arguments. Keys are considered equal if
   /// the short or the long argument are equal, whatever is set first in
   /// both keys.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this and \a other have the same key.
   /// @since  0.15.0, 21.06.2017
   bool operator ==( const Data& other) const
   {
      return mKey == other.mKey;
   } // Data< U>::operator ==

   /// Equality comparison operator.<br>
   /// Keys are considered equal if the short or the long argument are equal,
   /// whatever is set first in both keys.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this and \a other have the same key.
   /// @since  0.15.0, 21.06.2017
   bool operator ==( const ArgumentKey& other) const
   {
      return mKey == other;
   } // Data< U>::operator ==

   /// Checks the given key if there is a mismatch with any other existing
   /// entry.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if a mismatch with an existing entry was detected.
   /// @since  0.15.0, 22.06.2017
   bool mismatch( const ArgumentKey& other) const
   {
      return mKey.mismatch( other);
   } // Data< U>::mismatch

   /// Returns the key of an entry.
   /// @return  The key.
   /// @since  0.15.0, 21.06.2017
   const ArgumentKey& key() const
   {
      return mKey;
   } // Data< U>::key

   /// Returns the data element of an entry.
   /// @return  The data.
   /// @since  0.15.0, 21.06.2017
   const U& data() const
   {
      return mData;
   } // Data< U>::data

private:
   /// The key == short and/or long argument.
   ArgumentKey  mKey;
   /// The data to store with the argument.
   U            mData;

}; // Data< U>


// Template Storage
// ================


/// Helper class to store data with an ArgumentKey as key.<br>
/// The objects stored in this container are deleted when the container is
/// deleted.<br>
/// Instead of using two maps, one with the short argument key (character) and
/// the other using the long argument key (string, word) as index, we store
/// all data in an unsorted vector.<br>
/// This may be a bit slower because we have to linear-search through the
/// container for an entry, but since we are talking about program arguments
/// here, we don't expect millions of entries.
/// @tparam  T  The type of the objects to store.
/// @tparam  E  The type of exception to throw when an argument already exists.
/// @since  0.15.0, 21.06.2017
template< typename T, class E = std::invalid_argument> class Storage
{
public:
   /// Constructor.
   /// @param[in]  allow_dups  Specifies if duplicate entries should be allowed.
   /// @since  0.15.0, 21.06.2017
   Storage( bool allow_dups = false);

   /// Adds a new entry.<br>
   /// Ensures that no entry with the same key (short or long argument) exists
   /// already.
   /// @param[in]  data  The data to store with the key.
   /// @param[in]  key   The key for this entry.
   /// @since  0.15.0, 23.06.2017
   void addArgument( T data, const ArgumentKey& key) noexcept( false);

   /// Adds a new entry.<br>
   /// Ensures that no entry with the same key (short or long argument) exists
   /// already.
   /// @param[in]  data      The data to store with the key.
   /// @param[in]  arg_spec  The argument character, string or both.
   /// @since  0.15.0, 21.06.2017
   void addArgument( T data, const std::string& arg_spec) noexcept( false);

   /// Adds multiple keys to the internal container, all with the same value.
   /// @param[in]  first  Iterator pointing to the first key to add.
   /// @param[in]  last   End-iterator.
   /// @param[in]  data   The value to add with the keys.
   /// @since  0.15.0, 20.07.2017
   template< typename I> void insert( I first, const I& last, T data)
      noexcept( false);

   /// Storage type for the argument keys and objects.
   using cont_t = std::vector< Data< T>>;

   /// Iterator type for accessing the elements in the container.
   using const_iterator = typename cont_t::const_iterator;

   /// Returns the first entry.
   /// @return  Iterator pointing to the first entry.
   /// @since  0.15.0, 26.06.2017
   const_iterator begin() const;

   /// Returns the first entry.
   /// @return  Iterator pointing to the first entry.
   /// @since  0.15.0, 26.06.2017
   const_iterator cbegin() const;

   /// Returns the past-the-end entry.
   /// @return  Iterator pointing behind the last entry.
   /// @since  0.15.0, 26.06.2017
   const_iterator end() const;

   /// Returns the past-the-end entry.
   /// @return  Iterator pointing behind the last entry.
   /// @since  0.15.0, 26.06.2017
   const_iterator cend() const;

   /// Searches for an entry.
   /// @param[in]  key  The key of the entry to search for.
   /// @return  Iterator pointing to the entry when found.
   /// @since  0.15.0, 26.06.2017
   const_iterator find( const ArgumentKey& key) const;

   /// Returns if then container is empty.
   /// @return  \c true if the container is empty.
   /// @since  0.15.0, 26.06.2017
   bool empty() const;

   /// Removes the entry that the given iterator is pointing to.
   /// @param[in]  it  Iterator pointing to the element to delete.
   /// @return  Iterator pointing to the next entry.
   /// @since  0.15.0, 27.06.2017
   const_iterator erase( const_iterator& it);

   /// Returns the number of entries.
   /// @return  Number of entries.
   /// @since  0.15.0, 27.06.2017
   size_t size() const;

   /// Iterates over the stored arguments, checks which ones have been set and
   /// prints the details into the stream.
   ///
   /// @param[in]  contents_set
   ///    Set of flags that specify the contents of the summary to print.
   /// @param[out]  os
   ///    The stream to write the summary to.
   /// @param[in]   arg_prefix
   ///    Specifies the prefix for the arguments of this handler. Used when the
   ///    argument handler handles the arguments of a sub-group.
   /// @since  1.8.0, 03.07.2018
   void printSummary( sumoptset_t contents_set, std::ostream& os,
      const char* arg_prefix) const;

private:
   /// Flag set in constructor, specifies if duplicates are allowed.
   const bool  mAllowDuplicates;
   /// The argument keys and their objects.
   cont_t      mArgs;

}; // Storage< T, E>


// inlined methods
// ===============


template< typename T, typename E> Storage< T, E>::Storage( bool allow_dups):
   mAllowDuplicates( allow_dups),
   mArgs()
{
} // Storage< T, E>::Storage


template< typename T, typename E>
   void Storage< T, E>::addArgument( T data, const ArgumentKey& key)
{

   if (!mAllowDuplicates)
   {
      for (const auto& entry : mArgs)
      {
         if (entry == key)
            throw E( "argument with key '" + format::toString( key)
                     + "' stored already");
         if (entry.mismatch( key))
            throw E( "argument with key '" + format::toString( key)
                     + "' conflicts with stored entry '"
                     + format::toString( entry.key()));
      } // end for
   } // end if

   mArgs.push_back( Data< T>( key, data));

} // Storage< T, E>::addArgument


template< typename T, typename E>
   void Storage< T, E>::addArgument( T data, const std::string& arg_spec)
{
   return addArgument( data, ArgumentKey( arg_spec));
} // Storage< T, E>::addArgument


template< typename T, typename E>
   template< typename I>
      void Storage< T, E>::insert( I first, const I& last, T data)
{
   while (first != last)
      addArgument( data, *first++);
} // Storage< T, E>::insert


template< typename T, typename E>
   typename Storage< T, E>::const_iterator Storage< T, E>::begin() const
{
   return mArgs.begin();
} // Storage< T, E>::begin


template< typename T, typename E>
   typename Storage< T, E>::const_iterator Storage< T, E>::cbegin() const
{
   return mArgs.cbegin();
} // Storage< T, E>::cbegin


template< typename T, typename E>
   typename Storage< T, E>::const_iterator Storage< T, E>::end() const
{
   return mArgs.end();
} // Storage< T, E>::end


template< typename T, typename E>
   typename Storage< T, E>::const_iterator Storage< T, E>::cend() const
{
   return mArgs.cend();
} // Storage< T, E>::cend


template< typename T, typename E>
   typename Storage< T, E>::const_iterator
      Storage< T, E>::find( const ArgumentKey& key) const
{
//   return mArgs.find( key);
   return std::find( mArgs.cbegin(), mArgs.cend(), key);
} // Storage< T, E>::find


template< typename T, typename E> bool Storage< T, E>::empty() const
{
   return mArgs.empty();
} // Storage< T, E>::empty


template< typename T, typename E>
   typename Storage< T, E>::const_iterator
      Storage< T, E>::erase( const_iterator& it)
{
   return mArgs.erase( it);
} // Storage< T, E>::erase


template< typename T, typename E> size_t Storage< T, E>::size() const
{
   return mArgs.size();
} // Storage< T, E>::size


template< typename T, typename E>
   void Storage< T, E>::printSummary( sumoptset_t contents_set,
      std::ostream& os, const char* arg_prefix) const
{

   for (auto const& entry : mArgs)
   {
      // pointer to the object that handles this argument, derived from
      // TypedArgBase
      auto const  argh = entry.data();

      if (argh->hasValue())
      {
         std::ostringstream  os_value;

         argh->printValue( os_value, contents_set & SummaryOptions::with_type);

         os << "   ";

         os << "Value <" << os_value.str() << "> set on variable '"
            << argh->varName() << "'";

         if (contents_set & SummaryOptions::with_key)
         {
            os << " by argument '";

            // have an argument prefix from a group-handler?
            if (arg_prefix != nullptr)
               os << arg_prefix << "'/'";

            os << format::toString( argh->key()) << "'";
         } // end if

         os << "." << std::endl;
      } // end if
   } // end for

} // Storage< T, E>::printSummary


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_STORAGE_HPP


// =====  END OF storage.hpp  =====

