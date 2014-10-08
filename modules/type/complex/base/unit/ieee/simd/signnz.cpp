//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/signnz.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( signnz_real, NT2_SIMD_REAL_TYPES)
{
  using nt2::signnz;
  using nt2::tag::signnz_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  typedef typename nt2::meta::call<signnz_(vcT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, vcT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(signnz(nt2::Inf<vcT>()  ), nt2::One<r_t>());
  NT2_TEST_EQUAL(signnz(nt2::Minf<vcT>() ), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(signnz(nt2::Nan<vcT>()  ), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(nt2::Inf<T>(), nt2::Inf<T>()))), nt2::Cnan<vcT>());
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(nt2::Inf<T>(), 1))), nt2::splat<vcT>(cT(1)));
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(1, nt2::Inf<T>()))), nt2::splat<vcT>(cT(0, 1)));
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(0, nt2::Inf<T>()))), nt2::splat<vcT>(cT(0, 1)));
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(1, nt2::Nan<T>()))), nt2::Cnan<vcT>());
  NT2_TEST_EQUAL(signnz(nt2::splat<vcT>(cT(0, nt2::Nan<T>()))), nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Nan<T>())));
#endif
  NT2_TEST_EQUAL(signnz(nt2::Mone<vcT>() ), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(signnz(nt2::One<vcT>()  ), nt2::One<r_t>());
  NT2_TEST_EQUAL(signnz(nt2::Zero<vcT>() ), nt2::One<r_t>());
  NT2_TEST_ULP_EQUAL(signnz(nt2::splat<vcT>(cT(3, 4))), nt2::splat<vcT>(cT(3.0/5.0, 4.0/5.0)), 0.5);
}
