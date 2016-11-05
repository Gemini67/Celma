
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions celma::common::find_sequence_end()
/// and find_sequence_start().


#ifndef CELMA_COMMON_FIND_SEQUENCE_HPP
#define CELMA_COMMON_FIND_SEQUENCE_HPP


#include <cstddef>


namespace celma { namespace common {


/// Finds the end of a sequence that starts at \a first. The sequence may
/// contain a nested sequence within.
/// @tparam  T  The type of the value stored in the data.
/// @tparam  I  Forward-iterator type.
/// @param[in]  first    Iterator pointing to the beginning of the sequence.
/// @param[in]  last     End of the data to search in.
/// @param[in]  end_seq  The value that means 'end of the sequence'.
/// @return  Iterator pointing to the position of the corresponding \a end_seq
///          value, \a last if the end of the sequence was not found.
/// @since  0.5, 05.11.2016
template< typename T, typename I>
   I find_sequence_end( I first, I last, T end_seq)
{

   // number of sequence-start values we have found, i.e. number of sequence-end
   // values we still have to find
   size_t      num_seq_start = 1;
   // store the value that marks the beginning of a sequence
   const auto  seq_start = *first;

   while (++first != last)
   {
      if (*first == end_seq)
      {
         if (--num_seq_start == 0)
            break;   // while
      } else if (*first == seq_start)
      {
         ++num_seq_start;
      } // end if
   } // end while

   return first;
} // find_sequence_end


/// Finds the beginning of a sequence that ends at \a last. The sequence may
/// contain a nested sequence within.
/// @tparam  T  The type of the value stored in the data.
/// @tparam  I  Backward-iterator type.
/// @param[in]  last       Iterator pointing to the end of the sequence.
/// @param[in]  first      Beginning of the data to search in.
/// @param[in]  start_seq  The value that means 'start of the sequence'.
/// @return  Iterator pointing to the position of the corresponding \a start_seq
///          value, \a first if the beginning of the sequence was not found.
/// @since  0.5, 05.11.2016
template< typename T, typename I>
   I find_sequence_start( I last, I first, T start_seq)
{

   // number of sequence-end values we have found, i.e. number of sequence-start
   // values we still have to find
   size_t      num_seq_end = 1;
   // store the value that marks the beginning of a sequence
   const auto  seq_end = *last;

   while (--last != first)
   {
      if (*last == start_seq)
      {
         if (--num_seq_end == 0)
            break;   // while
      } else if (*last == seq_end)
      {
         ++num_seq_end;
      } // end if
   } // end while

   return last;
} // find_sequence_start


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_FIND_SEQUENCE_HPP


// ========================  END OF find_sequence.hpp  ========================

