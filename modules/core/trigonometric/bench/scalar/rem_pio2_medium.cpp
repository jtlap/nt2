//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2_medium.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<rem_pio2_medium_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::rem_pio2_medium_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(rem_pio2_medium_,(RS(T,nt2::Zero<T>(),64*nt2::Pi<T>())))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(rem_pio2_medium_,(RS(T,nt2::Zero<T>(),64*nt2::Pi<T>())))
}

#undef RS
