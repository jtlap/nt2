/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function tie"

#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( forwarding, NT2_REAL_TYPES)
{
  using nt2::table;
  using nt2::of_size_;
  using boost::mpl::_;

  table<T> a = nt2::ones (4, 4, nt2::meta::as_<T>());
  table<T> h = nt2::zeros(6, 1, nt2::meta::as_<T>());
  table<T> m = nt2::zeros(6, 1, nt2::meta::as_<T>());
  NT2_DISPLAY(m);
  table<T> x = nt2::colvect(nt2::_(T(1), T(6)));
  table<T> g, l;
  BOOST_AUTO_TPL(p, nt2::cons(2, 3));
  tie(g,l) = nt2::planerot(x(p));
  m(p) = l;
  NT2_DISPLAY(m);
  //The folowing line does not compile
  tie(g,h(p)) = nt2::planerot(x(p));
  NT2_TEST_EQUAL(h, m);

}
