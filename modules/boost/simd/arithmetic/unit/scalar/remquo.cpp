//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - remquo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/toolbox/arithmetic/include/functions/remquo.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/remainder.hpp>
#include <boost/simd/include/functions/idivround.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <cmath>
#include <nt2/include/constants/nan.hpp>

#include <boost/simd/sdk/math.hpp>

NT2_TEST_CASE_TPL ( remquo_real__2_0,  (double))
{
  using boost::simd::remquo;
  using boost::simd::tag::remquo_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<remquo_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename boost::dispatch::meta::as_integer<T,signed>::type> wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  iT n = 0;
  int32_t n1;
  T r, r1;

  remquo(boost::simd::Nan<double>(), T(1), r, n);
  NT2_TEST_EQUAL(r, boost::simd::Nan<double>());
  NT2_TEST_EQUAL(n, 0);
  remquo(T(1), boost::simd::Nan<double>(), r, n);
  NT2_TEST_EQUAL(r, boost::simd::Nan<double>());
  NT2_TEST_EQUAL(n, 0);

#ifdef BOOST_SIMD_HAS_REMQUO
  T a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  T b[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

  for(int i=0; i < 10; ++i)
  {
    for(int j=0; j < 9; ++j)
    {
      remquo(a[i], b[j], r, n);
      r1 = ::remquo(a[i], b[j], &n1);
      NT2_TEST_EQUAL(r, r1);
      NT2_TEST_EQUAL(n&3, n1&3);
    }
  }
#endif

}// end of test for double

NT2_TEST_CASE_TPL ( remquo_real__2_0f,  (float))
{
  using boost::simd::remquo;
  using boost::simd::tag::remquo_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<remquo_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename boost::dispatch::meta::as_integer<T,signed>::type> wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  iT n = 0;
  int32_t n1;
  T r, r1;

  remquo(boost::simd::Nan<float>(), T(1), r, n);
  NT2_TEST_EQUAL(r, boost::simd::Nan<float>());
  NT2_TEST_EQUAL(n, 0);
  remquo(T(1), boost::simd::Nan<float>(), r, n);
  NT2_TEST_EQUAL(r, boost::simd::Nan<float>());
  NT2_TEST_EQUAL(n, 0);

#ifdef BOOST_SIMD_HAS_REMQUO
  T a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  T b[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

  for(int i=0; i < 10; ++i)
  {
    for(int j=0; j < 9; ++j)
    {
      remquo(a[i], b[j], r, n);
      r1 = ::remquo(a[i], b[j], &n1);
      std::cout << "nt2 : a " << a[i] << " --- b " << b[j] << " --> quo = " << n << " rem = " << r << std::endl;
      std::cout << "C   : a " << a[i] << " --- b " << b[j] << " --> quo = " << n1<< " rem = " << r1<< std::endl;
      NT2_TEST_EQUAL(r, r1);
      NT2_TEST_EQUAL(n&3, n1&3);
    }
  }
#endif

}// end

