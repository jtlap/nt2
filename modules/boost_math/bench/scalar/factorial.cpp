//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 boost_math toolbox - factorial/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of boost_math components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/boost_math/include/factorial.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/unit/bench_includes.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<factorial_> from boost_math
//////////////////////////////////////////////////////////////////////////////
using nt2::boost_math::tag::factorial_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef int8_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n2 {
  typedef int16_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n3 {
  typedef int32_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n4 {
  typedef int64_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n5 {
  typedef uint8_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n6 {
  typedef uint16_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n7 {
  typedef uint32_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}
namespace n8 {
  typedef uint64_t T;
  typedef nt2::meta::as_integer<T>::type iT;
  NT2_TIMING(factorial_<double>,(RS(T,T(0),T(10))))
}

#undef RS
