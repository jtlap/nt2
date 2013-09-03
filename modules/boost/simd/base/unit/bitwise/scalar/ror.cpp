//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ror.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( ror_i,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::ror;
  using boost::simd::tag::ror_;
  typedef typename boost::dispatch::meta::call<ror_(T,int32_t)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(ror(boost::simd::Mone<T>(),T(1)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Mone<T>(),T(5)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Two<T>(),-1),  boost::simd::One<T>());
  NT2_TEST_EQUAL(ror(boost::simd::Two<T>(),1), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Four<T>(),1), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Four<T>(),-1), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Four<T>(), 2), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Four<T>(),-2), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( ror_integer, BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(T,int)>::type
                  , T
                  );

  int w = sizeof(T)*CHAR_BIT;

  for(int i=0;i<w;++i)
  {
    NT2_TEST_EQUAL(ror(T(1),i), T(T(1)<<((w-i) & (w-1))));
    NT2_TEST_EQUAL(ror(T(1),-i), T(T(1)<<((w-i) & (w-1))));
  }

}

NT2_TEST_CASE_TPL ( ror_real, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;
  using boost::simd::bitwise_cast;

  typedef typename boost::dispatch::meta::as_integer<T>::type iT;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(T,iT)>::type
                  , T
                  );

  int w = sizeof(T)*CHAR_BIT;

  for(int i=0;i<w;++i)
  {
    NT2_TEST_EQUAL( ror(bitwise_cast<T>(iT(1)),i)
                  , bitwise_cast<T>(iT(1)<<((w-i) & (w-1)))
                  );
    NT2_TEST_EQUAL( ror(bitwise_cast<T>(iT(1)),-i)
                  , bitwise_cast<T>(iT(1)<<((w-i) & (w-1)))
                  );
  }
}
