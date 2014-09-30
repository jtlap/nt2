//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/linalg/details/utility/llspgen.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/cond.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/table.hpp>

#include <iostream>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(llspgen, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  t_t a,x,r,b;

  size_t m=20, n=10, nr=1, q=1;

  nt2::tie(a,x,r,b) = nt2::llspgen(m,n,q,nr, nt2::meta::as_<T>());

  t_t s = nt2::svd(a);

  NT2_TEST_ULP_EQUAL(s(1)/s(n), nt2::pow((T)n,(T)q), T(10));
}
