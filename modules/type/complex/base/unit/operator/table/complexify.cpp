//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/plus.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/constants/zero.hpp>


NT2_TEST_CASE_TPL( complexify1, NT2_REAL_TYPES )
{
  nt2::table<T> a0 = nt2::_(T(1), T(3));
  typedef typename nt2::meta::as_complex<T>::type cT;
  nt2::table<cT> ca0 = a0+nt2::Zero<cT>();
  NT2_TEST_EQUAL(ca0, complexify(a0));
  NT2_DISPLAY(complexify(nt2::_(T(1), T(3))));
  a0 = nt2::ones(3, 3, nt2::meta::as_<T>());
  ca0= a0+nt2::Zero<cT>();
  NT2_TEST_EQUAL(a0, nt2::real(complexify(a0)));

}
NT2_TEST_CASE_TPL( complexify2, NT2_REAL_TYPES )
{
  nt2::table<T>   a0 = nt2::ones(3, 3, nt2::meta::as_<T>());
  NT2_TEST_EQUAL(a0, real(complexify(a0)));
  NT2_TEST_EQUAL(complexify(a0), complexify(complexify(a0)));
}
NT2_TEST_CASE_TPL( complexify3, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_dry<T>::type dT;
  nt2::table<dT> a0 = nt2::ones(3, 3, nt2::meta::as_<dT>());
  NT2_TEST_EQUAL(a0, real(complexify(a0)));
  NT2_TEST_EQUAL(nt2::real(a0), nt2::real(complexify(a0)));
}

