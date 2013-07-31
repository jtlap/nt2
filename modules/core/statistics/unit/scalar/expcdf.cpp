//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/expcdf.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>

NT2_TEST_CASE_TPL ( expcdf_1,  NT2_REAL_TYPES)
{

  using nt2::expcdf;
  using nt2::tag::expcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::One<T>()),  T(0.63212055882855766598), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                 0.63212055882855766598, 0.86466471676338729768,
                                 0.9502129316321360486, 0.9816843611112657797,
                                 0.99326205300091452433);
  NT2_TEST_ULP_EQUAL(expcdf(a), r, 1);

} // end of test for floating_

NT2_TEST_CASE_TPL ( expcdf_2, NT2_REAL_TYPES)
{

  using nt2::expcdf;
  using nt2::tag::expcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::One<T>(), nt2::One<T>()),  T(0.63212055882855766598), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Inf<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r, plo, pup;
  nt2::table<T> r1 = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                  0.086899283717737654809, 0.15351827510938589882,
                                  0.20607734218204873389, 0.24852270692471406521,
                                  0.28346868942621072929);
  NT2_TEST_ULP_EQUAL(expcdf(a,a+T(10)), r1, 1);
  nt2::table<T> r2 = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                  0.39346934028736657574, 0.63212055882855766598,
                                  0.77686983985157020971, 0.86466471676338729768,
                                  0.91791500137610115839);
  NT2_TEST_ULP_EQUAL(expcdf(a, nt2::Two<T>()), r2, 1);
  nt2::table<T> r3 = nt2::cons<T>( 0.18126924692201815126, 0.15351827510938589882,
                                   0.13312210024981835366, 0.1175030974154046004,
                                   0.10516068318563022432, 0.095162581964040426907,
                                   0.086899283717737654809, 0.079955585370676748869,
                                   0.074038921357684028823, 0.06893722029597722234,
                                   0.064493014968382264551);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::One<T>(), a+T(10)), r3, 1);

  nt2::tie(r, plo, pup) = nt2::expcdf(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(0.5), T(0.05));
   nt2::table<T> rr = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                  0.63212055882855766598, 0.86466471676338729768, 0.9502129316321360486,
                                  0.9816843611112657797, 0.99326205300091452433);
   nt2::table<T> pplo = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.22127526565061650388, 0.3935877881124821287, 0.52777181139167061996,
                                   0.63226422927368808313, 0.71363505963038698088);
   nt2::table<T> ppup = nt2::cons<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.98165573262491157003, 0.99966348785447123326, 0.99999382693122740307,
                                   0.99999988675957596218, 0.99999999792268734478);
  NT2_TEST_ULP_EQUAL(r, rr, 1);
  NT2_TEST_ULP_EQUAL(plo, pplo, 2);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_

