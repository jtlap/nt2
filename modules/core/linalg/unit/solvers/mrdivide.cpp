//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/mrdivide.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(mrdivide, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;


typedef nt2::table<T,nt2::rectangular_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(1, 3),1,2,5);
t_t x ;
t_t x1;
// X = linsolve(A,B)
x = ctrans(nt2::linsolve(ctrans(a),ctrans(b)));
x1= nt2::mrdivide(b, a);


NT2_TEST_ULP_EQUAL( x , x1 , 0.5);


}

NT2_TEST_CASE_TPL(mrdivide2, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;


typedef nt2::table<T,nt2::rectangular_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(1, 3),1,2,5);
t_t x ;
t_t x1;
T r, r1;
nt2::tie(x, r) = nt2::linsolve(ctrans(a),ctrans(b));
nt2::tie(x1, r1)= nt2::mrdivide(b, a);


NT2_TEST_ULP_EQUAL( ctrans(x) , x1 , 0.5);
NT2_TEST_ULP_EQUAL( r , r1 , 0.5);

}
