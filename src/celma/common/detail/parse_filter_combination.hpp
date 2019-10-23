
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
/// See documentation of template function
/// celma::common::detail::parseFilterCombination()<>.


#ifndef CELMA_COMMON_DETAIL_PARSE_FILTER_COMBINATION_HPP
#define CELMA_COMMON_DETAIL_PARSE_FILTER_COMBINATION_HPP


// all other includes are in the top-level headerfile, except:
#include <boost/lexical_cast.hpp>


namespace celma { namespace common { namespace detail {


/// Parses the sub-string of a filter string which contains all conditions that
/// must be combined in one filter.
/// The first filter must be added, all other filters must be appended.
///
/// @tparam  T  The type of the values to create the filters for.
/// @param[out]  vf
///    The filter object to add the filters to.
/// @param[in]  cond
///    The string with the part of the conditions to parse.
/// @throw
///    std::invalid_argument when the string contains invalid contents.
/// @throw
///    boost::bad_lexical_cast when an expected filter value cannot be
///    converted into the filter value type.
/// @since  x.y.z, 09.10.2019
template< typename T>
   void parseFilterCombination( ValueFilter< T>& vf, const std::string& cond)
      noexcept( false)
{

   Tokenizer  tk( cond, '+');
   bool       first = true;

   for (auto filter_def : tk)
   {
      bool  inverted = (filter_def[ 0] == '!');
      if (inverted)
      {
         filter_def.erase( 0, 1);

         if (filter_def.empty())
            throw std::invalid_argument( "filter part string must not be empty");
      } // end if

      switch (filter_def[ 0])
      {
      case '[':
         {
            filter_def.erase( 0, 1);
            const T  min_val = boost::lexical_cast< T>( filter_def);
            if (first)
               vf.addMinimumFilter( min_val);
            else
               vf.appendMinimumFilter( min_val);
         } // end scope
         break;

      case ']':
         {
            filter_def.erase( 0, 1);
            const T  max_val = boost::lexical_cast< T>( filter_def);
            if (first)
               vf.addMaximumFilter( max_val);
            else
               vf.appendMaximumFilter( max_val);
         } // end scope
         break;

      default:
         // single value or range
         {
            auto const  pos = filter_def.find( "-");
            if (pos == std::string::npos)
            {
               const T  val = boost::lexical_cast< T>( filter_def);
               if (first)
                  vf.addSingleValueFilter( val, inverted);
               else
                  vf.appendSingleValueFilter( val, inverted);
            } else
            {
               const T  startval = boost::lexical_cast< T>( filter_def.substr( 0, pos));
               const T  endval = boost::lexical_cast< T>( filter_def.substr( pos + 1));
               if (first)
                  vf.addRangeFilter( startval, endval, inverted);
               else
                  vf.appendRangeFilter( startval, endval, inverted);
            } // end if
         } // end scope
         break;
      } // end switch

      first = false;
   } // end for

   if (first)
      throw std::invalid_argument( "no valid filter found");

} // parseFilterCombination


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_PARSE_FILTER_COMBINATION_HPP


// =====  END OF parse_filter_combination.hpp  =====

