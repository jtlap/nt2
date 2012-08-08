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
#include <nt2/include/functions/adjfun.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/two.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

// NT2_TEST_CASE_TPL( adjfun_scalar, NT2_TYPES )
// {
//   nt2::functor<nt2::tag::plus_> f;
//   T x = nt2::adjfun(f, T(42));
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::adjfun(f, T(42),1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::adjfun(f, T(42),2);
//   NT2_TEST_EQUAL( x, T(42) );
// }

NT2_TEST_CASE_TPL( adjfun, (uint16_t)(int16_t))//NT2_TYPES )
{
  using nt2::_;
  using nt2::end_; 
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy1, sy2, sy3;
  nt2::table<T> ssy1, ssy2; 


  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = nt2::sqr(i + j);
  nt2::functor<nt2::tag::multiplies_> f;
  NT2_DISPLAY(y);
  
  sy = nt2::adjfun(f, y);
  NT2_DISPLAY(sy);
  ssy1 =  y(_(1, end_-1), _)*y(_(2, end_), _);
  NT2_TEST(nt2::isequal(sy, ssy1)); 
  //   NT2_TEST(nt2::isequal(sy, y(_(1, end_-1), _)*y(_(2, end_), _))); 
  sy1 = nt2::adjfun(f, y, 1);
  NT2_DISPLAY(sy1);
  //  NT2_TEST(nt2::isequal(sy1, y(_(1, end_-1), _)*y(_(2, end_), _))); 
  NT2_TEST(nt2::isequal(sy1, ssy1)); 
  sy2 = nt2::adjfun(f, y, 2);
  ssy2 =  y(_, _(1, end_-1))*y(_, _(2, end_)); 
  NT2_DISPLAY(sy2);
  NT2_DISPLAY(ssy2);
  NT2_TEST(nt2::isequal(sy2, ssy2)); 
  sy3 = nt2::adjfun(f, y, 3);
  NT2_DISPLAY(sy3);
  NT2_TEST(nt2::isempty(sy3)); 




}

