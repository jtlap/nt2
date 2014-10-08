//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ldexp.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( ldexp_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::ldexp;
  using nt2::tag::ldexp_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  NT2_TEST_TYPE_IS( (typename nt2::meta::call<ldexp_(vcT, iT)>::type), vcT );

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ldexp(nt2::Inf<vcT>(),  iT(2)), nt2::Inf<vcT>());
  NT2_TEST_EQUAL(ldexp(nt2::Minf<vcT>(), 2), nt2::Minf<vcT>());
  NT2_TEST_EQUAL(ldexp(nt2::Nan<vcT>(),  2), nt2::Nan<vcT>());
  NT2_TEST_EQUAL(ldexp(nt2::Inf<vdT>(),  2), nt2::Inf<vdT>());
  NT2_TEST_EQUAL(ldexp(nt2::Minf<vdT>(), 2), nt2::Minf<vdT>());
  NT2_TEST_EQUAL(ldexp(nt2::Nan<vdT>(),  2), nt2::Nan<vdT>());
#endif
  NT2_TEST_EQUAL(ldexp(nt2::One<vcT>(),  2), nt2::Four<vcT>());
  NT2_TEST_EQUAL(ldexp(nt2::Zero<vcT>(), 2), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(ldexp(nt2::splat<vcT>(cT(nt2::One<T>(),nt2::One<T>())) ,  2), nt2::splat<vcT>(cT(nt2::Four<T>(),nt2::Four<T>())) );
  NT2_TEST_EQUAL(ldexp(nt2::One<vdT>(),  2), nt2::Four<vdT>());
  NT2_TEST_EQUAL(ldexp(nt2::Zero<vdT>(), 2), nt2::Zero<vdT>());
}
