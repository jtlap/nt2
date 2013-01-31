//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - degree"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/degree.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( degree_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::degree;
  using nt2::tag::degree_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(0), T(0), T(3));
  nt2::table<T> c(nt2::of_size(1, 0));
  NT2_DISPLAY(a);
  NT2_DISPLAY(degree(a));
  NT2_DISPLAY(b);
  NT2_DISPLAY(degree(b));
  NT2_TEST_EQUAL(3, degree(a));
  NT2_TEST_EQUAL(-1, degree(b));
  b(3) = T(1);
  NT2_TEST_EQUAL(0, degree(b));

} // end of test for floating_


