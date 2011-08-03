//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 reduction toolbox - posmin/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of reduction components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/reduction/include/posmin.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<posmin_> from reduction
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::posmin_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(posmin_,(RS(T,T(-100),T(100))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  BOOST_SIMD_TIMING(posmin_,(RS(T,T(-100),T(100))))
}

#undef RS
