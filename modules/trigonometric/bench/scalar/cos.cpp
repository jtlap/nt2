//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 trigonometric toolbox - cos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/trigonometric/include/cos.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<cos_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cos_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))
namespace n01 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n02 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n1 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n2 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
// namespace n3 {
//   typedef nt2::uint8_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(0),T(40))))
// }
// namespace n4 {
//   typedef nt2::uint16_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(0),T(40))))
// }
// namespace n5 {
//   typedef nt2::uint32_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(0),T(40))))
// }
// namespace n6 {
//   typedef nt2::uint64_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(0),T(40))))
// }
// namespace n7 {
//   typedef nt2::int8_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(-40),T(40))))
// }
// namespace n8 {
//   typedef nt2::int16_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(-40),T(40))))
// }
// namespace n9 {
//   typedef nt2::int32_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(-40),T(40))))
// }
// namespace n10 {
//   typedef nt2::int64_t T;
//   typedef nt2::meta::as_integer<T>::type iT;
//   NT2_TIMING(cos_,(RS(T,T(-40),T(40))))
// }
namespace n11 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
}
namespace n21 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
}
namespace n111 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
}
namespace n211 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
}
namespace n1111 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,T(-1.0e38),T(-1.0e38))))
}
namespace n2111 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(cos_,(RS(T,T(-1.0e300),T(-1.0e300))))
}
#undef RS
