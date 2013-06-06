//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED

#include <boost/simd/memory/aligned_input_iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd
{
  template<std::size_t N, class Iterator> BOOST_FORCEINLINE
  boost::iterator_range<aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type, N> >
  aligned_output_range( Iterator const& begin, Iterator const& end )
  {
    return  boost::make_iterator_range(input_begin<N>(begin),input_end<N>(end));
  }

  template<class Iterator> BOOST_FORCEINLINE
  boost::iterator_range< simd::aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type> >
  aligned_output_range( Iterator const& begin, Iterator const& end )
  {
    return boost::make_iterator_range( input_begin(begin), input_end(end) );
  }

  template<std::size_t N, class Range> BOOST_FORCEINLINE
  boost::iterator_range<aligned_input_iterator<typename range_value<Range const>::type,N> >
  aligned_output_range( Range const& r )
  {
    return aligned_output_range<N>( boost::begin(r), boost::end(r) );
  }

  template<class Range> BOOST_FORCEINLINE
  boost::iterator_range<aligned_input_iterator<typename range_value<Range const>::type> >
  aligned_output_range( Range const& r )
  {
    return aligned_output_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
