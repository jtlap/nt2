//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_sincospi.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <boost/fusion/include/std_pair.hpp>


NT2_TEST_CASE_TPL ( fast_sincospi_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::fast_sincospi;
  using nt2::tag::fast_sincospi_;
  typedef typename nt2::meta::call<fast_sincospi_(T)>::type r_t;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-0.25), T(0.25));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::fast_sincospi(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = r.first;
        r_t1 r1 = r.second;
        NT2_TEST_ULP_EQUAL( r0, nt2::sin(nt2::Pi<T>()*a0), 0.5);
        NT2_TEST_ULP_EQUAL( r1, nt2::cos(nt2::Pi<T>()*a0), 0.5);
     }
   }
} // end of test for floating_
