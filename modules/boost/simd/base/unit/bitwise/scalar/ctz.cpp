//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ctz.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/functions/clz.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

NT2_TEST_CASE_TPL( ctz_types, BOOST_SIMD_TYPES )
{
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  using boost::simd::Nbmantissabits;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ctz_(T)>::type
                  , (typename boost::dispatch::meta::as_integer<T,unsigned>::type)
                  );
}

NT2_TEST_CASE_TPL( ctz_real,  BOOST_SIMD_REAL_TYPES )
{
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  using boost::simd::Nbmantissabits;

  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;

  NT2_TEST_EQUAL(ctz(boost::simd::Inf<T>())     , r_t(Nbmantissabits<T>()));
  NT2_TEST_EQUAL(ctz(boost::simd::Minf<T>())    , r_t(Nbmantissabits<T>()));
  NT2_TEST_EQUAL(ctz(boost::simd::Nan<T>())     , r_t(0)                  );
  NT2_TEST_EQUAL(ctz(boost::simd::Signmask<T>()), r_t(sizeof(T)*CHAR_BIT-1)      );
}

NT2_TEST_CASE_TPL( ctz_signed_integer,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES )
{
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  using boost::simd::Signmask;

  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;

  for(std::size_t j=0; j< (sizeof(T)*CHAR_BIT-1); j++)
  {
    // Test 01111 ... 10000b
    T value = ~T(0) & ~((T(1)<<j)-1);
    NT2_TEST_EQUAL(ctz( value ), r_t(j));
    NT2_TEST_EQUAL(ctz( T(-value) ), r_t(j));
  }

  NT2_TEST_EQUAL(ctz(Signmask<T>()) , r_t(sizeof(T)*CHAR_BIT-1) );
}

NT2_TEST_CASE_TPL( ctz_unsigned_integer, BOOST_SIMD_UNSIGNED_TYPES )
{
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;

  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;

  for(std::size_t j=0; j< sizeof(T)*CHAR_BIT; j++)
  {
    // Test 1111 ... 10000b
    T value = ~T(0) & ~((T(1)<<j)-1);
    NT2_TEST_EQUAL(ctz( value ), r_t(j));
  }
 }
