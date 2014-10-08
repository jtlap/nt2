//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/pow.hpp>

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
#include <nt2/include/functions/splat.hpp>
#include <nt2/table.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( pow3,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  nt2::table<T> a = nt2::ones(3, 3, nt2::meta::as_<T>());
  nt2::table<T> b = nt2::ones(3, 3, nt2::meta::as_<T>());
  // specific values tests
 for(int i=1; i <= 3; i++)
 {
   NT2_TEST_ULP_EQUAL(nt2::pow(nt2::splat<vcT>(a(i)), nt2::splat<vcT>(b(i))), nt2::splat<vcT>(a(i)), 10.0);
 }
}

NT2_TEST_CASE_TPL ( pow4,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  nt2::table<cT> a = nt2::ones(1, 3, nt2::meta::as_<T>());
  for(int i=1; i <= 3; i++) a(i) =  cT(i, i);
  nt2::table<cT> b = nt2::ones(1, 3, nt2::meta::as_<T>());
  for(int i=1; i <= 3; i++) b(i) = cT(i-1);
  nt2::table<cT> r(nt2::of_size(1, 3));
  r(1) = cT(1,0); r(2) = cT(2,2); r(3) = cT(0,18);

  // specific values tests
 for(int i=1; i <= 3; i++)
 {
   NT2_TEST_ULP_EQUAL(nt2::pow(nt2::splat<vcT>(a(i)), nt2::splat<vcT>(b(i))), nt2::splat<vcT>(r(i)), 10.0);
 }

}
