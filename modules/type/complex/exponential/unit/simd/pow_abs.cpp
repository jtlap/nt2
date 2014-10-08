//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/pow_abs.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/table.hpp>

#include <nt2/include/constants/i.hpp>
#include <nt2/include/constants/two.hpp>

NT2_TEST_CASE_TPL ( pow_abs3,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  nt2::table<cT> a = nt2::ones(3, 3, nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::ones(3, 3, nt2::meta::as_<cT>());

  // specific values tests
  for(int i=1; i <= 3; i++)
    NT2_TEST_EQUAL(nt2::splat<vcT>(a(i)), nt2::pow_abs(nt2::splat<vcT>(a(i)), nt2::splat<vcT>(b(i))));
}

NT2_TEST_CASE_TPL ( pow_abs4,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  nt2::table<cT> a = nt2::ones(1, 3, nt2::meta::as_<cT>());
  nt2::table<cT> b = T(2)*nt2::ones(1, 3, nt2::meta::as_<cT>());

  for(int i=1; i <= 3; i++)
  {
    a(i) =  cT(i, i);
    // specific values tests
    NT2_TEST_ULP_EQUAL(nt2::pow_abs(nt2::splat<vcT>(a(i)), nt2::splat<vcT>(b(i))), nt2::Two<vcT>()*nt2::splat<vcT>(nt2::sqr(nt2::real(a(i)))), 2.0);
  }
}
