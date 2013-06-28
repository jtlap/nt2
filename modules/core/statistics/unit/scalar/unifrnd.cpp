//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - unifrnd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/unifrnd.hpp>
#include <nt2/include/functions/kstest.hpp>
#include <nt2/include/functions/unifcdf.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/options.hpp>
#include <nt2/table.hpp>

template < class S > struct unif_cdf
{
  unif_cdf(const S& a,  const S& b) : a_(a), b_(b){}

  template < class A >  typename nt2::meta::call<nt2::tag::unifcdf_(const  A&, const  S&,  const S&)>::type
  operator()(const A& a) const
  {
    return nt2::unifcdf(a, a_, b_);
  }
private :
  S a_, b_;
};
NT2_TEST_CASE_TPL ( unifrnd_realf,  (float))
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;
  // specific values tests
  nt2::table<T> b = unifrnd(T(0.0), T(1.0));
  NT2_TEST_ULP_EQUAL(b, 0.81472367048263549805f, 0.5);

  nt2::table<T> c =  unifrnd(T(0.0), T(1.0), 3);
  nt2::table<T> cr= nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         0.13547700643539428711f, 0.12698681652545928955f, 0.22103404998779296875f,
                                         0.90579193830490112305f, 0.96886777877807617188f, 0.63235926628112792969f,
                                         0.83500856161117553711f, 0.9133758544921875f, 0.30816704034805297852f )
                              );

  NT2_TEST_ULP_EQUAL(c, cr, 0.5);
  nt2::table<T> d =  unifrnd(T(0.0), T(1.0), 5, 3);
  nt2::table<T> dr=nt2::trans(nt2::cons(nt2::of_size(3, 5),
                                        0.097540400922298431396f, 0.99288129806518554688f, 0.15761308372020721436f,
                                        0.54722058773040771484f, 0.9575068354606628418f, 0.7258389592170715332f,
                                        0.27849823236465454102f, 0.99646133184432983398f, 0.97059279680252075195f,
                                        0.18838196992874145508f, 0.96488851308822631836f, 0.98110967874526977539f,
                                        0.54688149690628051758f, 0.96769493818283081055f, 0.95716696977615356445f
                                       )
                             );
  NT2_TEST_ULP_EQUAL(d, dr, 0.5);
  nt2::table<T> e =  unifrnd(T(-2.0), T(2.0), nt2::of_size(3, 2));
  nt2::table<T> er=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                        -1.5605529546737670898f, 1.2011218070983886719f,
                                        -0.05849742889404296875f, -0.81188225746154785156f,
                                        1.1924233436584472656f, -1.4324545860290527344f
                                       )
                             );
  NT2_TEST_ULP_EQUAL(e, er, 0.5);
  nt2::table<T> f =  unifrnd(T(0.0), T(1.0), size(e));
  nt2::table<T> fr=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                        0.0047834841534495353699f, 0.91573554277420043945f,
                                        0.42176127433776855469f, 0.63976335525512695312f,
                                        0.11246451735496520996f, 0.79220730066299438477f
                                       )
                             );
  NT2_TEST_ULP_EQUAL(f, fr, 0.5);
 } // end of test for floating_

NT2_TEST_CASE_TPL ( unifrnd_reald,  (double))
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;
  // specific values tests
  std::cout << std::setprecision(20);
  nt2::table<T> b = unifrnd(T(0.0), T(1.0));
  NT2_TEST_ULP_EQUAL(b, 0.87843064521439373493, 0.5);

  nt2::table<T> c =  unifrnd(T(0.0), T(1.0), 3);
  nt2::table<T> cr= nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         0.95949242520146071911, 0.79792861500754952431, 0.84912930545397102833,
                                         0.50366267748177051544, 0.035711679374799132347, 0.21192433219403028488,
                                         0.6557406960055232048, 0.36129400134086608887, 0.93399324570782482624
                                        )
                              );

  NT2_TEST_ULP_EQUAL(c, cr, 0.5);
  nt2::table<T> d =  unifrnd(T(0.0), T(1.0), 5, 3);

  nt2::table<T> dr=nt2::trans(nt2::cons(nt2::of_size(3, 5),
                                        0.68135953834280371666, 0.74313247110694646835, 0.17386517184786498547,
                                        0.6787351581733673811, 0.47475868044421076775, 0.17118668975308537483,
                                        0.39873851975426077843, 0.39222701964899897575, 0.30191312683746218681,
                                        0.75774012552574276924, 0.42208768101409077644, 0.70604608370922505856,
                                        0.74064724449999630451, 0.65547789353877305984, 0.79727991507388651371
                                       )
                             );
  NT2_TEST_ULP_EQUAL(d, dr, 0.5);
  nt2::table<T> e =  unifrnd(T(-2.0), T(2.0), nt2::of_size(3, 2));
  nt2::table<T> er=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                        -1.8726686220616102219, 1.4897152800112962723,
                                        -0.73379822075366973877, -1.8153144381940364838,
                                        -0.89230807125568389893, -1.4035440944135189056
                                       )
                             );
  NT2_TEST_ULP_EQUAL(e, er, 0.5);
  nt2::table<T> f =  unifrnd(T(0.0), T(1.0), size(e));
  nt2::table<T> fr=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                        0.097131775924935936928, 0.8219032646156847477,
                                        0.99406849429942667484, 0.69482862227596342564,
                                        0.82345782429911196232, 0.12518276437185704708
                                       )
                             );
  NT2_TEST_ULP_EQUAL(f, fr, 0.5);
 } // end of test for floating_

NT2_TEST_CASE_TPL ( unifrnd_real,  NT2_REAL_TYPES)
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;
  // specific values tests
  nt2::table<T> a =  nt2::ones(3, 4, nt2::meta::as_<T>());
  nt2::table<T> b = unifrnd(T(-1.0), T(2.0));
  NT2_TEST(nt2::globalall(ge(b, T(-1))));
  NT2_TEST(nt2::globalall(le(b, T(2))));
  nt2::table<T> c =  unifrnd(T(-1.0), T(2.0), 3);
  NT2_TEST(nt2::globalall(ge(c, T(-1))));
  NT2_TEST(nt2::globalall(le(c, T(2))));
  nt2::table<T> d =  unifrnd(T(-1.0), T(2.0), 3, 5);
  NT2_TEST(nt2::globalall(ge(d, T(-1))));
  NT2_TEST(nt2::globalall(le(d, T(2))));
  nt2::table<T> e =  unifrnd(T(-1.0), T(2.0), nt2::of_size(3, 2));
  NT2_TEST(nt2::globalall(ge(e, T(-1))));
  NT2_TEST(nt2::globalall(le(e, T(2))));
  nt2::table<T> f =  unifrnd(T(-1.0), T(2.0), size(e));
  NT2_TEST(nt2::globalall(ge(f, T(-1))));
  NT2_TEST(nt2::globalall(le(f, T(2))));

 } // end of test for floating_


NT2_TEST_CASE_TPL ( unifks,  NT2_REAL_TYPES)
{

  T a = 0;
  T b = 1;
  nt2::table<T> vals = nt2::sort(unifrnd(a, b, nt2::of_size(1, 1000)), 2);
  unif_cdf<T>  cu(a, b);
  T d, p;
  nt2:: kstest(vals, cu, d, p);
  //Kolmogorov smirnov at 5%
  NT2_TEST_GREATER_EQUAL(p, 0.05);
}

