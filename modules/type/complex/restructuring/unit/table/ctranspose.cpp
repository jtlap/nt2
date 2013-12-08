//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( ctranspose, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> z, x( nt2::of_size(4, 5) ),y( nt2::of_size(5, 4) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
    {
      y(j, i)  = cT(i + 10*j, i + 3*j);
      x(i,j) = nt2::conj(y(j, i));
    }

  z = nt2::ctrans(y);
  NT2_TEST_EQUAL( x, z);
}

NT2_TEST_CASE_TPL( ctranspose_scalar, NT2_TYPES )
{
  typedef std::complex<T> cT;
  NT2_TEST_EQUAL(nt2::ctranspose(cT(1)), cT(1));
  NT2_TEST_EQUAL(nt2::ctranspose(nt2::I<cT>()), -nt2::I<cT>());
}
