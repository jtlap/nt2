//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sysv.hpp>
#include <nt2/include/functions/sysvx.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(ssysv, (float) )
{
using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>       t_i;

t_t a = nt2::rand(10, 10, nt2::meta::as_<T>());
t_t x = nt2::rand(10,1,nt2::meta::as_<T>() );
t_t b(x);
a = nt2::mtimes(a,nt2::trans(a));
t_t a1(a);

t_i ipiv = nt2::zeros(nt2::of_size(10,1), nt2::meta::as_<nt2_la_int>() );
t_i ipiv1(ipiv);

T rcond;

nt2_la_int p = nt2::sysvx( boost::proto::value(a),boost::proto::value(ipiv1)
           , boost::proto::value(b) , boost::proto::value(x) , rcond);

nt2_la_int p1 = nt2::sysv( boost::proto::value(a1),boost::proto::value(ipiv)
           , boost::proto::value(b) );


NT2_TEST_EQUAL(p,0);
NT2_TEST_EQUAL(p1,0);
NT2_TEST_ULP_EQUAL(b,x,T(1000));
}


NT2_TEST_CASE_TPL(dsysv, (double) )
{
using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>       t_i;

t_t a = nt2::rand(10, 10, nt2::meta::as_<T>());
t_t x = nt2::rand(10,1,nt2::meta::as_<T>() );
t_t b(x);
a = nt2::mtimes(a,nt2::trans(a));
t_t a1(a);

t_i ipiv = nt2::zeros(nt2::of_size(10,1), nt2::meta::as_<nt2_la_int>() );
t_i ipiv1(ipiv);

T rcond;

nt2_la_int p = nt2::sysvx( boost::proto::value(a),boost::proto::value(ipiv1)
           , boost::proto::value(b) , boost::proto::value(x) , rcond);

nt2_la_int p1 = nt2::sysv( boost::proto::value(a1),boost::proto::value(ipiv)
           , boost::proto::value(b) );


NT2_TEST_EQUAL(p,0);
NT2_TEST_EQUAL(p1,0);
NT2_TEST_ULP_EQUAL(b,x,T(1000));
}
