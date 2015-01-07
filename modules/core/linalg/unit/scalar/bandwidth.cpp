//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/bandwidth.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/band.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(bandwidth1, NT2_REAL_TYPES)
{
  using nt2::bandwidth;
  using nt2::tag::bandwidth_;
  nt2::table<T> n = nt2::eye(6, 10, nt2::meta::as_<T>());
  int l, u;
  l =  bandwidth(n, nt2::lower_);

  boost::fusion::vector_tie(l, u) = bandwidth(n);
  NT2_TEST_ULP_EQUAL(l, 0, 0);
  NT2_TEST_ULP_EQUAL(u, 0, 0);
  n = nt2::ones(6, 10, nt2::meta::as_<T>());
  boost::fusion::vector_tie(l, u) = bandwidth(n);
  NT2_TEST_ULP_EQUAL(l, nt2::height(n)-1, 0);
  NT2_TEST_ULP_EQUAL(u, nt2::width(n)-1, 0);
  nt2::table<T> m =  band(n, -3, 4);
  boost::fusion::vector_tie(l, u) = bandwidth(m);
  NT2_TEST_ULP_EQUAL(l, 3, 0);
  NT2_TEST_ULP_EQUAL(u, 4, 0);
 }

