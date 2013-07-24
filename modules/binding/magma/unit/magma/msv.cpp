//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/msv.hpp>
#include <nt2/include/functions/sv.hpp>
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



t_t a = nt2::ones(127 , 127, nt2::meta::as_<T>());
t_t b = nt2::ones(127 , 1,nt2::meta::as_<T>() );

t_t a1(a);

t_t x(b);
t_t x1(b);
t_i piv;
nt2_la_int iter= nt2::msv(a,b,x);s

}
