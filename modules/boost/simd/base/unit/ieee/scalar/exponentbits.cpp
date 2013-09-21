//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/exponentbits.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>


NT2_TEST_CASE_TPL ( exponentbits_real,  (float))
{
  using boost::simd::exponentbits;
  using boost::simd::tag::exponentbits_;
  typedef typename boost::dispatch::meta::call<exponentbits_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  for(int i=1, k = 0; i < 10; i*= 2, ++k)
  {
    NT2_TEST_EQUAL(1065353216+k*8388608, exponentbits(T(i)));
  }
}

NT2_TEST_CASE_TPL ( exponentbits_reald,  (double))
{
  using boost::simd::exponentbits;
  using boost::simd::tag::exponentbits_;
  typedef typename boost::dispatch::meta::call<exponentbits_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  for(int i=1, k = 0; i < 10; i*= 2, ++k)
   {
     NT2_TEST_EQUAL(4607182418800017408ll+k*4503599627370496ll, exponentbits(T(i)));
   }
}
