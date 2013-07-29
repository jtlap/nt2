//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/exppdf.hpp>
#include <nt2/include/constants/invexp_1.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( exppdf_1, NT2_REAL_TYPES)
{

  using nt2::exppdf;
  using nt2::tag::exppdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::One<T>()),  nt2::Invexp_1<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Zero<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r =  nt2::cons<T>( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                                   0.36787944117144233402, 0.13533528323661270232, 0.049787068367863944462,
                                   0.018315638888734178669, 0.0067379469990854670008);
  NT2_TEST_ULP_EQUAL(exppdf(a), r, 1);
} // end of test for floating_

NT2_TEST_CASE_TPL ( exppdf_2,  NT2_REAL_TYPES)
{

  using nt2::exppdf;
  using nt2::tag::exppdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::One<T>(), nt2::One<T>()),   nt2::Invexp_1<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Inf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r =  nt2::cons<T>( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                                   0.36787944117144233402, 0.13533528323661270232, 0.049787068367863944462,
                                   0.018315638888734178669, 0.0067379469990854670008);
  NT2_TEST_ULP_EQUAL(exppdf(a), r, 1);
  NT2_TEST_ULP_EQUAL(exppdf(a, nt2::One<T>()), r, 1);
  nt2::table<T> r1 =  nt2::cons<T>(  0.033689734995427336739, 0.014872513059998150944, 0.0063831737588816135978,
                                    0.0026837010232200948258, 0.0011106882367801159967, 0.00045399929762484844686,
                                    0.00018371870869270226544, 7.3730548239938514289e-05, 2.9384282290753705114e-05,
                                    1.1641402067449950703e-05, 4.5885348075273863649e-06
                                 );
   NT2_TEST_ULP_EQUAL(exppdf(nt2::One<T>(), a+T(10)), r1, 1);
   a = nt2::reshape(_(T(1), T(16)), 4, 4);
   nt2::table<T> z = exppdf(a, a/T(10)+T(0.05));
   nt2::table<T> zz =  nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                               0.12910619646375867675, 0.035160323663689166396, 0.00018386784458018914446, 3.224523980484168886e-08,
                                               0.15163266492815835607, 0.013157242439772847895, 2.8913271817234518384e-05, 2.2140632307335824579e-09,
                                               0.12247821218890438122, 0.0039356387993860382501, 3.6886941271645263231e-06, 1.238753783407859502e-10,
                                               0.074384499699713946264, 0.00094670887566808208883, 3.8237790062728223237e-07, 5.6507959076111078999e-12
                                              ));
   NT2_TEST_ULP_EQUAL(z, zz, 5);
   a = _(T(-5), T(1), T(5));
   nt2::table<T> b = _(T(1), T(1), T(11));
  nt2::table<T> rr =  nt2::cons<T>( 0.0, 0.0, 0.0, 0.0, 0.0, 6.0,
                                    0.0063831737588816135978, 9.0028139775407293166e-07, 1.6915759348851748341e-11,
                                    4.248354255291588871e-17, 1.4295395675082535051e-23
                                  );
   NT2_TEST_ULP_EQUAL(exppdf(a, b), rr, 1);
} // end of test for floating_

