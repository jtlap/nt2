//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/expinv.hpp>
#include <nt2/include/functions/expcdf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( expinv_1,  NT2_REAL_TYPES)
{

  using nt2::expinv;
  using nt2::tag::expinv_;
  using nt2::_;
  using nt2::container::table;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expinv(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::One<T>()),  nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Half<T>()),  nt2::Log_2<T>(), 0);

  table<T> a = _(T(0), T(0.5), T(5))/T(5);
  NT2_TEST_ULP_EQUAL(a, nt2::expcdf(expinv(a)), T(3));

  table<T> b = _(T(0), T(0.5), T(10))/T(5);
  NT2_TEST_ULP_EQUAL(b, nt2::expinv(nt2::expcdf(b)), T(3));
} // end of test for floating_

NT2_TEST_CASE_TPL ( expinv_2, NT2_REAL_TYPES)
{

  using nt2::expinv;
  using nt2::tag::expinv_;
  using nt2::_;
  using nt2::container::table;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expinv(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Zero<T>(), nt2::One<T>() ), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::One<T>(), nt2::One<T>()),   nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Half<T>(), nt2::One<T>()), nt2::Log_2<T>(), 0);
  table<T> a = _(T(0), T(1), T(10))/T(10);
  table<T> r, plo, pup;
  a = nt2::reshape(_(T(1), T(16)), 4, 4)/T(16);
  table<T> z = expinv(a, a+T(10));
  table<T> zz = nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                             0.64941886894681000175, 3.8640261973645477767, 8.7317924292609419012, 18.099870187993698067,
                                             1.3520053503232916103, 4.8762876534245069848, 10.42131081324959041, 22.61392676576821259,
                                             2.1153260286783659438, 6.0053632624309258858, 12.431174279798213433, 30.325189149497607133,
                                             2.9487412426307542113, 7.2780453958794257829, 14.902664382038823376, nt2::Inf<double>()
                                            ));
  NT2_TEST_ULP_EQUAL(z, zz, 1);
  a = _(T(0), T(1), T(10))/T(10);
  table<T> b = _(T(1), T(1), T(11));
  nt2::tie(r, plo, pup) = nt2::expinv(a, nt2::ones(nt2::size(a), nt2::meta::as_<T>()), T(0.5), T(0.05));
  table<T> rr =  nt2::cons<T>(0.0, 0.10536051565782630912, 0.22314355131420976486,
                              0.35667494393873239167, 0.51082562376599072174, 0.69314718055994528623,
                              0.91629073187415499557, 1.2039728043259358969, 1.6094379124341005038,
                              2.3025850929940459011, nt2::Inf<double>());
  table<T> pplo = nt2:: cons<T>(0.0, 0.026350417712275989168, 0.055807678523765377743,
                                0.08920356645568566778, 0.12775628972890218371, 0.17335448322176297276,
                                0.22916216174552833662, 0.30111077295066512871, 0.40251664496729139264,
                                0.57587112818905439315, nt2::Inf<double>());
  table<T> ppup =  nt2::cons<T>(0.0,0.42127750614410425234, 0.89222569026793119296, 1.4261427058176698868,
                                2.0425046661078845034, 2.7715061358037331729, 3.6637318260716642548,
                                4.8140108019116167881, 6.4352379618753978718, 9.2067440976791310447,
                                nt2::Inf<double>());
  NT2_TEST_ULP_EQUAL(r, rr, 1);
  NT2_TEST_ULP_EQUAL(plo, pplo, 2);
  NT2_TEST_ULP_EQUAL(pup, ppup, 2);
  r =  nt2::expinv(a, nt2::ones(nt2::size(a), nt2::meta::as_<T>()), T(0.5), T(0.05));
  rr =  nt2::cons<T>(0.0,0.10536051565782630912, 0.22314355131420976486, 0.35667494393873239167,
                     0.51082562376599072174, 0.69314718055994528623, 0.91629073187415499557,
                     1.2039728043259358969, 1.6094379124341005038, 2.3025850929940459011,
                     nt2::Inf<double>());
  NT2_TEST_ULP_EQUAL(r, rr, 1);
} // end of test for floating_
