//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/flipdim.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( flipdim_scalar, NT2_TYPES )
{
  typedef std::complex<T> cT;
  cT x = nt2::flipdim(cT(42), 2);
  NT2_TEST_EQUAL( x, cT(42) );
}

NT2_TEST_CASE_TPL( flipdim, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = cT(i + 10*j);

  x = nt2::flipdim(y, 2);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( x(i,j),y(i,4-j) );
}

NT2_TEST_CASE_TPL( flipud, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x,x2,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = cT(i + 10*j);

  x = nt2::flipdim(y, 1);
  x2 = nt2::flipdim(y, 1)(nt2::_);

  for(int j=1;j<=3;j++)
  {
    for(int i=1;i<=5;i++)
    {
      NT2_TEST_EQUAL( x(i,j), y(6-i,j) );
      NT2_TEST_EQUAL( x2(i+(j-1)*5),y(6-i,j) );
    }
  }
}

NT2_TEST_CASE_TPL( noflip, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = T(i + 10*j);

  NT2_TEST_EQUAL( nt2::flipdim(y, 3) , y);
}

NT2_TEST_CASE_TPL( flipflip, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = cT(i + 10*j);

  x = nt2::flipdim(y, 1);
  NT2_TEST_EQUAL( y,  nt2::flipdim(x, 1) );

  x = nt2::flipdim(y, 2);
  NT2_TEST_EQUAL( y,  nt2::flipdim(x, 2) );
}

NT2_TEST_CASE_TPL( flipflip1, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> xr,yr = nt2::_(T(1), T(5));
  xr = nt2::flipdim(yr);
  NT2_TEST_EQUAL( xr,  nt2::flipdim(yr, 2) );

  nt2::table<cT> xl,yl = nt2::_(T(1), T(5));
  yl.resize(nt2::of_size(5, 1));
  xl = nt2::flipdim(yl);
  NT2_TEST_EQUAL( xl,  nt2::flipdim(yl, 1) );

}
