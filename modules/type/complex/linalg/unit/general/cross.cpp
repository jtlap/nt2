//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cross"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of algebra components
//////////////////////////////////////////////////////////////////////////////

#include <nt2/table.hpp>
#include <nt2/include/functions/cross.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL( cross, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::cross;
  using nt2::tag::cross_;
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef typename nt2::table<cT> ct_t;
  ct_t a = nt2::_(T(1), T(3));
  ct_t b = a+T(3);
  ct_t r1 =  cons(nt2::of_size(1, 3), cT(-3), cT(6), cT(-3));
  NT2_TEST_EQUAL(nt2::cross(a, b), r1);
  NT2_TEST_EQUAL(nt2::cross(a, b, 2), r1);
  ct_t aa = reshape(nt2::_(T(1), T(24)), 4, 2, 3);
  ct_t bb = reshape(nt2::_(T(24),T(-1), T(1)), 4, 2, 3);
  ct_t r2(nt2::of_size( 4, 2, 3));
  r2(_, _, 1) = r2(_, _, 3) = cT(-200);
  r2(_, _, 2) = cT(400);
  NT2_TEST_EQUAL(nt2::cross(aa, bb), r2);
  NT2_TEST_EQUAL(nt2::cross(aa, bb, 3), r2);

}
NT2_TEST_CASE_TPL( cross_2, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::cross;
  using nt2::tag::cross_;
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef typename nt2::table<cT> ct_t;
  ct_t a = nt2::_(T(1), T(3));
  ct_t b = a+T(3)+nt2::I<cT>()*nt2::_(T(3), T(-1), T(1));
  ct_t r1 =  cons(nt2::of_size(1, 3), cT(-3, -4), cT(6, 8), cT(-3, -4));
  NT2_TEST_EQUAL(nt2::cross(a, b), r1);
  NT2_TEST_EQUAL(nt2::cross(a, b, 2), r1);
  ct_t aa = reshape(nt2::_(T(1), T(24)), 4, 2, 3);
  ct_t bb = reshape(nt2::_(T(24),T(-1), T(1)), 4, 2, 3)+nt2::I<cT>()*aa;
  ct_t r2(nt2::of_size( 4, 2, 3));
  r2(_, _, 1) = r2(_, _, 3) = cT(-200);
  r2(_, _, 2) = cT(400);
  NT2_TEST_EQUAL(nt2::cross(aa, bb), r2);
  NT2_TEST_EQUAL(nt2::cross(aa, bb, 3), r2);

}
NT2_TEST_CASE_TPL( cross_3, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::cross;
  using nt2::tag::cross_;
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef typename nt2::table<T> t_t;
  typedef typename nt2::table<cT> ct_t;
  t_t a = nt2::_(T(1), T(3));
  ct_t b = a+T(3)+nt2::I<cT>()*nt2::_(T(3), T(-1), T(1));
  ct_t r1 =  cons(nt2::of_size(1, 3), cT(-3, -4), cT(6, 8), cT(-3, -4));
  NT2_TEST_EQUAL(nt2::cross(a, b), r1);
  NT2_TEST_EQUAL(nt2::cross(a, b, 2), r1);
}
