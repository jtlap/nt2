//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/fibonacci.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/core/container/table/table.hpp>

NT2_TEST_CASE_TPL ( fibonacci_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::fibonacci;
  using nt2::tag::fibonacci_;

  // specific values tests
  NT2_TEST_EQUAL(fibonacci(T(1),T(1), 10), T(55));
}

NT2_TEST_CASE_TPL ( fibonacci_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::fibonacci;
  using nt2::tag::fibonacci_;

  // specific values tests
  nt2::container::table<T> res =  nt2::cons<T>(nt2::of_size(1, 10), T(1),T(1),T(2),T(3),T(5),T(8),T(13),T(21),T(34),T(55));
  nt2::container::table<T> fib = fibonacci(T(1), T(1), nt2::_(T(1), T(10)));
  NT2_TEST_EQUAL(fib, res);
}
