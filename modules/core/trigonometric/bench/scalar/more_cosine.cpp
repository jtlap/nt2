//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cosine.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <nt2/include/constants/pi.hpp>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<more_cosine_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cosine_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::small_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n011 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_small_>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n11 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_small_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn011 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::medium_>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn11 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::medium_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_medium_>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_medium_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0111 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_medium_>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn111 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_medium_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}


#undef RS
