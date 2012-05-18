/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::size function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/depth.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// size of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_size )
{
  using nt2::size;
  using nt2::width;
  using nt2::height;
  using nt2::depth;

  NT2_TEST_EQUAL( std::size_t( size( 3 )(1)), height(3));
  NT2_TEST_EQUAL( std::size_t( size( 3 )(2)), width(3));
  NT2_TEST_EQUAL( size( 3 , 1 ), height(3));
  NT2_TEST_EQUAL( size( 3 , 2 ), width(3));
  NT2_TEST_EQUAL( size( 3 , 3 ), depth(3));
}

////////////////////////////////////////////////////////////////////////////////
// size of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_table )
{
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;
  
  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(1)), height(x));
  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(2)), width(x));
  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(3)), depth(x)); 

  NT2_TEST_EQUAL( nt2::size( x , 1), height(x)); 
  NT2_TEST_EQUAL( nt2::size( x , 2), width(x));
  NT2_TEST_EQUAL( nt2::size( x , 3), depth(x));
}

////////////////////////////////////////////////////////////////////////////////
// size of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_expression )
{
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(1)), height(x));
  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(2)), width(x)); 
  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(3)), depth(x)); 

  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 1), height(x));
  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 2), width(x)); 
  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 3), depth(x)); 
}

////////////////////////////////////////////////////////////////////////////////
// size of size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_size )
{
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;
  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size(x) )(1)), height( nt2::size(x)));
  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size(x) )(2)), width ( nt2::size(x)));

  NT2_TEST_EQUAL( nt2::size( nt2::size(x) , 1) , height( nt2::size(x)));      
  NT2_TEST_EQUAL( nt2::size( nt2::size(x) , 2) , width ( nt2::size(x)));
  NT2_TEST_EQUAL( nt2::size( nt2::size(x) , 3) , depth ( nt2::size(x)));

  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size( nt2::size(x) ) )(1)),  height( nt2::size(nt2::size(x))));      
  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size( nt2::size(x) ) )(2)),   width ( nt2::size(nt2::size(x))));

  NT2_TEST_EQUAL( nt2::size( nt2::size( nt2::size(x) ) , 1),  height( nt2::size(nt2::size(x)))); 
  NT2_TEST_EQUAL( nt2::size( nt2::size( nt2::size(x) ) , 2),   width ( nt2::size(nt2::size(x))));
  NT2_TEST_EQUAL( nt2::size( nt2::size( nt2::size(x) ) , 3),   depth ( nt2::size(nt2::size(x))));
                  
  nt2::table<int> a( nt2::of_size(4,5) );
  NT2_TEST_EQUAL( std::size_t( nt2::size(nt2::size(a), 1)), height( nt2::size(a))); 
  NT2_TEST_EQUAL( std::size_t( nt2::size(nt2::size(a), 2)),  width ( nt2::size(a)));
  NT2_TEST_EQUAL( std::size_t( nt2::size(nt2::size(a), 3)),  depth ( nt2::size(a)));
  NT2_TEST_EQUAL( std::size_t( nt2::size(nt2::size(a))(1)), height( nt2::size(a))); 
  NT2_TEST_EQUAL( std::size_t( nt2::size(nt2::size(a))(2)),  width ( nt2::size(a)));

}

////////////////////////////////////////////////////////////////////////////////
// size of static table 2D
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_static_table2D )
{
  using nt2::of_size_;
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;
  table < float, nt2::settings(of_size_<5, 2, 4>) > x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), height ( x)); 
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)),  width ( x));
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(3)),  depth ( x));
  NT2_TEST_EQUAL( nt2::size(x, 1),              height ( x)); 
  NT2_TEST_EQUAL( nt2::size(x, 2),               width ( x));
  NT2_TEST_EQUAL( nt2::size(x, 3),               depth ( x));

}

////////////////////////////////////////////////////////////////////////////////
// size of container
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_cont )
{
  using nt2::memory::container;
  using nt2::of_size_;
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;
  typedef container<float, of_size_<5> > cont;
  cont x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), height(  x)); 
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)),  width ( x));
  NT2_TEST_EQUAL( nt2::size(x, 1),              height(  x)); 
  NT2_TEST_EQUAL( nt2::size(x, 2),               width ( x));
  NT2_TEST_EQUAL( nt2::size(x, 3),               depth ( x));

}
////////////////////////////////////////////////////////////////////////////////
// size of static table 1D
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_static_table )
{
  using nt2::of_size_;
  using nt2::table;
  using nt2::width;
  using nt2::height;
  using nt2::depth;
  table < float, nt2::settings(of_size_<5>) > x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), height ( x)); 
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)),  width ( x));
  NT2_TEST_EQUAL( nt2::size(x, 1),              height ( x)); 
  NT2_TEST_EQUAL( nt2::size(x, 2),               width ( x));
  NT2_TEST_EQUAL( nt2::size(x, 3),               depth ( x));
}
