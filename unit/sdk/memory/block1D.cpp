/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::block - dynamic mode"

#include <iostream>
#include <nt2/sdk/memory/block.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>

#include <boost/array.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

/*
////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer static properties
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(block_1d_default_ctor)
{
  using nt2::memory::block;
  using nt2::memory::allocator;

  boost::array<int,1> bs = {{1}};
  boost::array<int,1> ss = {{5}};

  typedef block < float,1
                , boost::array<int,1>
                , boost::array<int,1>
                , boost::mpl::vector_c<int,0>
                , nt2::memory::no_padding
                , allocator<float>
                >
  block_type;

  block_type b(bs,ss);

  for(int i=1;i<=5;++i) b.data<1>()[i] = i;

  for(int i=1;i<=5;++i)
    std::cout << b.data<1>()[i] << " ";
  std::cout << "\n";

  for(int i=1;i<=5;++i)
    std::cout << b(boost::fusion::make_vector(i)) << " ";
  std::cout << "\n";
}
*/

NT2_TEST_CASE(block_2d_default_ctor)
{
  using nt2::memory::block;
  using nt2::memory::allocator;

  boost::array<int,2> bs = {{1,-1}};
  boost::array<int,2> ss = {{5,3}};

  typedef block < float,2
                , boost::array<int,2>
                , boost::array<int,2>
                , boost::mpl::vector_c<int,0,1>
                , nt2::memory::no_padding
                , allocator<float>
                >
  block_type;

  block_type b(bs,ss);

  for(int j=b.lower<2>();j<=b.upper<2>();++j)
  {
    for(int i=b.lower<1>();i<=b.upper<1>();++i)
      b(boost::fusion::make_vector(i,j)) = j*100+i;
  }

  for(int i=b.data<1>().lower();i<=b.data<1>().upper();++i)
    std::cout << b(boost::fusion::make_vector(i)) << " ";
  std::cout << "\n\n";

  for(int i=b.lower<1>();i<=b.upper<1>();++i)
  {
    for(int j=b.lower<2>();j<=b.upper<2>();++j)
      std::cout << b(boost::fusion::make_vector(i,j)) << " ";
    std::cout << "\n";
  }
}

NT2_TEST_CASE(block_2d_default_ctor2)
{
  using nt2::memory::block;
  using nt2::memory::allocator;

  boost::array<int,2> bs = {{1,-1}};
  boost::array<int,2> ss = {{5,3}};

  typedef block < float,2
                , boost::array<int,2>
                , boost::array<int,2>
                , boost::mpl::vector_c<int,1,0>
                , nt2::memory::no_padding
                , allocator<float>
                >
  block_type;

  block_type b(bs,ss);
  for(int j=b.lower<2>();j<=b.upper<2>();++j)
  {
    for(int i=b.lower<1>();i<=b.upper<1>();++i)
      b(boost::fusion::make_vector(i,j)) = j*100+i;
  }

 for(int i=b.data<1>().lower();i<=b.data<1>().upper();++i)
    std::cout << b(boost::fusion::make_vector(i)) << " ";
  std::cout << "\n\n";

  for(int i=b.lower<1>();i<=b.upper<1>();++i)
  {
    for(int j=b.lower<2>();j<=b.upper<2>();++j)
      std::cout << b(boost::fusion::make_vector(i,j)) << " ";
    std::cout << "\n";
  }

for(int j=b.lower<2>();j<=b.upper<2>();++j)
  {
    for(int i=b.lower<1>();i<=b.upper<1>();++i)
      std::cout << b(boost::fusion::make_vector(i,j)) << " ";
    std::cout << "\n";
  }
}

/*
NT2_TEST_CASE(block_3d_default_ctor)
{
  using nt2::memory::block;
  using nt2::memory::allocator;

  boost::array<int,3> bs = {{1,0,-1}};
  boost::array<int,3> ss = {{5,7,3}};

  typedef block < float,3
                , boost::array<int,3>
                , boost::array<int,3>
                , boost::mpl::vector_c<int,0,1,2>
                , nt2::memory::lead_padding
                , allocator<float>
                >
  block_type;

  block_type b(bs,ss);
}

NT2_TEST_CASE(block_4d_default_ctor)
{
  using nt2::memory::block;
  using nt2::memory::allocator;

  boost::array<int,4> bs = {{1,0,-1,-10}};
  boost::array<int,4> ss = {{5,7,3,5}};

  typedef block < float,4
                , boost::array<int,4>
                , boost::array<int,4>
                , boost::mpl::vector_c<int,0,1,2,3>
                , nt2::memory::lead_padding
                , allocator<float>
                >
  block_type;

  block_type b(bs,ss);
}
*/

/*
////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_default_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;

  buffer_type b;

  NT2_TEST_EQUAL( b.size()    , 0U          );
  NT2_TEST_EQUAL( b.capacity(), 0U          );
  NT2_TEST_EQUAL( b.lower()   ,  0          );
  NT2_TEST_EQUAL( b.upper()   , -1          );
  NT2_TEST_EQUAL( b.origin()  , (float*)(0) );
  NT2_TEST_EQUAL( b.begin()   , (float*)(0) );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor from allocator
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_allocator_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;

  allocator<float> a;
  buffer_type b(a);

  NT2_TEST_EQUAL( b.size()    , 0U          );
  NT2_TEST_EQUAL( b.capacity(), 0U          );
  NT2_TEST_EQUAL( b.lower()   ,  0          );
  NT2_TEST_EQUAL( b.upper()   , -1          );
  NT2_TEST_EQUAL( b.origin()  , (float*)(0) );
  NT2_TEST_EQUAL( b.begin()   , (float*)(0) );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor from base/size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;
  buffer_type b(0,5);

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.capacity()  , align_on(5U)        );
  NT2_TEST_EQUAL( b.lower()     ,  0                  );
  NT2_TEST_EQUAL( b.upper()     ,  4                  );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = 1+i;

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_assignment)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;
  buffer_type b,x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 1+i;

  b = x;

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.capacity()  , align_on(5U)        );
  NT2_TEST_EQUAL( b.lower()     ,  0                  );
  NT2_TEST_EQUAL( b.upper()     ,  4                  );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_swap)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;
  buffer_type b(-1,3),x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 1+i;
  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = i;

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.capacity()  , align_on(5U)        );
  NT2_TEST_EQUAL( b.lower()     ,  0                  );
  NT2_TEST_EQUAL( b.upper()     ,  4                  );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  NT2_TEST_EQUAL( x.size()      , 3U                  );
  NT2_TEST_EQUAL( x.capacity()  , align_on(3U)        );
  NT2_TEST_EQUAL( x.lower()     ,  -1                 );
  NT2_TEST_EQUAL( x.upper()     ,   1                 );
  NT2_TEST_NOT_EQUAL( x.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( x.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( x.origin()    , x.begin()+x.lower() );
  NT2_TEST( align_on(x.origin()) );

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], i );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}
*/
