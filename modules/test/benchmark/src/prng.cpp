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
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/prng.hpp>
#include <boost/foreach.hpp>

// \note std::rand() does not produce portably reproducible numbers so we
// resort to Boost.Random.
//                                           (24.10.2012.) (Domagoj Saric)
// \note NT2Bench configuration has exceptions disabled and Boost.Random
// fails to compile then because it uses naked throw statements.
// https://svn.boost.org/trac/boost/ticket/7497
//                                           (12.10.2012.) (Domagoj Saric)
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace nt2
{
  namespace details
  {
    static boost::random::rand48 prng_singleton;

    template <typename T>
    BOOST_DISPATCH_NOTHROW
    void prng_fill_impl ( boost::iterator_range<T*> const data
                        , T const minimum
                        , T const maximum
                        )
    {
      boost::random::uniform_real_distribution<T> const dist(minimum, maximum);

      BOOST_FOREACH( T & scalar, data )
        scalar = dist( prng_singleton );
    }

    template NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW
    void prng_fill_impl( boost::iterator_range<int*>    , int   , int     );

    template NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW
    void prng_fill_impl( boost::iterator_range<float*>  , float , float   );

    template NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW
    void prng_fill_impl( boost::iterator_range<double*> , double, double  );
  }

  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOTHROW void prng_reset()
  {
    details::prng_singleton.seed( 42 );
  }
}
