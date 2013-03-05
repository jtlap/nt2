//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::multind "

#include <nt2/table.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  using nt2::_;
  using nt2::meta::as_;
  nt2::table<T> a(nt2::of_size(1, 10));
  nt2::table<T> b(nt2::of_size(1, 10));
  nt2::table<T> c(nt2::of_size(10, 1));

// Ca c'est ok -------------------------------------
  a = _(T(1), T(10));
  NT2_DISPLAY(a);
  a(_(1, 2, 10)) = T(1);
  NT2_DISPLAY(a);
  a(_(2, 2, 10)) = T(1);
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));
// fin ok ------------------------------------------
  typedef typename nt2::meta::as_integer<T>::type itype;
  // le reste ne passe pas,  décommente ce que tu veux
  nt2::table<itype> ind = _(itype(1), itype(10));
  NT2_DISPLAY(ind);
  a(ind) = T(1);
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));

  b = a;
  c = nt2::ones(10, 1, as_<T>());
  NT2_DISPLAY(ind);
  a(ind) = b;
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));

  NT2_DISPLAY(ind);
  a(ind) = b(ind);
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));

  NT2_DISPLAY(ind);
  a(_) = b(ind);
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));

  NT2_DISPLAY(ind);
  a(_) = b(ind);
  NT2_TEST_EQUAL(a, nt2::ones(1, 10, as_<T>()));

}
NT2_TEST_CASE_TPL( table_2, NT2_TYPES)
{
  using nt2::table;
  using nt2::_;
  using nt2::meta::as_;
  nt2::table<T> c = nt2::rif(6, 1, nt2::meta::as_<T>());
  typedef typename nt2::meta::as_integer<T>::type itype;
  nt2::table<itype> ind = ((itype(2)*_(itype(0), itype(10))) % itype(5)) + itype(1);
  // 1 3 5 2 4 1 3 5 2 4

  nt2::table<T> ci = c(ind);
  for(std::size_t i=1; i <= nt2::numel(ci); ++i)
    NT2_TEST_EQUAL(ci(i), c(ind(i)));
}
