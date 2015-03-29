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
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/signm.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/colon.hpp>

NT2_TEST_CASE_TPL(signm0, NT2_REAL_TYPES)
{
  NT2_TEST_EQUAL(nt2::sign(T(3)), nt2::signm(T(3)));
 }

NT2_TEST_CASE_TPL(signm1, NT2_REAL_TYPES)
{
  using nt2::signm;
  using nt2::tag::signm_;
  typedef std::complex<T> cT;
  nt2::table<cT> n =  nt2::from_diag(T(2)*nt2::_((1),T(3)));
  nt2::table<cT> signmn = nt2::signm(n);
  nt2::table<cT> el =  nt2::from_diag(nt2::sign(nt2::diag_of(n)));
  NT2_TEST_ULP_EQUAL(el, signmn, 0.5);
 }


NT2_TEST_CASE_TPL ( signm2, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  typedef std::complex<T> cT;
  nt2::table<cT> n =  nt2::cons<T>(nt2::of_size(4, 4),
                                   0.76781,    0.76816,    0.31533,    0.02304,
                                   0.00000,    0.64811,    0.10059,    0.93646,
                                   0.00000,    0.00000,   -0.31738,    0.30999,
                                   0.00000,    0.00000,    0.00000,   -0.10539);
  nt2::table<cT> u =  nt2::cons<T>(nt2::of_size(4, 4),
                                   -0.442299, -0.313246 ,-0.839601,-0.0363337,
                                   -0.527294,  0.817116 ,-0.017025,-0.232361 ,
                                   -0.5181,   -0.475381 , 0.473258,-0.530671 ,
                                   -0.507843, -0.0906132, 0.266098, 0.814295 );
  n = mtimes(u, mtimes(n, ctrans(u)));
   nt2::table<cT> s, nn;
   nt2::tie(s, nn) = nt2::signm(n);
   nt2::tie(s, nn) = nt2::signm(n, 10*nt2::Eps<T>());
//    NT2_DISPLAY(s);
//    NT2_DISPLAY(nn);
//    NT2_DISPLAY(globalmax(nt2::abs(mtimes(nn, s)-n)));
   NT2_TEST_LESSER(globalmax(nt2::abs(mtimes(nn, s)-n)), height(n)*nt2::Ten<T>()*nt2::Eps<T>());


}

NT2_TEST_CASE_TPL ( signm2r, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  typedef std::complex<T> cT;
  nt2::table<T> n =  nt2::cons<T>(nt2::of_size(4, 4),
                                   0.76781,    0.76816,    0.31533,    0.02304,
                                   0.00000,    0.64811,    0.10059,    0.93646,
                                   0.00000,    0.00000,   -0.31738,    0.30999,
                                   0.00000,    0.00000,    0.00000,   -0.10539);
  nt2::table<T> u =  nt2::cons<T>(nt2::of_size(4, 4),
                                   -0.442299, -0.313246 ,-0.839601,-0.0363337,
                                   -0.527294,  0.817116 ,-0.017025,-0.232361 ,
                                   -0.5181,   -0.475381 , 0.473258,-0.530671 ,
                                   -0.507843, -0.0906132, 0.266098, 0.814295);
  n = mtimes(u, mtimes(n, ctrans(u)));
  nt2::table<T> s, nn;
  nt2::tie(s, nn) = nt2::signm(n);
  nt2::tie(s, nn) = nt2::signm(n, 10*nt2::Eps<T>());
//   NT2_DISPLAY(s);
//   NT2_DISPLAY(nn);
//   NT2_DISPLAY(globalmax(nt2::abs(mtimes(nn, s)-n)));
  NT2_TEST_LESSER(globalmax(nt2::abs(mtimes(nn, s)-n)), height(n)*nt2::Ten<T>()*nt2::Eps<T>());


}

