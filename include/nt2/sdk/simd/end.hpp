/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_END_HPP_INCLUDED
#define NT2_SDK_SIMD_END_HPP_INCLUDED

#include <nt2/sdk/simd/iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace nt2 { namespace simd
{
  template<std::size_t N, class ContiguousRange>
  iterator<typename boost
                    ::iterator_value< typename
                                      ContiguousRange::const_iterator
                                    >::type
          , N
          >
  end( ContiguousRange const& rng )
  {
    typedef typename ContiguousRange::const_iterator      it_type;
    typedef typename boost::iterator_value<it_type>::type value_type;

    std::size_t sz  = boost::size(rng);
    std::size_t asz = memory::align_on<N>(sz);
    it_type     ptr = boost::begin(rng) + asz - N*(sz != asz);

    iterator<value_type,N> that(&(*ptr));
    return that;
  }
} }

#endif
