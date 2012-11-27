/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::asump function"

#include <nt2/table.hpp>
#include <nt2/include/functions/asump.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/pow_abs.hpp>
#include <nt2/include/functions/pow.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( asump_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T>  cT;
  T x = nt2::asump(cT(42), T(2));
  NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

  x = nt2::asump(cT(42),T(2), 1);
  NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

  x = nt2::asump(cT(42),T(2), 2);
  NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

}

NT2_TEST_CASE_TPL( asump, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T>  cT;
  using nt2::_;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sz( nt2::of_size(1,3) );

  for(size_t j=1;j<=nt2::size(y, 2);j++)
    for(size_t i=1;i<=nt2::size(y, 1);i++)
      y(i,j) = cT(i + 10*j);

  sy = nt2::asump(y(_), nt2::Three<T>());
  display("rr", nt2::sum(nt2::pow_abs(y(_), nt2::Three<T>())));
  sz = nt2::sum(nt2::pow_abs(y(_), nt2::Three<T>()));
  std::cout << nt2::size(sy) << std::endl;
  std::cout << nt2::size(sz) << std::endl;
  std::cout << sy(1) << std::endl;
  std::cout << sz(1) << std::endl;
  NT2_TEST_ULP_EQUAL(sy(1), sz(1), 0.5);

}

