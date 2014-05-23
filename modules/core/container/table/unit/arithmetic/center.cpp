//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/mean.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( center, (float)(double))
{
  nt2::table<T> y( nt2::of_size(8, 4) );
  nt2::table<T> sy, m, ref( nt2::of_size(8, 4) );

  for(std::size_t j=1;j<=nt2::size(y, 2);j++)
    for(std::size_t i=1;i<=nt2::size(y, 1);i++)
      y(i,j) = T(i) - T(j);

  sy = nt2::center(y, 2);
   m = mean(y, 2);

  for(std::size_t j=1;j<=nt2::size(y, 2);j++)
    for(std::size_t i=1;i<=nt2::size(y, 1);i++)
      ref(i,j) = y(i,j) - m(i);

  NT2_TEST_EQUAL(sy,ref);

  sy = nt2::center(y, 1);
   m = mean(y, 1);

  for(std::size_t j=1;j<=nt2::size(y, 2);j++)
    for(std::size_t i=1;i<=nt2::size(y, 1);i++)
      ref(i,j) = y(i,j) - m(j);

  NT2_TEST_EQUAL(sy,ref);
}
