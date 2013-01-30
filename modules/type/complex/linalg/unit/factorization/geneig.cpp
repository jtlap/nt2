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
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL(geneig2, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::geneig_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef std::complex<T> cT;
  typedef nt2::table<cT, nt2::_2D > ct_t;
  typedef nt2::table<T, nt2::_2D> t_t;
  typedef nt2::table<itype_t, nt2::_2D> it_t;
  typedef typename nt2::meta::call<geneig_(ct_t const&, ct_t const&, char, char, char)>::type result_type;
  ct_t a =       nt2::ones (4, 4, nt2::meta::as_<cT>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<cT>());
  ct_t b =  nt2::eye(4,4, nt2::meta::as_<cT>());
  nt2::display("a     ", a);
  nt2::display("b     ", b);
  result_type f = nt2::factorization::geneig(a, b, 'V', 'V', 'S');
  nt2::display("values", f.values());
  ct_t eigen  = f.eigen();
  nt2::display("eigen    ", eigen);
  ct_t w  = f.w();
  nt2::display("w    ", w);
//   t_t wi  = f.wi();
//   nt2::display("wi    ", wi);
  ct_t vsl = f.vl();
  nt2::display("vsl    ", vsl);
  ct_t vsr = f.vr();
  nt2::display("vsr    ", vsr);
  ct_t s = f.s();
  nt2::display("s    ", s);
  ct_t t = f.t();
  nt2::display("t    ", t);
//   //   (A,B) = ( (VSL)*S*(VSR)**T, (VSL)*T*(VSR)**T )
  NT2_TEST(nt2::isulpequal(a, nt2::mtimes(vsl, nt2::mtimes(s, nt2::trans(vsr))), T(10.0)));
  NT2_TEST(nt2::isulpequal(b, nt2::mtimes(vsl, nt2::mtimes(t, nt2::trans(vsr))), T(10.0)));

}
