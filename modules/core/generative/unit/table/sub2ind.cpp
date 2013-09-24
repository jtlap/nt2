//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::sub2ind_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::sub2ind_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::sub2ind_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::elementwise_< nt2::tag::sub2ind_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::sub2ind_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::unspecified_<nt2::tag::sub2ind_>)
                    );
}

NT2_TEST_CASE_TPL( value_type, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::table;
  using nt2::size;
  using nt2::of_size;
  using nt2::meta::value_type_;

  nt2::table<T>   ss( of_size(4,4) );

  // Size with an extent
  NT2_TEST_EXPR_TYPE( ( nt2::sub2ind(of_size(4,4),T(1),T(1)) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::sub2ind(of_size(4,4),ss,ss) )
                    , (value_type_<_>)
                    , (T)
                    );

  // Size with a size
  NT2_TEST_EXPR_TYPE( ( nt2::sub2ind(size(ss),T(1),T(1)) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::sub2ind(size(ss),ss,ss) )
                    , (value_type_<_>)
                    , (T)
                    );
}

NT2_TEST_CASE_TPL( sub2ind_2D, NT2_TYPES )
{
  using nt2::sub2ind;
  using nt2::of_size;

  nt2::_2D sz = of_size(7,5);
  nt2::table<T> x( of_size(1,35) );
  nt2::table<T> y( of_size(1,35) );

  for(std::size_t i=1;i<=nt2::numel(sz);i++) x(i) = (i-1)%7+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) y(i) = (i-1)/7+1;

  NT2_TEST_EQUAL( nt2::extent(sub2ind(sz,x,y)), nt2::extent(x) );
  NT2_TEST_EQUAL( sub2ind(sz,x,y), nt2::_(T(1),T(nt2::numel(sz))) );
}

NT2_TEST_CASE_TPL( sub2ind_3D, NT2_TYPES )
{
  using nt2::sub2ind;
  using nt2::of_size;

  nt2::_3D sz = of_size(3,4,3);
  nt2::table<T> x( of_size(1,36) );
  nt2::table<T> y( of_size(1,36) );
  nt2::table<T> z( of_size(1,36) );

  for(std::size_t i=1;i<=nt2::numel(sz);i++) x(i) = (i-1)%3+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) y(i) = ((i-1)/3)%4+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) z(i) = (i-1)/12+1;

  NT2_TEST_EQUAL( nt2::extent(sub2ind(sz,x,y,z)), nt2::extent(x) );
  NT2_TEST_EQUAL( sub2ind(sz,x,y,z), nt2::_(T(1),T(nt2::numel(sz))) );
}

NT2_TEST_CASE_TPL( sub2ind_4D, NT2_TYPES )
{
  using nt2::sub2ind;
  using nt2::of_size;

  nt2::_4D sz = of_size(3,2,3,2);
  nt2::table<T> x( of_size(1,36) );
  nt2::table<T> y( of_size(1,36) );
  nt2::table<T> z( of_size(1,36) );
  nt2::table<T> w( of_size(1,36) );

  for(std::size_t i=1;i<=nt2::numel(sz);i++) x(i) = (i-1)%3+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) y(i) = ((i-1)/3)%2+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) z(i) = ((i-1)/6)%3+1;
  for(std::size_t i=1;i<=nt2::numel(sz);i++) w(i) = ((i-1)/18)+1;

  NT2_TEST_EQUAL( nt2::extent(sub2ind(sz,x,y,z,w)), nt2::extent(x) );
  NT2_TEST_EQUAL( sub2ind(sz,x,y,z,w), nt2::_(T(1),T(nt2::numel(sz))) );
}
