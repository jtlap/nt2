//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/lsy.hpp>
#include <nt2/include/functions/sv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(lsy, NT2_REAL_TYPES )
{
  using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,2,1,5,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);


t_t a1(a);
t_t b1(b);

t_i jpvt,jpvt1;

nt2_la_int p = nt2::lsy(a,jpvt,b);
nt2_la_int p1 = nt2::sv(a1,jpvt1,b1);

NT2_DISPLAY(b);
NT2_DISPLAY(b1);

NT2_TEST_ULP_EQUAL(b, b1, T(10) );

}

