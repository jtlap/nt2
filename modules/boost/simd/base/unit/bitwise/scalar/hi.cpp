//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/hi.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/real_splat.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( return_type,  BOOST_SIMD_TYPES)
{
  using boost::simd::tag::hi_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<hi_(T)>::type
                  , (typename boost::dispatch::meta::as_integer<T,unsigned>::type)
                  );
}

NT2_TEST_CASE_TPL ( real_hi,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::hi;

  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type  iT;

  T  val = boost::simd::real_constant<T, 0x12345678FFFFFFFFLL, 0x1234FFFF>();
  T  res = boost::simd::real_constant<T, 0x0000000012345678LL, 0x00001234>();
  iT ref = boost::simd::bitwise_cast<iT>(res);

  NT2_TEST_EQUAL( hi(val), ref );
}

NT2_TEST_CASE_TPL( integer_hi, BOOST_SIMD_INTEGRAL_TYPES )
{
  using boost::simd::hi;
  using boost::simd::splat;

  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type iT;

  T  val = splat<T>(~0);
  iT ref = splat<T>( (T(1)<< (sizeof(T)*(CHAR_BIT/2))) - 1);

  NT2_TEST_EQUAL( hi(val), ref );
}
