/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::repmat function"

#include <nt2/table.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/eye.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( expr, NT2_TYPES )
{
  nt2::table<T> pattern = nt2::eye(2,2, nt2::meta::as_<T>() );

  nt2::table<T> ref( nt2::of_size(6,6) );
  for(std::size_t j = 1; j <= 6;++j)
    for(std::size_t i = 1; i <= 6;++i)
      ref(i,j) = (i+j)%2 ? T(0) : T(1);

  nt2::table<T> a0;
  a0 = nt2::repmat(pattern,3);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,3) )
                , nt2::of_size(6,6)
                );
  NT2_TEST_EQUAL(a0,ref);

  nt2::table<T> a1;
  a1 = nt2::repmat(pattern,3,3);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,3,3) )
                , nt2::of_size(6,6)
                );
  NT2_TEST_EQUAL(a1, ref );

  nt2::table<T> a2;
  a2 = nt2::repmat(pattern,nt2::of_size(3,3));
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,nt2::of_size(3,3)) )
                , nt2::of_size(6,6)
                );
  NT2_TEST_EQUAL(a2, ref);

  nt2::table<int> sz( nt2::of_size(1,2) );
  sz(1) = 3; sz(2) = 3;

  nt2::table<T> a3 = nt2::repmat(pattern,sz);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,sz) )
                , nt2::of_size(6,6)
                );
  NT2_TEST_EQUAL(a3,ref);
}

NT2_TEST_CASE_TPL( scalar, NT2_TYPES )
{
  T pattern = T(42);

  nt2::table<T> ref = nt2::repnum( pattern, nt2::of_size(3,3) );

  nt2::table<T> a0;
  a0 = nt2::repmat(pattern,3);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,3) )
                , nt2::of_size(3,3)
                );
  NT2_TEST_EQUAL(a0,ref);

  nt2::table<T> a1;
  a1 = nt2::repmat(pattern,3,3);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,3,3) )
                , nt2::of_size(3,3)
                );
  NT2_TEST_EQUAL(a1, ref );

  nt2::table<T> a2;
  a2 = nt2::repmat(pattern,nt2::of_size(3,3));
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,nt2::of_size(3,3)) )
                , nt2::of_size(3,3)
                );
  NT2_TEST_EQUAL(a2, ref);

  nt2::table<int> sz( nt2::of_size(1,2) );
  sz(1) = 3; sz(2) = 3;

  nt2::table<T> a3 = nt2::repmat(pattern,sz);
  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(pattern,sz) )
                , nt2::of_size(3,3)
                );
  NT2_TEST_EQUAL(a3,ref);
}
