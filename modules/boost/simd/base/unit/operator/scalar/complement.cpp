//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/complement.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/shift_left.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( complement_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::complement;
  using boost::simd::tag::complement_;
  typedef typename boost::dispatch::meta::call<complement_(T)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(complement(boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(complement(boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( complement_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::complement;
  using boost::simd::tag::complement_;
  typedef typename boost::dispatch::meta::call<complement_(T)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
  NT2_TEST_EQUAL(complement(boost::simd::One<T>()), boost::simd::shli(boost::simd::Mone<r_t>(),1));
  NT2_TEST_EQUAL(complement(boost::simd::Three<T>()), boost::simd::shli(boost::simd::Mone<r_t>(),2));
  NT2_TEST_EQUAL(complement(boost::simd::Zero<T>()), boost::simd::Mone<r_t>());
} // end of test for integer_
