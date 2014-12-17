//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( along_scalar, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(3, 4, 2, 3) );

  for(size_t k = 0, m=1;m<=size(y, 4);m++)
    for(size_t l=1;l<=size(y, 3);l++)
      for(size_t j=1;j<=size(y, 2);j++)
        for(size_t i=1;i<=size(y, 1);i++)
          y(i,j, l, m) = k++;

  for(size_t k=1;k<= nt2::size(y, 1);++k)
  {
    std::cout << "column " << k << std::endl;
    NT2_TEST_EQUAL(y(k, _, _, _), nt2::along(y, k, 1));
  }

  for(size_t k=1;k<= nt2::size(y, 2);++k)
  {
    std::cout << "row " << k << std::endl;
    NT2_TEST_EQUAL(y(_, k, _, _), nt2::along(y, k, 2));
  }

  for(size_t k=1;k<= nt2::size(y, 3);++k)
  {
    std::cout << "depth " << k << std::endl;
    NT2_TEST_EQUAL(y(_, _, k, _), nt2::along(y, k, 3));
  }

  for(size_t k=1;k<= nt2::size(y, 4);++k)
  {
    std::cout << "page " << k << std::endl;
    NT2_TEST_EQUAL(y(_, _, _, k), nt2::along(y, k, 4));
  }
}

NT2_TEST_CASE_TPL( along_vect, NT2_REAL_TYPES )
{
  using nt2::_;
  typedef typename nt2::meta::as_integer<T>::type iT;

  nt2::table<T> y( nt2::of_size(3, 4, 2, 3) );

  for(size_t k = 0, m=1;m<=size(y, 4);m++)
    for(size_t l=1;l<=size(y, 3);l++)
      for(size_t j=1;j<=size(y, 2);j++)
        for(size_t i=1;i<=size(y, 1);i++)
          y(i,j, l, m) = k++;

  nt2::table<iT> kk = _(iT(1), iT(2));
  NT2_TEST_EQUAL(y(kk, _, _, _), nt2::along(y, kk, 1));
  NT2_TEST_EQUAL(y(_, kk, _, _), nt2::along(y, kk, 2));
  NT2_TEST_EQUAL(y(_, _, kk, _), nt2::along(y, kk, 3));
  NT2_TEST_EQUAL(y(_, _, _, kk), nt2::along(y, kk, 4));
}

NT2_TEST_CASE_TPL( along_write, NT2_REAL_TYPES )
{
  using nt2::_;

  nt2::table<T> y   = zeros( nt2::of_size(3, 4, 2, 3), nt2::meta::as_<T>() );
  nt2::table<T> ref = T(3)*ones( nt2::of_size(3, 4, 2, 3), nt2::meta::as_<T>() );

  nt2::along(y, _(1,3), 1) = T(3);
  nt2::along(y, _(1,4), 2) = T(3);
  nt2::along(y, _(1,2), 3) = T(3);
  nt2::along(y, _(1,3), 4) = T(3);

  NT2_TEST_EQUAL(y, ref );
}
