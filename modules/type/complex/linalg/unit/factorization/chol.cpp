//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied chol function"

#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/pascal.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL(chol, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::lower_;
  using nt2::upper_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           ct_t;

  ct_t r,l;
  int info;
  nt2::table<cT,nt2::positive_definite_>
      a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);


  // R = CHOL(A)
  r = nt2::chol(a);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::ctrans(r),r), T(20) );

  // R = CHOL(A,upper_)
  r = nt2::chol(a,upper_);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::ctrans(r),r), T(20) );

  // R = CHOL(A,lower_)
  nt2::tie(l,info) = nt2::chol(a,lower_);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l,nt2::ctrans(l)), T(20) );

  // [R,P] = CHOL(A)
  nt2::tie(r,info) = nt2::chol(a);
  NT2_TEST_EQUAL(info,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::ctrans(r),r), T(20) );

  // [R,P] = CHOL(A,upper_)
  nt2::tie(r,info) = nt2::chol(a);
  NT2_TEST_EQUAL(info,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::ctrans(r),r), T(20) );

  // [R,P] = CHOL(A,lower_)
  nt2::tie(l,info) = nt2::chol(a,lower_);
  NT2_TEST_EQUAL(info,0);
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(l,nt2::ctrans(l)), T(20) );
}

NT2_TEST_CASE_TPL(cholnd, NT2_REAL_TYPES )
{
  // testing when matrix is positive but not definite
  using nt2::_;
  using nt2::lower_;
  using nt2::upper_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           ct_t;
  typedef nt2::table<T>            t_t;

  ct_t l;

  t_t ra = nt2::pascal(5, nt2::meta::as_<T>());
  ra(5, 5) = nt2::dec(ra(5, 5));
  ct_t a = ra;
  NT2_DISPLAY(a);
  int p;
  nt2::tie(l,p) = nt2::chol(a,lower_);
  NT2_TEST_EQUAL(p,5);
  NT2_DISPLAY(l);
  NT2_TEST_ULP_EQUAL(a(nt2::_(1, 4), nt2::_(1, 4)), nt2::mtimes(l(nt2::_(1, 4), nt2::_(1, 4)),nt2::trans(l(nt2::_(1, 4), nt2::_(1, 4)))), T(20) );

  ct_t r;
  nt2::tie(r,p) = nt2::chol(a,upper_);
  NT2_TEST_EQUAL(p,5);
  NT2_DISPLAY(l);
  NT2_TEST_ULP_EQUAL(a(nt2::_(1, 4), nt2::_(1, 4)), nt2::mtimes(nt2::trans(r(nt2::_(1, 4), nt2::_(1, 4))),r(nt2::_(1, 4), nt2::_(1, 4))), T(20) );
}

