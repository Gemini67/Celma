
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// This file combines the declarations of both the forward and reverse bitset
/// iterators, and also defines the overloads of the begin and end functions
/// in the namespace std, so that the functions are usable in a range-based
/// for loop.<br>
/// All iterators can only be used to access the bitset for reading, therefore
/// there is no real difference between an iterator and a const iterator.<br>
/// Functions defined in this module:
/// - std::begin()
/// - std::end()
/// - std::cbegin()
/// - std::cend()
/// - std::rbegin()
/// - std::rend()
/// - std::crbegin()
/// - std::crend()


#ifndef CELMA_COMMON_BITSET_ITERATOR_HPP
#define CELMA_COMMON_BITSET_ITERATOR_HPP


#include "celma/common/detail/forward_bitset_iterator.hpp"
#include "celma/common/detail/reverse_bitset_iterator.hpp"


namespace std {


/// Returns a forward bitset iterator pointing to first bit in the bitset that
/// is set.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Forward bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ForwardBitsetIterator< N>
   begin( bitset< N>& bs)
{
   return celma::common::detail::ForwardBitsetIterator< N>( bs);
} // begin


/// Returns a const forward bitset iterator pointing to first bit in the bitset
/// that is set.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Const forward bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ForwardBitsetIterator< N>
   cbegin( const bitset< N>& bs)
{
   return celma::common::detail::ForwardBitsetIterator< N>( bs);
} // cbegin


/// Returns a forward bitset iterator pointing to the end of the bitset.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Forward bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ForwardBitsetIterator< N>
   end( bitset< N>& bs)
{
   return celma::common::detail::ForwardBitsetIterator< N>( bs, true);
} // end


/// Returns a const forward bitset iterator pointing to the end of the bitset.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Const forward bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ForwardBitsetIterator< N>
   cend( const bitset< N>& bs)
{
   return celma::common::detail::ForwardBitsetIterator< N>( bs, true);
} // cend


/// Returns a reverse bitset iterator pointing to the last bit in the bitset
/// that is set.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Reverse bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ReverseBitsetIterator< N>
   rbegin( bitset< N>& bs)
{
   return celma::common::detail::ReverseBitsetIterator< N>( bs);
} // rbegin


/// Returns a const reverse bitset iterator pointing to the last bit in the
/// bitset that is set.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Const reverse bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ReverseBitsetIterator< N>
   crbegin( const bitset< N>& bs)
{
   return celma::common::detail::ReverseBitsetIterator< N>( bs);
} // crbegin


/// Returns a reverse bitset iterator pointing to the endof the bitset.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Reverse bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ReverseBitsetIterator< N>
   rend( bitset< N>& bs)
{
   return celma::common::detail::ReverseBitsetIterator< N>( bs, true);
} // rend


/// Returns a const reverse bitset iterator pointing to the last bit in the
/// bitset that is set.
///
/// @param[in]  bs  The bitset to iterate over.
/// @return  Const reverse bitset iterator.
/// @since  1.7.0, 18.07.2018
template< size_t N> celma::common::detail::ReverseBitsetIterator< N>
   crend( const bitset< N>& bs)
{
   return celma::common::detail::ReverseBitsetIterator< N>( bs, true);
} // crend


} // namespace std


#endif   // CELMA_COMMON_BITSET_ITERATOR_HPP


// =====  END OF bitset_iterator.hpp  =====

