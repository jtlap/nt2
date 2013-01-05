//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 integration toolbox - quadgk"

#include <iostream>
#include <nt2/sdk/timing/tic.hpp>
#include <nt2/include/functions/quadgk.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/toolbox/integration/transforms.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/table.hpp>
struct f
{
  template < class X > inline
  //  typename nt2::meta::call<nt2::tag::exp_(const X&)>::type
  nt2::container::table<typename X::value_type>
  operator()(const X & x ) const
  {
    return nt2::if_else_zero(x, x*nt2::sin(rec(x)));
  }
};
struct ff
{
  template < class X > inline
  //  typename nt2::meta::call<nt2::tag::exp_(const X&)>::type
  nt2::container::table<typename X::value_type>
  operator()(const X & x ) const
  {
    return nt2::exp(-sqr(x))*nt2::sqr(nt2::log(x));
  }
};
struct g
{
  template < class X > inline
  X operator()(const X & x ) const
  {
    return nt2::oneminus(x)/nt2::log(x);
  }
};

struct h
{
  template < class X> inline
  //  typename nt2::meta::as_complex<X>::type
  nt2::container::table<std::complex<typename X::value_type > > operator()(const X & x ) const
  {
    return nt2::exp(nt2::mul_i(x));
  }
};
struct k
{
  template < class X> inline
  X operator()(const X & x ) const
  {
    return nt2::rec(nt2::minusone(x+x));
  }
};

typedef std::complex<double> value_t;
typedef nt2::table<value_t> vtab_t;

// const vtab_t& wt()
// {
//   static const value_t pwt[] = {
//     value_t(0.2044329400752989), value_t(0.1903505780647854), value_t(0.1690047266392679),
//     value_t(0.1406532597155259), value_t(0.1047900103222502), value_t(0.06309209262997855),
//     value_t(0.02293532201052922) };
//   static const vtab_t wt(nt2::of_size(1, 7), &pwt[0], &pwt[7]);
//   static const vtab_t wt15 = nt2::cath(nt2::cath(nt2::fliplr(wt),value_t(0.2094821410847278)),wt);
//   return wt15;
// }

// NT2_TEST_CASE_TPL( quadgk_functor_, NT2_REAL_TYPES )
// {
//   typedef T real_t;
//   typedef T input_t;
//   typedef std::complex<T> value_t;
//   typedef nt2::table<value_t> vtab_t;
//   typedef nt2::table<input_t> itab_t;
//   typedef nt2::table<real_t>  rtab_t;
//   input_t a_ =  T(-1);
//   input_t b_ =  T(1);
//   nt2::details::f1<h, input_t, rtab_t, vtab_t> pipo(h(), a_, b_);
//   itab_t z = nt2::linspace(T(0), T(1), 3);
//   NT2_DISPLAY(pipo(z));

// }


NT2_TEST_CASE_TPL( quadgk_functor_, NT2_REAL_TYPES )
{
  using nt2::quadgk;
  using nt2::options;
  using nt2::integration::output;
  typedef typename nt2::meta::as_logical<T>::type lT;
  nt2::tic();
  BOOST_AUTO_TPL(res, (quadgk<T, T>(f(), T(0), T(1)))); //, options [nt2::range::waypoints_ = nt2::linspace(T(0), T(1), 5)])));
  nt2::toc();
  NT2_TEST(res.successful);
  std::cout << "Integrals:" << res.integrals(nt2::end_) << ") with error " << res.errors
            << " after " << res.eval_count <<  " evaluations\n";

}

// NT2_TEST_CASE_TPL( quadgk_functor_1, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef typename nt2::meta::as_logical<T>::type lT;

//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(ff(), T(0), nt2::Inf<T>())));
//   nt2::toc();

//   std::cout << "Integrals:" << res.integrals(nt2::end_) << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST(res.successful);
// }


// NT2_TEST_CASE_TPL( quadgk_cplx_out, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef typename nt2::meta::as_complex<T>::type cT;
//   typedef nt2::table<T> tab_t;
//   tab_t x =  nt2::linspace(-nt2::Pio_2<T>(), nt2::Pio_2<T>(), 2);
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<T, cT>(h(), -nt2::Pio_2<T>(), nt2::Pio_2<T>())));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_TEST(res.successful);
// }

// NT2_TEST_CASE_TPL( quadgk_cplx_inout, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef typename nt2::meta::as_complex<T>::type cT;
//   typedef nt2::table<cT> tab_t;
//   cT cx[] = { std::complex<T>(0, 0), std::complex<T>(1, 1),std::complex<T>(1, -1),std::complex<T>(0, 0)};
//   tab_t x(nt2::of_size(1, 4), &cx[0], &cx[4]);
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<cT, cT>(k(), x)));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_DISPLAY(nt2::Quadgkabstol<T>());
//   NT2_TEST_LESSER_EQUAL(nt2::dist(res.integrals(nt2::begin_), std::complex<T>(0, -nt2::Pi<T>())), nt2::Quadgkabstol<T>());
// }

