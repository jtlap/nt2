//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 polynomials toolbox - legendre/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of polynomials components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/polynomials/include/functions/legendre.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<legendre_> from polynomials
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::legendre_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<iT,ext_t> viT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(legendre_,(RS(viT,iT(0),iT(10)))(RS(vT,T(-1),T(1))))
}
namespace n2 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<iT,ext_t> viT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(legendre_,(RS(viT,iT(0),iT(10)))(RS(vT,T(-1),T(1))))
}

#undef RS
