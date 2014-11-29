//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/evstat.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/include/constants/euler.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( evstat, NT2_REAL_TYPES)
{
  using nt2::evstat;
  using nt2::tag::evstat_;
  using nt2::sqr;

  T rmean = T(5.696083774616789e-02);
  T rvar = T(1.028083791780141e+01);
  std::cout << nt2::Euler<T>() << std::endl;
  std::cout << nt2::Euler<T>()-T(5.772156649015323e-01)<< std::endl;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<evstat_(T, T)>::type)
                  , (std::pair<T,T>)
                  );

  T mean;
  T var;
  T m = T(1.5);
  T s = T(2.5);
  {
    evstat(m, s, mean, var);
    NT2_TEST_ULP_EQUAL(var, rvar, 2);
    NT2_TEST_ULP_EQUAL(mean, rmean, 2);
  }

  {
    mean = evstat(m, s, var);
    NT2_TEST_ULP_EQUAL(var, rvar, 2);
    NT2_TEST_ULP_EQUAL(mean, rmean, 2);
  }

  {
    boost::fusion::vector_tie(mean,var) = evstat(m, s);
    NT2_TEST_ULP_EQUAL(var, rvar, 2);
    NT2_TEST_ULP_EQUAL(mean, rmean, 2);
  }

  {
    std::pair<T,T> p;

    p = evstat(m, s);
    NT2_TEST_ULP_EQUAL(p.first, rmean, 2);
    NT2_TEST_ULP_EQUAL(p.second, rvar, 2);
  }
}
