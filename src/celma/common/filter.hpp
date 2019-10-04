
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
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_FILTER_HPP
#define CELMA_COMMON_FILTER_HPP


#include <stdexcept>
#include <vector>
#include "celma/common/clear_container.hpp"
#include "celma/common/detail/filters.hpp"


namespace celma { namespace common {


template< typename T> class Filter
{
public:
   /// 
   /// @since  x.y.z, 31.10.2017
   Filter();

   ~Filter();

   void addSingleValueFilter( const T& value, bool inverted = false);

   void addRangeFilter( const T& min_value, const T& max_value,
                        bool inverted = false);

   /// 
   /// @param[in]  value_list  .
   /// @param[in]  inverted    .
   /// @since  x.y.z, 02.11.2017
   void addValueListFilter( const std::vector <T>& value_list,
                            bool inverted = false);

   /// 
   /// @param[in]  min_val  .
   /// @since  x.y.z, 02.11.2017
   void addMinimumFilter( const T& min_val);

   /// 
   /// @param[in]  max_val  .
   /// @since  x.y.z, 02.11.2017
   void addMaximumFilter( const T& max_val);

   bool matches( const T& value) const noexcept( false);

private:
   using filter_base_t = detail::FilterBase< T>;
   using filter_cont_t = std::vector< filter_base_t*>;

   filter_cont_t  mFilters;

}; // Filter< T>


// inlined methods
// ===============


template< typename T> Filter< T>::Filter():
   mFilters()
{
}


template< typename T> Filter< T>::~Filter()
{
   Vector::clear( mFilters);
}


template< typename T>
   void Filter< T>::addSingleValueFilter( const T& value, bool inverted)
{
   mFilters.push_back( new detail::SingleValue< T>( value, inverted));
}


template< typename T>
   void Filter< T>::addRangeFilter( const T& min_value, const T& max_value,
                                    bool inverted)
{
   mFilters.push_back( new detail::ValueRange< T>( min_value, max_value,
                                                   inverted));
}


template< typename T>
   void Filter< T>::addValueListFilter( const std::vector <T>& value_list,
                                        bool inverted)
{
   mFilters.push_back( new detail::ValueList< T>( value_list, inverted));
}


template< typename T> void Filter< T>::addMinimumFilter( const T& min_val)
{
   mFilters.push_back( new detail::MinimumValue< T>( min_val));
}


template< typename T> void Filter< T>::addMaximumFilter( const T& max_val)
{
   mFilters.push_back( new detail::MaximumValue< T>( max_val));
}


template< typename T> bool Filter< T>::matches( const T& value) const
{
   if (mFilters.empty())
      throw std::runtime_error( "no filter specified");

   bool  final_result = false;

   for (auto const& next_fiter : mFilters)
   {
      switch (next_fiter->matches( value))
      {
      case detail::FilterBase< T>::Result::matches:
         final_result = true;
         break;
      case detail::FilterBase< T>::Result::excluded:
         return false;
      default:
         break;
      } // end switch
   } // end for
   return final_result;
}


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_FILTER_HPP


// =====  END OF filter.hpp  =====

