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
#include <nt2/toolbox/trigonometric/include/cosine.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<cosine_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cosine_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))
namespace nn01 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  typedef nt2::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_cephes>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  typedef nt2::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_cephes>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n01 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  typedef nt2::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::small>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n1 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  typedef nt2::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::small>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
// namespace n11 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


// namespace n02 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace n2 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }

// namespace n21 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }

// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }

// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,T(-1.0e15),T(1.0e15))))
// }

// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


// namespace m01 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace m02 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }namespace m1 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace m2 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace m11 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace m21 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace m111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace m211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace m111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace m211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace m111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }
// namespace m211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }

// namespace n01 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace n02 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }namespace n1 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace n2 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace n11 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n21 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n111 {
//   typedef float T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }
// namespace n211 {
//   typedef double T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   typedef nt2::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


#undef RS
