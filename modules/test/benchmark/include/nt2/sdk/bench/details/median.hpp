//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_MEDIAN_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_MEDIAN_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace nt2 { namespace details
{
  template <typename T> NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW
  T median_impl( boost::iterator_range<T*> data );

  template<class Range>
  typename Range::value_type median( Range & data )
  {
    typedef boost::iterator_range<typename Range::value_type*> range_t;
    return median_impl<typename Range::value_type>(range_t( &*data.begin()
                                                          , (&*(data.end()-1))+1
                                                          )
                                                  );
  }
} }

#endif
