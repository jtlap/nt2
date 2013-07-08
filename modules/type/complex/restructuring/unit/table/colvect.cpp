//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::colvect function"

#include <nt2/table.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( colvect_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  NT2_TEST_EQUAL(nt2::colvect(cT(0, 1)), cT(0, 1));
}

NT2_TEST_CASE_TPL( colvect2, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  nt2::table<cT> r;
  nt2::table<cT, nt2::_2D> y( nt2::of_size(4,4) );
  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = cT(i + 10*j, j);
  r = nt2::colvect(y);
  NT2_TEST_EQUAL(r, y(nt2::_));
  NT2_TEST_EQUAL(nt2::colvect(y), y(nt2::_));
}
