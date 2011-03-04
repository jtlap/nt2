//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - split/scalar Mode"

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
#include <nt2/toolbox/swar/include/split.hpp>

NT2_TEST_CASE_TPL ( split_real__1,  NT2_REAL_TYPES)
{
  
  using nt2::split;
  using nt2::tag::split_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<split_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_EQUAL(split(nt2::Inf<T>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(split(nt2::Minf<T>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(split(nt2::Mone<T>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(split(nt2::Nan<T>()), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(split(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(split(nt2::Zero<T>()), nt2::Zero<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::split(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        r_t0 r0 = boost::fusion::get<0>(r);
        NT2_TEST_EQUAL( boost::fusion::get<0>(r), ();
     }
     
   }
} // end of test for real_
