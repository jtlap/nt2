//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gesvx.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/gesv.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(svx, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;

T rcond = 1;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t s = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);
t_t x = b;

nt2_la_int p = 5;
p = nt2::gesvx( boost::proto::value(a),boost::proto::value(b)
            , boost::proto::value(x), rcond );

NT2_TEST_EQUAL(T(p),T(0) );
NT2_TEST_ULP_EQUAL(s,x, T(10));
}



NT2_TEST_CASE_TPL(svx1, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>          t_t;
typedef nt2::table<nt2_la_int> t_i;

T rcond = 1;

t_t a = T(10)* nt2::ones (4000, 4000, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (4000, 4000, nt2::meta::as_<T>());
t_t b = nt2::ones (4000, 1, nt2::meta::as_<T>());



t_t a1(a);

t_t x(b);
t_t x1(b);
t_i piv = nt2::zeros(4000,1, nt2::meta::as_<nt2_la_int>());

nt2_la_int p= nt2::gesv( boost::proto::value(a1),boost::proto::value(piv)
                     , boost::proto::value(x1) );


nt2_la_int iter= nt2::gesvx( boost::proto::value(a),boost::proto::value(b)
                         , boost::proto::value(x), rcond );


NT2_TEST_ULP_EQUAL(x , x1, T(1000000) );
NT2_TEST_EQUAL(iter>=0?true:false,true);
NT2_TEST_EQUAL(T(p),T(0));
}


NT2_TEST_CASE_TPL(svxc, NT2_REAL_TYPES )
{
using nt2::_;

typedef std::complex<T> cT;
typedef nt2::table<cT>           t_t;

nt2::table<nt2_la_int>  piv = nt2::zeros( nt2::of_size(3,1)
                                        , nt2::meta::as_<nt2_la_int>());
T rcond= 1;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(2,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t s = nt2::cons<cT>(nt2::of_size(3,1),cT(-1,0),cT(0,0),cT(3,0));
t_t x(nt2::of_size(3,1));

nt2_la_int p = 5;
p = nt2::gesvx( boost::proto::value(a),boost::proto::value(b)
            , boost::proto::value(x), rcond );

NT2_TEST_ULP_EQUAL(s,x, T(100));
NT2_TEST_EQUAL(T(p),T(0));

}
