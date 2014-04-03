//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/bsv.hpp>
#include <nt2/include/functions/gbcon.hpp>
#include <nt2/include/functions/langb.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(band, NT2_REAL_TYPES )
{
  using nt2::_;

// Matrice A is in lapack band storage format
  nt2::table<T, nt2::band_diagonal_<1,2> >  a =
  nt2::cons<T>(nt2::of_size(6,6)
                    ,T(0),T(0),T(666),T(1),T(27.5),T(0)
                    ,T(0),T(0),T(0),T(-50),T(27.5),T(0)
                    ,T(0),T(0),T(22.5),T(-50),T(27.5),T(0)
                    ,T(0),T(0),T(22.5),T(-50),T(27.5),T(-1)
                    ,T(0),T(0),T(22.5),T(-50),T(4),T(666)
                    ,T(0),T(0),T(22.5),T(-2.6),T(666),T(666)
                    );

  nt2::table<T> a1(a);

  nt2::table<T> b =   nt2::cons<T>(nt2::of_size(6,1)
                    ,T(1),T(1),T(1),T(1),T(1),T(0)
                    );


  nt2::table<T> x =   nt2::cons<T>(nt2::of_size(6,1)
                    ,T(1),T(1.0273467549118133757),T(1.1052150109151397395),T(1.2448317682525384953),T(1.4599189161093590883),T(1.7672476523788065439)
                    );

  char norm = 'I';
  nt2::table<nt2_la_int> piv;

  T anorm = nt2::langb(boost::proto::value(a),norm);
  nt2_la_int info = nt2::bsv( boost::proto::value(a),boost::proto::value(piv)
                            , boost::proto::value(b));

  T rnorm = nt2::gbcon(boost::proto::value(a),boost::proto::value(piv),anorm);

  NT2_TEST_EQUAL(info,T(0));
  NT2_TEST_ULP_EQUAL(b,x,T(20));
  NT2_TEST_ULP_EQUAL(rnorm,T(0.00013043604323150989),T(20));
}


NT2_TEST_CASE_TPL(bandc, NT2_REAL_TYPES )
{
  using nt2::_;
  typedef std::complex<T>  cT;
 // Matrice A is in lapack band storage format
  nt2::table<cT, nt2::band_diagonal_<1,2> >  a =
  nt2::cons<cT>(nt2::of_size(6,6)
                    ,cT(0,0),cT(0,0),cT(666 ,0),cT(1   ,0 ),cT(27.5,0),cT(0  ,0)
                    ,cT(0,0),cT(0,0),cT(0   ,0),cT(-50 ,0 ),cT(27.5,0),cT(0  ,0)
                    ,cT(0,0),cT(0,0),cT(22.5,0),cT(-50 ,0 ),cT(27.5,0),cT(0  ,0)
                    ,cT(0,0),cT(0,0),cT(22.5,0),cT(-50 ,0 ),cT(27.5,0),cT(-1 ,0)
                    ,cT(0,0),cT(0,0),cT(22.5,0),cT(-50 ,0 ),cT(4   ,0),cT(666,0)
                    ,cT(0,0),cT(0,0),cT(22.5,0),cT(-2.6,0 ),cT(666 ,0),cT(666,0)
                    );

  nt2::table<cT> a1(a);

  nt2::table<cT> b =   nt2::cons<cT>(nt2::of_size(6,1)
                    ,cT(1,0),cT(1,0),cT(1,0),cT(1,0),cT(1,0),cT(0,0)
                    );


  nt2::table<cT> x =   nt2::cons<cT>(nt2::of_size(6,1)
                    ,cT(1,0),cT(1.0273467549118133757,0),cT(1.1052150109151397395,0),cT(1.2448317682525384953,0)
                    ,cT(1.4599189161093590883,0),cT(1.7672476523788065439,0)
                    );

  char norm = 'I';
  nt2::table<nt2_la_int> piv;

  T anorm = nt2::langb(boost::proto::value(a),norm);
  nt2_la_int info = nt2::bsv( boost::proto::value(a),boost::proto::value(piv)
                            , boost::proto::value(b));

  T rnorm = nt2::gbcon(boost::proto::value(a),boost::proto::value(piv),anorm);

  NT2_TEST_EQUAL(info,T(0));
  NT2_TEST_ULP_EQUAL(b,x,T(20));
  NT2_TEST_ULP_EQUAL(rnorm,T(0.00013043604323150989),T(20));}


//original matrix
// [    1,     0,     0,     0,    0,    0]     [1]
// [27.50,   -50,  22.5,     0,    0,    0]     [1]
// [    0, 27.50,   -50,  22.5,    0,    0] x = [1]
// [    0,     0, 27.50,   -50, 22.5,    0]     [1]
// [    0,     0,     0, 27.50,  -50, 22.5]     [1]
// [    0,     0,     0,    -1,    4,-2.60]     [0]
