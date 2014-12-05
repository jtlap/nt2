//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/scal.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/plus.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(scal, NT2_REAL_TYPES )
{
  using nt2::scal;

  nt2::table<T> x = nt2::_(T(0), T(10));
  T alpha = T(2);
  nt2::table<T> x2 = x+x;
  scal(alpha, boost::proto::value(x), 1);
  NT2_TEST_ULP_EQUAL(x, x2, 0.5);

}

