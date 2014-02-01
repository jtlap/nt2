//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_sincosd.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/cosd.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/pio_4.hpp>
#include <boost/fusion/include/std_pair.hpp>


NT2_TEST_CASE_TPL ( fast_sincosd,  NT2_REAL_TYPES)
{

  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;
  typedef typename nt2::meta::call<fast_sincosd_(T)>::type r_t;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-45), T(45));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::fast_sincosd(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_ULP_EQUAL( r0, nt2::sind(a0), 1.0);
        NT2_TEST_ULP_EQUAL( r1, nt2::cosd(a0), 1.0);
     }
   }
} // end of test for floating_
