/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/idx_linear.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <boost/fusion/include/make_vector.hpp>

NT2_TEST_CASE_TPL( idx_linear, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
  nt2::table<T> yi =nt2::idx_linear(x, xi);
  std::cout << "1 extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  yi =nt2::idx_linear(x, xi, false);
  std::cout << "2 extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "3 extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::idx_linear(x, xi, true);
  NT2_DISPLAY(yi);
  T z =  T(33);
  std::cout << "4 extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::idx_linear(x, xi, z);
  NT2_DISPLAY(yi);
  std::cout << "5 extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::idx_linear(x, xi, T(33));
  NT2_DISPLAY(yi);
  std::cout << "6 extrap " <<  "-" <<  " extrapval1 " << "33" <<  " extrapval1 " << "42"<< std::endl;
  yi =nt2::idx_linear(x, xi, T(33), T(42));
  NT2_DISPLAY(yi);
}


NT2_TEST_CASE_TPL( idx_linear2, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4);
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
  nt2::table<T> yi;
  yi =nt2::idx_linear(x, xi, _, 2lu);
  std::cout << "1 extrap " <<  false <<  " extrapval " << "-" <<  " dim " << "2" << std::endl;
  NT2_DISPLAY(yi);
  yi =nt2::idx_linear(x, nt2::trans(xi), _, 1lu);
  std::cout << "2 extrap " <<  false <<  " extrapval " << "-" <<  " dim " << "1" << std::endl;
  NT2_DISPLAY(yi);
  yi =nt2::idx_linear(x, xi, _, 1lu);
  std::cout << "3 extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);

  yi =nt2::idx_linear(x, xi, false);
  std::cout << "4 extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);

  yi =nt2::idx_linear(x, xi, false, _, 1);
  std::cout << "5 extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);

  std::cout << "6 extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::idx_linear(x, xi, true, _, 1);
  NT2_DISPLAY(yi);

  std::cout << "7 extrap " <<  "-" <<  " extrapval1 " << "33" <<  " extrapval2 " << "42" << std::endl;
  yi =nt2::idx_linear(x, xi, T(33), T(42), 1);
  NT2_DISPLAY(yi);

     /*     //   std::cout << "8 extrap " <<  "-" <<  " extrapval1 " << "33" <<  " extrapval2 " << "42" << std::endl;
     //   typedef boost::fusion::vector<T,T>  result_type;
     //   result_type a =  boost::fusion::make_vector(T(-3), T(25));
     //   std::cout << boost::fusion::at_c<0>(a) << std::endl;
     //   std::cout << boost::fusion::at_c<1>(a) << std::endl;
     //   yi =nt2::idx_linear(x, xi, a);
     //   NT2_DISPLAY(yi);

     //   std::cout << "9 extrap " <<  "-" <<  " extrapval1 " << "33" <<  " extrapval2 " << "42" << std::endl;
     //   nt2::table<T>   a(nt2::of_size(1, 2));
     //   a(1) = T(-3);  a(2) = T(25);
     //   yi =nt2::idx_linear(x, xi, a);
     //   NT2_DISPLAY(yi);
     */
 }

NT2_TEST_CASE_TPL( idx_linear1, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(3), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
  nt2::table<T> y0, yi;
  y0 =nt2::idx_linear(x, xi);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(y0);
  yi =nt2::idx_linear(x, xi, false);
  NT2_TEST(isequal(y0, yi));
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::idx_linear(x, xi, true);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  T z =  T(33);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::idx_linear(x, xi, z);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::idx_linear(x, xi, T(33));
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
}
