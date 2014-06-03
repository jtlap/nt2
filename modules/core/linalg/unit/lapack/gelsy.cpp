//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gelsy.hpp>
#include <nt2/include/functions/gesv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <stdio.h>

NT2_TEST_CASE_TPL(lsy, NT2_REAL_TYPES )
{
  using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,2,1,5,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);


t_t a1(a);
t_t b1(b);

t_i jpvt = nt2::zeros(nt2::of_size(3,1), nt2::meta::as_<nt2_la_int>());
t_i jpvt1(jpvt);

nt2_la_int p = nt2::gelsy(boost::proto::value(a),boost::proto::value(jpvt)
                       ,boost::proto::value(b));
nt2_la_int p1 = nt2::gesv(boost::proto::value(a1),boost::proto::value(jpvt1)
                       ,boost::proto::value(b1));

NT2_TEST_ULP_EQUAL(b, b1, T(20) );
NT2_TEST_EQUAL(p, 0);
NT2_TEST_EQUAL(p1, 0);
}

NT2_TEST_CASE_TPL(lsyc, NT2_REAL_TYPES )
{
  using nt2::_;

typedef std::complex<T> cT;
typedef nt2::table<cT>           t_t;
typedef nt2::table<nt2_la_int>  t_i;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,2),cT(1,1),cT(2,2)
                    ,cT(1,1),cT(5,5),cT(1,1)
                    ,cT(1,1),cT(1,1),cT(2,2)
                    );

t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,1),cT(2,2),cT(5,5));


t_t a1(a);
t_t b1(b);

t_i jpvt = nt2::zeros(nt2::of_size(3,1), nt2::meta::as_<nt2_la_int>());
t_i jpvt1(jpvt);

nt2_la_int p = nt2::gelsy(boost::proto::value(a),boost::proto::value(jpvt)
                       ,boost::proto::value(b));
nt2_la_int p1 = nt2::gesv(boost::proto::value(a1),boost::proto::value(jpvt1)
                       ,boost::proto::value(b1));

NT2_TEST_ULP_EQUAL(b, b1, T(20) );
NT2_TEST_EQUAL(p, 0);
NT2_TEST_EQUAL(p1, 0);

}

