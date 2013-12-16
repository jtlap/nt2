//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/am.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/colon.hpp>



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// double Jacobi_am(double u, char arg, double x)                             //
//                                                                            //
//  Description:                                                              //
//     Let F(phi,k) = F(phi \ alpha) = F(phi | m) be Legendre's elliptic      //
//     function of the first kind with modulus k, modular angle alpha where   //
//     k = sin(alpha) or parameter m where m = k^2, i.e.                      //
//        F(phi,k) = Integral(0,phi) dtheta / sqrt(1 - k^2 sin^2(theta))      //
//        F(phi \ alpha) = Integral(0,phi) dtheta /                           //
//                                        sqrt(1 - sin^2(alpha) sin^2(theta)) //
//        F(phi | m) = Integral(0,phi) dtheta / sqrt(1 - m sin^2(theta))      //
//                                                                            //
//     This Jacobi elliptic amplitude function, am, is defined as             //
//               am(u,k) = am(u \ alpha) = am(u | m)  = phi                   //
//     where u = F(phi,k) = F(phi \ alpha) = F(phi | m).                      //
//                                                                            //
//     The common mean method, sometimes called the Gauss transform method,   //
//     is a variant of the descending Landen transformation in which two      //
//     sequences are formed: Setting a[0] = 1 and g[0] = 1-m, a[i] is the     //
//     arithmetic average and g[i] is the geometric mean of a[i-1] and g[i-1],//
//     i.e. a[i+1] = (a[i] + g[i])/2 and g[i+1] = sqrt(a[i]*g[i]).  The       //
//     sequences, a[i] and g[i], satisfy the inequalities                     //
//     g[0] < g[1] < ... < a[1] < a[0].  Further, lim g[n] = lim a[n].        //
//                                                                            //
//     Set phi[n] = 2^n a[n] u, the recursively compute phi[n-1] by           //
//        phi[n-1] = [ phi[n] + arcsin( c[n] sin(phi[n]) / a[n] ] / 2         //
//     for until n = 1.  Then am(u,k) = am(u \ alpha) = am(u | m) = phi[0].   //
//                                                                            //
//  Arguments:                                                                //
//     double  u                                                              //
//                The first argument of am(u,x) corresponding to the value of //
//                the elliptic integral of the first kind u = F(am(u,x),x).   //
//     char    arg                                                            //
//                The type of argument of the second argument of am():        //
//                  If arg = 'k', then x = k, the modulus of F(phi,k).        //
//                  If arg = 'a', then x = alpha, the modular angle of        //
//                                F(phi \ alpha), alpha in radians.           //
//                  If arg = 'm', then x = m, the parameter of F(phi | m).    //
//                  The value of arg defaults to 'k'.                         //
//     double  x                                                              //
//                The second argument of the amplitude function am(u,x)       //
//                corresponding to the second argument of the elliptic        //
//                integral of the first kind F(phi,x).  'x' may the the       //
//                modulus, modular angle, or parameter depending on the value //
//                of 'arg'.  If 'arg' = 'm', then x must be between 0 and 1   //
//                inclusively and if 'arg' = 'k', then x must be between -1   //
//                and 1 inclusively.                                          //
//                                                                            //
//  Return Value:                                                             //
//     The amplitude am(u,m) in radians.                                      //
//                                                                            //
//  Example:                                                                  //
//     double u, x;                                                           //
//     double am;                                                             //
//     char   arg;                                                            //
//                                                                            //
//     ( code to initialize u, arg, and x )                                   //
//                                                                            //
//     phi = Jacobi_am( u, arg, x );                                          //
////////////////////////////////////////////////////////////////////////////////

#include <math.h>           // required for sqrtl(), fabsl(), fabs(), asinl(),
                            // atan(), sinl(), and M_PI_2
#include <float.h>          // required for LDBL_EPSILON


