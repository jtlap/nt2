/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory iliffe_buffer"

#include <nt2/core/container/memory/iliffe_buffer.hpp>

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

using nt2::memory::no_padding;
using nt2::memory::lead_padding;
using nt2::memory::global_padding;

////////////////////////////////////////////////////////////////////////////////
// Build 1/2/3/4D iliffe_buffer with various padding strategies
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_ctor, (no_padding)(lead_padding)(global_padding) )
{
  using nt2::slice;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using boost::array;
  
  typedef iliffe_buffer<1,double,T,allocator<double> > buffer1D;
  typedef iliffe_buffer<2,double,T,allocator<double> > buffer2D;
  typedef iliffe_buffer<3,double,T,allocator<double> > buffer3D;
  typedef iliffe_buffer<4,double,T,allocator<double> > buffer4D;

  T padding;
  array<int,1> s1D = {{3}};
  array<int,2> s2D = {{3,2}};
  array<int,3> s3D = {{3,2,2}};
  array<int,4> s4D = {{3,2,2,2}};
  
  array<int,1> b1D = {{-1}};
  array<int,2> b2D = {{-1,-1}};
  array<int,3> b3D = {{-1,-1,-1}};
  array<int,4> b4D = {{-1,-1,-1,-1}};

  buffer1D b1(s1D,b1D,padding);
  buffer2D b2(s2D,b2D,padding);
  buffer3D b3(s3D,b3D,padding);
  buffer4D b4(s4D,b4D,padding);
  
  NT2_TEST_EQUAL( b1.begin(), b1.data() );
  NT2_TEST_EQUAL( b2.begin(), b2.data() );
  NT2_TEST_EQUAL( b3.begin(), b3.data() );
  NT2_TEST_EQUAL( b4.begin(), b4.data() );
  
  NT2_TEST_EQUAL( (b1.end()-b1.begin()), slice<1>(s1D,padding) );
  NT2_TEST_EQUAL( (b2.end()-b2.begin()), slice<1>(s2D,padding) );
  NT2_TEST_EQUAL( (b3.end()-b3.begin()), slice<1>(s3D,padding) );
  NT2_TEST_EQUAL( (b4.end()-b4.begin()), slice<1>(s4D,padding) );
}