// NT2_TEST_CASE_TPL( quadgk_cplx_inout2, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef typename nt2::meta::as_complex<T>::type cT;
//   typedef nt2::table<cT> tab_t;
//   cT cx[] = { std::complex<T>(0, 0), std::complex<T>(1, 1),std::complex<T>(1, -1),std::complex<T>(0, 0)};
//   tab_t x(nt2::of_size(1, 4), &cx[0], &cx[4]);
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<cT, cT>(k(), std::complex<T>(0, 0), std::complex<T>(0, 0),
//                                      options[nt2::range::waypoints_ =x,
//                                              nt2::range::return_waypoints_ = true//,
//                                        ] )));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_DISPLAY(nt2::Quadgkabstol<T>());
//   NT2_TEST_LESSER_EQUAL(nt2::dist(res.integrals(nt2::end_), std::complex<T>(0, -nt2::Pi<T>())), nt2::Quadgkabstol<T>());
// }

// NT2_TEST_CASE_TPL( quadgk_functor_cplx, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   typedef typename nt2::meta::as_complex<T>::type cT;
// //   tab_t x = nt2::_(T(0), T(5), T(5));
// //   tab_t x0= nt2::_(T(0), T(5), T(5));
// //  NT2_DISPLAY(x);
//   typedef nt2::table<cT> tab_t ;
//   cT cx[] = { cT(1, 1),cT(1, -1)};
//   tab_t x(nt2::of_size(1, 4), &cx[0], &cx[2]);

//   //output<tab_t,T>
// //  nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<cT, cT>(f(), cT(0), cT(0), options [nt2::range::waypoints_ = x])));

// //   nt2::toc();
//   std::cout << "Integrals:" << res.integrals(end_) << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

// //   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::sqr(T(5))*nt2::Half<T>())), T(1.0e-5));
// }



// NT2_TEST_CASE_TPL( quadgk_functor__, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(5), T(5));
//   tab_t x0= nt2::_(T(0), T(5), T(5));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(f(), T(0), T(5), options [ nt2::tolerance::abstol_ = T(1.0e-5),
//                                                               nt2::range::waypoints_ =x,
//                                                               nt2::range::return_waypoints_ = true]))); //nt2::_(T(0), T(5), T(5)) ]));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::sqr(x)*nt2::Half<T>())), T(1.0e-5));
// }

// NT2_TEST_CASE_TPL( quadgk_functorc, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(1), T(5));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(f(), T(0), T(5), options [ nt2::tolerance::abstol_ = T(1.0e-5),
//                                                               nt2::range::return_waypoints_ = true,
//                                                               nt2::range::waypoints_ = nt2::_(T(0), T(1), T(5)) ])));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::sqr(x)*nt2::Half<T>())), T(1.0e-5));
// }

// NT2_TEST_CASE_TPL( quadgk_functorb, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(5), T(5));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   nt2::tic();
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(f(), x, options [ nt2::tolerance::abstol_ = T(1.0e-5),
//                                                      nt2::range::return_waypoints_ = true])));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::sqr(x)*nt2::Half<T>())), T(1.0e-5));
// }

// NT2_TEST_CASE_TPL( quadgk_functor0, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   tab_t x = nt2::_(T(0), T(1), T(1));
//   nt2::tic();
//   output<tab_t,T> res =  (quadgk<T, T>(g(), x, options [ nt2::tolerance::abstol_ = T(1.0e-8),
//                                                        nt2::range::singular_a_ = true,
//                                                        nt2::range::singular_b_ = true]));
//   nt2::toc();
//   std::cout << "Integrals:" << res.integrals << ") with error " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::dist(res.integrals(nt2::end_), -nt2::log(T(2))), T(1.0e-7));


// }


// NT2_TEST_CASE_TPL( quadgk_tag, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(5));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(nt2::functor<nt2::tag::exp_>(), x)));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_DISPLAY(x);
//   NT2_DISPLAY(res.integrals);
//   NT2_DISPLAY(nt2::expm1(x));

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::expm1(T(5)))), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( quadgk_tag_r, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(5), T(-1), T(4));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(nt2::functor<nt2::tag::exp_>(), T(5), T(4))));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_DISPLAY(x);
//   NT2_DISPLAY(res.integrals);
//   NT2_DISPLAY( nt2::exp(x)-nt2::exp(T(5)));
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::exp(x(nt2::end_))-nt2::exp(T(5)))), nt2::Sqrteps<T>());
// }

// NT2_TEST_CASE_TPL( quadgk_tag_reverse, NT2_REAL_TYPES )
// {
//   using nt2::quadgk;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(5), T(-1), T(0));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   BOOST_AUTO_TPL(res, (quadgk<T, T>(nt2::functor<nt2::tag::exp_>(), x)));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";
//   NT2_DISPLAY(x);
//   NT2_DISPLAY(res.integrals);
//   NT2_DISPLAY( nt2::exp(x)-nt2::exp(T(5)));
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::exp(x(nt2::end_))-nt2::exp(T(5)))), nt2::Sqrteps<T>());
// }





