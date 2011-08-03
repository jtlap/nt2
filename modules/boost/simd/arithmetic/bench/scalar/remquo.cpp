//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 arithmetic toolbox - remquo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/arithmetic/include/remquo.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<remquo_> from arithmetic
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::remquo_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(remquo_,(RS(T,T(0),T(10)))(RS(T,T(0),T(10))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(remquo_,(RS(T,T(0),T(10)))(RS(T,T(0),T(10))))
}

#undef RS
