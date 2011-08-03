//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_BENCH_MODULE "nt2 predicates toolbox - is_not_less_equal/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/predicates/include/is_not_less_equal.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>
typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<is_not_less_equal_> from predicates
//////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::is_not_less_equal_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(is_not_less_equal_,(RS(vT,T(-10000),T(10000)))(RS(vT,T(-10000),T(10000))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  BOOST_SIMD_TIMING(is_not_less_equal_,(RS(vT,T(-10000),T(10000)))(RS(vT,T(-10000),T(10000))))
}

#undef RS
