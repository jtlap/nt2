/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::repnum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/repnum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

// template<class T, int N> struct hierarchy_impl
// {
//   typedef typename hierarchy_impl<T,N-1>::type base;
//   typedef typename base::parent           type;
// };

// template<class T> struct hierarchy_impl<T,0>
// {
//   typedef typename nt2::meta::hierarchy_of<T>::type type;
// };

// template<class T, class N>
// struct hierarchy : hierarchy_impl<T,N::value>
// {};

// NT2_TEST_CASE( repnum_hierarchy )
// {
//   using boost::mpl::_;
//   using boost::mpl::int_;

//   NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
//                     , (hierarchy<_,int_<0> >)
//                     , (nt2::tag::repnum_)
//                     );

//   NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
//                     , (hierarchy<_,int_<1> >)
//                     , (nt2::ext::generative_< nt2::tag::repnum_ >
//                       )
//                     );

//   NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
//                     , (hierarchy<_,int_<2> >)
//                     , (nt2::ext::elementwise_<nt2::tag::repnum_>)
//                     );

//   NT2_TEST_EXPR_TYPE( (nt2::tag::repnum_() )
//                     , (hierarchy<_,int_<3> >)
//                     , (nt2::ext::unspecified_<nt2::tag::repnum_>)
//                     );
// }

// NT2_TEST_CASE_TPL( repnum_value_type, NT2_TYPES )
// {
//   using boost::mpl::_;
//   using nt2::meta::value_type_;

//   NT2_TEST_EXPR_TYPE( (nt2::repnum(nt2::of_size(4,4)))
//                     , (value_type_<_>)
//                     , (double)
//                     );

//   NT2_TEST_EXPR_TYPE( (nt2::repnum(nt2::of_size(4,4),nt2::meta::as_<T>()))
//                     , (value_type_<_>)
//                     , (T)
//                     );
// }

// NT2_TEST_CASE( repnum_size )
// {
//   NT2_TEST( nt2::extent( nt2::repnum(11, nt2::of_size(4,5)) ) == nt2::of_size(4,5) );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5)), 1 ), 4 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5)), 2 ), 5 );

//   NT2_TEST( nt2::extent( nt2::repnum(11, nt2::of_size(4,5,6)) ) == nt2::of_size(4,5,6) );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6)), 1 ), 4 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6)), 2 ), 5 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6)), 3 ), 6 );

//   NT2_TEST( nt2::extent( nt2::repnum(11, nt2::of_size(4,5,6,7)) ) == nt2::of_size(4,5,6,7) );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6,7)), 1 ), 4 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6,7)), 2 ), 5 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6,7)), 3 ), 6 );
//   NT2_TEST_EQUAL( nt2::size( nt2::repnum(11, nt2::of_size(4,5,6,7)), 4 ), 7 );
// }

NT2_TEST_CASE( repnum_nd_untyped )
{
  nt2::table<double> x0 = nt2::repnum(11.5, nt2::of_size(64, 1));
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x0(i)) );
  
  nt2::table<double> x1 = nt2::repnum(11.5, nt2::of_size(1, 64));
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x1(i)) );
   
  nt2::table<double> x2 = nt2::repnum(11.5,nt2::of_size(8,8));
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x2(i)) );

  nt2::table<double> x3 = nt2::repnum(11.5,nt2::of_size(8,4,2));
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x3(i)) );

  nt2::table<double> x4 = nt2::repnum(11.5,nt2::of_size(4,4,2,2));
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x4(i)) );


//   nt2::table<double> x1 = nt2::repnum(11.5, 8);
//   for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x1(i)) );

//   nt2::table<double> x2 = nt2::repnum(11.5,8,8);
//   for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x2(i)) );

//   nt2::table<double> x3 = nt2::repnum(11.5,8,4,2);
//   for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x3(i)) );

//   nt2::table<double> x4 = nt2::repnum(11.5,4,4,2,2);
//   for(int i=1;i<=64;++i) NT2_TEST_EQUAL( 11.5, double(x4(i)) );
}

