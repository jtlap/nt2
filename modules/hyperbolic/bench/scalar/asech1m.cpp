//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/hyperbolic/include/asech1m.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>


//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<asech1m_> from hyperbolic
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::asech1m_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) ,T(V2))

namespace n1 {
  typedef float T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n2 {
  typedef double T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n3 {
  typedef uint8_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n4 {
  typedef uint16_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n5 {
  typedef uint32_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n6 {
  typedef uint64_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n7 {
  typedef int8_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n8 {
  typedef int16_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n9 {
  typedef int32_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}
namespace n10 {
  typedef int64_t T;
  NT2_TIMING(nt2::tag::asech1m_,(RS(T,T(0),T(1))))
}

#undef RS
