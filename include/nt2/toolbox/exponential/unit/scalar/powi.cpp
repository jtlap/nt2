//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - powi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
/// modified by jt the 08/12/2010
/// modified by jt the 14/12/2010
=======
/// created by jt the 08/12/2010
/// modified by jt the 22/01/2011
>>>>>>> functor2
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/exponential/include/powi.hpp>

NT2_TEST_CASE_TPL ( powi_real__2,  NT2_REAL_TYPES)
{
  using nt2::powi;
<<<<<<< HEAD
  using nt2::functors::powi_;
=======
  using nt2::tag::powi_;
>>>>>>> functor2
  typedef int32_t iT;
  typedef typename nt2::meta::call<powi_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
<<<<<<< HEAD
=======
  double ulpd;
>>>>>>> functor2


  // specific values tests
  NT2_TEST_ULP_EQUAL(  powi(nt2::Inf<T>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  powi(nt2::Minf<T>(),3), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  powi(nt2::Mone<T>(),3), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  powi(nt2::Nan<T>(),3), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  powi(nt2::One<T>(),3), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  powi(nt2::Zero<T>(),3), nt2::Zero<r_t>(), 0);
  // random verifications
  static const uint32_t NR = 100;
  {
    typedef int32_t iT;
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    NT2_CREATE_BUFFER(a1,iT, 100, T(-10), T(10));
<<<<<<< HEAD
=======
    double ulp0 = 0.0;
>>>>>>> functor2
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::powi(a0,nt2::Two<iT>()),nt2::sqr(a0),1);
<<<<<<< HEAD
        NT2_TEST_ULP_EQUAL( nt2::powi(a0,nt2::Three<iT>()),a0*nt2::sqr(a0),1);
     }
=======
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::powi(a0,nt2::Three<iT>()),a0*nt2::sqr(a0),1);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
>>>>>>> functor2
   }
} // end of test for real_