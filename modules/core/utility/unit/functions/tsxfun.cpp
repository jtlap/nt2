//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::tsxfun function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tsxfun.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( tsxfun_1, NT2_TYPES)
{
  nt2::table<T> a = nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<T>()),
    b = nt2::cif(nt2::of_size(1, 3), nt2::meta::as_<T>()),
    c = nt2::ones(3, 3, nt2::meta::as_<T>()),
    d, e;
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(c);

  d = nt2::bsxfun(nt2::functor<nt2::tag::plus_>(), nt2::bsxfun(nt2::functor<nt2::tag::multiplies_>(), a, b), c);
  e = tsxfun(nt2::functor<nt2::tag::fma_>(), a, b, c);
  NT2_TEST_EQUAL(e, d);
}


NT2_TEST_CASE_TPL( tsxfun_4, NT2_TYPES)
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(6)),2, 1, 3);
  nt2::table<T> b = nt2::reshape(nt2::_(T(7), T(12)),1, 2, 1, 3);
  nt2::table<T> c = nt2::reshape(nt2::_(T(7), T(12)),2, 1, 1, 3);
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(c);

  nt2::table<T> d = nt2::bsxfun(nt2::functor<nt2::tag::plus_>(), nt2::bsxfun(nt2::functor<nt2::tag::multiplies_>(), a, b), c);
  nt2::table<T> e = tsxfun(nt2::functor<nt2::tag::fma_>(), a, b, c);
  NT2_TEST_EQUAL(e, d);

}
