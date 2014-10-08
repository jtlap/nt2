//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/is_ngtz.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( is_ngtz_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::is_ngtz;
  using nt2::tag::is_ngtz_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::meta::as_logical<vcT>::type vlT;
  typedef typename boost::dispatch::meta::call<is_ngtz_(vcT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, vlT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(is_ngtz(nt2::Inf<vcT>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_ngtz(nt2::Minf<vcT>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_ngtz(nt2::Nan<vcT>()), nt2::True<r_t>());
#endif
  NT2_TEST_EQUAL(is_ngtz(nt2::Mzero<vcT>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_ngtz(nt2::One<vcT>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_ngtz(nt2::Zero<vcT>()), nt2::True<r_t>());
}
