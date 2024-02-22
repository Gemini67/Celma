
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of classes celma::common::ExecuteStatistic and
/// celma::common::ExecuteCounter, and the macros COUNT_EXECUTIONS and
/// GET_EXECUTIONS.


#pragma once


#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include "boost/preprocessor/cat.hpp"
#include "celma/common/extract_funcname.hpp"
#include "celma/common/singleton.hpp"
#include "celma/common/string_util.hpp"


namespace celma::common {


class ExecuteCounter;


// Class ExecuteStatistic
// ======================


/// Stores the "execute statistic" of a program, i.e. the counters, how many
/// times a specific function or blck of code was executed.<br>
/// Use the class ExecuteCounter and the macro COUNT_EXECUTIONS to define the
/// statistic count points.
///
/// @since  1.30.0, 23.06.2019
class ExecuteStatistic final: public Singleton< ExecuteStatistic>
{

   friend class Singleton< ExecuteStatistic>;
   friend class ExecuteCounter;

public:
   /// The key data that is used to identify a call point:
   /// - The name of the file.
   /// - The name of the function/method in which the call point is defined.
   /// - The line number where the call point is defined.
   using map_key_t = std::tuple< std::string, std::string, int>;
   /// The type of the container in which the call points and their counters are
   /// stored.
   using map_t = std::map< map_key_t, size_t>;

   /// The macro COUNT_EXECUTIONS stores the absolute path and file name for
   /// each call point. If the first part of the path should be removed, e.g.
   /// the path of the project development directory, pass the part to remove
   /// here.
   ///
   /// @param[in]  prefix
   ///    Part of the path to remove from the call point filenames.
   /// @since
   ///    1.30.0, 15.08.2019
   void erasePathPrefix( const std::string& prefix)
   {
      mPrefix = prefix;
   } // ExecuteStatistic::erasePathPrefix

   /// Returns the current execute counter for the given call point.
   ///
   /// @param[in]  file_name
   ///    Name of the file.
   /// @param[in]  func_name
   ///    Name of the function or method.
   /// @param[in]  line_nbr
   ///    Line number in the source file where the call point is defined.
   /// @return
   ///    Current number of executions of the call point, 0 if the call point
   ///    was never passed yet.
   /// @since  1.30.0, 23.06.2019
   size_t getExecutions( std::string file_name,
      const std::string& func_name, int line_nbr)
   {
      if (file_name.starts_with( mPrefix))
      {
         file_name.erase( 0, mPrefix.length());
      } // end if

      auto const  fname = extractFuncname( func_name);
      auto const  upper_bound = make_tuple( file_name, fname, line_nbr);
      auto        it = --mStats.upper_bound( upper_bound);

      return (it == mStats.end()) ? 0 : it->second;
   } // ExecuteStatistic::getExecutions

   /// Resets all counters to 0.
   ///
   /// @since  1.30.0, 23.06.2019
   void reset()
   {
      for (auto & it : mStats)
         it.second = 0;
   } // ExecuteStatistic::reset

   /// Returns an iterator pointing to the first counter in the map.
   ///
   /// @returns  Iterator pointing to the first element in the map.
   /// @since  1.30.0, 23.06.2019
   typename map_t::const_iterator begin() const
   {
      return mStats.begin();
   } // ExecuteStatistic::begin

   /// Returns an iterator pointing behind the last counter in the map.
   ///
   /// @returns  Iterator pointing behind the last element in the map.
   /// @since  1.30.0, 23.06.2019
   typename map_t::const_iterator end() const
   {
      return mStats.end();
   } // ExecuteStatistic::end

   /// Returns the size of the execute counter map, i.e. the number of counters/
   /// call points that were passed at least once.
   ///
   /// @returns  Current number of counters in the map.
   /// @since  1.30.0, 23.06.2019
   std::size_t size() const
   {
      return mStats.size();
   } // ExecuteStatistic::size

