//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/is_prime.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/seven.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/core/container/table/table.hpp>

NT2_TEST_CASE_TPL ( is_prime_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::is_prime;
  using nt2::tag::is_prime_;

  // specific values tests
  NT2_TEST(!is_prime(nt2::Eight<T>()));
  NT2_TEST(is_prime(nt2::Seven<T>()));
  NT2_TEST(is_prime(nt2::Two<T>()));
  NT2_TEST(!is_prime(nt2::One<T>()));
  NT2_TEST_ASSERT(is_prime(nt2::Mone<T>()));
}

NT2_TEST_CASE_TPL ( is_prime_integer__1_0,  NT2_INTEGRAL_TYPES)
{
  using nt2::is_prime;
  using nt2::tag::is_prime_;

  // specific values tests
  NT2_TEST(!is_prime(nt2::Eight<T>()));
  NT2_TEST(is_prime(nt2::Seven<T>()));
  NT2_TEST(is_prime(nt2::Two<T>()));
  NT2_TEST(!is_prime(nt2::One<T>()));
}

NT2_TEST_CASE_TPL ( is_prime_integer__2_0,  NT2_INTEGRAL_TYPES)
{
  using nt2::is_prime;
  using nt2::tag::is_prime_;

  // specific values tests
  nt2::container::table<T> p =  nt2::primes(T(8));
  NT2_TEST(!is_prime(nt2::Eight<T>(), p));
  NT2_TEST(is_prime(nt2::Seven<T>(), p));
  NT2_TEST(is_prime(nt2::Two<T>(), p));
  NT2_TEST(!is_prime(nt2::One<T>(), p));
}

NT2_TEST_CASE_TPL ( is_prime_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::is_prime;
  using nt2::tag::is_prime_;

  // specific values tests
  nt2::container::table<uint32_t> p =  nt2::primes(uint32_t(8));
  NT2_TEST(!is_prime(nt2::Eight<T>(), p));
  NT2_TEST(is_prime(nt2::Seven<T>(), p));
  NT2_TEST(is_prime(nt2::Two<T>(), p));
  NT2_TEST(!is_prime(nt2::One<T>(), p));
  NT2_TEST_ASSERT(is_prime(nt2::Mone<T>()));
}
