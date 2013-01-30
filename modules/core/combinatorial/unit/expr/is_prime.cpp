//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - is_prime/expr Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/toolbox/combinatorial/include/functions/is_prime.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( is_prime_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::is_prime;
  using nt2::tag::is_prime_;
  typedef typename nt2::meta::as_logical<T>::type bT;
  nt2::table<T> a = nt2::_(T(1), T(30));
  int aa[] = {false, true, true, false, true, false, true, false, false, false,
               true, false, true, false, false, false, true, false, true, false,
               false, false, true, false, false, false, false, false, true, false};
  nt2::table<bT> ba(nt2::of_size(1, 30));

  for(int i=0; i < 30; i++) ba(i+1) = nt2::is_nez(aa[i]);
  NT2_DISPLAY( is_prime(a));
  nt2::table<bT> p = is_prime(a);
  NT2_TEST_EQUAL(p, ba);

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

