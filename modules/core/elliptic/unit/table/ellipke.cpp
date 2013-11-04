//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/elliptic/include/functions/scalar/ellipke.hpp>
#include <nt2/elliptic/include/functions/simd/ellipke.hpp>
#include <nt2/include/functions/ellipke.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(ellipke_table, NT2_REAL_TYPES)
{
  using nt2::ellipke;
  using nt2::table;
  typedef table<T> tab_t;
  static const size_t nb = 60;
  tab_t a = nt2::linspace(T(0), T(1), nb);
  tab_t  s(nt2::of_size(1, nb)), c(nt2::of_size(1, nb));
  {
    ellipke(a, nt2::Eps<T>(), s, c);
    for(size_t i =  1; i <= nb; ++i)
    {
      T s1, c1;
      boost::fusion::vector_tie(s1, c1) = nt2::ellipke(a(i));
      NT2_TEST_ULP_EQUAL(s(i), s1, 2);
      NT2_TEST_ULP_EQUAL(c(i), c1, 2);
    }
  }

  {
    s = ellipke(a, nt2::Eps<T>(), c);
    for(size_t i =  1; i <= nb; ++i)
    {
      T s1, c1;
      boost::fusion::vector_tie(s1, c1) = nt2::ellipke(a(i));
      NT2_TEST_ULP_EQUAL(s(i), s1, 2);
      NT2_TEST_ULP_EQUAL(c(i), c1, 2);
    }
  }

  {
    nt2::tie(s, c) = ellipke(a);
    for(size_t i =  1; i <= nb; ++i)
    {
      T s1, c1;
      boost::fusion::vector_tie(s1, c1) = nt2::ellipke(a(i));
      NT2_TEST_ULP_EQUAL(s(i), s1, 2);
      NT2_TEST_ULP_EQUAL(c(i), c1, 2);
    }
  }
}
