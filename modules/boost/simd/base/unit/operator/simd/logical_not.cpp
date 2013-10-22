//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/logical_not.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_less_equal.hpp>
#include <boost/simd/include/functions/is_greater_equal.hpp>
#include <boost/simd/include/functions/is_not_less.hpp>
#include <boost/simd/include/functions/is_not_greater.hpp>
#include <boost/simd/include/functions/is_not_less_equal.hpp>
#include <boost/simd/include/functions/is_not_greater_equal.hpp>
#include <boost/simd/sdk/simd/pack.hpp>

#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( logical_not_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::logical_not;
  using boost::simd::tag::logical_not_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< boost::simd::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<logical_not_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(logical_not(boost::simd::False<vlT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_not(boost::simd::True<vlT>()), boost::simd::False<r_t>());
}

NT2_TEST_CASE_TPL ( logical_not_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::logical_not;
  using boost::simd::tag::logical_not_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< boost::simd::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<logical_not_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(logical_not(boost::simd::False<vlT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_not(boost::simd::True<vlT>()), boost::simd::False<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( logical_not_optimization,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical_not;
  using boost::simd::tag::is_not_less_;
  using boost::simd::tag::is_not_less_equal_;
  using boost::simd::tag::is_not_greater_;
  using boost::simd::tag::is_not_greater_equal_;
  using boost::simd::pack;
  using boost::simd::splat;
  using boost::dispatch::meta::call;

  typedef typename call<is_not_less_(pack<T>,pack<T>)>::type nl_t;
  typedef typename call<is_not_less_equal_(pack<T>,pack<T>)>::type nle_t;
  typedef typename call<is_not_greater_(pack<T>,pack<T>)>::type ng_t;
  typedef typename call<is_not_greater_equal_(pack<T>,pack<T>)>::type nge_t;

  pack<T> x,y;

  NT2_TEST_EXPR_TYPE( !(x<y) , boost::mpl::_, nl_t  );
  NT2_TEST_EXPR_TYPE( !(x<=y), boost::mpl::_, nle_t );
  NT2_TEST_EXPR_TYPE( !(x>y) , boost::mpl::_, ng_t  );
  NT2_TEST_EXPR_TYPE( !(x>=y), boost::mpl::_, nge_t );
}
