//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/repmat.hpp>

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

  NT2_TEST_EXPR_TYPE( (nt2::tag::meshgrid_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::meshgrid_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::meshgrid_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::tieable_< nt2::tag::meshgrid_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::meshgrid_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::unspecified_<nt2::tag::meshgrid_>)
                    );
}

NT2_TEST_CASE_TPL( value_type, NT2_TYPES )
{
  using nt2::table;
  using nt2::of_size;
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<T>   ss( of_size(1,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::meshgrid(ss,ss) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::meshgrid(ss,ss,ss) )
                    , (value_type_<_>)
                    , (T)
                    );
}

NT2_TEST_CASE( meshgrid_size )
{
  using nt2::table;
  using nt2::of_size;
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<double>                      x( of_size(1,4) );
  nt2::table<double>                      y( of_size(1,3) );
  nt2::table<double,nt2::of_size_<1,5> >  xs;
  nt2::table<double,nt2::of_size_<1,6> >  ys;

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(4,5)) )
                    , (_)
                    , (nt2::of_size_<1,1>)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,y)) )
                    , (_)
                    , (nt2::_2D)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(4,y)) )
                    , (_)
                    , (nt2::of_size_<-1,1>)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,5)) )
                    , (_)
                    , (nt2::of_size_<1,-1>)
                    );

  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,y)), of_size(3,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,xs)) )
                    , (_)
                    , (nt2::of_size_<5,-1>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,xs)), of_size(5,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,y)) )
                    , (_)
                    , (nt2::of_size_<-1,5>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,y)), of_size(3,5) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,ys)) )
                    , (_)
                    , (nt2::of_size_<6,5>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,ys)), of_size(6,5) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,y,x)) )
                    , (_)
                    , nt2::_3D
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,y,x)), of_size(3,4,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,y,xs)) )
                    , (_)
                    , (nt2::of_size_<-1,-1,5>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,y,xs)), of_size(3,4,5) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,ys,x)) )
                    , (_)
                    , (nt2::of_size_<6,-1,-1>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,ys,x)), of_size(6,4,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,y,x)) )
                    , (_)
                    , (nt2::of_size_<-1,5,-1>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,y,x)), of_size(3,5,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,ys,x)) )
                    , (_)
                    , (nt2::of_size_<6,5,-1>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,ys,x)), of_size(6,5,4) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,y,xs)) )
                    , (_)
                    , (nt2::of_size_<-1,5,5>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,y,xs)), of_size(3,5,5) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(x,ys,xs)) )
                    , (_)
                    , (nt2::of_size_<6,-1,5>)
                    );
  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(x,ys,xs)), of_size(6,4,5) );

  NT2_TEST_EXPR_TYPE( ( nt2::extent(nt2::meshgrid(xs,ys,xs)) )
                    , (_)
                    , (nt2::of_size_<6,5,5>)
                    );

  NT2_TEST_EQUAL( nt2::extent(nt2::meshgrid(xs,ys,xs)), of_size(6,5,5) );
}


NT2_TEST_CASE( meshgrid_assert )
{
  nt2::table<double> ix = nt2::_(1.,7.);
  nt2::table<double> iy = nt2::_(1.,3.);
  nt2::table<double> iz = nt2::_(1.,2.);
  nt2::table<double> w,x,y,z;

  NT2_TEST_ASSERT( nt2::tie(x,y,z)   = nt2::meshgrid(ix,iy)    );
  NT2_TEST_ASSERT( nt2::tie(x,y,z,w) = nt2::meshgrid(ix,iy,iz) );
}

NT2_TEST_CASE_TPL( meshgrid, NT2_TYPES )
{
  using nt2::repmat;
  using nt2::reshape;

  nt2::table<T> ix = nt2::_(T(1),T(7));
  nt2::table<T> iy = nt2::_(T(1),T(3));
  nt2::table<T> iz = nt2::_(T(1),T(2));
  nt2::table<T> w,x,y,z;

  nt2::table<T> ry = repmat( reshape(iy,3,1),1,7);
  nt2::table<T> rx = repmat( reshape(ix,1,7),3,1);

  x = nt2::meshgrid(ix,iy);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());

  nt2::tie(x,y) = nt2::meshgrid(ix,iy);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());

  nt2::table<T> rz = repmat( reshape(iz,1,1,2),3,7,1);
  ry = repmat( reshape(iy,3,1,1),1,7,2);
  rx = repmat( reshape(ix,1,7,1),3,1,2);

  x = nt2::meshgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());

  nt2::tie(x,y) = nt2::meshgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());

  nt2::tie(x,y,z) = nt2::meshgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());
  NT2_TEST_EQUAL(z,rz);
  NT2_TEST_EQUAL(z.extent(),rz.extent());
}
