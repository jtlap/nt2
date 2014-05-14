//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sign.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <complex>

//////////////////////////////////////////////////////////////////////////////
// scalar runtime benchmark for functor<sign_>
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::sign_;

namespace n1 {
  typedef float             sT;
  typedef std::complex<sT>  T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(sT)>::type vcT;
  NT2_TIMING(sign_,((vcT,T(-10, -10),T(10, 10))))
}
namespace n2 {
  typedef double           sT;
  typedef std::complex<sT>  T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(sT)>::type vcT;
  NT2_TIMING(sign_,((vcT,T(-10, -10),T(10, 10))))
}


#undef RS
