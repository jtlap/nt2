/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::freqspace2 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/freqspace2.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( freqspace2, (double)(float) )
{
  typedef T r_t;
  {
    const int n = 4;
    const int m = 7;
    nt2::table<T> xd1, xd2;
    boost::fusion::tie(xd1, xd2)= nt2::freqspace2(m, n, nt2::meta::as_<T>());
    T hvm = m*nt2::Half<T>();
    T hm = nt2::rec(hvm);
    T lm = -nt2::floor(hvm)*hm;
    T hvn = n*nt2::Half<T>();
    T hn = nt2::rec(hvn);
    T ln = -nt2::floor(hvn)*hn;

    nt2::table<T> yd1 = nt2::colon(ln, hn, T(1)-T(2)/n);
    nt2::table<T> yd2 = nt2::colon(lm, hm, T(1)-T(1)/m);
    NT2_TEST_EQUAL( xd1.extent(), nt2::of_size(1,n ) );
    NT2_TEST_EQUAL( xd2.extent(), nt2::of_size(1,m ) );

     for(int i=1;i<=n;++i)
       NT2_TEST_ULP_EQUAL( xd1(i), yd1(i), 1.0 );
     for(int i=1;i<=m;++i)
       NT2_TEST_ULP_EQUAL( xd2(i), yd2(i), 1.0 );
     nt2::display("xd1", xd1);
     nt2::display("yd1", yd1);
     nt2::display("xd2", xd2);
     nt2::display("yd2", yd2);

   }
//   {
//     const int n = 4;
//     nt2::table<T> xd = nt2::freqspace2(n, nt2::whole_, nt2::meta::as_<T>());
//     nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(2)*(n-1)/n);

//      NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n ) );

//      for(int i=1;i<=n;++i)
//        NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
//    }
}
// NT2_TEST_CASE( freqspace2_no_type )
// {
//   typedef double T;
//   typedef double r_t;
//   {
//     for(int n = 1; n <= 10; ++n)
//       {
//         nt2::table<T> xd = nt2::freqspace2(n);
//         nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(1));
//         NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n/2+1 ) );

//         for(int i=1;i<=n/2+1;++i)
//           NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
//       }
//   }
//   {
//     for(int n = 1; n <= 10; ++n)
//       {
//         nt2::table<T> xd = nt2::freqspace2(n, nt2::whole_);
//         nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(2)*(n-1)/n);

//         NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n ) );

//         for(int i=1;i<=n;++i)
//           NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
//       }
//   }
// }

