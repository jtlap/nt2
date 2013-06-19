//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ysv.hpp>
#include <nt2/include/functions/ysvx.hpp>
#include <nt2/include/functions/sv.hpp>
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

NT2_TEST_CASE_TPL(ysvx, NT2_REAL_TYPES )
{
using nt2::_;


typedef nt2::table<T>         t_t;
nt2::table<nt2_la_int> piv;


T rcond;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x(b);
t_t x1(b);
t_t a1(a);
t_t a2(a);


nt2_la_int p = nt2::ysv(a,piv,b,x);
nt2_la_int p1 = nt2::ysvx(a1,piv,b,x1,rcond);
nt2_la_int p2 = nt2::sv(a2,piv,b);

NT2_TEST_ULP_EQUAL(x, x1, T(10) );
NT2_TEST_ULP_EQUAL(x, b, T(10) );

}
