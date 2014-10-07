//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/negate.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( negate_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::negate;
  using nt2::tag::negate_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::meta::call<negate_(vcT, vcT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, vcT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::negate(nt2::Inf<vcT>(), nt2::Inf<vcT>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(nt2::negate(nt2::Minf<vcT>(), nt2::Minf<vcT>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(nt2::negate(nt2::Nan<vcT>(), nt2::Nan<vcT>()), nt2::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(nt2::negate(nt2::Mone<vcT>(), nt2::Mone<vcT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(nt2::negate(nt2::One<vcT>(), nt2::Mone<vcT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(nt2::negate(nt2::One<vcT>(), nt2::One<vcT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(nt2::negate(nt2::Zero<vcT>(), nt2::Zero<vcT>()), nt2::Zero<r_t>());
}
