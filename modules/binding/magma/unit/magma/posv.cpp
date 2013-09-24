//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/posv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/transpose.hpp>
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

NT2_TEST_CASE_TPL(magma_posv, NT2_REAL_TYPES )
{
using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>       t_i;

// t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
// t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
// t_t x = nt2::cons<T/error>(nt2::of_size(3,1),-1,0,3);

nt2_la_int n = 6000;

t_t a = nt2::rand(6000, 6000, nt2::meta::as_<T>());
t_t b = nt2::rand(6000,1,nt2::meta::as_<T>() );
t_t x(b);

a = a + nt2::transpose(a);
a = a + T(n)*nt2::eye(n,n,nt2::meta::as_<T>());

nt2_la_int p = 5;
p = nt2::posv(a,b,x);

// NT2_TEST_EQUAL(b,x);
NT2_TEST_EQUAL(p,0);
}




// NT2_TEST_CASE_TPL(magma_posv_1, NT2_REAL_TYPES )
// {
// using nt2::_;

// typedef nt2::table<T>         t_t;
// typedef nt2::table<nt2_la_int>       t_i;

// t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
// t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);

// t_t x(b);


// nt2_la_int p = 5;
// p = nt2::posv(a,b,x);

// // NT2_TEST_EQUAL(b,x);
// NT2_TEST_EQUAL(p,0);

// NT2_DISPLAY(x);
// }



