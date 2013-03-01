//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - is_prime/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/toolbox/combinatorial/include/functions/is_prime.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>



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
} // end of test for floating_

NT2_TEST_CASE_TPL ( is_prime_integer__1_0,  NT2_INTEGRAL_TYPES)
{

  using nt2::is_prime;
  using nt2::tag::is_prime_;
  NT2_TEST(!is_prime(nt2::Eight<T>()));
  NT2_TEST(is_prime(nt2::Seven<T>()));
  NT2_TEST(is_prime(nt2::Two<T>()));
  NT2_TEST(!is_prime(nt2::One<T>()));
 } // end of test for integer_

NT2_TEST_CASE_TPL ( is_prime_integer__2_0,  NT2_INTEGRAL_TYPES)
{

  using nt2::is_prime;
  using nt2::tag::is_prime_;
  nt2::table<T> p =  nt2::primes(T(8));
  NT2_TEST(!is_prime(nt2::Eight<T>(), p));
  NT2_TEST(is_prime(nt2::Seven<T>(), p));
  NT2_TEST(is_prime(nt2::Two<T>(), p));
  NT2_TEST(!is_prime(nt2::One<T>(), p));
 } // end of test for integer_

NT2_TEST_CASE_TPL ( is_prime_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::is_prime;
  using nt2::tag::is_prime_;
  nt2::table<uint32_t> p =  nt2::primes(uint32_t(8));
  NT2_TEST(!is_prime(nt2::Eight<T>(), p));
  NT2_TEST(is_prime(nt2::Seven<T>(), p));
  NT2_TEST(is_prime(nt2::Two<T>(), p));
  NT2_TEST(!is_prime(nt2::One<T>(), p));
  NT2_TEST_ASSERT(is_prime(nt2::Mone<T>()));
} // end of test for integer_
