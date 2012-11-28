/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::dot function"

#include <nt2/table.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests.hpp>
NT2_TEST_CASE_TPL( dot_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T>  cT;
  cT x = nt2::dot(cT(42), cT(42));
  NT2_TEST_EQUAL( x, nt2::sqr(cT(42)) );

  x = nt2::dot(cT(42), cT(42),1);
  NT2_TEST_EQUAL( x, nt2::sqr_abs(cT(42)) );

  x = nt2::dot(cT(42), cT(42),2);
  NT2_TEST_EQUAL( x, nt2::sqr_abs(T(42)) );

}

NT2_TEST_CASE_TPL( dot, NT2_REAL_TYPES )
{
  typedef std::complex<T>  cT;
  using nt2::_;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<cT> sy;
  nt2::table<cT> sz;


  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = cT(T(i) - T(j), T(i)-T(j));

  sy = nt2::dot(y, y);
  sz = nt2::sum(nt2::multiplies(y, conj(y)));
  for(size_t j=1;j<=size(y, 2);j++)
    NT2_TEST_EQUAL(sz(j), sy(j));
  NT2_TEST_ULP_EQUAL(sy, sz, 1);

  sy = nt2::dot(y, y, 1);
  sz = nt2::sum(nt2::multiplies(y, conj(y)), 1);
  for(size_t j=1;j<=size(y, 2);j++)
    NT2_TEST_EQUAL(sz(j), sy(j));
  NT2_TEST_ULP_EQUAL(sy, sz, 1);

  sy = nt2::dot(y, y, 2);
  sz = nt2::sum(nt2::multiplies(y, conj(y)), 2);
  for(size_t i=1;i<=size(y, 1);i++)
    NT2_TEST_EQUAL(sz(i), sy(i));
  NT2_TEST_ULP_EQUAL(sy, sz, 1);

  sy = nt2::dot(y, y, 3);
  sz = nt2::sum(nt2::multiplies(y, conj(y)), 3);
  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i, j));
  NT2_TEST_ULP_EQUAL(sy, sz, 1);

  sy = nt2::dot(y(_), y(_));
  sz = nt2::sum(nt2::sqr_abs(y(_)));
  display(y(_));
  display(sy);
  display(sz);
  NT2_TEST_EQUAL(sy(1), sz(1));


}

