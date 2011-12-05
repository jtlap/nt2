/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory iliffe_buffer sharing capability"

#include <nt2/core/container/memory/iliffe_buffer.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/settings/storage_order.hpp>

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

#include <boost/array.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#define PADDING                                                                   \
(nt2::memory::no_padding)(nt2::memory::lead_padding)(nt2::memory::global_padding) \
/**/

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_1D_shared_buffer, PADDING)
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  //  iliffe_buffer<1,int,buffer<int>&,buffer<byte>,C_order_,T,allocator<int> > tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  typedef  buffer<int> buffer_type;
  buffer_type data(-2,5);
  iliffe_buffer<1,int,buffer<int>&,buffer<byte>,C_order_,T,allocator<int> > tab(data);

  for ( buffer_type::index_type i = data.lower(); i <= data.upper(); ++i ){
    data[i] = buffer_type::value_type(1+i);
  }


  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  share( tab, sizes, bases,T(), data);
  
  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-2;pos[0]<=2;++pos[0]){
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), data[pos[0] ] );
  }
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( iliffe_buffer_2D_shared_buffer_no_padding )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,nt2::memory::no_padding,allocator<int> > tab;

  typedef  buffer<int> buffer_type;
  buffer_type data(-2,10);

  for ( buffer_type::index_type i = data.lower(); i <= data.upper(); ++i )
    data[i] = buffer_type::value_type(1+i);


  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::ptrdiff_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // Build a iliffe_buffre from shared data
  //////////////////////////////////////////////////////////////////////////////
  share(tab, sizes, bases, nt2::memory::no_padding(), data );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=2;++pos[0])
    {
      NT2_TEST_EQUAL(dereference<2UL>(tab,pos), data[(pos[0]) + pos[1]*5] );
    }
}

//////////////////////////////////////////////////////////////////////////////
//iliffe_buffer models Buffer Concept
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( iliffe_buffer_2D_shared_buffer_global_padding )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,nt2::memory::global_padding,allocator<int> > tab;


  typedef  buffer<int> buffer_type;
  buffer_type data(-2,10);

  for ( buffer_type::index_type i = data.lower(); i <= data.upper(); ++i )
    data[i] = buffer_type::value_type(1+i);

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::ptrdiff_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // Build a iliffe_buffer from shared data
  //////////////////////////////////////////////////////////////////////////////
  share(tab, sizes, bases, nt2::memory::global_padding(), data );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=2;++pos[0])
    {
      NT2_TEST_EQUAL(dereference<2UL>(tab,pos), data[(pos[0]) + pos[1]*5] );
    }
}

// ////////////////////////////////////////////////////////////////////////////////
// // iliffe_buffer models Buffer Concept
// ////////////////////////////////////////////////////////////////////////////////
// NT2_TEST_CASE( iliffe_buffer_2D_shared_buffer_lead_padding )
// {
//   using nt2::memory::allocator;
//   using nt2::memory::initialize;
//   using nt2::memory::dereference;
//   using nt2::memory::iliffe_buffer;
//   using nt2::memory::buffer;
//   using nt2::memory::byte;
//   using nt2::C_order_;

//   iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,nt2::memory::lead_padding,allocator<int> > tab;

//   //int data[2*BOOST_SIMD_CONFIG_ALIGNMENT];


//   typedef  buffer<int> buffer_type;
//   buffer_type data(-2,2*BOOST_SIMD_CONFIG_ALIGNMENT);

// //   for ( buffer_type::index_type i = data.lower(); i <= data.upper(); ++i )
// //     data[i] = buffer_type::value_type(1+i);

//   for(int i=0;i<2;++i)
//     for(int j=0;j<BOOST_SIMD_CONFIG_ALIGNMENT;++j)
//     data[j + i*BOOST_SIMD_CONFIG_ALIGNMENT] = -1;

//   int k = 0;
//   for(int i=0;i<2;++i)
//     for(int j=data.lower();j<5-data.lower();++j)
//     data[j + i*BOOST_SIMD_CONFIG_ALIGNMENT] = k++;

//   boost::array<std::size_t,2> sizes = {{5,2}};
//   boost::array<std::size_t,2> bases = {{-2,0}};
//   boost::array<std::ptrdiff_t,2> pos;

//   //////////////////////////////////////////////////////////////////////////////
//   // Build a iliffe_buffer from shared data
//   //////////////////////////////////////////////////////////////////////////////
//   share(tab, sizes, bases, nt2::memory::lead_padding(), data );

//   //////////////////////////////////////////////////////////////////////////////
//   // iliffe_buffer supports R/W access through Position
//   //////////////////////////////////////////////////////////////////////////////
//   for(pos[1]=0;pos[1]<=1;++pos[1])
//     for(pos[0]=-2;pos[0]<=2;++pos[0])
//     {
//       NT2_TEST_EQUAL( dereference<2UL>(tab,pos)
//                     , data[(pos[0]) + pos[1]*BOOST_SIMD_CONFIG_ALIGNMENT] 
//                     );
//     }

//   for(pos[1]=0;pos[1]<=1;++pos[1])
//     for(pos[0]=-2;pos[0]<=2;++pos[0])
//     {
//       dereference<2UL>(tab,pos) = 999;
//     }
      
//   for(pos[1]=0;pos[1]<=1;++pos[1])
//     for(pos[0]=-2;pos[0]<=2;++pos[0])
//     {
//       NT2_TEST_EQUAL( dereference<2UL>(tab,pos), 999 );
//     }
// }

// /*
// ////////////////////////////////////////////////////////////////////////////////
// // array type models Buffer Concept
// ////////////////////////////////////////////////////////////////////////////////
// NT2_TEST_CASE_TPL( iliffe_buffer_3D_as_buffer, PADDING )
// {
//   using nt2::memory::allocator;
//   using nt2::memory::initialize;
//   using nt2::memory::dereference;
//   using nt2::memory::iliffe_buffer;

//   iliffe_buffer<3,int,T,allocator<int> > tab;

//   boost::array<std::size_t,3> sizes = {{2,2,2}};
//   boost::array<std::size_t,3> bases = {{0,0,0}};
//   boost::array<std::size_t,3> pos;

//   //////////////////////////////////////////////////////////////////////////////
//   // array type supports being initialized externally
//   //////////////////////////////////////////////////////////////////////////////
//   initialize(tab, sizes, bases, T() );

//   //////////////////////////////////////////////////////////////////////////////
//   // array type supports R/W access through Position
//   //////////////////////////////////////////////////////////////////////////////
//   for(pos[2]=0;pos[2]<2;++pos[2])
//     for(pos[1]=0;pos[1]<2;++pos[1])
//       for(pos[0]=0;pos[0]<2;++pos[0])
//       dereference<3UL>(tab,pos) = 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]);

//   for(pos[2]=0;pos[2]<2;++pos[2])
//     for(pos[1]=0;pos[1]<2;++pos[1])
//       for(pos[0]=0;pos[0]<2;++pos[0])
//     NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));
// }
// */
