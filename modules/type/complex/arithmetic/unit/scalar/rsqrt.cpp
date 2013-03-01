//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - rsqrt/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
///
#include <nt2/toolbox/arithmetic/include/functions/rsqrt.hpp>
#include <nt2/toolbox/arithmetic/include/functions/sqr.hpp>
#include <nt2/toolbox/arithmetic/include/functions/rec.hpp>
#include <nt2/include/constants/i.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rsqrt_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::rsqrt;
  using nt2::tag::rsqrt_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<rsqrt_(cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef cT wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
 ulpd=0.0;

  // std::cout << nt2::type_id(nt2::I<T>()) << std::endl;
  // specific values tests
   NT2_TEST_EQUAL(rsqrt(cT(1)), T(1));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::Inf<T>())), cT(nt2::Zero<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::Minf<T>())), cT(0, nt2::Zero<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::Mone<T>())), cT(0, nt2::Mone<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::Nan<T>())), cT(nt2::Nan<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::One<T>())), cT(nt2::One<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
   std::complex < T > a(1, 0);
   NT2_TEST_EQUAL(rsqrt(a), nt2::One<T>());
   std::complex < T > b(0, 1);
   NT2_TEST_EQUAL(rsqrt(b), cT(nt2::Sqrt_2o_2<T>(),nt2::Sqrt_2o_2<T>()));

  for(T i=-5; i <=  T(5) ; i+= T(0.5))
    {
      for(T j =-5; j < T(5); j+= T(0.5))
        {
          NT2_TEST_ULP_EQUAL(nt2::rec(nt2::sqr(nt2::rsqrt(cT(i, j)))), cT(i, j), 10);

} // end of test for floating_

