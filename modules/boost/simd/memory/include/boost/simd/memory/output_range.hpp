//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_OUTPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_OUTPUT_RANGE_HPP_INCLUDED

#include <boost/simd/memory/output_iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd
{
  template<std::size_t N, class Iterator> BOOST_FORCEINLINE
  boost::iterator_range<output_iterator<typename std::iterator_traits<Iterator>::value_type, N> >
  output_range( Iterator const& begin, Iterator const& end )
  {
    return boost::make_iterator_range(output_begin<N>(begin),output_end<N>(end));
  }

  template<class Iterator> BOOST_FORCEINLINE
  boost::iterator_range< simd::output_iterator<typename std::iterator_traits<Iterator>::value_type> >
  output_range( Iterator const& begin, Iterator const& end )
  {
    return boost::make_iterator_range( output_begin(begin), output_end(end) );
  }

  template<std::size_t N, class Range> BOOST_FORCEINLINE
  boost::iterator_range<output_iterator<typename range_value<Range const>::type,N> >
  output_range( Range const& r )
  {
    return output_range<N>( boost::begin(r), boost::end(r) );
  }

  template<class Range> BOOST_FORCEINLINE
  boost::iterator_range<output_iterator<typename range_value<Range const>::type> >
  output_range( Range const& r )
  {
    return output_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
