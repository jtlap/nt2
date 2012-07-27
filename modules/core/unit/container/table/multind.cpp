/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::multind "

#include <nt2/table.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  using nt2::_;
  using nt2::meta::as_; 
  typedef T r_t;
  nt2::table<T> a(nt2::of_size(1, 10));
  nt2::table<T> b(nt2::of_size(1, 10));
  nt2::table<T> c(nt2::of_size(10, 1));

// Ca c'est ok -------------------------------------
//   a = _(T(1), T(10));
//   NT2_DISPLAY(a); 
//   a(_(1, 2, 10)) = T(1);
//   NT2_DISPLAY(a); 
//   a(_(2, 2, 10)) = T(1);
//   NT2_DISPLAY(a);
//   NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));
// fin ok ------------------------------------------

  // le reste ne passe pas,  décommente ce que tu veux
  nt2::table<int> ind = _(1, 10);
  NT2_DISPLAY(ind);
  a(ind) = T(1);
  NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));

//   b = a;
//   c = nt2::ones(10, 1, as_<T>())
//   nt2::table<int> ind = _(1, 10);
//   NT2_DISPLAY(ind);
//   a(ind) = b;
//   NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));

//   nt2::table<int> ind = _(1, 10);
//   NT2_DISPLAY(ind);
//   a(ind) = b(ind);
//   NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));
  
//   nt2::table<int> ind = _(1, 10);
//   NT2_DISPLAY(ind);
//   a(_) = b(ind);
//   NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));
  
//   nt2::table<int> ind = _(1, 10);
//   NT2_DISPLAY(ind);
//   a(_) = b(ind);
//   NT2_TEST(isequal(a, nt2::ones(1, 10, as_<T>())));

}
