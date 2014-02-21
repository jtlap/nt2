//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

using nt2::tag::pow_;

#define RS(T,V1,V2) (T, (V1) ,(V2))


namespace n1 {
  typedef float T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(vT,T(-10),T(10))))
}
namespace n2 {
  typedef double T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(vT,T(-10),T(10))))
}
namespace n3 {
  typedef float T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
  typedef typename nt2::meta::scalar_of<viT>::type iT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(viT,iT(-10),iT(10))))
}
namespace n4 {
  typedef double T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
  typedef typename nt2::meta::scalar_of<viT>::type iT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(viT,iT(-10),iT(10))))
}

namespace n3 {
  typedef float T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
  typedef typename nt2::meta::scalar_of<viT>::type iT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(iT,iT(-10),iT(10))))
}
namespace n4 {
  typedef double T;
  typedef boost::simd::meta::vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
  typedef typename nt2::meta::scalar_of<viT>::type iT;
  NT2_TIMING(pow_,(RS(vT,T(0),T(10)))(RS(iT,iT(-10),iT(10))))
}
#undef RS
