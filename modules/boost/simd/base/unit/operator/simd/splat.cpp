//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/splat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( splat,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::splat;
  using boost::simd::tag::splat_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<splat_(T, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t value = splat<r_t>(42);

  for(size_t i=0;i<cardinal_of<r_t>::value;++i) NT2_TEST_EQUAL(value[i], T(42) );
}

NT2_TEST_CASE_TPL ( splat_id,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::splat;
  using boost::simd::tag::splat_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<splat_(vT, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t base = splat<r_t>(42);
  r_t value = splat<r_t>(base);

  for(size_t i=0;i<cardinal_of<r_t>::value;++i) NT2_TEST_EQUAL(value[i], base[i] );
}
