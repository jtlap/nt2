//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::inbtrue function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/is_not_nan.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( inbtrue_scalar, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T> cT;
  cT x = nt2::inbtrue(cT(1));
  NT2_TEST_EQUAL( x, cT(1) );

  x = nt2::inbtrue(cT(1),1);
  NT2_TEST_EQUAL( x, cT(1) );

  x = nt2::inbtrue(cT(1),2);
  NT2_TEST_EQUAL( x, cT(1)) ;

  x = nt2::inbtrue(cT(0),2);
  NT2_TEST_EQUAL( x, cT(0)) ;

}

NT2_TEST_CASE_TPL( inbtrue_expr, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::_;
  typedef typename nt2::meta::as_integer<T, unsigned>::type itype_t;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<cT> y1;
  nt2::table<itype_t> sy1, sy, sy2, sy3;
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (i > j) || (j == 2)|| (i == 1);
  sy  = nt2::inbtrue(y);
  sy  = nt2::inbtrue(y, 1);
  sy2 = nt2::cast<itype_t>(nt2::real(nt2::sum(y, 1)));
  NT2_TEST_EQUAL(sy2, sy);
  sy = nt2::inbtrue(y, 2);
  sy2 =  nt2::cast<itype_t>(nt2::real(nt2::sum(y, 2)));
  NT2_TEST_EQUAL(sy2, sy);
  sy = nt2::inbtrue(y, 3);
  sy2 =  nt2::cast<itype_t>(nt2::real(nt2::sum(y, 3)));
  NT2_TEST_EQUAL(sy2, sy);
//   sy = nt2::inbtrue(y(_));
//   sy2 =  nt2::cast<itype_t>(nt2::sum(y(_)));
//   NT2_TEST_EQUAL(sy2, sy);
 }


