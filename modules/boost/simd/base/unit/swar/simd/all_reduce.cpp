//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/all_reduce.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( all_reduce, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::all_reduce;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::plus_;
  using boost::simd::tag::logical_and_;
  using boost::simd::tag::all_reduce_;
  using boost::simd::native;
  using boost::simd::logical;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef native<logical<T>,ext_t>      vlT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                                            ::call<all_reduce_(vT,as_<plus_>)>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                                            ::call<all_reduce_(vT,as_<logical_and_>)>::type
                  , vlT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];

  for(std::size_t i=0;i<n;++i) data[i] = T(i+1);

  vT vn = boost::simd::load<vT>(&data[0]);
  NT2_TEST_EQUAL(all_reduce<plus_>(vn), splat<vT>( n*(n+1)/2 ) );

  vn[0] = T(0);
  NT2_TEST_EQUAL(all_reduce<logical_and_>(vn), splat<vlT>( false ) );
}
