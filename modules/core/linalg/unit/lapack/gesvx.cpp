//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gesvx.hpp>
#include <nt2/include/functions/gelsy.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(svx, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;
nt2::table<nt2_la_int>  piv = nt2::zeros( nt2::of_size(3,1)
                                        , nt2::meta::as_<nt2_la_int>());
T rcond;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t a1(a);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x(nt2::of_size(3,1));



nt2_la_int p = nt2::gesvx(boost::proto::value(a),boost::proto::value(b)
                        ,boost::proto::value(x),rcond);
nt2_la_int p1 = nt2::gelsy(boost::proto::value(a1),boost::proto::value(piv)
                        ,boost::proto::value(b));

NT2_TEST_ULP_EQUAL(x,b,T(10));
NT2_TEST_EQUAL(T(p),T(0));
NT2_TEST_EQUAL(T(p1),T(0));

}


NT2_TEST_CASE_TPL(svxc, NT2_REAL_TYPES )
{
using nt2::_;

typedef std::complex<T> cT;
typedef nt2::table<cT>           t_t;
nt2::table<nt2_la_int>  piv = nt2::zeros( nt2::of_size(3,1)
                                        , nt2::meta::as_<nt2_la_int>());
T rcond;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,2),cT(1,1),cT(1,1)
                    ,cT(1,1),cT(2,2),cT(2,2)
                    ,cT(2,2),cT(5,5),cT(7,7)
                    );
t_t a1(a);
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,1),cT(2,2),cT(5,5));
t_t x(nt2::of_size(3,1));

nt2_la_int p = nt2::gesvx(boost::proto::value(a),boost::proto::value(b)
                        ,boost::proto::value(x),rcond);

nt2_la_int p1 = nt2::gelsy(boost::proto::value(a1),boost::proto::value(piv)
                        ,boost::proto::value(b));

NT2_TEST_ULP_EQUAL(x,b,T(30));
NT2_TEST_EQUAL(T(p),T(0));
NT2_TEST_EQUAL(T(p1),T(0));

}
