//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/dawson.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>

using nt2::tag::dawson_;

#define RS(T,V1,V2) (T, T(V1) ,T(V2))

// benches tests on each computing branch of dawson
namespace n1 {
  typedef float T;
  NT2_TIMING(dawson_,(RS(T,T(0),T(10))))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(dawson_,(RS(T,T(0),T(10))))
}
namespace n3 {
  typedef float T;
  NT2_TIMING(dawson_,(RS(T,T(0),T(3.25))))
}
namespace n4 {
  typedef double T;
  NT2_TIMING(dawson_,(RS(T,T(0),T(3.25))))
}
namespace n5 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(dawson_,(RS(T,T(3.25),T(6.25))))
}
namespace n6 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(dawson_,(RS(T,T(3.25),T(6.25))))
}
namespace n7 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(dawson_,(RS(T,T(6.25),T(10))))
}
namespace n8 {
  typedef double T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  NT2_TIMING(dawson_,(RS(T,T(6.25),T(10))))
}

#undef RS
