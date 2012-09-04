//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 trigonometric toolbox - cosine/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/trigonometric/include/functions/cosine.hpp>
#include <nt2/toolbox/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<cosine_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cosine_;
using nt2::tag::fast_cos_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))
namespace nnn01 {
  typedef float T;
  NT2_TIMING(fast_cos_,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nnn1 {
  typedef float T;
  NT2_TIMING(fast_cos_,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn01 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_small>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_small>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n01 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::small_>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n1 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::small_>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n011 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_small>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n11 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_small>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn011 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::medium>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn11 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::medium>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_medium>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::direct_medium>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0111 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_medium>,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn111 {
  typedef float T;
  NT2_TIMING(cosine_<nt2::clipped_medium>,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}


#undef RS
