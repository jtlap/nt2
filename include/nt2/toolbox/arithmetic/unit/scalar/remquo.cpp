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
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/arithmetic/include/remquo.hpp>
// specific includes for arity 2 tests
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/idivfix.hpp>
#include <nt2/include/functions/idivfloor.hpp>
#include <nt2/include/functions/idivround.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp> 

NT2_TEST_CASE_TPL ( remquo_real__2,  NT2_REAL_TYPES)
{
  using nt2::remquo;
  using nt2::tag::remquo_;
  typedef typename nt2::meta::call<remquo_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    NT2_CREATE_BUFFER(a1,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        r_t r = nt2::remquo(a0,a1);
        typename boost::fusion::result_of::at_c<r_t,0>::type r0 = boost::fusion::get<0>(r);
        typename boost::fusion::result_of::at_c<r_t,1>::type r1 = boost::fusion::get<1>(r);
	NT2_TEST_TUPLE_ULP_EQUAL( r0,nt2::remainder(a0,a1),0);
	//I do not really understand what quo is !?
     }
   }
} // end of test for real_
