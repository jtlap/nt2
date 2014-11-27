//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/normstat.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( normstat, NT2_REAL_TYPES)
{
  using nt2::normstat;
  using nt2::tag::normstat_;
  using nt2::sqr;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<normstat_(T, T)>::type)
                  , (std::pair<T,T>)
                  );

  T mean;
  T var;
  T m = T(1.5);
  T s = T(2.5);
  {
    normstat(m, s, mean, var);
    NT2_TEST_EQUAL(var, sqr(s));
    NT2_TEST_EQUAL(mean, m);
  }

  {
    mean = normstat(m, s, var);
    NT2_TEST_EQUAL(var, sqr(s));
    NT2_TEST_EQUAL(mean, m);
  }

  {
    boost::fusion::vector_tie(mean,var) = normstat(m, s);
    NT2_TEST_EQUAL(var, sqr(s));
    NT2_TEST_EQUAL(mean, m);
  }

  {
    std::pair<T,T> p;

    p = normstat(m, s);
    NT2_TEST_EQUAL(p.first, m);
    NT2_TEST_EQUAL(p.second, sqr(s));
  }
}
