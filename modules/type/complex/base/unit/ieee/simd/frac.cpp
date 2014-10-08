//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/frac.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( frac_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::frac;
  using nt2::tag::frac_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<frac_(vcT)>::type), vcT );

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL( frac(nt2::Inf<vcT>()  ), nt2::Nan<vcT>());
  NT2_TEST_EQUAL( frac(nt2::Minf<vcT>() ), nt2::Nan<vcT>());
  NT2_TEST_EQUAL( frac(nt2::Nan<vcT>()  ), nt2::Nan<vcT>());
#endif
  NT2_TEST_EQUAL( frac(nt2::Mone<vcT>() ), nt2::Zero<vcT>());
  NT2_TEST_EQUAL( frac(nt2::One<vcT>()  ), nt2::Zero<vcT>());
  NT2_TEST_EQUAL( frac(nt2::Zero<vcT>() ), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(frac(nt2::splat<vcT>(cT(1.5, 2.25))), nt2::splat<vcT>(cT(0.5, 0.25)));
  NT2_TEST_ULP_EQUAL(frac(nt2::splat<vcT>(cT(1.5, 2.3))), nt2::splat<vcT>(cT(0.5, 0.3)), 2);
}
