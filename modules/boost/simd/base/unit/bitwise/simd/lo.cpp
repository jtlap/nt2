//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/lo.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/real_splat.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( return_type,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::tag::lo_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<lo_(vT)>::type
                  , (typename boost::dispatch::meta::as_integer<vT,unsigned>::type)
                  );
}

NT2_TEST_CASE_TPL ( real_lo,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::lo;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                       vT;
  typedef typename boost::dispatch::meta::as_integer<vT,unsigned>::type  viT;

  vT  val = boost::simd::real_constant<vT, 0xFFFFFFFF12345678LL, 0xFFFF1234>();
  vT  res = boost::simd::real_constant<vT, 0x0000000012345678LL, 0x00001234>();
  viT ref = boost::simd::bitwise_cast<viT>(res);

  NT2_TEST_EQUAL( lo(val), ref );
}

NT2_TEST_CASE_TPL( integer_lo, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  using boost::simd::lo;
  using boost::simd::splat;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename boost::dispatch::meta::as_integer<vT,unsigned>::type viT;

  vT  val = splat<vT>(~0);
  viT ref = splat<viT>( (T(1)<< (sizeof(T)*(CHAR_BIT/2))) - 1);

  NT2_TEST_EQUAL( lo(val), ref );
}
