//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/splatted_prod.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( splatted_prod_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::splatted_prod;
  using boost::simd::tag::splatted_prod_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                                            ::call<splatted_prod_(vT)>::type
                  , vT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];
  T fact = 1;

  for(std::size_t i=0;i<n;++i) data[i] = i%2 ? T(i+1) : T(1)/(i+1);
  for(std::size_t i=0;i<n;++i) fact *= i%2 ? T(i+1) : T(1)/(i+1);

  vT vn = boost::simd::load<vT>(&data[0]);
  NT2_TEST_ULP_EQUAL(splatted_prod(vn), splat<vT>( fact ), 0.5 );
}

NT2_TEST_CASE_TPL ( splatted_prod_int, BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::splatted_prod;
  using boost::simd::tag::splatted_prod_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                                            ::call<splatted_prod_(vT)>::type
                  , vT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];
  T fact = 1;

  for(std::size_t i=0;i<n;++i) data[i] = T(i+1);
  for(std::size_t i=0;i<n;++i) fact *= T(i+1);

  vT vn = boost::simd::load<vT>(&data[0]);
  NT2_TEST_EQUAL(splatted_prod(vn), splat<vT>( fact ) );
}
