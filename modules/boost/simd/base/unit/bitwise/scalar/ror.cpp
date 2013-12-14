//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/scalar/ror.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( ror_integer, BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(T,T)>::type
                  , T
                  );

  T w = sizeof(T)*CHAR_BIT;

  for(T i=0;i<w;++i)
  {
    NT2_TEST_EQUAL(ror(T(1),i), T(T(1)<<((w-i) & (w-1))));
  }

  NT2_TEST_ASSERT(ror(T(1),T(-1)));
  NT2_TEST_ASSERT(ror(T(1),T(w+1)));
}

NT2_TEST_CASE_TPL ( ror_real, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;
  using boost::simd::bitwise_cast;

  typedef typename boost::dispatch::meta::as_integer<T>::type iT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(T,iT)>::type
                  , T
                  );

  iT w = sizeof(T)*CHAR_BIT;

  for(iT i=0;i<w;++i)
    NT2_TEST_EQUAL( ror(bitwise_cast<T>(iT(1)),i)
                  , bitwise_cast<T>(iT(1)<<((w-i) & (w-1)))
                  );

  NT2_TEST_ASSERT(ror(T(1),iT(-1)));
  NT2_TEST_ASSERT(ror(T(1),iT(w+1)));
}
