//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied linsolve function"

#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/mlinsolve.hpp>
#include <nt2/include/functions/plinsolve.hpp>
#include <nt2/include/functions/clinsolve.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/sysv.hpp>
#include <nt2/include/functions/sycon.hpp>
#include <nt2/include/functions/pocon.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/lansy.hpp>

#include <nt2/include/functions/gecon.hpp>
#include <nt2/include/functions/gesvx.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(linsolv_fast, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::rectangular_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a+a,b,fast_);
nt2::mlinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(boost::proto::value(a), norm);
rcond1 = nt2::gecon( boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_fast_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T> cT;
typedef nt2::table<cT,nt2::rectangular_>    t_t;


t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(2,0),cT(2,0)
                    ,cT(2,0),cT(5,0),cT(7,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);

T rcond,rcond1;

// X = linsolve(A,B)
x = nt2::linsolve(a+a,b,fast_);
nt2::mlinsolve(a+a,b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);

nt2_la_int p = nt2::gesvx(boost::proto::value(a),boost::proto::value(b)
                        ,boost::proto::value(x),rcond1);


NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
NT2_TEST_EQUAL(T(p), T(0) );

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
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a+a,b,precise_);
nt2::plinsolve(a+a,b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon( boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}


NT2_TEST_CASE_TPL(linsolv_precise_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T> cT;
typedef nt2::table<cT,nt2::rectangular_>    t_t;


t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(2,0),cT(2,0)
                    ,cT(2,0),cT(5,0),cT(7,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1;

// X = linsolve(A,B)
x = nt2::linsolve(a+a,b,precise_);
nt2::plinsolve(a+a,b, nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);


nt2_la_int p = nt2::gesvx(boost::proto::value(a),boost::proto::value(b)
                        ,boost::proto::value(x),rcond1);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
NT2_TEST_EQUAL(T(0), T(p) );

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
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon( boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
}

NT2_TEST_CASE_TPL(linsolv_classic_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T> cT;
typedef nt2::table<cT,nt2::rectangular_>    t_t;


t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(2,0),cT(2,0)
                    ,cT(2,0),cT(5,0),cT(7,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1;

// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

nt2_la_int p = nt2::gesvx(boost::proto::value(a),boost::proto::value(b)
                        ,boost::proto::value(x),rcond1);


NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );
NT2_TEST_EQUAL(T(0), T(p) );
}

// // SYMMETRIC

NT2_TEST_CASE_TPL(linsolv_fast_sy_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>                  cT;
typedef nt2::table<cT,nt2::symmetric_>   t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(2,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';

// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,fast_);
nt2::mlinsolve(a+a,b+b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

nt2::table<nt2_la_int> piv = nt2::zeros(a.leading_size(), 1, nt2::meta::as_<nt2_la_int>() );
t_t lu = a;
nt2::sysv( boost::proto::value(lu),boost::proto::value(piv), boost::proto::value(b));
anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_());
rcond1 = nt2::sycon( boost::proto::value(lu),boost::proto::value(piv),anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_fast_sy, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::symmetric_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';

// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,fast_);
nt2::mlinsolve(a+a,b+b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon( boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_precise_sy,NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::symmetric_>    t_t;


t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a,b+b,precise_);
nt2::plinsolve(a,b+b,nt2::tie(x1));

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon( boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_precise_sy_complex,NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>                  cT;
typedef nt2::table<cT,nt2::symmetric_>   t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(2,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x = nt2::ones(nt2::of_size(3,1),nt2::meta::as_<cT>());
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a,b+b,precise_);
nt2::plinsolve(a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

nt2::table<nt2_la_int> piv = nt2::zeros(a.leading_size(), 1, nt2::meta::as_<nt2_la_int>() );
t_t lu = a;
nt2::sysv( boost::proto::value(lu),boost::proto::value(piv), boost::proto::value(b));
anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_());
rcond1 = nt2::sycon( boost::proto::value(lu),boost::proto::value(piv),anorm);

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
t_t x;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

nt2::table<nt2_la_int> piv = nt2::zeros(a.leading_size(), 1, nt2::meta::as_<nt2_la_int>() );
t_t lu = a;
nt2::sysv( boost::proto::value(lu),boost::proto::value(piv), boost::proto::value(b));
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::sycon( boost::proto::value(lu),boost::proto::value(piv),anorm);
NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}

NT2_TEST_CASE_TPL(linsolv_classic_sy_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>                  cT;
typedef nt2::table<cT,nt2::symmetric_>   t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(1,0),cT(2,0)
                    );
t_t b = nt2::cons<cT>(nt2::of_size(3,1)
                    ,cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

nt2::table<nt2_la_int> piv = nt2::zeros(a.leading_size(), 1, nt2::meta::as_<nt2_la_int>() );
t_t lu = a;
nt2::sysv( boost::proto::value(lu),boost::proto::value(piv), boost::proto::value(b));
anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_() );
rcond1 = nt2::sycon( boost::proto::value(lu),boost::proto::value(piv),anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}



// Positive definite

NT2_TEST_CASE_TPL(linsolv_fast_posdef, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef nt2::table<T,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,fast_);
nt2::mlinsolve(a+a,b+b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon(  boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}

NT2_TEST_CASE_TPL(linsolv_fast_posdef_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>                           cT;
typedef nt2::table<cT,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                     ,cT(2,0),cT(-1,0),cT(0,0)
                     ,cT(-1,0),cT(2,0),cT(-1,0)
                     ,cT(0,0),cT(-1,0),cT(2,0));
t_t b = nt2::cons<cT>(nt2::of_size(3,1),cT(1,0),cT(2,0),cT(5,0));
t_t x;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';

// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,fast_);
nt2::mlinsolve(a+a,b+b,x1 );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)
nt2::tie(x,rcond) = nt2::linsolve(a,b);

anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_());
nt2::posv(boost::proto::value(a), boost::proto::value(b));
rcond1 = nt2::pocon(  boost::proto::value(a),anorm);

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


t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,precise_);
nt2::plinsolve(a+a,b+b, nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange(  boost::proto::value(a), norm);
rcond1 = nt2::gecon(  boost::proto::value(lu),norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );

}


NT2_TEST_CASE_TPL(linsolv_precise_posdef_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>                           cT;
typedef nt2::table<cT,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                     ,cT(2,0),cT(-1,0),cT(0,0)
                     ,cT(-1,0),cT(2,0),cT(-1,0)
                     ,cT(0,0),cT(-1,0),cT(2,0));
t_t b = nt2::cons<cT>(nt2::of_size(3,1),cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)
x = nt2::linsolve(a+a,b+b,precise_);
nt2::plinsolve(a+a,b+b, nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

 // // [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_());
nt2::posv(boost::proto::value(a), boost::proto::value(b));
rcond1 = nt2::pocon(  boost::proto::value(a),anorm);

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

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,-1,0,-1,2,-1,0,-1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

t_t lu = nt2::lu(a);
anorm = nt2::lange( boost::proto::value(a), norm);
rcond1 = nt2::gecon(  boost::proto::value(lu) ,norm,anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}


NT2_TEST_CASE_TPL(linsolv_classic_posdef_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;


typedef std::complex<T>                           cT;
typedef nt2::table<cT,nt2::positive_definite_>    t_t;

t_t a = nt2::cons<cT>(nt2::of_size(3,3)
                     ,cT(2,0),cT(-1,0),cT(0,0)
                     ,cT(-1,0),cT(2,0),cT(-1,0)
                     ,cT(0,0),cT(-1,0),cT(2,0));
t_t b = nt2::cons<cT>(nt2::of_size(3,1),cT(1,0),cT(2,0),cT(5,0));
t_t x ;
t_t x1(b);
T rcond,rcond1,anorm;
char norm = '1';


// X = linsolve(A,B)

x = nt2::linsolve(a+a,b+b,classic_);
nt2::clinsolve(a+a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

anorm = nt2::lange( boost::proto::value(a), norm, nt2::symmetric_());
nt2::posv(boost::proto::value(a), boost::proto::value(b));
rcond1 = nt2::pocon(  boost::proto::value(a),anorm);

NT2_TEST_ULP_EQUAL(rcond, rcond1, T(10) );


}

// Band matrix

NT2_TEST_CASE_TPL(linsolv_classic_band, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

nt2::table<T, nt2::band_diagonal_<2,2> >  a = nt2::rand(7, 7, nt2::meta::as_<T>());
nt2::table<T> b = nt2::rand(7, 1, nt2::meta::as_<T>());

nt2::table<T> x ;
nt2::table<T> x1(b);
T rcond;

// X = linsolve(A,B)

x = nt2::linsolve(a,b+b,classic_);
nt2::clinsolve(a,b+b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b+b);

NT2_TEST_ULP_EQUAL(x, x1, T(10) );


}


NT2_TEST_CASE_TPL(linsolv_classic_band_complex, NT2_REAL_TYPES )
{
using nt2::_;
using nt2::meta::as_;
using nt2::classic_;
using nt2::fast_;
using nt2::precise_;

typedef std::complex<T>  cT;
nt2::table<cT, nt2::band_diagonal_<2,2> >  a = nt2::ones(7, 7, nt2::meta::as_<cT>())
                                             + T(10)*nt2::eye(7, 7, nt2::meta::as_<cT>());
nt2::table<cT> b = nt2::ones(7, 1, nt2::meta::as_<cT>());

nt2::table<cT> x ;
nt2::table<cT> x1(b);
T rcond;

// X = linsolve(A,B)

x = nt2::linsolve(a,b,classic_);
nt2::clinsolve(a,b,nt2::tie(x1) );

NT2_TEST_ULP_EQUAL( x , x1 , T(10));

// [X,R] = linsolve(A,B)

nt2::tie(x,rcond) = nt2::linsolve(a,b);

NT2_TEST_ULP_EQUAL(x, x1, T(10) );

}


NT2_TEST_CASE_TPL(linsolve_trsm, NT2_REAL_TYPES )
{
  using nt2::_;

typedef nt2::table<T>         t_t;

t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,1,1,1,1,2);
t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
t_t x = nt2::cons<T>(nt2::of_size(3,1),-1,0,3);

t_t y(b),p;

nt2::table<T,nt2::upper_triangular_> u;
nt2::table<T,nt2::lower_triangular_> l;

nt2::tie(l,u,p) = nt2::lu(a);

y = nt2::mtimes(p,b);

y = nt2::linsolve(l,y);
y = nt2::linsolve(u,y);

NT2_TEST_EQUAL( y, x);
}
