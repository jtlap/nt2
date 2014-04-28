//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/factor.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/two.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>
#include <nt2/include/constants/maxflint.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL ( factor_integer__1_0, NT2_INTEGRAL_TYPES)
{

  using nt2::factor;
  using nt2::tag::factor_;

  T p[] = {3, 5};
  nt2::table<T> myp = factor(T(15));
  // specific values tests

  for(size_t i=1; i <= nt2::length(myp); ++i)
    {
      NT2_TEST_EQUAL(p[i-1], myp(i));
    }
  myp = factor(T(15*3*2));
  // specific values tests
  T p1[] = {2, 3, 3, 5};
  NT2_DISPLAY(myp);

  for(size_t i=1; i <= nt2::length(myp); ++i)
    {
      std::cout << i << std::endl;
      NT2_TEST_EQUAL(p1[i-1], myp(i));
    }

}

NT2_TEST_CASE_TPL ( factor_integer__2_0, (int8_t))
{
  using nt2::factor;
  using nt2::tag::factor_;

 NT2_TEST_ASSERT(factor(T(15*3*2*2)));

}

NT2_TEST_CASE_TPL ( factor_real, NT2_REAL_TYPES)
{
  using nt2::factor;
  using nt2::tag::factor_;
  nt2::table<T> myp = nt2::cons(T(2), T(2), T(3), T(3), T(5));
  NT2_TEST_EQUAL(factor(T(15*3*2*2)), myp);
  NT2_TEST_EQUAL(factor(nt2::Maxflint<T>()), nt2::two(1, nt2::Nbmantissabits<T>()+1, boost::dispatch::meta::as_<T>()));
}
