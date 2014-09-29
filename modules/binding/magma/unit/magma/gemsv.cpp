//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gemsv.hpp>
#include <nt2/include/functions/gesv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(msv, (double) )
{
using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;

t_t a = T(10)* nt2::ones (4000, 4000, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (4000, 4000, nt2::meta::as_<T>());
t_t b = nt2::ones (4000, 1, nt2::meta::as_<T>());

t_t a1(a);

t_t x(b);
t_t x1(b);
t_i piv;

nt2_la_int info = nt2::gesv( boost::proto::value(a1),boost::proto::value(piv)
                     , boost::proto::value(x1) );

nt2_la_int iter = nt2::gemsv( boost::proto::value(a),boost::proto::value(b)
                         , boost::proto::value(x) );


NT2_TEST_ULP_EQUAL(x , x1, T(1000000) );
NT2_TEST_EQUAL(iter>=0?true:false,true);
NT2_TEST_EQUAL(T(info),T(0));

}


NT2_TEST_CASE_TPL(msvc, (double) )
{
using nt2::_;

typedef std::complex<T>                cT;
typedef nt2::table<cT>                  t_t;
typedef nt2::table<nt2_la_int>         t_i;



t_t a = T(10)* nt2::ones (4000, 4000, nt2::meta::as_<cT>())
           - T(4)*nt2::eye  (4000, 4000, nt2::meta::as_<cT>());
t_t b = nt2::ones (4000, 1, nt2::meta::as_<cT>());



t_t a1(a);

t_t x(b);
t_t x1(b);
t_i piv;

nt2_la_int info = nt2::gesv( boost::proto::value(a1),boost::proto::value(piv)
                     , boost::proto::value(x1) );


nt2_la_int iter = nt2::gemsv( boost::proto::value(a),boost::proto::value(b)
                         , boost::proto::value(x) );


NT2_TEST_ULP_EQUAL(x , x1, T(1000000) );
NT2_TEST_EQUAL(iter>=0?true:false,true);
NT2_TEST_EQUAL(T(info),T(0));

}
