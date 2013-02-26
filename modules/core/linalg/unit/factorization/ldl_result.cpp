//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - ldl_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/ldl.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(ldl_result, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::tag::factorization::ldl_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t a =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  NT2_DISPLAY(a);
  nt2::details::ldl_result<t_t> f('L', a);
  NT2_DISPLAY(f.values());
  NT2_DISPLAY(f.original());
  NT2_DISPLAY(f.ipiv());
  NT2_DISPLAY(f.status());
  NT2_DISPLAY(f.l());
  NT2_DISPLAY(a);
  t_t l = f.l();
  t_t inv_l = nt2::inv(l);
  t_t z = nt2::diagonal(nt2::mtimes(nt2::mtimes(inv_l, a), nt2::trans(inv_l)));
  NT2_TEST_ULP_EQUAL(a, nt2::mtimes(nt2::mtimes(l, z), nt2::trans(l)), 4);
}

