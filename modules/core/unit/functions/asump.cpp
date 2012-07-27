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

// NT2_TEST_CASE_TPL( asump_scalar, (float)(double))//NT2_TYPES )
// {
//   T x = nt2::asump(T(42), T(2));
//   NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

//   x = nt2::asump(T(42),T(2), 1);
//   NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

//   x = nt2::asump(T(42),T(2), 2);
//   NT2_TEST_EQUAL( x, nt2::pow(T(42), T(2)) );

// }

NT2_TEST_CASE_TPL( asump, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sz( nt2::of_size(1,3) );

  for(size_t j=1;j<=nt2::size(y, 2);j++)
    for(size_t i=1;i<=nt2::size(y, 1);i++)
      y(i,j) = i + 10*j;

//   sy = nt2::asump(y, nt2::Three<T>());
//   sz = nt2::asum(nt2::pow_abs(y, nt2::Three<T>()));
//   display("y", y);
//   display("sy", sy);
//   display("sz", sz);
//   for(int j=1;j<=nt2::size(y, 2);j++)
//       NT2_TEST_EQUAL(sz(j), sy(j));

//   sy = nt2::asump(y, T(nt2::Three<T>()), 1);
//   sz = nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 1);
//   display("y", y);
//   display("sy", sy);
//   display("sz", sz);

//   for(size_t j=1;j<=nt2::size(y, 2);j++)
//       NT2_TEST_EQUAL(sz(j), sy(j));
//   sy = nt2::asump(y, nt2::Three<T>(), 2);
//   sz = nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 2);
//   display("y", y);
//   display("sy", sy);
//   display("sz", sz);

//   for(int i=1;i<=size(y, 1);i++)
//     NT2_TEST_EQUAL(sz(i), sy(i));

//   sy = nt2::asump(y, nt2::Three<T>(), 3);
//   sz = nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 3);
//   display("y", y);
//   display("sy", sy);
//   display("sz", sz);

//   for(int j=1;j<=3;j++)
//     for(int i=1;i<=5;i++)
//       NT2_TEST_EQUAL(sz(i, j), sy(i, j));

  sy = nt2::asump(y(_), nt2::Three<T>());
  display("rr", nt2::sum(nt2::pow_abs(y(_), nt2::Three<T>())));
  //  display("asump(zy(_), 3)", sy);
  sz = nt2::sum(nt2::pow_abs(y(_), nt2::Three<T>()));
  std::cout << nt2::size(sy) << std::endl;
  std::cout << nt2::size(sz) << std::endl;
  std::cout << sy(1) << std::endl;
  std::cout << sz(1) << std::endl;
  NT2_TEST_EQUAL(sy(1), sz(1));
  //  nt2::table<T> zut =  y(_);
//   sy = nt2::asump(zut, nt2::Three<T>());
//   sz = nt2::sum(nt2::pow_abs(zut, nt2::Three<T>()));
//   std::cout << size(sy) << std::endl;
//   std::cout << size(sz) << std::endl;
//   std::cout << sy(1) << std::endl;
//   std::cout << sz(1) << std::endl;
//   //  display("asump(zut, 3)", sy)
//   NT2_TEST_EQUAL(sy(1), sz(1));


}

