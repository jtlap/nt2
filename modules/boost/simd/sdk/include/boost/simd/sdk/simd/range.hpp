//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_RANGE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_RANGE_HPP_INCLUDED

#include <boost/simd/sdk/simd/iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd
{
  template<std::size_t N, class ContiguousRange>
  boost::iterator_range< simd::input_iterator<typename range_value<ContiguousRange const>::type, N> >
  range( ContiguousRange const& rng )
  {
    return boost::make_iterator_range( simd::input_begin<N>(boost::begin(rng))
                                     , simd::input_end<N>(boost::end(rng))
                                     );
  }

  template<class ContiguousRange>
  boost::iterator_range< simd::input_iterator<typename range_value<ContiguousRange const>::type> >
  range( ContiguousRange const& rng )
  {
    return boost::make_iterator_range( simd::input_begin(boost::begin(rng))
                                     , simd::input_end(boost::end(rng))
                                     );
  }

  template<std::size_t N, class ForwardIterator>
  boost::iterator_range< simd::input_iterator<typename std::iterator_traits<ForwardIterator>::value_type, N> >
  range( ForwardIterator const& begin, ForwardIterator const& end )
  {
    return boost::make_iterator_range( simd::input_begin<N>(begin)
                                     , simd::input_end<N>(end)
                                     );
  }

  template<class ForwardIterator>
  boost::iterator_range< simd::input_iterator<typename std::iterator_traits<ForwardIterator>::value_type> >
  range( ForwardIterator const& begin, ForwardIterator const& end )
  {
    return boost::make_iterator_range( simd::input_begin(begin)
                                     , simd::input_end(end)
                                     );
  }
} }

#endif
