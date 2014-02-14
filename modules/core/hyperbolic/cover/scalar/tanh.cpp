//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 hyperbolic toolbox - tanh/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of hyperbolic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 20/02/2011
///
#include <nt2/hyperbolic/include/functions/tanh.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/exponential/constants.hpp>
extern "C" { long double cephes_tanhl(long double); }

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

#include <nt2/constant/constant.hpp>
#include <cmath>


NT2_TEST_CASE_TPL ( tanh_real__1_0, NT2_REAL_TYPES)
{

  using nt2::tanh;
  using nt2::tag::tanh_;
  typedef typename nt2::meta::call<tanh_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-0.625), T(0.625));
    NT2_CREATE_BUF(tab_a1,T, NR, T( 0.625), T(10));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-10),    T(-0.625));
    T a0, a1, a2;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << "  a1 = "<< (a1 = tab_a1[j])
                  << "  a2 = "<< (a2 = tab_a2[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::tanh(a0),::cephes_tanhl(a0),1.0);
        NT2_TEST_ULP_EQUAL( nt2::tanh(a1),::cephes_tanhl(a1),1.0);
        NT2_TEST_ULP_EQUAL( nt2::tanh(a2),::cephes_tanhl(a2),1.0);
      }
   }
} // end of test for floating_


