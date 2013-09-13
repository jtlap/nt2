//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fast_rec.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>

NT2_TEST_CASE_TPL ( fast_rec_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::fast_rec;
  using boost::simd::tag::fast_rec_;

  typedef typename boost::dispatch::meta::call<fast_rec_(T)>::type r_t;
  NT2_TEST_TYPE_IS( r_t, T );

  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Mone<T>()), boost::simd::Mone<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Mzero<T>()), boost::simd::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::One<T>()), boost::simd::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Zero<T>()), boost::simd::Inf<r_t>(), 0);
}