   /// Insertion operator for objects of this class, prints the current list of
   /// call points and their counters.
   ///
   /// @param[in]  os
   ///    Stream to write into.
   /// @param[in]  es
   ///    Object to print the statistic of.
   /// @returns  Stream as passed in.
   /// @since  1.30.0, 23.06.2019
   friend std::ostream& operator <<( std::ostream& os,
      const ExecuteStatistic& es)
   {
      for (auto const& it : es.mStats)
      {
         os << std::get< 0>( it.first) << ": " << std::get< 1>( it.first)
            << "[" << std::get< 2>( it.first) << "] = " << it.second << std::endl;
      } // end for
      return os;
   } // operator <<

protected:
   /// Default constructor.
   /// Called through the singleton.
   ///
   /// @since  1.30.0, 23.06.2019
   ExecuteStatistic() = default;

private:
   /// Returns an iterator pointing to the entry in the map for the given call
   /// point.
   ///
   /// @param[in]  file_name
   ///    Name of the file.
   /// @param[in]  func_name
   ///    Name of the function or method.
   /// @param[in]  line_nbr
   ///    Line number in the source file where the call point is defined.
   /// @return
   ///    Iterator pointing to the entry in the map for this call point.
   /// @since  1.30.0, 23.06.2019
   map_t::iterator callpoint( std::string file_name,
      const std::string& func_name, int line_nbr)
   {
      if (file_name.starts_with( mPrefix))
      {
         file_name.erase( 0, mPrefix.length());
      } // end if

      return mStats.insert( {{ file_name, func_name, line_nbr}, 0}).first;
   } // ExecuteStatistic::callpoint

   /// The map with the call points and their counters.
   map_t        mStats;
   /// The part of the path to remove from file names.
   std::string  mPrefix;

}; // ExecuteStatistic


// Class ExecuteCounter
// ====================


/// Helper class to create an entry for a call point in the ExecuteStatistic
/// and count the number of times that a call point was passed.
///
/// @since  1.30.0, 23.06.2019
class ExecuteCounter final
{
public:
   /// Constructor, stores the entry of this call point in the execute statistic
   /// container.
   ///
   /// @param[in]  file_name
   ///    Name of the file.
   /// @param[in]  func_name
   ///    Name of the function or method.
   /// @param[in]  line_nbr
   ///    Line number in the source file where the call point is defined.
   /// @since  1.30.0, 23.06.2019
   ExecuteCounter( const char* const file_name, const char* const func_name,
      int line_nbr)
   {
      mMyStat = ExecuteStatistic::instance().callpoint( file_name,
         extractFuncname( func_name), line_nbr);
   } // ExecuteCounter::ExecuteCounter

   /// This method should be called every time that a call point is passed. It
   /// increases the call counter in the execute statistic map.
   ///
   /// @since  1.30.0, 23.06.2019
   void count()
   {
      ++mMyStat->second;
   } // ExecuteCounter::count

private:
   /// Iterator pointing to the entry of this call point in the execute
   /// statistic container.
   ExecuteStatistic::map_t::iterator  mMyStat;

}; // ExecuteCounter


} // namespace celma::common


/// Helper macro to
/// - define a call point
/// - increase the execute counter every time the call point is passed.
/// .
/// This is achieved by ceating a static object of the ExecuteCounter class and
/// call the count() method on this object every time we pass by.
///
/// @since  1.30.0, 23.06.2019
#define  COUNT_EXECUTIONS \
   static celma::common::ExecuteCounter  BOOST_PP_CAT( ec, __LINE__)( __FILE__, \
      __PRETTY_FUNCTION__, __LINE__); \
   BOOST_PP_CAT( ec, __LINE__.count())


/// Helper macro to get the current execute statistic for the "current" call
/// point.<br>
/// Since the "current" call point is not actually known, it returns the last
/// call point in the same file and function defined before the current line.
/// This means that e.g. scope blocks are not taken into account.
///
/// @return
///    Number of times that the previous call point in the same file and
///    function was called.
/// @since  1.30.0, 23.06.2019
#define GET_EXECUTIONS() \
   celma::common::ExecuteStatistic::instance().getExecutions( __FILE__, \
      __PRETTY_FUNCTION__, __LINE__)


// =====  END OF execute_statistic.hpp  =====

