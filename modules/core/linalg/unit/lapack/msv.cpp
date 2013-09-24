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

#include <time.h>
#include <stdio.h>

// NT2_TEST_CASE_TPL(msv, (double) )
// {
// using nt2::_;

// typedef nt2::table<T>         t_t;
// typedef nt2::table<nt2_la_int>         t_i;

// t_t a = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
// t_t a1(a);
// t_t b = nt2::cons<T>(nt2::of_size(3,1),1,2,5);
// t_t x(b);
// t_t x1(b);
// t_i piv;


// nt2_la_int iter= nt2::msv(a,b,x);
// nt2_la_int info= nt2::sv(a1,piv,x1);

// NT2_TEST_ULP_EQUAL(x, x1 , T(10));

// }
#define FLOPS_GETRF(m, n) ( FMULS_GETRF((double)(m), (double)(n))              \
                          + FADDS_GETRF((double)(m), (double)(n))              \
                          )                                                    \
/**/

#define FMULS_GETRF(m, n)   ( ((m) < (n))                                      \
                            ? ( 0.5 * (m) * ( (m) * ((n) - (1./3.) * (m) - 1. )\
                                            + (n)                              \
                                            )                                  \
                                + (2. / 3.) * (m)                              \
                              )                                                \
                            : ( 0.5 * (n) * ( (n) * ((m) - (1./3.) * (n) - 1. )\
                                            + (m)                              \
                                            )                                  \
                                + (2. / 3.) * (n))                             \
                            )                                                  \
/**/

#define FADDS_GETRF(m, n)   ( ((m) < (n))                                      \
                            ? (0.5 * (m)  * (  (m) * ((n) - (1./3.) * (m))     \
                                            - (n)) + (1. / 6.) * (m)           \
                                            )                                  \
                            : (0.5 * (n)  * ( (n) * ((m) - (1./3.) * (n))      \
                                            - (m)) + (1. / 6.) * (n)           \
                                            )                                  \
                            )                                                  \


#define FLOPS_DGETRS(n, nrhs) ( FMULS_GETRS((double)(n), (double)(nrhs))       \
                              + FADDS_GETRS((double)(n), (double)(nrhs))       \
                              )                                                \
/**/

#define FMULS_GETRS(n, nrhs) ((nrhs) * (n) *  (n)      )
#define FADDS_GETRS(n, nrhs) ((nrhs) * (n) * ((n) - 1 ))


NT2_TEST_CASE_TPL(msv, (double) )
{
using nt2::_;

typedef nt2::table<T>         t_t;
typedef nt2::table<nt2_la_int>         t_i;

t_t a = nt2::rand(10000,10000,nt2::meta::as_<T>());
t_t a1(a);
t_t b = nt2::rand(10000,1,nt2::meta::as_<T>());
t_t x(b);
t_t x1(b);
t_i piv;

size_t start;

start = time(NULL);
nt2_la_int iter= nt2::msv(a,b,x);


double dif = time(NULL) - start;

double flops = ((FLOPS_GETRF(10000,10000) + FLOPS_DGETRS(10000,10000)) /dif)/1000.;
printf("flops : %f\n",flops);
printf ("Elasped time is %.2lf seconds.", dif );

}
