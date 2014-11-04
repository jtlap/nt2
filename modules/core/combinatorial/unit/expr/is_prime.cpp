//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/is_prime.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
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
//  NT2_DISPLAY( is_prime(a)); // this is an error with clang
  // home/jt/DevC++/nt2_300a/build/clang++/unit/core.combinatorial.expr.is_prime.unit:0x59db02: runtime error:
  //  load of value 4294967294, which is not a valid value for type 'std::_Ios_Fmtflags'

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