double Jacobi_am(double u, char arg,  double x)
{
  static const int N = 30;            // More than sufficient for extended precision
                                     // Near m = 1, usually an N of 10 would do.
   long double a[N+1];
   long double g[N+1];
   long double c[N+1];
   long double two_n;
   long double phi;
   long double k;
   int n;

                        // Check special case x = 0 //
                        // i.e. k = m = alpha = 0.  //

   if ( x == 0.0 ) return u;

   switch (arg) {
      case 'a': k = sinl( fabsl((long double) x) ); break;
      case 'm': k = sqrtl( fabsl((long double) x) ); break;
      default:  k = (long double) fabs(x);
   }

                   // Check special case k = 1 //

   if ( k == 1.0 ) return 2.0 * atan( exp(u) ) - M_PI_2;

         // If k > 1, then perform a Jacobi modulus transformation. //
         // Initialize the sequence of arithmetic and geometric     //
         // means, a = 1, g = k'.                                   //

   a[0] = 1.0L;
   g[0] = sqrtl(1.0L - k * k);
   c[0] = k;

   // Perform the sequence of Gaussian transformations of arithmetic and //
   // geometric means of successive arithmetic and geometric means until //
   // the two means converge to a common mean (upto machine accuracy)    //
   // starting with a = 1 and g = k', which were set above.              //

   two_n = 1.0L;
   for (n = 0; n < N; n++) {
      if ( fabsl(a[n] - g[n]) < (a[n] * LDBL_EPSILON) ) break;
      two_n += two_n;
      a[n+1] = 0.5L * (a[n] + g[n]);
      g[n+1] = sqrtl(a[n] * g[n]);
      c[n+1] = 0.5L * (a[n] - g[n]);
   }

         // Prepare for the inverse transformation of phi = x * cm. //

   phi = two_n * a[n] * u;

                      // Perform backward substitution //

   for (; n > 0; n--) phi = 0.5L * ( phi + asinl( c[n] * sinl(phi) / a[n]) );

   return (double) phi;
}





NT2_TEST_CASE_TPL ( am_real,  NT2_REAL_TYPES)
{
  using nt2::am;
  using nt2::tag::am_;
  typedef typename nt2::meta::call<am_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(am(nt2::Inf<T>(), T(0)), nt2::Inf<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Minf<T>(), T(0)), nt2::Minf<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Nan<T>(), T(0)), nt2::Nan<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Inf<T>(), T(0.5)), nt2::Nan<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Minf<T>(), T(0.5)), nt2::Nan<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Nan<T>(), T(0.5)), nt2::Nan<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Inf<T>(), T(1)), nt2::Pio_2<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Minf<T>(), T(1)), -nt2::Pio_2<r_t>(), 1.0);
  NT2_TEST_ULP_EQUAL(am(nt2::Nan<T>(), T(1)), nt2::Nan<r_t>(), 1.0);
#endif
  // specific values tests
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),T(0)),    Jacobi_am(nt2::One<r_t>(),'x',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0)),  Jacobi_am(nt2::Pio_2<r_t>(),'x',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(),T(0)),   Jacobi_am(nt2::Zero<r_t>(),'x',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),T(0.5)),  Jacobi_am(nt2::One<T>(),'x',T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0.5)),Jacobi_am(nt2::Pio_2<T>(),'x', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(),T(0.5)), Jacobi_am(nt2::Zero<T>(),'x', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),T(1)),    Jacobi_am(nt2::One<T>(),'x',T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(1)),  Jacobi_am(nt2::Pio_2<T>(),'x', T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(),T(1)),   Jacobi_am(nt2::Zero<T>(),'x', T(1)), 1);

  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(0),  'a'),    Jacobi_am(nt2::One<r_t>(),  'a',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0),  'a'),  Jacobi_am(nt2::Pio_2<r_t>(),  'a',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(0),  'a'),   Jacobi_am(nt2::Zero<r_t>(),  'a',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(0.5), 'a'),  Jacobi_am(nt2::One<T>(),    'a',T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0.5), 'a'),Jacobi_am(nt2::Pio_2<T>(),    'a', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(0.5), 'a'), Jacobi_am(nt2::Zero<T>(),    'a', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(1),  'a'),    Jacobi_am(nt2::One<T>(),    'a',T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(1),  'a'),  Jacobi_am(nt2::Pio_2<T>(),    'a', T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(1),  'a'),   Jacobi_am(nt2::Zero<T>(),    'a', T(1)), 1);

  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(0),  'm'),    Jacobi_am(nt2::One<r_t>(),  'm',T(0) ), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0),  'm'),  Jacobi_am(nt2::Pio_2<r_t>(),  'm',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(0),  'm'),   Jacobi_am(nt2::Zero<r_t>(),  'm',T(0)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(0.5), 'm'),  Jacobi_am(nt2::One<T>(),    'm',T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(0.5), 'm'),Jacobi_am(nt2::Pio_2<T>(),    'm', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(0.5), 'm'), Jacobi_am(nt2::Zero<T>(),    'm', T(0.5)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::One<T>(),  T(1),  'm'),    Jacobi_am(nt2::One<T>(),    'm',T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Pio_2<T>(),T(1),  'm'),  Jacobi_am(nt2::Pio_2<T>(),    'm', T(1)), 1);
  NT2_TEST_ULP_EQUAL(am(nt2::Zero<T>(), T(1),  'm'),   Jacobi_am(nt2::Zero<T>(),    'm', T(1)), 1);
}
