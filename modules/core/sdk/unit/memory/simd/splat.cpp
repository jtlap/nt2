//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/memory/include/functions/splat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/include/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( splat,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::splat;
  using nt2::tag::splat_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<splat_(T, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t value = splat<r_t>(42);
  r_t ref;

  for(size_t i=0;i<cardinal_of<r_t>::value;++i) ref[i] = T(42);
  NT2_TEST_EQUAL(value, ref );
}

NT2_TEST_CASE_TPL ( splat_id,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::splat;
  using nt2::tag::splat_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<splat_(vT, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t base = splat<r_t>(42);
  r_t value = splat<r_t>(base);

  NT2_TEST_EQUAL(value, base);
}

NT2_TEST_CASE_TPL ( far_too_big_splat,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::splat;
  using nt2::tag::splat_;
  using boost::simd::meta::vector_of;
  using boost::simd::meta::cardinal_of;

  typedef typename vector_of<T,BOOST_SIMD_BYTES*4>::type                        vT;
  typedef typename boost::dispatch::meta::call<splat_(T, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t ref, value = splat<r_t>(42);

  for(size_t i=0;i<cardinal_of<r_t>::value;++i) ref[i] = T(42);

  NT2_TEST_EQUAL(value, ref );
}

NT2_TEST_CASE_TPL ( bool_test,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::splat;
  using nt2::tag::splat_;
  using boost::simd::meta::cardinal_of;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef native<lT,ext_t>               vT;
  typedef typename boost::dispatch::meta::call<splat_(lT, boost::dispatch::meta::as_<vT>)>::type r_t;

  r_t ref, value = splat<r_t>(1);

  for(size_t i=0;i<cardinal_of<r_t>::value;++i) ref[i] = lT(1);

  NT2_TEST_EQUAL(value, ref);
}

