//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - pow/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/toolbox/exponential/include/functions/pow.hpp>
#include <nt2/include/functions/ones.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( pow3,  NT2_REAL_TYPES)
{

  using nt2::exp;
  using nt2::tag::exp_;
  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::ones(3, 3, nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::ones(3, 3, nt2::meta::as_<cT>());
  NT2_DISPLAY(nt2::pow(a, b));
  NT2_TEST_EQUAL(nt2::pow(a, b), a);

}
NT2_TEST_CASE_TPL ( pow4,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::ones(1, 3, nt2::meta::as_<cT>());

  for(int i=1; i <= 3; i++) a(i) =  cT(i, i);
  NT2_DISPLAY(a);

  nt2::table<cT> b = nt2::ones(1, 3, nt2::meta::as_<T>());
  for(int i=1; i <= 3; i++) b(i) = cT(i-1);
  NT2_DISPLAY(b);

  NT2_DISPLAY(nt2::pow(a, b));
  nt2::table<cT> r(nt2::of_size(1, 3));  r(1) = cT(1,0); r(2) = cT(2,2); r(3) = cT(0,18);
  NT2_TEST_ULP_EQUAL(nt2::pow(a, b), r, 10.0);
}

