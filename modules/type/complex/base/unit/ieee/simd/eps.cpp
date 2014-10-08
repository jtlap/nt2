//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/eps.hpp>

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


#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( eps_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::eps;
  using nt2::tag::eps_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;

  typedef typename nt2::meta::call<eps_(vcT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, vT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(eps(nt2::Inf<vcT>() ), nt2::Nan<vT>());
  NT2_TEST_EQUAL(eps(nt2::Minf<vcT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(eps(nt2::Nan<vcT>() ), nt2::Nan<vT>());
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::Inf<T>(), nt2::Inf<T>()))), nt2::Nan<vT>());
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::Minf<T>(),nt2::Minf<T>()))), nt2::Nan<vT>());
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::Nan<T>() ,nt2::Nan<T>()))),  nt2::Nan<vT>());
#endif
  NT2_TEST_EQUAL(eps(nt2::Mone<vcT>()), eps(nt2::Mone<vT>()));
  NT2_TEST_EQUAL(eps(nt2::One<vcT>() ), eps(nt2::One<vT>() ));
  NT2_TEST_EQUAL(eps(nt2::Zero<vcT>()), eps(nt2::Zero<vT>()));
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::Mone<T>(),nt2::Mone<T>()))), eps(nt2::Sqrt_2<vT>()));
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::One<T>() ,nt2::One<T>()) )), eps(nt2::Sqrt_2<vT>() ));
  NT2_TEST_EQUAL(eps(nt2::splat<vcT>(cT(nt2::Zero<T>(),nt2::Zero<T>()))), eps(nt2::Zero<vT>()));
}
