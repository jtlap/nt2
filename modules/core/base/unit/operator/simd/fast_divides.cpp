//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/fast_divides.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( fast_divides_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::fast_divides;
  using boost::simd::splat;
  using nt2::tag::fast_divides_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_divides_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(fast_divides(splat<vT>(0),splat<vT>(0)), boost::simd::Nan<vT>());

  NT2_TEST_ULP_EQUAL(fast_divides(splat<vT>(1) , splat<vT>(2) ), splat<vT>(0.5)  , 16);
  NT2_TEST_ULP_EQUAL(fast_divides(splat<vT>(1) , splat<vT>(10)), splat<vT>(0.1)  , 16);
  NT2_TEST_ULP_EQUAL(fast_divides(splat<vT>(2) , splat<vT>(3) ), splat<vT>(2./3.), 16);
}

NT2_TEST_CASE_TPL ( fast_divides_ints,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using nt2::fast_divides;
  using boost::simd::splat;
  using nt2::tag::fast_divides_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_divides_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(fast_divides(splat<vT>(1) , splat<vT>(2) ), splat<vT>(0) );
  NT2_TEST_EQUAL(fast_divides(splat<vT>(5) , splat<vT>(2) ), splat<vT>(2) );
  NT2_TEST_EQUAL(fast_divides(splat<vT>(9) , splat<vT>(3) ), splat<vT>(3) );
}
