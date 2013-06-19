//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied linsolve function"

#include <nt2/include/functions/linsolv.hpp>
#include <nt2/include/functions/mlinsolve.hpp>
#include <nt2/include/functions/plinsolve.hpp>
#include <nt2/include/functions/clinsolve.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/con.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL(linsolv_fast, (double) )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::rectangular_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,fast_);
nt2::mlinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}



NT2_TEST_CASE_TPL(linsolv_precise, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::rectangular_>    t_t;


t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,precise_);
nt2::plinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_classic, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::rectangular_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolv(a+a,b,classic_);
nt2::clinsolve(a+a,b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
}



// SYMMETRIC

NT2_TEST_CASE_TPL(linsolv_fast_sy, (double) )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::symmetric_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,fast_);
nt2::mlinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}



NT2_TEST_CASE_TPL(linsolv_precise_sy, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::symmetric_>    t_t;


t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,precise_);
nt2::plinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_classic_sy, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::symmetric_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolv(a+a,b,classic_);
nt2::clinsolve(a+a,b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}



// Positive definite

NT2_TEST_CASE_TPL(linsolv_fast_posdef, (double) )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,fast_);
nt2::mlinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}



NT2_TEST_CASE_TPL(linsolv_precise_posdef, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::positive_definite_>    t_t;


t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolv(a+a,b,precise_);
nt2::plinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_classic_posdef, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::ones(nt2::of_size(3,1));
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolv(a+a,b,classic_);
nt2::clinsolve(a+a,b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolv(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(a, norm);
rcond1 = nt2::con(lu,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}
