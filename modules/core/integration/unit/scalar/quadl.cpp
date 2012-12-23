//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - quadl"

#include <iostream>
#include <nt2/include/functions/quadl.hpp>
#include <nt2/toolbox/optimization/output.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/table.hpp>
struct f
{
  template < class X > inline
  X operator()(const X & x ) const
  {
    return x;
  }
};


NT2_TEST_CASE_TPL( quadl_functor, NT2_REAL_TYPES )
{
  using nt2::quadl;
  using nt2::options;
  using nt2::optimization::output;
  typedef nt2::table<T> tab_t;
  tab_t x = nt2::_(T(0), T(5), T(5));
  NT2_DISPLAY(x);
  BOOST_AUTO_TPL(res, quadl<T>(f(), T(0), T(5)));
//    std::cout << "Integrals:" << res.integrals << " with " << res.errors
//              << " after " << res.eval_count <<  " evaluations\n";

//    NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::sqr(x)*nt2::Half<T>())), nt2::Sqrteps<T>());


}

// NT2_TEST_CASE_TPL( quadl_tag, NT2_REAL_TYPES )
// {
//   using nt2::quadl;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(5));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   BOOST_AUTO_TPL(res, quadl<T>(nt2::functor<nt2::tag::exp_>(), x));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::expm1(x))), nt2::Sqrteps<T>());


// }
// NT2_TEST_CASE_TPL( quadl_tag_reverse, NT2_REAL_TYPES )
// {
//   using nt2::quadl;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(5), T(-1), T(0));
//   NT2_DISPLAY(x);
//   //output<tab_t,T>
//   BOOST_AUTO_TPL(res, quadl<T>(nt2::functor<nt2::tag::exp_>(), x));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, nt2::exp(x)-nt2::exp(T(5)))), nt2::Sqrteps<T>());


// }

// NT2_TEST_CASE_TPL( quadl_2, NT2_REAL_TYPES )
// {
//   using nt2::quadl;
//   using nt2::options;
//   using nt2::integration::output;
//   typedef nt2::table<T> tab_t;
//   typedef typename nt2::meta::as_logical<T>::type lT;
//   tab_t x = nt2::_(T(0), T(5), T(5));
//   NT2_DISPLAY(x);

//   BOOST_AUTO_TPL(res, quadl<T>(nt2::functor<nt2::tag::exp_>(), T(0), T(5)));
//   std::cout << "Integrals: " << res.integrals << " with " << res.errors
//             << " after " << res.eval_count <<  " evaluations\n";

//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::dist(res.integrals, expm1(x))), nt2::Sqrteps<T>());


// }

