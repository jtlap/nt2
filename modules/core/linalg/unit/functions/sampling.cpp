//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - sampling function"

#include <nt2/table.hpp>
#include <nt2/include/functions/sampling.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( sampling, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> m3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(7),    T(-2),    T(-1),
                                         T(4),    T( 4),    T(-4),
                                         T(3),    T( 6),    T(-5)
                                        )/T(2));

  nt2::table<T> z = nt2::sampling(nt2::_(T(1), T(3)));
  NT2_TEST_ULP_EQUAL(z, m3, 0.5);
  NT2_TEST_ULP_EQUAL(nt2::sampling<T>(3), m3, 0.5);
  NT2_TEST_ULP_EQUAL(nt2::cast<T>(nt2::sampling(3)), m3, 0.5);
}




