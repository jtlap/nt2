//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - kolmogorov-smirnov kstest"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components
//////////////////////////////////////////////////////////////////////////////

#include <nt2/include/functions/kstest.hpp>
#include <nt2/include/functions/normrnd.hpp>
#include <nt2/include/functions/caucdf.hpp>
#include <nt2/include/functions/unifrnd.hpp>
#include <nt2/include/functions/unifcdf.hpp>
#include <nt2/include/functions/normcdf.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

template < class S > struct cau_cdf
{
  cau_cdf(const S& med,  const S& scal) : med_(med), scal_(scal){}

  template < class A >  typename nt2::meta::call<nt2::tag::caucdf_(const  A&, const  S&,  const S&)>::type
  operator()(const A& a) const
  {
    return nt2::caucdf(a, med_, scal_);
  }
private :
  S med_, scal_;
};

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


template < class S > struct norm_cdf
{
  norm_cdf(const S& ,  const S& sig) : mu_(), sig_(sig){}

  template < class A >  typename nt2::meta::call<nt2::tag::normcdf0_(const  A&, const  S&,  const S&)>::type
  operator()(const A& a) const
  {
    return nt2::normcdf(a, mu_, sig_);
  }
private :
  S mu_, sig_;
};
template < class T > struct ref
{
  static const nt2::table<T> nd()
  {
    // 200 number following normal N(0, 1)
    static const nt2::table<T> aa =  nt2::cons(nt2::of_size(1, 200),
                                               0.1832,   -1.0298,    0.9492,    0.3071,    0.1352,    0.5152,    0.2614,   -0.9415,   -0.1623,   -0.1461,
                                               -0.5320,    1.6821,   -0.8757,   -0.4838,   -0.7120,   -1.1742,   -0.1922,   -0.2741,    1.5301,   -0.2490,   -1.0642,    1.6035,
                                               1.2347,   -0.2296,   -1.5062,   -0.4446,   -0.1559,    0.2761,   -0.2612,    0.4434,    0.3919,   -1.2507,   -0.9480,   -0.7411,
                                               -0.5078,   -0.3206,    0.0125,   -3.0292,   -0.4570,    1.2424,   -1.0667,    0.9337,    0.3503,   -0.0290,    0.1825,   -1.5651,
                                               -0.0845,    1.6039,    0.0983,    0.0414,   -0.7342,   -0.0308,    0.2323,    0.4264,   -0.3728,   -0.2365,    2.0237,   -2.2584,
                                               2.2294,    0.3376,    1.0001,   -1.6642,   -0.5900,   -0.2781,    0.4227,   -1.6702,    0.4716,   -1.2128,    0.0662,    0.6524,
                                               0.3271,    1.0826,    1.0061,   -0.6509,    0.2571,   -0.9444,   -1.3218,    0.9248,    0.0000,   -0.0549,    0.9111,    0.5946,
                                               0.3502,    1.2503,    0.9298,    0.2398,   -0.6904,   -0.6516,    1.1921,   -1.6118,   -0.0245,   -1.9488,    1.0205,    0.8617,
                                               0.0012,   -0.0708,   -2.4863,    0.5812,   -2.1924,   -2.3193,    0.0799,   -0.9485,    0.4115,    0.6770,    0.8577,   -0.6912,
                                               0.4494,    0.1006,    0.8261,    0.5362,    0.8979,   -0.1319,   -0.1472,    1.0078,   -2.1237,   -0.5046,   -1.2706,   -0.3826,
                                               0.6487,    0.8257,   -1.0149,   -0.4711,    0.1370,   -0.2919,    0.3018,    0.3999,   -0.9300,   -0.1768,   -2.1321,    1.1454,
                                               -0.6291,   -1.2038,   -0.2539,   -1.4286,   -0.0209,   -0.5607,    2.1778,    1.1385,   -2.4969,    0.4413,   -1.3981,   -0.2551,
                                               0.1644,    0.7477,   -0.2730,    1.5763,   -0.4809,    0.3275,    0.6647,    0.0852,    0.8810,    0.3232,   -0.7841,   -1.8054,
                                               1.8586,   -0.6045,    0.1034,    0.5632,    0.1136,   -0.9047,   -0.4677,   -0.1249,    1.4790,   -0.8608,    0.7847,    0.3086,
                                               -0.2339,   -1.0570,   -0.2841,   -0.0867,   -1.4694,    0.1922,   -0.8223,   -0.0942,    0.3362,   -0.9047,   -0.2883,    0.3501,
                                               -1.8359,    1.0360,    2.4245,    0.9594,   -0.3158,    0.4286,   -1.0360,    1.8779,    0.9407,    0.7873,   -0.8759,    0.3199,
                                               -0.5583,   -0.3114,   -0.5700,   -1.0257,   -0.9087,   -0.2099,   -1.6989,    0.6076,   -0.1178,    0.6992);
    return aa;
  }
};

  NT2_TEST_CASE_TPL ( normks,  NT2_REAL_TYPES)
{

  T mu = 0;
  T sig = 1;
  nt2::table<T> a = nt2::sort(ref<T>::nd(), 2);
  norm_cdf<T>  ca(mu, sig);
  T d, p;
  nt2:: kstest(a, ca, d, p);
  //Kolmogorov smirnov at 5% must succeed
  NT2_TEST_GREATER_EQUAL(p, 0.05);
}

NT2_TEST_CASE_TPL ( cauks,  NT2_REAL_TYPES)
{

  T med = 0;
  T scal = 1;

  nt2::table<T> a = nt2::sort(ref<T>::nd(), 2);
  cau_cdf<T>  ca(med, scal);
  T d, p;
  nt2:: kstest(a, ca, d, p);
  //Kolmogorov smirnov at 5% must fail
  NT2_TEST_LESSER_EQUAL(p, 0.05);
}

NT2_TEST_CASE_TPL ( unifks,  NT2_REAL_TYPES)
{

  T a = -1;
  T b = 1;
  nt2::table<T> v = nt2::sort(ref<T>::nd(), 2);
  unif_cdf<T>  cu(a, b);
  T d, p;
  nt2:: kstest(v, cu, d, p);
  //Kolmogorov smirnov at 5% must fail
  NT2_TEST_LESSER_EQUAL(p, 0.05);
}
