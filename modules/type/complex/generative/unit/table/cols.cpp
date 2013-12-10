//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cols.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL( _0d, NT2_REAL_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  typedef std::complex<T> cT;

  nt2::table<cT> x1 = nt2::cols( T(42) );
  NT2_TEST_EXPR_TYPE( ( nt2::cols( cT(42) )), (value_type_<_>), (cT) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1),T(42) );
}

NT2_TEST_CASE_TPL( square, NT2_REAL_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  typedef std::complex<T> cT;

  T s = 42;
  nt2::table<cT> ref( nt2::of_size(3,3) );
  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      ref(i,j) = j-1+s;

  nt2::table<cT> x0 = nt2::cols(3,s);

  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE_TPL( nd, NT2_REAL_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  typedef std::complex<T> cT;

  T s = 42;

  nt2::table<cT> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = j-1+s;

  nt2::table<cT> x1 = nt2::cols(nt2::of_size(8, 8), s );

  NT2_TEST_EQUAL(x1,ref);

  nt2::table<cT> x2 = nt2::cols(8, 8, s );
  NT2_TEST_EQUAL(x2,ref);

  nt2::table<cT> x3 = nt2::cols(8, s );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE_TPL( typed_expr, NT2_REAL_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  typedef std::complex<T> cT;

  T s = 42;
  nt2::table<cT> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = j-1+s;

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table<cT> x1 = nt2::cols( t1, s );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = j-1+s;

  nt2::table<cT> x2 = nt2::cols( t2, s );
  NT2_TEST_EQUAL(x2,ref);

}
