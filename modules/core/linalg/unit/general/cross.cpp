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

NT2_TEST_CASE_TPL( cross, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::cross;
  using nt2::tag::cross_;
  typedef typename nt2::table<T> t_t;
  t_t a = nt2::_(T(1), T(3));
  t_t b = a+T(3);
  t_t r1 =  cons(nt2::of_size(1, 3), T(-3), T(6), T(-3));
  NT2_TEST_EQUAL(nt2::cross(a, b), r1);
  NT2_TEST_EQUAL(nt2::cross(a, b, 2), r1);
  t_t aa = reshape(nt2::_(T(1), T(24)), 4, 2, 3);
  t_t bb = reshape(nt2::_(T(24),T(-1), T(1)), 4, 2, 3);
  t_t r2(nt2::of_size( 4, 2, 3));
  r2(_, _, 1) = r2(_, _, 3) = T(-200);
  r2(_, _, 2) = T(400);
  NT2_TEST_EQUAL(nt2::cross(aa, bb), r2);
  NT2_TEST_EQUAL(nt2::cross(aa, bb, 3), r2);

}
