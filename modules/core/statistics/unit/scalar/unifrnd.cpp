//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( unifrnd_realf,  (float))
{
  using nt2::unifrnd;
  using nt2::tag::unifrnd_;

  nt2::table<T> b = unifrnd(T(0.0), T(1.0));
  NT2_TEST_ULP_EQUAL(b, 0.5488135218620300293f, 0.5);

  nt2::table<T> c =  unifrnd(T(0.0), T(1.0), 3);
  nt2::table<T> cr= nt2::trans(nt2::cons(nt2::of_size(3, 3),
              0.59284460544586181641f, 0.60276335477828979492f, 0.84725171327590942383f,
              0.71518933773040771484f, 0.85794562101364135742f, 0.42365479469299316406f,
              0.84426575899124145508f, 0.54488319158554077148f, 0.62356370687484741211f )
                              );

  NT2_TEST_ULP_EQUAL(c, cr, 0.5);

  nt2::table<T> d =  unifrnd(T(0.0), T(1.0), 5, 3);
  nt2::table<T> dr=nt2::trans(nt2::cons(nt2::of_size(3, 5),
                              0.64589411020278930664f, 0.056712977588176727295f, 0.79172503948211669922f,
                              0.38438171148300170898f, 0.96366274356842041016f, 0.81216871738433837891f,
                              0.43758720159530639648f, 0.27265629172325134277f, 0.52889490127563476562f,
                              0.29753461480140686035f, 0.38344150781631469727f, 0.47997716069221496582f,
                              0.891773f, 0.47766512632369995117f, 0.56804454326629638672f
                              )
                            );

  NT2_TEST_ULP_EQUAL(d, dr, 0.5);

  nt2::table<T> e =  unifrnd(T(-2.0), T(2.0), nt2::of_size(3, 2));
  nt2::table<T> er=  nt2::trans(nt2::cons(nt2::of_size(2, 3),
                              -0.42886078357696533203f, -1.7158558368682861328f,
                               1.7023866176605224609f , -0.65041530132293701172f,
                               1.3443150520324707031f , -1.6514828205108642578f
                                       )
                             );

  NT2_TEST_ULP_EQUAL(e, er, 0.5);

  nt2::table<T> f =  unifrnd(T(0.0), T(1.0), size(e));
  nt2::table<T> fr=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                          0.64817190170288085938f, 0.83261984586715698242f,
                                          0.020218398422002792358f, 0.95715516805648803711f,
                                          0.36824154853820800781f, 0.77815675735473632812f
                                       )
                             );

  NT2_TEST_ULP_EQUAL(f, fr, 0.5);
 }

NT2_TEST_CASE_TPL ( unifrnd_reald,  (double))
{
  using nt2::unifrnd;
  using nt2::tag::unifrnd_;

  nt2::table<T> b = unifrnd(T(0.0), T(1.0));
  NT2_TEST_ULP_EQUAL(b, 0.14035077742300927639, 0.5);

  nt2::table<T> c =  unifrnd(T(0.0), T(1.0), 3);
  nt2::table<T> cr= nt2::trans(nt2::cons(nt2::of_size(3, 3),
                  0.87001214525662362576, 0.47360804001800715923, 0.46147936279885470867,
                  0.87008725106716156006, 0.79915856383740901947, 0.52047748048789799213,
                  0.97861834289506077766, 0.80091075249947607517, 0.7805291756521910429
                                        )
                              );

  nt2::table<T> d =  unifrnd(T(0.0), T(1.0), 5, 3);
  nt2::table<T> dr=nt2::trans(nt2::cons(nt2::of_size(3, 5),
    0.67887953366152942181, 0.14335328550077974796, 0.10590760642662644386,
    0.1182744237594306469, 0.53737322823144495487, 0.41466194111853837967,
    0.72063265158794820309, 0.94466891861520707607, 0.47360042273066937923,
    0.63992101699113845825, 0.75861562043428421021, 0.26455561141483485699,
    0.58201979123987257481, 0.52184832817874848843, 0.18633234454318881035
                                       )
                             );
  NT2_TEST_ULP_EQUAL(d, dr, 0.5);

  nt2::table<T> e =  unifrnd(T(-2.0), T(2.0), nt2::of_size(3, 2));
  nt2::table<T> er=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                1.0969347460195422173, -1.1337985731661319733,
                                0.94767271168529987335, 0.27373579330742359161,
                                -0.17539865616708993912, -1.4591273069381713867
                                       )
                             );
  NT2_TEST_ULP_EQUAL(e, er, 0.5);

  nt2::table<T> f =  unifrnd(T(0.0), T(1.0), size(e));
  nt2::table<T> fr=nt2::trans(nt2::cons(nt2::of_size(2, 3),
                                 0.01878979802131652832, 0.14967486378736793995,
                                 0.32414100412279367447, 0.61209572246298193932,
                                 0.61763550085015594959, 0.22232138551771640778
                                  )
                             );

  NT2_TEST_ULP_EQUAL(f, fr, 0.5);
}

NT2_TEST_CASE_TPL ( unifrnd_real,  NT2_REAL_TYPES)
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;

  nt2::table<T> a = nt2::ones(3, 4, nt2::meta::as_<T>());
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
}

template<class S> struct unif_cdf
{
  unif_cdf(const S& a, const S& b) : a_(a), b_(b){}

  template<class A>
  typename nt2::meta::call<nt2::tag::unifcdf_(const A&, const S&, const S&)>::type
  operator()(const A& a) const
  {
    return nt2::unifcdf(a, a_, b_);
  }

  private :
  S a_, b_;
};

NT2_TEST_CASE_TPL ( unifks,  NT2_REAL_TYPES)
{
  T a = 0;
  T b = 1;
  nt2::table<T> vals = nt2::sort(unifrnd(a, b, nt2::of_size(1, 1000)), 2);
  unif_cdf<T>  cu(a, b);

  T d, p;
  nt2::kstest(vals, cu, d, p);

  //Kolmogorov smirnov at 5%
  NT2_TEST_GREATER_EQUAL(p, 0.05);
}
