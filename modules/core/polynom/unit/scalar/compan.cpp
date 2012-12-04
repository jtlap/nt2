//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - compan/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
//#include <nt2/include/functions/polyder.hpp>
#include <nt2/include/functions/compan.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( compan_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  T cpc[] = {   -2,     1,     0,
                -3,     0,     1,
                -4,     0,     0 };
  nt2::table<T> cp(nt2::of_size(3, 3), &cpc[0], &cpc[9]);
  NT2_DISPLAY(compan(a));
  NT2_DISPLAY(cp);
  NT2_TEST(nt2::isequal(cp, compan(a)));
} // end of test for floating_

NT2_TEST_CASE_TPL ( compan_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(3));
  T cpc[] = {   -2,  1, -3, 0};
  nt2::table<T> cp(nt2::of_size(2, 2), &cpc[0], &cpc[4]);
  NT2_DISPLAY(compan(a));
  NT2_DISPLAY(cp);
  NT2_TEST(nt2::isequal(cp, compan(a)));
} // end of test for floating_

NT2_TEST_CASE_TPL ( compan_real__3_0,  NT2_REAL_TYPES)
{

  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(2));
  T cpc[] = {   -2  };
  nt2::table<T> cp(nt2::of_size(1, 1), &cpc[0], &cpc[1]);
  NT2_DISPLAY(compan(a));
  NT2_DISPLAY(cp);
  NT2_TEST(nt2::isequal(cp, compan(a)));
} // end of test for floating_




