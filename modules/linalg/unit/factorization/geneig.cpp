//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - geneig_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/geneig.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(geneig, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::geneig_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  typedef typename nt2::meta::call<geneig_(t_t const&, t_t const&, char, char, char)>::type result_type;
  t_t a =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  t_t b =  nt2::eye(4,4, nt2::meta::as_<T>());
  nt2::display("a     ", a);
  nt2::display("b     ", b);
  result_type f = nt2::factorization::geneig(a, b, 'V', 'V', 'S');
  nt2::display("values", f.values());
  t_t wr  = f.wr();
  nt2::display("wr    ", wr);
  t_t wi  = f.wi();
  nt2::display("wi    ", wi);
  t_t vsl = f.vl();
  nt2::display("vsl    ", vsl);
  t_t vsr = f.vr();
  nt2::display("vsr    ", vsr);

}
