//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::repnum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::repnum_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::repnum_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::repnum_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::repnum_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::repnum_>)
                    );
}

NT2_TEST_CASE_TPL( square, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<T> ref( nt2::of_size(3,3) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  nt2::table<T> x0 = nt2::repnum(T(42),3);

  NT2_TEST_EXPR_TYPE( (nt2::repnum(T(42),3)), (value_type_<_>), (T) );
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE_TPL( nd, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<T> ref( nt2::of_size(8,8) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  nt2::table<T> x1 = nt2::repnum(T(42),nt2::of_size(8, 8));

  NT2_TEST_EXPR_TYPE( ( nt2::repnum(T(42),nt2::of_size(8, 8)) ), (value_type_<_>), (T) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<T> x2 = nt2::repnum(T(42), 8, 8 );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(3,2,4) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  x1 = nt2::repnum(T(42),nt2::of_size(3, 2 , 4));
  NT2_TEST_EQUAL(x1,ref);

  x2 = nt2::repnum(T(42), 3, 2, 4 );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  x1 = nt2::repnum(T(42),nt2::of_size(2,2,2,2));
  NT2_TEST_EQUAL(x1,ref);

  x2 = nt2::repnum(T(42), 2, 2, 2, 2 );
  NT2_TEST_EQUAL(x2,ref);
}

NT2_TEST_CASE_TPL( typed_expr, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<T> ref( nt2::of_size(8,8) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table<T> x1 = nt2::repnum( T(42), t1 );
  NT2_TEST_EXPR_TYPE( ( nt2::repnum(T(42), t1) ), (value_type_<_>), (T) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(std::size_t i=1;i<= numel(ref);++i) ref(i) = T(42);

  nt2::table<T> x2 = nt2::repnum( T(42), t2 );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::repnum(T(42),x2) );
}
