//==============================================================================
//         Copyright 2014 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>

using nt2::tag::plus_;

namespace c1
{
  typedef float             sT;
  typedef std::complex<sT>  T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(sT)>::type vT;

  NT2_TIMING( plus_
            , ((vT,T(-100,-100),T(100,100)))
              ((vT,T(-100,-100),T(100,100)))
            )
}

namespace n2
{
  typedef double            sT;
  typedef std::complex<sT>  T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(sT)>::type vT;

  NT2_TIMING( plus_
            , ((vT,T(-100,-100),T(100,100)))
              ((vT,T(-100,-100),T(100,100)))
            )
}
