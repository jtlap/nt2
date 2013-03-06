//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::fill_pattern function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/fill_pattern.hpp>

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

  NT2_TEST_EXPR_TYPE( (nt2::tag::fill_pattern_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::fill_pattern_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::fill_pattern_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::elementwise_<nt2::tag::fill_pattern_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::fill_pattern_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::unspecified_<nt2::tag::fill_pattern_>)
                    );
}

NT2_TEST_CASE_TPL( of_size, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table<T> x  = nt2::_(T(1),T(3));
  nt2::table<T> ref;

  nt2::table<T> x1 = nt2::fill_pattern(x, nt2::of_size(0) );
  NT2_TEST_EXPR_TYPE((nt2::fill_pattern(x,nt2::of_size(0))),(value_type_<_>),(T));
  NT2_TEST( nt2::isempty(x1) );

  ref.resize( nt2::of_size(5) );
  for(std::size_t i=1;i<=5;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x2 = nt2::fill_pattern(x, nt2::of_size(5) );
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(5) );
  NT2_TEST_EQUAL( x2, ref );

  ref.resize( nt2::of_size(5,5) );
  for(std::size_t i=1;i<=25;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x3 = nt2::fill_pattern(x, nt2::of_size(5,5) );
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(5,5) );
  NT2_TEST_EQUAL( x3, ref );

  ref.resize( nt2::of_size(5,5,5) );
  for(std::size_t i=1;i<=125;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x4 = nt2::fill_pattern(x, nt2::of_size(5,5,5) );
  NT2_TEST_EQUAL( nt2::extent(x4), nt2::of_size(5,5,5) );
  NT2_TEST_EQUAL( x4, ref );
}

NT2_TEST_CASE_TPL( nd_size, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table<T> x  = nt2::_(T(1),T(3));
  nt2::table<T> ref;

  nt2::table<T> x1 = nt2::fill_pattern(x, 0 );
  NT2_TEST_EXPR_TYPE((nt2::fill_pattern(x,0)),(value_type_<_>),(T));
  NT2_TEST( nt2::isempty(x1) );

  ref.resize( nt2::of_size(5) );
  for(std::size_t i=1;i<=5;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x2 = nt2::fill_pattern(x, 5, 1 );
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(5) );
  NT2_TEST_EQUAL( x2, ref );

  ref.resize( nt2::of_size(5,5) );
  for(std::size_t i=1;i<=25;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x3 = nt2::fill_pattern(x, 5 );
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(5,5) );
  NT2_TEST_EQUAL( x3, ref );

  nt2::table<T> x3p = nt2::fill_pattern(x, 5,5 );
  NT2_TEST_EQUAL( nt2::extent(x3p), nt2::of_size(5,5) );
  NT2_TEST_EQUAL( x3p, ref );

  ref.resize( nt2::of_size(5,5,5) );
  for(std::size_t i=1;i<=125;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<T> x4 = nt2::fill_pattern(x, 5,5,5 );
  NT2_TEST_EQUAL( nt2::extent(x4), nt2::of_size(5,5,5) );
  NT2_TEST_EQUAL( x4, ref );
}
