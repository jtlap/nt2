//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/deltac.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(deltac,  NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;

  nt2::table<cT> ref =  nt2::zeros(3, nt2::meta::as_<cT>());
  ref(2, 3) = cT(1.0);
  nt2::table<int> p(nt2::of_size(1, 2)); p(1) = p(2) = 3;
  nt2::table<cT> x0 = nt2::deltac(0, 2, nt2::of_size(3, 3), nt2::meta::as_<cT>());
  nt2::table<cT> x1 = nt2::deltac(1, 2, 3, nt2::meta::as_<cT>());

  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, 3, nt2::meta::as_<cT>()));
  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, 3, 3, nt2::meta::as_<cT>()));
  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, p, nt2::meta::as_<cT>()));
}
