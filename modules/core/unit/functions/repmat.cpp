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

NT2_TEST_CASE( repmat_size )
{
  nt2::table<float> a0( nt2::of_size(3,3) );

  nt2::table<int> sz( nt2::of_size(1,3) );
  sz(1) = 2; sz(2) = 4; sz(3) = 5;

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(a0, nt2::of_size(2,1,4,2) ) )
                , nt2::of_size(6,3,4,2)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(a0, 7 ) )
                , nt2::of_size(21,21)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(a0, 7,5 ) )
                , nt2::of_size(21,15)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(a0, sz ) )
                , nt2::of_size(6,12,5,1)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(3., nt2::of_size(2,1,4,2) ) )
                , nt2::of_size(2,1,4,2)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(3., 7 ) )
                , nt2::of_size(7,7)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(3., 7,5 ) )
                , nt2::of_size(7,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::repmat(3., sz ) )
                , nt2::of_size(2,4,5,1)
                );
}

NT2_TEST_CASE_TPL( repmat_expr, NT2_TYPES )
{
  nt2::table<T> pattern = nt2::eye(2,2, nt2::meta::as_<T>() );

  {
    nt2::table<T> a0;
    a0 = nt2::repmat(pattern,5);

    for(std::size_t j = 1; j < 2*5;++j)
      for(std::size_t i = 1; i < 2*5;++i)
        NT2_TEST_EQUAL(a0(i,j), (i+j)%2 ? T(0) : T(1) );
  }

  {
    nt2::table<T> a1, a12;
    a1 = nt2::repmat(pattern,5,2);
    a12 = nt2::repmat(pattern,5,2)(nt2::_);

    for(std::size_t j = 1; j < 2*2;++j)
    {
      for(std::size_t i = 1; i < 2*5;++i)
      {
        NT2_TEST_EQUAL(a1(i,j), (i+j)%2 ? T(0) : T(1) );
        NT2_TEST_EQUAL(a12(i+(j-1)*2*5), (i+j)%2 ? T(0) : T(1) );
      }
    }
  }

  {
    nt2::table<T> a2;
    a2 = nt2::repmat(pattern,nt2::of_size(5,3,2));

    for(std::size_t j = 1; j < 2*6;++j)
      for(std::size_t i = 1; i < 2*5;++i)
        NT2_TEST_EQUAL(a2(i,j), (i+j)%2 ? T(0) : T(1) );
  }

  {
    nt2::table<T> a3;

    nt2::table<int> sz( nt2::of_size(1,4) );
    sz(1) = 2; sz(2) = 2; sz(3) = 2; sz(4) = 2;

    a3 = nt2::repmat(pattern,sz);

    for(std::size_t j = 1; j < 2*8;++j)
      for(std::size_t i = 1; i < 2*2;++i)
      {
        NT2_TEST_EQUAL(a3(i,j), (i+j)%2 ? T(0) : T(1) );
      }
  }
}

NT2_TEST_CASE_TPL( repmat_scalar, NT2_TYPES )
{
  nt2::table<T> a0;
  nt2::table<int> sz( nt2::of_size(1,4) );
  sz(1) = 2; sz(2) = 2; sz(3) = 2; sz(4) = 2;

  a0 = nt2::repmat(T(3),9);
  for(std::size_t i = 1; i < 9*9;++i)
    NT2_TEST_EQUAL(a0(i), T(3) );

  a0 = nt2::repmat(T(4),9,4);
  for(std::size_t i = 1; i < 9*4;++i)
    NT2_TEST_EQUAL(a0(i), T(4) );

  a0 = nt2::repmat(T(5),nt2::of_size(9,2,3));
  for(std::size_t i = 1; i < 9*2*3;++i)
    NT2_TEST_EQUAL(a0(i), T(5) );

  a0 = nt2::repmat(T(6),sz);
  for(std::size_t i = 1; i < 2*2*2*2;++i)
    NT2_TEST_EQUAL(a0(i), T(6) );
}
