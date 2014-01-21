//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_cotpi.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<fast_cotpi_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::fast_cotpi_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(fast_cotpi_,(RS(T,T(-0.25),T(0.25))))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(fast_cotpi_,(RS(T,T(-0.25),T(0.25))))
}


#undef RS
