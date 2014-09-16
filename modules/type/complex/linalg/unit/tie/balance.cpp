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
#include <nt2/include/functions/balance.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/options.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <complex>


NT2_TEST_CASE_TPL ( balance_exprc, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_integer<T, signed>::type iT;
  typedef nt2::table<cT> ct_t;
  typedef nt2::table<iT> it_t;

  T bc[25] =  {
    1.0, 2.0, 0., 0., 0.,
    0. , 2.0, 0., 0., 0.,
    1.,  100.,  10000., 4., 0.2,
    .01,  1.,  100., 0.2, 0.1,
    .0001,  .01,  1., 0., 0.000
  };

  int k = 0;
  ct_t a(nt2::of_size(5, 5));
  for(int i=1; i <= 5; i++)
    {
      for(int j=1; j <= 5; j++)
        {
          a(i, j) = bc[k++];
        }

    }
  NT2_DISPLAY(a);
  ct_t t, b, zz, b1;
  ct_t s;
  it_t ip;
  b = nt2::balance(a);
  b = nt2::balance(a, nt2::no_perm_);
  b = nt2::balance(a, nt2::perm_);
  b = nt2::balance(a, nt2::both_);
  b = nt2::balance(a, nt2::none_);



  tie(t, b) = nt2::balance(a);
  zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), a), t);
  NT2_TEST_ULP_EQUAL(zz, b, 10);

  tie(t, b) = nt2::balance(a, nt2::no_perm_);
  zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), a), t);
  NT2_TEST_ULP_EQUAL(zz, b, 10);

  tie(t, b) = nt2::balance(a, nt2::perm_);
  zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), a), t);
  NT2_TEST_ULP_EQUAL(zz, b, 10);

  tie(t, b) = nt2::balance(a, nt2::both_);
  zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), a), t);
  NT2_TEST_ULP_EQUAL(zz, b, 10);

  tie(t, b) = nt2::balance(a, nt2::none_);
  zz = nt2::mtimes(nt2::mtimes(nt2::inv(t), a), t);
  NT2_TEST_ULP_EQUAL(zz, b, 10);

  std::cout << "nt2::balance(a, nt2::none_);" << std::endl;
  nt2::tie(s, ip, b) = nt2::balance(a, nt2::none_);
  NT2_TEST_ULP_EQUAL(a, b, 10);
  iT n = height(a);
  NT2_TEST_ULP_EQUAL(s, nt2::ones(n, 1, boost::dispatch::meta::as_<cT>()), 0);
  NT2_TEST_ULP_EQUAL(ip, nt2::_(iT(1), n), 0);

  std::cout << "nt2::balance(a);" << std::endl;
  nt2::tie(s, ip, b) = nt2::balance(a);
  nt2::tie(t, b1) = nt2::balance(a);
  NT2_TEST_ULP_EQUAL(t(nt2::_, ip), from_diag(s), 0);
  NT2_TEST_ULP_EQUAL(b(ip, ip), mtimes(mtimes(from_diag(nt2::One<T>()/s), a), from_diag(s)), 0.5);

  std::cout << "nt2::balance(a, nt2::perm_);" << std::endl;
  nt2::tie(s, ip, b) = nt2::balance(a, nt2::perm_);
  nt2::tie(t, b1) = nt2::balance(a, nt2::perm_);
  NT2_TEST_ULP_EQUAL(t(nt2::_, ip), from_diag(s), 0);
  NT2_TEST_ULP_EQUAL(b(ip, ip), mtimes(mtimes(from_diag(nt2::One<T>()/s), a), from_diag(s)), 0.5);

  std::cout << "nt2::balance(a, nt2::no_perm_);" << std::endl;
  nt2::tie(s, ip, b) = nt2::balance(a, nt2::no_perm_);
  nt2::tie(t, b1) = nt2::balance(a, nt2::no_perm_);
  NT2_TEST_ULP_EQUAL(t(nt2::_, ip), from_diag(s), 0);
  NT2_TEST_ULP_EQUAL(b(ip, ip), mtimes(mtimes(from_diag(nt2::One<T>()/s), a), from_diag(s)), 0.5);

}
