//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/geneig.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(geneig_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T>         cT;
  typedef nt2::table<cT>         t_t;
  T a0 =  nt2::One<T>();
  T a1 =  nt2::Two<T>();
  t_t s = nt2::geneig(a0);
  NT2_TEST_ULP_EQUAL(s,cT(a0),1);
  NT2_TEST_ULP_EQUAL(s,cT(a0/a1),1);
  typedef  nt2::table<T, nt2::_2D> t_t2d;
  t_t2d ta0 = a0,  ta1 = a1;
  typedef typename nt2::meta::call<nt2::tag::factorization::geneig_(t_t2d const&, t_t2d const&, char, char, char)>::type result_type;
  result_type f = nt2::factorization::geneig(ta0, ta1, 'V', 'V', 'S');
  t_t s1 = f.wr();
  NT2_TEST_ULP_EQUAL(s,s1,1);
}

NT2_TEST_CASE_TPL(geneig, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::geneig_;
  typedef nt2::table<T, nt2::_2D> t_t;
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
  t_t s = f.s();
  nt2::display("s    ", s);
  t_t t = f.t();
  nt2::display("vsr    ", vsr);
  //   (A,B) = ( (VSL)*S*(VSR)**T, (VSL)*T*(VSR)**T )
  NT2_TEST(nt2::isulpequal(a, nt2::mtimes(vsl, nt2::mtimes(s, nt2::trans(vsr))), T(10.0)));
  NT2_TEST(nt2::isulpequal(b, nt2::mtimes(vsl, nt2::mtimes(t, nt2::trans(vsr))), T(10.0)));

}

