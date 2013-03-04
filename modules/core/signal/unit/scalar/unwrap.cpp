//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - unwrap"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/signal/include/functions/unwrap.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( unwrap_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::unwrap;
  using nt2::tag::unwrap_;
  typedef typename nt2::table<T> t_t;
  t_t r = nt2::_(T(0), T(100));
  t_t w = r - nt2::Twopi<T>()*nt2::floor((r+nt2::Pi<T>())/(nt2::Twopi<T>()));  // wrapped into [-pi,pi]
  NT2_DISPLAY(w);
  NT2_DISPLAY(unwrap(w));
  NT2_TEST_ULP_EQUAL(r, unwrap(w), 1);
  NT2_TEST_ULP_EQUAL(nt2::trans(r), unwrap(nt2::trans(w)), 1);
  NT2_TEST_ULP_EQUAL(nt2::cath(nt2::trans(r),nt2::trans(r)),unwrap(nt2::cath(nt2::trans(w),nt2::trans(w))), 1);
  NT2_TEST_ULP_EQUAL(nt2::catv(r, r), unwrap(nt2::catv(w, w), 2), 1);
  NT2_TEST_ULP_EQUAL(r+T(10), unwrap(w+T(10)), 1);
  NT2_TEST_EQUAL(nt2::trans(w),  unwrap(nt2::trans(w), 2));
  NT2_TEST_EQUAL(w, unwrap(w, 1));
  NT2_TEST_EQUAL(nt2::catv(w, w), unwrap(nt2::catv(w, w)));
} // end of test for floating_
