//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 arithmetic toolbox - remainder/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/arithmetic/include/remainder.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<remainder_> from arithmetic
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::remainder_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,T(-10),T(10)))(RS(T,T(-10),T(10))))
}
namespace n2 {
  typedef double T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,T(-10),T(10)))(RS(T,T(-10),T(10))))
}
namespace n3 {
  typedef uint8_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,0,100))(RS(T,1,100)))
}
namespace n4 {
  typedef uint16_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,0,100))(RS(T,1,100)))
}
namespace n5 {
  typedef uint32_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,0,100))(RS(T,1,100)))
}
namespace n6 {
  typedef uint64_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,0,100))(RS(T,1,100)))
}
namespace n7 {
  typedef int8_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,-100,100))(RS(T,1,100)))
}
namespace n8 {
  typedef int16_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,-100,100))(RS(T,1,100)))
}
namespace n9 {
  typedef int32_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,-100,100))(RS(T,1,100)))
}
namespace n10 {
  typedef int64_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(remainder_,(RS(T,-100,100))(RS(T,1,100)))
}

#undef RS
