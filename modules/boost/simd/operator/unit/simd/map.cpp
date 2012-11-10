//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - map/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/operator/include/functions/map.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/unary_plus.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/if_else.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>

NT2_TEST_CASE_TPL ( map_integer__2_0,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::map;
  using boost::simd::native;
  using boost::simd::tag::map_;
  using boost::simd::tag::unary_plus_;
  using boost::simd::tag::plus_;
  using boost::simd::tag::if_else_;
  typedef boost::dispatch::functor<unary_plus_> uni_f;
  typedef boost::dispatch::functor<plus_> bin_f;
  typedef boost::dispatch::functor<if_else_> tri_f;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> nT;
  typedef typename boost::simd::meta::as_logical<nT>::type nlT;

  typedef typename boost::dispatch::meta::call<map_(uni_f,nT)>::type ur_t;
  typedef typename boost::dispatch::meta::call<map_(bin_f,nT,nT)>::type br_t;
  typedef typename boost::dispatch::meta::call<map_(tri_f,nT,nT,nT)>::type tr_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(ur_t, nT);
  NT2_TEST_TYPE_IS(br_t, nT);
  NT2_TEST_TYPE_IS(tr_t, nT);

  // specific values tests
  NT2_TEST_EQUAL(map(uni_f(),boost::simd::One<nT>()), boost::simd::One<ur_t>());
  NT2_TEST_EQUAL(map(uni_f(),boost::simd::One<nT>()), boost::simd::One<ur_t>());
  NT2_TEST_EQUAL(map(uni_f(),boost::simd::One<nT>()), boost::simd::One<ur_t>());

  NT2_TEST_EQUAL(map(bin_f(),boost::simd::One<nT>(), boost::simd::One<nT>()), boost::simd::Two<br_t>());
  NT2_TEST_EQUAL(map(bin_f(),boost::simd::One<nT>(), boost::simd::One<nT>()), boost::simd::Two<br_t>());
  NT2_TEST_EQUAL(map(bin_f(),boost::simd::One<nT>(), boost::simd::One<nT>()), boost::simd::Two<br_t>());

  NT2_TEST_EQUAL(map(tri_f(),boost::simd::False<nlT>(),boost::simd::One<nT>(), boost::simd::Two<nT>()), boost::simd::Two<br_t>());
  NT2_TEST_EQUAL(map(tri_f(),boost::simd::True<nlT>(),boost::simd::One<nT>(), boost::simd::Two<nT>()), boost::simd::One<br_t>());
  NT2_TEST_EQUAL(map(tri_f(),boost::simd::True<nlT>(),boost::simd::One<nT>(), boost::simd::Two<nT>()), boost::simd::One<br_t>());
}
