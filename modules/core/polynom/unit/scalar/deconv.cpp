//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynom toolbox - deconv"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/deconv.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/polyadd.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( deconv_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::deconv;
  using nt2::tag::deconv_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  nt2::table<T, nt2::_2D> b =  nt2::_(T(1), T(2));
  nt2::table<T, nt2::_2D> c(nt2::of_size(1, 0));
  nt2::table<T, nt2::_2D> q1, q, r;
  nt2::tie(q, r) = deconv(a, b);

  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  NT2_DISPLAY(nt2::conv(b, q));
  NT2_TEST_ULP_EQUAL(polyadd(conv(b, q), r), a, 0.5);
  q1 =  deconv(a, b);
  NT2_TEST_ULP_EQUAL(q, q1, 0.5);

} // end of test for floating_


