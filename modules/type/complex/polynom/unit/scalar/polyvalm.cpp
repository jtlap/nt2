//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polyvalm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>
#include <complex>
#include <nt2/include/functions/complexify.hpp>


NT2_TEST_CASE_TPL ( polyvalm_real__1_0,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::polyvalm;
  using nt2::tag::polyvalm_;
  nt2::table<cT> p =  nt2::_(T(1), T(4));
  nt2::table<cT> a =  nt2::eye(3, nt2::meta::as_<T>());
  NT2_TEST_EQUAL(polyvalm(p, a), T(10)*a);
  nt2::table<cT> b = T(15)*nt2::eye(2, nt2::meta::as_<cT>());
  b(2) = b(3) = T(11);
  nt2::table<cT> c =  nt2::ones(2, nt2::meta::as_<cT>());
  NT2_TEST_EQUAL(polyvalm(p, c), b);
}

