//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - comparator/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of swar components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// modified by jt the 04/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/no_ulp_tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/swar/include/comparator.hpp>
#include <boost/fusion/tuple.hpp>

NT2_TEST_CASE_TPL ( comparator_real__3,  NT2_REAL_TYPES)
{
  
  using nt2::comparator;
  using nt2::tag::comparator_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<comparator_(T,T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,T,bool> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,2>::type>::type r_t2;
  {
    r_t res = comparator(nt2::Inf<T>(), nt2::Inf<T>(), nt2::Inf<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Inf<r_t1>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Minf<T>(), nt2::Minf<T>(), nt2::Minf<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Minf<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Mone<T>(), nt2::Mone<T>(), nt2::Mone<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Mone<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::One<T>(), nt2::One<T>(), nt2::One<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  {
    r_t res = comparator(nt2::Zero<T>(), nt2::Zero<T>(), nt2::Zero<T>());
    NT2_TEST_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<1>(res), nt2::Zero<r_t0>());
    NT2_TEST_EQUAL( boost::fusion::get<2>(res), 0);
  }
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-100), T(100));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-100), T(100));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    T a1;
    T a2;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << ", a2 = "<< u_t(a2 = tab_a2[j])
                  << std::endl;
        r_t r = nt2::comparator(a0,a1,a2);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,2>::type>::type r_t2;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        r_t2 r2 = boost::fusion::get<2>(r);
        NT2_TEST_EQUAL( boost::fusion::get<0>(r), nt2::min(a0,a1));
        NT2_TEST_EQUAL( boost::fusion::get<1>(r), nt2::max(a0,a1));
        NT2_TEST_EQUAL( boost::fusion::get<2>(r), a0>a1);
     }
     
   }
} // end of test for real_
