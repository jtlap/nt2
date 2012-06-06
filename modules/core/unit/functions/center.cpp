/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::center function"

#include <nt2/table.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/mean.hpp>

#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( center_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::center(T(42));
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::center(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::center(T(42),0);
  NT2_TEST_EQUAL( x, T(0) );
  
  x = nt2::center(nt2::Nan<T>(),1);
  NT2_TEST_EQUAL( x, nt2::Nan<T>() );

}

NT2_TEST_CASE_TPL( center, (float)(double))//NT2_TYPES )
{
  using nt2::_; 
  nt2::table<T> y( nt2::of_size(8, 4) );
  nt2::table<T> sy, m, z; 

  for(int j=1;j<=size(y, 2);j++)
    for(int i=1;i<=size(y, 1);i++)
      y(i,j) = i - j;

  sy = nt2::center(y, 2);
  NT2_DISP(y); 
  NT2_DISP(sy);

  m =  mean(y, 2);
  NT2_DISP(m);
  std::cout << " ================= " << std::endl;
  sy = nt2::center(y, 1);
  NT2_DISP(y); 
  NT2_DISP(sy);

  m =  mean(y, 1);
  NT2_DISP(m);
//   z =  nt2::bsxfun(nt2::functor<nt2::tag::minus_>(), y, m);
//   NT2_DISP(z);
  

  
//   sz = nt2::sum(nt2::abs(y)); 
//   for(int j=1;j<=size(y, 2);j++)
//       NT2_TEST_EQUAL(sz(j), sy(j));
//   sy = nt2::center(y, 1);
//   sz = nt2::sum(nt2::abs(y), 1); 
//   for(int j=1;j<=size(y, 2);j++)
//       NT2_TEST_EQUAL(sz(j), sy(j));
//   sy = nt2::center(y, 2);
//   sz = nt2::sum(nt2::abs(y), 2); 
//     for(int i=1;i<=size(y, 1);i++)
//       NT2_TEST_EQUAL(sz(i), sy(i));
//   sy = nt2::center(y, 3);
//   sz = nt2::sum(nt2::abs(y), 3); 
//   for(int j=1;j<=size(y, 2);j++)
//     for(int i=1;i<=size(y, 1);i++)
//       NT2_TEST_EQUAL(sz(i, j), sy(i, j));


}

