//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ldexp.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( ldexp_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::ldexp;
  using boost::simd::tag::ldexp_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ldexp_(T,iT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  std::cout << std::endl;
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ldexp(boost::simd::Inf<T>(),  2), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Minf<T>(), 2), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Nan<T>(),  2), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(ldexp(boost::simd::Mone<T>(), 2), -boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<T>(),  2), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Zero<T>(), 2), boost::simd::Zero<r_t>());
}
