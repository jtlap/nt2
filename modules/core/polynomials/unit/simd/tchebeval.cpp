//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - tchebeval/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/polynomials/include/functions/tchebeval.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/array.hpp>

NT2_TEST_CASE_TPL ( tchebeval_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::tchebeval;
  using nt2::tag::tchebeval_;
  using boost::simd::native;

  typedef boost::array<T, 4 >         A_t;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  static const boost::array<T, 4 > A= {{ T(1), T(2), T(3), T(4) }};

  NT2_TEST_EQUAL(tchebeval( nt2::splat<vT>(1), A)[0], T(1.5));
  NT2_TEST_EQUAL(tchebeval( nt2::splat<vT>(2), A)[0], T(8.0));
  NT2_TEST_EQUAL(tchebeval( nt2::splat<vT>(3), A)[0], T(22.5));

} // end of test for floating_
