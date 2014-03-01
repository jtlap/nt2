//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/prod.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( prod_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::prod;
  using boost::simd::tag::prod_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<prod_(vT)>::type
                  , T
                  );

  static const std::size_t n = vT::static_size;
  T data[n];
  T fact = 1;

  for(std::size_t i=0;i<n;++i) data[i] = i%2 ? T(i+1) : T(1)/(i+1);
  for(std::size_t i=0;i<n;++i) fact *= i%2 ? T(i+1) : T(1)/(i+1);

  vT vn = boost::simd::load<vT>(&data[0]);
  NT2_TEST_EQUAL(prod(vn), T( fact ) );
}

NT2_TEST_CASE_TPL ( prod_int, BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::prod;
  using boost::simd::tag::prod_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<prod_(vT)>::type
                  , T
                  );

  static const std::size_t n = vT::static_size;
  T data[n];
  T fact = 1;

  for(std::size_t i=0;i<n;++i) data[i] = i+1;
  for(std::size_t i=0;i<n;++i) fact *= (i+1);

  vT vn = boost::simd::load<vT>(&data[0]);
  NT2_TEST_EQUAL(prod(vn), T( fact ) );
}
