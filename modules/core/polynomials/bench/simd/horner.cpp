//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/real_splat.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

typedef float T;
typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
typedef vT::native_type nT;
#define C0 0x3c19c53b
#define C1 0x3b4c779c
#define C2 0x3cc821b5
#define C3 0x3d5ac5c9
#define C4 0x3e0896dd

extern "C"
{

/* horner0_case:
 *   vmulps  .LC0(%rip), %ymm0, %ymm1
 *   vaddps  .LC1(%rip), %ymm1, %ymm1
 *   vmulps  %ymm1, %ymm0, %ymm1
 *   vaddps  .LC2(%rip), %ymm1, %ymm1
 *   vmulps  %ymm1, %ymm0, %ymm1
 *   vaddps  .LC3(%rip), %ymm1, %ymm1
 *   vmulps  %ymm1, %ymm0, %ymm0
 *   vaddps  .LC4(%rip), %ymm0, %ymm0
 *   ret
 */
BOOST_FORCEINLINE vT horner0_case_impl(vT const& x)
{
  return nt2::horner< NT2_HORNER_COEFF(T, 5, (C0, C1, C2, C3, C4)) >(x);
}
BOOST_NOINLINE nT horner0_case(nT x_)
{
  vT x = x_;
  return horner0_case_impl(x);
}

BOOST_FORCEINLINE vT horner1_case_impl(vT const& x)
{
  using boost::simd::fma;
  using boost::simd::single_constant;
  return fma(x, fma(x, fma(x, fma(x, single_constant<vT, C0>(), single_constant<vT, C1>()), single_constant<vT, C2>()), single_constant<vT, C3>()), single_constant<vT, C4>());
}
BOOST_NOINLINE nT horner1_case(nT x_)
{
  vT x = x_;
  return horner1_case_impl(x);
}

BOOST_FORCEINLINE vT horner2_case_impl(vT const& x)
{
  using boost::simd::fma;
  using boost::simd::single_constant;

  vT y = single_constant<vT, C0>();
  vT c = single_constant<vT, C1>();

  y = fma(x, y, c);
  c = single_constant<vT, C2>();
  y = fma(x, y, c);
  c = single_constant<vT, C3>();
  y = fma(x, y, c);
  c = single_constant<vT, C4>();
  y = fma(x, y, c);

  return y;
}
BOOST_NOINLINE nT horner2_case(nT x_)
{
  vT x = x_;
  return horner2_case_impl(x);
}

/* estrin_case:
 *   vmulps  .LC1(%rip), %ymm0, %ymm1
 *   vmulps  .LC3(%rip), %ymm0, %ymm2
 *   vmulps  %ymm0, %ymm0, %ymm0
 *   vaddps  .LC2(%rip), %ymm1, %ymm1
 *   vaddps  .LC4(%rip), %ymm2, %ymm2
 *   vmulps  %ymm1, %ymm0, %ymm1
 *   vmulps  %ymm0, %ymm0, %ymm0
 *   vaddps  %ymm2, %ymm1, %ymm1
 *   vmulps  .LC0(%rip), %ymm0, %ymm0
 *   vaddps  %ymm1, %ymm0, %ymm0
 *   ret
 */
BOOST_FORCEINLINE vT estrin_case_impl(vT const& x)
{
  using boost::simd::fma;
  using boost::simd::sqr;
  using boost::simd::single_constant;

  return fma(sqr(x)*sqr(x), single_constant<vT, C0>(), fma(sqr(x), fma(x, single_constant<vT, C1>(), single_constant<vT, C2>()), fma(x, single_constant<vT, C3>(), single_constant<vT, C4>())));
}
BOOST_NOINLINE nT estrin_case(nT x_)
{
  vT x = x_;
  return estrin_case_impl(x);
}

}

NT2_TEST_CASE(consistency_test)
{
  vT x = boost::simd::splat<vT>(10.2);

  vT y1 = horner0_case(x);
  vT y2 = horner1_case(x);
  vT y3 = horner2_case(x);
  vT y4 = estrin_case(x);

  NT2_TEST_ULP_EQUAL(y1, y2, 0.5);
  NT2_TEST_ULP_EQUAL(y1, y3, 0.5);
  NT2_TEST_ULP_EQUAL(y1, y4, 0.5);
}
