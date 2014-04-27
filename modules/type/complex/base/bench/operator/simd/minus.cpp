//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <complex>
#include <cmath>
#include <boost/simd/sdk/tuple.hpp>
#include <boost/simd/sdk/simd/native.hpp>
//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<plus_> from operator
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::plus_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float                             T;
  using boost::simd::native;
  typedef std::complex<T>                  cT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;
  NT2_TIMING(plus_,(RS(vcT,cT(-100, -100),cT(100, 100)))(RS(vcT,cT(-100, -100),cT(100, 100))))
}
namespace n2 {
  typedef double                             T;
  using boost::simd::native;
  typedef std::complex<T>                  cT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;
  NT2_TIMING(plus_,(RS(vcT,cT(-100, -100),cT(100, 100)))(RS(vcT,cT(-100, -100),cT(100, 100))))
}


#undef RS
