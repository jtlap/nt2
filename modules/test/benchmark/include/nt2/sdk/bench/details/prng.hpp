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
#ifndef NT2_SDK_BENCH_DETAILS_PRNG_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_PRNG_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace nt2
{
  namespace details
  {
    template<typename T>
    NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW
    void prng_fill_impl( boost::iterator_range<T*> data, T minimum, T maximum );
  }

  // Portably reproducible pseudo "random" values.
  //                                         (24.07.2012.) (Domagoj Saric)
  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW void prng_reset();


  template<typename Range>
  void roll ( Range & data
            , typename Range::value_type const minimum
            , typename Range::value_type const maximum
            )
  {
    typedef boost::iterator_range<typename Range::value_type *> range_t;
    details::prng_fill_impl<typename Range::value_type>
    (
      range_t( &*data.begin(), (&*(data.end()-1))+1 ), minimum, maximum
    );
  }
}

#endif
