//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - frexp/table Mode"

#include <nt2/table.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE(frexp_table)
{
  typedef float T;
  typedef nt2::meta::as_integer<T>::type iT;

  nt2::table<T> v = nt2::linspace(T(1), T(5), 10);
  nt2::table<T> m(nt2::of_size(1, 10)), im(nt2::of_size(1, 10));
  nt2::table<iT> e(nt2::of_size(1, 10)), ie(nt2::of_size(1, 10));
  nt2::frexp(v, m, e);
  for(int i=1; i <= 10; ++i)
  {
    im(i) = nt2::frexp(v(i), ie(i));
  }
  NT2_TEST_EQUAL(m, im);
  NT2_TEST_EQUAL(e, ie);
}
