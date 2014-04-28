//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/nthroot.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <complex>

//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<nthroot_>
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::nthroot_;

#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef std::complex<float> T;
  typedef typename nt2::meta::as_integer<float>::type iT;
  NT2_TIMING(nthroot_,(RS(T,T(-10, -10),T(10, 10)))(RS(iT,iT(-10), iT(10))))
    }
namespace n2 {
  typedef std::complex<double> T;
  typedef typename nt2::meta::as_integer<double>::type iT;
  NT2_TIMING(nthroot_,(RS(T,T(-10, -10),T(10, 10)))(RS(iT,iT(-10), iT(10))))
    }


#undef RS
