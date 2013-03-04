//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 exponential toolbox - pow_abs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/toolbox/exponential/include/functions/pow_abs.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/real.hpp>
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

NT2_TEST_CASE_TPL ( pow_abs3,  NT2_REAL_TYPES)
{

  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::ones(3, 3, nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::ones(3, 3, nt2::meta::as_<cT>());
  NT2_DISPLAY(nt2::pow_abs(a, b));
  NT2_TEST_EQUAL(a, nt2::pow_abs(a, b));

}
NT2_TEST_CASE_TPL ( pow_abs4,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::ones(1, 3, nt2::meta::as_<cT>());

  for(int i=1; i <= 3; i++) a(i) =  cT(i, i);
  NT2_DISPLAY(a);

  nt2::table<T> b = T(2)*nt2::ones(1, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(b);

  NT2_DISPLAY(nt2::pow_abs(a, b));
  NT2_TEST_ULP_EQUAL(nt2::pow_abs(a, b), T(2)*nt2::sqr(nt2::real(a)), T(2.0));
}


