//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - toeplitz function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toeplitz.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

// NT2_TEST_CASE_TPL ( toeplitz, NT2_REAL_TYPES)
// {
//   nt2::table<T> t53 =
//     nt2::trans(nt2::reshape(nt2::cons(
//                                T(1), T(2),  T(3),
//                                T(2), T(1),  T(2),
//                                T(3), T(2),  T(1),
//                                T(4), T(3),  T(2),
//                                T(5), T(4),  T(3)
//                               ), nt2::of_size(3, 5)));
//   nt2::table<T> v =  nt2::toeplitz(nt2::_(T(1), T(5)), nt2::_(T(1), T(3)));
//   NT2_TEST_EQUAL(v, t53);
// }

// NT2_TEST_CASE_TPL ( toeplitzc2, NT2_REAL_TYPES)
// {
//   typedef std::complex<T> cT;
//   nt2::table<cT> v3 = nt2::cons(cT(1, 1), cT(2, 1), cT(3, 1));
//   nt2::table<cT> ct33 =  nt2::trans(nt2::reshape(nt2::cons(
//                                                   cT(1, 1),  cT(2, 1),  cT(3,1),
//                                                   cT(2,-1),  cT(1, 1),  cT(2,1),
//                                                   cT(3,-1),  cT(2,-1),  cT(1,1)
//                                                   ), nt2::of_size(3, 3)));

//   nt2::table<cT> v =  nt2::toeplitz(v3);
//   NT2_TEST_EQUAL(v, ct33);
// }

// NT2_TEST_CASE_TPL ( toeplitz2, NT2_REAL_TYPES)
// {
//   nt2::table<T> v =  nt2::toeplitz(nt2::_(T(1), T(3)));
//   nt2::table<T> t33 =
//     nt2::trans(nt2::reshape(nt2::cons(
//                               T(1),     T(2),     T(3),
//                               T(2),     T(1),     T(2),
//                               T(3),     T(2),     T(1)),
//                             nt2::of_size(3, 3)));
//   NT2_TEST_EQUAL(v, t33);
// }

NT2_TEST_CASE_TPL ( toeplitzexpr, NT2_REAL_TYPES)
{

  nt2::table<T> v1 = nt2::cons(T(1), T(1), T(1));
  nt2::table<T> v2 = nt2::cons(T(1), T(1), T(0));
  nt2::table<T> v =  nt2::toeplitz(v1, v2);
  T delta =  T(0);
  BOOST_AUTO_TPL( vv, nt2::toeplitz(v1, v2)+delta*nt2::ones(3, 3, nt2::meta::as_<T>()));
  NT2_DISPLAY(v);
  NT2_DISPLAY(vv);
  NT2_DISPLAY( nt2::toeplitz(v1, v2));
  NT2_TEST_EQUAL(v, nt2::toeplitz(v1, v2));
}

