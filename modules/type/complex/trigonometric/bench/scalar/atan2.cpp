//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/atan2.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <complex>

//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<atan2_>
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::atan2_;

#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef std::complex<float> T;
  NT2_TIMING(atan2_,(RS(T,T(-10, -10),T(10, 10)))(RS(T,T(-10, -10),T(10, 10))))
}
namespace n2 {
  typedef std::complex<double> T;
  NT2_TIMING(atan2_,(RS(T,T(-10, -10),T(10, 10)))(RS(T,T(-10, -10),T(10, 10))))
}


#undef RS
