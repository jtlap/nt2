//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - lognpdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/lognpdf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/constants/invsqrt_2pi.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( lognpdf_1,  NT2_REAL_TYPES)
{

  using nt2::lognpdf;
  using nt2::tag::lognpdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::One<T>()), T(3.989422804014327e-01), 0.5);
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::Mone<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::Inf<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(lognpdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( lognpdf_2,  NT2_REAL_TYPES)
{

  using nt2::lognpdf;
  using nt2::tag::lognpdf_;
  using nt2::_;
  nt2::table<T> a = _(T(0), T(1), T(10));
  nt2::table<T> r = nt2::cons<T>(0,                         2.419707245191434e-01,     1.902978048101056e-01,     1.323357515290211e-01,
                                 9.256496459388702e-02,     6.626564240615490e-02,     4.859962175189118e-02,     3.643513628744858e-02,
                                 2.784847432889856e-02,     2.164812453532450e-02 ,    1.707930831120357e-02);
  NT2_TEST_ULP_EQUAL(lognpdf(a, nt2::One<T>()), r, 1);
  a = nt2::trans(nt2::reshape(_(T(1), T(16)), 4, 4)/T(16));
  nt2::table<T> r1 = nt2::cons<T>(1.147253988135605e-01,     4.297462418871077e-01,     3.712269069024686e-01,     2.918132225401633e-01,
                                  2.810343860453922e-01,     4.243291779586457e-01,     3.504800902440171e-01,     2.741787739903252e-01,
                                  3.762470302383745e-01,     4.101084293290096e-01,     3.300957398696542e-01,     2.575759602831477e-01,
                                  4.183763928770736e-01,     3.915698160252086e-01,     3.104760536456558e-01,     2.419707245191434e-01
                                 );

  NT2_TEST_ULP_EQUAL(lognpdf(a, a), r1, 1.5);
} // end of test for floating_

