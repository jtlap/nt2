//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 swar toolbox - sort/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of swar components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/swar/include/sort.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<sort_> from swar
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::sort_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(sort_,(RS(T,T(-100),T(100))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(sort_,(RS(T,T(-100),T(100))))
}

#undef RS
