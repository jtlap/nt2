//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/lognstat.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( lognstat, NT2_REAL_TYPES)
{
  using nt2::lognstat;
  using nt2::tag::lognstat_;
  using nt2::sqr;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<lognstat_(T, T)>::type)
                  , (std::pair<T,T>)
                  );

  T mean;
  T var;
  T m = T(1.5);
  T s = T(2.5);
  T rm = T(1.020027730826997e+02);
  T rs = T(5.379293910566451e+06);
 {
    lognstat(m, s, mean, var);
    NT2_TEST_ULP_EQUAL(var, rs, 0.5);
    NT2_TEST_ULP_EQUAL(mean, rm, 0.5);
  }

  {
    mean = lognstat(m, s, var);
    NT2_TEST_ULP_EQUAL(var, rs, 0.5);
    NT2_TEST_ULP_EQUAL(mean, rm, 0.5);
  }

  {
    boost::fusion::vector_tie(mean,var) = lognstat(m, s);
    NT2_TEST_ULP_EQUAL(var, rs, 0.5);
    NT2_TEST_ULP_EQUAL(mean, rm, 0.5);
  }

  {
    std::pair<T,T> p;

    p = lognstat(m, s);
    NT2_TEST_ULP_EQUAL(p.first, rm, 0.5);
    NT2_TEST_ULP_EQUAL(p.second, rs, 0.5);
  }
}
