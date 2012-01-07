/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::length function"

#include <boost/array.hpp>
#include <nt2/include/functions/sub2ind.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( sub2ind_1D )
{
  using nt2::sub2ind;
  using boost::array;

  array<int,1> sub, size = {{ 5 }};

  for(int i=1;i<=5;++i)
  {
    sub[0] = i;
    std::cout << sub2ind( size, sub ) << "\n";
  }
}

NT2_TEST_CASE( sub2ind_2D )
{
  using nt2::sub2ind;
  using boost::array;

  array<int,2> sub, size = {{ 3,5 }};

  for(int j=1;j<=5;++j)
  {
    for(int i=1;i<=3;++i)
    {
      sub[0] = i; sub[1] = j;
      std::cout << sub2ind( size, sub ) << " ";
    }
    std::cout << "\n";
  }
}
