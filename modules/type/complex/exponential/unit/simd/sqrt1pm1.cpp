//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqrt1pm1.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sqrt1pm1;
  using nt2::tag::sqrt1pm1_;
  typedef typename std::complex<T> cT;  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Inf<vcT>()),   nt2::Inf<vcT>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Minf<vcT>()),  nt2::mul_i(nt2::Inf<vcT>())-nt2::One<vcT>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Nan<vcT>()),   nt2::Cnan<vcT>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Mone<vcT>()),     nt2::Mone<vcT>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::One<vcT>()),      nt2::Sqrt_2<vcT>()-nt2::One<vcT>(), 2);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(vcT(nt2::Eps<vT>())),  nt2::Eps<vcT>()*nt2::Half<vcT>(), 2);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(vcT(nt2::Mone<vT>(),   nt2::Two<vT>() )), nt2::I<vcT>(), 2);
  NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Zero<vcT>()),     nt2::Zero<vcT>(), 0);
}
