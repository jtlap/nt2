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
                                               T(0.1832),  T(-1.0298),  T( 0.9492),  T( 0.3071),  T( 0.1352),  T( 0.5152),  T( 0.2614),  T(-0.9415),  T(-0.1623),  T(-0.1461),
                                               T(-0.5320), T(  1.6821), T( -0.8757), T( -0.4838), T( -0.7120), T( -1.1742), T( -0.1922), T( -0.2741), T(  1.5301), T( -0.2490), T( -1.0642), T(  1.6035),
                                               T(1.2347),  T(-0.2296),  T(-1.5062),  T(-0.4446),  T(-0.1559),  T( 0.2761),  T(-0.2612),  T( 0.4434),  T( 0.3919),  T(-1.2507),  T(-0.9480),  T(-0.7411),
                                               T(-0.5078), T( -0.3206), T(  0.0125), T( -3.0292), T( -0.4570), T(  1.2424), T( -1.0667), T(  0.9337), T(  0.3503), T( -0.0290), T(  0.1825), T( -1.5651),
                                               T(-0.0845), T(  1.6039), T(  0.0983), T(  0.0414), T( -0.7342), T( -0.0308), T(  0.2323), T(  0.4264), T( -0.3728), T( -0.2365), T(  2.0237), T( -2.2584),
                                               T(2.2294),  T( 0.3376),  T( 1.0001),  T(-1.6642),  T(-0.5900),  T(-0.2781),  T( 0.4227),  T(-1.6702),  T( 0.4716),  T(-1.2128),  T( 0.0662),  T( 0.6524),
                                               T(0.3271),  T( 1.0826),  T( 1.0061),  T(-0.6509),  T( 0.2571),  T(-0.9444),  T(-1.3218),  T( 0.9248),  T( 0.0000),  T(-0.0549),  T( 0.9111),  T( 0.5946),
                                               T(0.3502),  T( 1.2503),  T( 0.9298),  T( 0.2398),  T(-0.6904),  T(-0.6516),  T( 1.1921),  T(-1.6118),  T(-0.0245),  T(-1.9488),  T( 1.0205),  T( 0.8617),
                                               T(0.0012),  T(-0.0708),  T(-2.4863),  T( 0.5812),  T(-2.1924),  T(-2.3193),  T( 0.0799),  T(-0.9485),  T( 0.4115),  T( 0.6770),  T( 0.8577),  T(-0.6912),
                                               T(0.4494),  T( 0.1006),  T( 0.8261),  T( 0.5362),  T( 0.8979),  T(-0.1319),  T(-0.1472),  T( 1.0078),  T(-2.1237),  T(-0.5046),  T(-1.2706),  T(-0.3826),
                                               T(0.6487),  T( 0.8257),  T(-1.0149),  T(-0.4711),  T( 0.1370),  T(-0.2919),  T( 0.3018),  T( 0.3999),  T(-0.9300),  T(-0.1768),  T(-2.1321),  T( 1.1454),
                                               T(-0.6291), T( -1.2038), T( -0.2539), T( -1.4286), T( -0.0209), T( -0.5607), T(  2.1778), T(  1.1385), T( -2.4969), T(  0.4413), T( -1.3981), T( -0.2551),
                                               T(0.1644),  T( 0.7477),  T(-0.2730),  T( 1.5763),  T(-0.4809),  T( 0.3275),  T( 0.6647),  T( 0.0852),  T( 0.8810),  T( 0.3232),  T(-0.7841),  T(-1.8054),
                                               T(1.8586),  T(-0.6045),  T( 0.1034),  T( 0.5632),  T( 0.1136),  T(-0.9047),  T(-0.4677),  T(-0.1249),  T( 1.4790),  T(-0.8608),  T( 0.7847),  T( 0.3086),
                                               T(-0.2339), T( -1.0570), T( -0.2841), T( -0.0867), T( -1.4694), T(  0.1922), T( -0.8223), T( -0.0942), T(  0.3362), T( -0.9047), T( -0.2883), T(  0.3501),
                                               T(-1.8359), T(  1.0360), T(  2.4245), T(  0.9594), T( -0.3158), T(  0.4286), T( -1.0360), T(  1.8779), T(  0.9407), T(  0.7873), T( -0.8759), T(  0.3199),
                                               T(-0.5583), T( -0.3114), T( -0.5700), T( -1.0257), T( -0.9087), T( -0.2099), T( -1.6989), T(  0.6076), T( -0.1178), T(  0.6992));
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
