//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/colon.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(sv, NT2_REAL_TYPES )
{
using nt2::_;


typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_i ipiv;

nt2_la_int p = nt2::sv(boost::proto::value(a),boost::proto::value(ipiv)
                      ,boost::proto::value(b));

NT2_TEST_EQUAL(b,x);


}

NT2_TEST_CASE_TPL(svc, NT2_REAL_TYPES )
{
using nt2::_;

typedef std::complex<T> cT;
typedef nt2::table<cT>           t_t;
typedef nt2::table<nt2_la_int>  t_i;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,2),cT(1,1),cT(1,1)
                    ,cT(1,1),cT(1,1),cT(1,1)
                    ,cT(1,1),cT(1,1),cT(2,2)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,1),cT(2,2),cT(5,5));
t_t x = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(-1,0),cT(0,0),cT(3,0));

t_i ipiv;

nt2_la_int p = nt2::sv(boost::proto::value(a),boost::proto::value(ipiv)
                      ,boost::proto::value(b));

NT2_TEST_EQUAL(b,x);


}
