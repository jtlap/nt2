//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/sqrt_2.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL(svd_scalar_complex, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  typedef nt2::table<T>           t_t;
  cT a0 =  cT(nt2::One<T>(),nt2::One<T>());
  t_t s = nt2::svd(a0);
  NT2_TEST_ULP_EQUAL(s, nt2::Sqrt_2<T>(),1 );
  s =  nt2::svd(a0, nt2::econ_);
  NT2_TEST_ULP_EQUAL(s, nt2::Sqrt_2<T>(),1 );
}

NT2_TEST_CASE_TPL(svd_complex, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>         cT;
  typedef nt2::table<cT>          t_t;
  typedef nt2::table<T>          t_rt;
  typedef nt2::table<nt2_la_int>  t_i;

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
