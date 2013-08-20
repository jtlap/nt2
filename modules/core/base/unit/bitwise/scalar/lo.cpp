//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/lo.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( return_type,  BOOST_SIMD_TYPES)
{
  using nt2::tag::lo_;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<lo_(T)>::type
                  , (typename nt2::meta::as_integer<T,unsigned>::type)
                  );
}

NT2_TEST_CASE_TPL ( real_lo,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::lo;

  typedef typename nt2::meta::as_integer<T,unsigned>::type  iT;

  T  val = nt2::real_constant<T, 0xFFFFFFFF12345678LL, 0xFFFF1234>();
  T  res = nt2::real_constant<T, 0x0000000012345678LL, 0x00001234>();
  iT ref = nt2::bitwise_cast<iT>(res);

  NT2_TEST_EQUAL( lo(val), ref );
}

NT2_TEST_CASE_TPL( integer_lo, BOOST_SIMD_INTEGRAL_TYPES )
{
  using nt2::lo;
  using nt2::splat;

  typedef typename nt2::meta::as_integer<T,unsigned>::type iT;

  T  val = splat<T>(~0);
  iT ref = splat<T>( (T(1)<< (sizeof(T)*(CHAR_BIT/2))) - 1);

  NT2_TEST_EQUAL( lo(val), ref );
}
