//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/remquo.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/linspace.hpp>

#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(remquo_table, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T>::type iT;

  // Reference values
  nt2::table<T>   v = nt2::rowvect(nt2::cons(T(1),T(2),T(3),T(4.5),T(7.1)));
  nt2::table<T>   im(nt2::extent(v));
  nt2::table<iT>  ie(nt2::extent(v));

  std::size_t nb = nt2::numel(v);

  for(std::size_t i=1; i <= nb; ++i)
  {

    im(i) = nt2::remquo(v(i), T(i*2), ie(i));
  }

  {
    // -1 to test resizing works properly
    nt2::table<T>   m(nt2::of_size(nb-1));
    nt2::table<iT>  e(nt2::of_size(nb));

    nt2::remquo(v,nt2::linspace(T(2),T(10),nb),m,e);
    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T>   m(nt2::of_size(nb-1));
    nt2::table<iT>  e(nt2::of_size(nb));

    m = remquo(v, nt2::linspace(T(2),T(10),nb), e);
    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T>   m(nt2::of_size(nb-1));
    nt2::table<iT>  e(nt2::of_size(nb));

    nt2::tie(m, e) = nt2::remquo(v,nt2::linspace(T(2),T(10),nb));

    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T>   m(nt2::of_size(nb-1));

    m = nt2::remquo(v,nt2::linspace(T(2),T(10),nb));
    NT2_TEST_EQUAL(m, im);
  }
}
