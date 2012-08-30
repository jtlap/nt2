//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - remquo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <nt2/toolbox/arithmetic/include/functions/remquo.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/idivround.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <cmath>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( remquo_real__2_0,  (double))
{
  
  using nt2::remquo;
  using nt2::tag::remquo_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<remquo_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  iT n = 0;
  int32_t n1; 
  T r, r1;
  
  remquo(nt2::Nan<double>(), T(1), r, n);
  NT2_TEST_EQUAL(r, nt2::Nan<double>());
  NT2_TEST_EQUAL(n, 0);   
  remquo(T(1), nt2::Nan<double>(), r, n);
  NT2_TEST_EQUAL(r, nt2::Nan<double>());
  NT2_TEST_EQUAL(n, 0);   
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

}// end of test for double
  
NT2_TEST_CASE_TPL ( remquo_real__2_0f,  (float))
{
  
  using nt2::remquo;
  using nt2::tag::remquo_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<remquo_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  iT n = 0;
  int32_t n1; 
  T r, r1;
  
  remquo(nt2::Nan<float>(), T(1), r, n);
  NT2_TEST_EQUAL(r, nt2::Nan<float>());
  NT2_TEST_EQUAL(n, 0);   
  remquo(T(1), nt2::Nan<float>(), r, n);
  NT2_TEST_EQUAL(r, nt2::Nan<float>());
  NT2_TEST_EQUAL(n, 0);   
  
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

}// end
