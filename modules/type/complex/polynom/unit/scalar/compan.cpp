//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/compan.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/complexify.hpp>


NT2_TEST_CASE_TPL ( compan_real__1_0,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<cT, nt2::_2D> a = nt2::complexify(nt2::_(T(1), T(4)));
  cT cpc[] = {cT(-2),     cT(1),     cT(0),
              cT(-3),     cT(0),     cT(1),
              cT(-4),     cT(0),     cT(0) };
  nt2::table<cT> cp(nt2::of_size(3, 3), &cpc[0], &cpc[9]);
  NT2_TEST_EQUAL(cp, compan(a));
}

NT2_TEST_CASE_TPL ( compan_real__2_0,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<cT, nt2::_2D> a =  nt2::complexify(nt2::_(T(1), T(3)));
  cT cpc[] = {cT(-2),  cT(1), cT(-3), cT(0)};
  nt2::table<cT> cp(nt2::of_size(2, 2), &cpc[0], &cpc[4]);
  NT2_TEST_EQUAL(cp, compan(a));
}

NT2_TEST_CASE_TPL ( compan_real__3_0,  NT2_REAL_TYPES)
{

  typedef std::complex<T> cT;
  using nt2::compan;
  using nt2::tag::compan_;
  nt2::table<cT, nt2::_2D> a =  nt2::complexify(nt2::_(T(1), T(2)));
  cT cpc[] = {   cT(-2)  };
  nt2::table<cT> cp(nt2::of_size(1, 1), &cpc[0], &cpc[1]);
  NT2_TEST_EQUAL(cp, compan(a));
}




