//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( square, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;

  nt2::table<cT> ref( nt2::of_size(3,3) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  nt2::table<cT> x0 = nt2::repnum(cT(42, 2),3);

  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE_TPL( nd, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;

  nt2::table<cT> ref( nt2::of_size(8,8) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  nt2::table<cT> x1 = nt2::repnum(cT(42, 2),nt2::of_size(8, 8));

  NT2_TEST_EQUAL(x1,ref);

  nt2::table<cT> x2 = nt2::repnum(cT(42,2), 8, 8 );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(3,2,4) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  x1 = nt2::repnum(cT(42, 2),nt2::of_size(3, 2 , 4));
  NT2_TEST_EQUAL(x1,ref);

  x2 = nt2::repnum(cT(42,2), 3, 2, 4 );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  x1 = nt2::repnum(cT(42,2),nt2::of_size(2,2,2,2));
  NT2_TEST_EQUAL(x1,ref);

  x2 = nt2::repnum(cT(42,2), 2, 2, 2, 2 );
  NT2_TEST_EQUAL(x2,ref);
}

NT2_TEST_CASE_TPL( typed_expr, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;

  nt2::table<cT> ref( nt2::of_size(8,8) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table<cT> x1 = nt2::repnum( cT(42,2), t1 );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = cT(42, 2);

  nt2::table<cT> x2 = nt2::repnum( cT(42,2), t2 );
  NT2_TEST_EQUAL(x2,ref);

}
