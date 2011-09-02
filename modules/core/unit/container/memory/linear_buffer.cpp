/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory linear_buffer"

#include <nt2/core/container/memory/linear_buffer.hpp>

#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build 1D linear_buffer with no_padding
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( linear_1D_no_padding )
{
  using nt2::memory::allocator;
  using nt2::memory::linear_buffer;
  using nt2::memory::no_padding;
  using boost::array;
  
  typedef linear_buffer<1,double,no_padding,allocator<double> > buffer;

  array<int,1> sizes = {{7}};
  array<int,1> bases = {{-3}};
    
  buffer b(sizes,bases,no_padding());
  
  //NT2_TEST_EQUAL( nt2::Eps<double>()            , 2.220446049250313e-16   );
}

////////////////////////////////////////////////////////////////////////////////
// Build 1D linear_buffer with lead_padding
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( linear_1D_lead_padding )
{
  using nt2::memory::allocator;
  using nt2::memory::linear_buffer;
  using nt2::memory::lead_padding;
  using boost::array;
  
  typedef linear_buffer<1,double,lead_padding,allocator<double> > buffer;

  array<int,1> sizes = {{7}};
  array<int,1> bases = {{-3}};

  buffer b(sizes,bases,lead_padding());
  
  //NT2_TEST_EQUAL( nt2::Eps<double>()            , 2.220446049250313e-16   );
}

////////////////////////////////////////////////////////////////////////////////
// Build 1D linear_buffer with global_padding
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( linear_1D_global_padding )
{
  using nt2::memory::allocator;
  using nt2::memory::linear_buffer;
  using nt2::memory::global_padding;
  using boost::array;
  
  typedef linear_buffer<1,double,global_padding,allocator<double> > buffer;

  array<int,1> sizes = {{7}};
  array<int,1> bases = {{-3}};

  buffer b(sizes,bases,global_padding());
  
  //NT2_TEST_EQUAL( nt2::Eps<double>()            , 2.220446049250313e-16   );
}
