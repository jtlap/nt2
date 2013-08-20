//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/hi.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( return_type,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::tag::hi_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<hi_(vT)>::type
                  , (typename nt2::meta::as_integer<vT,unsigned>::type)
                  );
}

NT2_TEST_CASE_TPL ( real_hi,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::hi;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                       vT;
  typedef typename nt2::meta::as_integer<vT,unsigned>::type  viT;

  vT  val = nt2::real_constant<vT, 0x12345678FFFFFFFFLL, 0x1234FFFF>();
  vT  res = nt2::real_constant<vT, 0x0000000012345678LL, 0x00001234>();
  viT ref = nt2::bitwise_cast<viT>(res);

  NT2_TEST_EQUAL( hi(val), ref );
}

NT2_TEST_CASE_TPL( integer_hi, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  using nt2::hi;
  using nt2::splat;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename nt2::meta::as_integer<vT,unsigned>::type viT;

  vT  val = splat<vT>(~0);
  viT ref = splat<viT>( (T(1)<< (sizeof(T)*(CHAR_BIT/2))) - 1);

  NT2_TEST_EQUAL( hi(val), ref );
}
