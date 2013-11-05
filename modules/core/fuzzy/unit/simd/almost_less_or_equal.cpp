//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/almost_less_or_equal.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( almost_less_or_equal_real_3,  NT2_SIMD_REAL_TYPES)
{
  using nt2::almost_less_or_equal;
  using nt2::tag::almost_less_or_equal_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::as_integer<vT>::type          ivT;
  typedef typename nt2::meta::call<almost_less_or_equal_(vT,vT,ivT)>::type r_t;
  typedef typename nt2::meta::as_logical<vT>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
  NT2_TEST_EQUAL(almost_less_or_equal(nt2::splat<vT>(0),nt2::splat<vT>(0),nt2::splat<ivT>(1)), nt2::True<r_t>());
  NT2_TEST_EQUAL(almost_less_or_equal(nt2::splat<vT>(0),nt2::splat<vT>(1),nt2::splat<ivT>(1)), nt2::True<r_t>());
}
