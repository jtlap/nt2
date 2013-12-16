//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/fastnormcdf.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/normcdf.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/abs.hpp>


NT2_TEST_CASE_TPL ( fastnormcdf_real__1_0,  (float))
{

  using nt2::fastnormcdf;
  using nt2::tag::fastnormcdf_;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    T v = 0, v0 = 0;
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        v0 = nt2::abs(nt2::fastnormcdf(a0)-nt2::normcdf(a0));
        NT2_TEST_LESSER_EQUAL( v0, 2*nt2::Eps<T>());
        v=nt2::max(v, v0);
     }
     std::cout << "max error found is: " << v << std::endl;
   }
} // end of test for floating_

