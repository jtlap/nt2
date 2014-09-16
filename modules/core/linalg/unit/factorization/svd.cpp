//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied svd function"

#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL(svd, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a0 = nt2::cons<T>(nt2::of_size(3,3),1.,1.,10.,1.,10.,1.,10.,1.,1.);
  t_t res = nt2::cons<T>(nt2::of_size(3,1),12.0,9.0,9.0);

  // X = SVD(A)
  t_t s = nt2::svd(a0);
  NT2_TEST_ULP_EQUAL(s, res,T(1) );

  // [U,S,V] = SVD(A)
  t_t s1;
  t_t u,u1;
  t_t vt,vt1;


  nt2::tie(u,s1,vt) = svd(a0);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

  // [U,S,V] = SVD(A,0)
  a0 = nt2::cons<T>(nt2::of_size(4,2),1.,2.,5.,7.,2.,4.,6.,8.);

  nt2::tie(u,s1,vt) = svd(a0,0);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

  // [U,S,V] = SVD(A,econ)
  a0 = nt2::cons<T>(nt2::of_size(2,4),1.,2.,5.,7.,2.,4.,6.,8.);

  nt2::tie(u,s1,vt) = svd(a0, nt2::econ_);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

}


NT2_TEST_CASE_TPL(svdc, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>         cT;
  typedef nt2::table<cT>          t_t;
  typedef nt2::table<T>          t_rt;

  t_t a0 = nt2::cons<cT>(nt2::of_size(3,3),cT(1,0),cT(1,0),cT(10,0),cT(1,0),cT(10,0)
                        ,cT(1,0),cT(10,0),cT(1,0),cT(1,0));
  t_t res = nt2::cons<cT>(nt2::of_size(3,1),cT(12,0),cT(9,0),cT(9,0));
  t_rt rres = nt2::cons<T>(nt2::of_size(3,1),12.0,9.0,9.0);
  t_rt s;
  // X = SVD(A)
  s = nt2::svd(a0);
  NT2_TEST_ULP_EQUAL(s, rres,T(1) );

  // [U,S,V] = SVD(A)
  t_rt s1;
  t_t u,u1;
  t_t vt,vt1;


  nt2::tie(u,s1,vt) = svd(a0);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

  // [U,S,V] = SVD(A,0)
  a0 = nt2::cons<cT>(nt2::of_size(4,2),cT(1,0),cT(2,0),cT(5,0),cT(7,0),cT(2,0),cT(4,0),cT(6,0),cT(8,0));

  nt2::tie(u,s1,vt) = svd(a0,0);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

  // [U,S,V] = SVD(A,econ)
  a0 = nt2::cons<cT>(nt2::of_size(2,4),cT(1,0),cT(2,0),cT(5,0),cT(7,0),cT(2,0),cT(4,0),cT(6,0),cT(8,0));

  nt2::tie(u,s1,vt) = svd(a0, nt2::econ_);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,s1),nt2::trans(vt)), a0,T(20));

}
