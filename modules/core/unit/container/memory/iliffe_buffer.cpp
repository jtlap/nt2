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
#include <nt2/core/container/memory/dereference.hpp>

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
// iliffe_buffer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_dimensions, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<1,int,T,allocator<int> > >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<2,int,T,allocator<int> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<3,int,T,allocator<int> > >::value), 3UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<4,int,T,allocator<int> > >::value), 4UL );
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer has some reference
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_reference, PADDING )
{
  using boost::is_same;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dereference_;

  typedef iliffe_buffer<3,int,T,allocator<int> > base;

  NT2_TEST((is_same< typename dereference_<base&,1>::type, int**&>::value) );
  NT2_TEST((is_same< typename dereference_<base&,2>::type, int*& >::value) );
  NT2_TEST((is_same< typename dereference_<base&,3>::type, int& >::value) );

  NT2_TEST((is_same< typename dereference_<base const&,1>::type, int** const&>::value) );
  NT2_TEST((is_same< typename dereference_<base const&,2>::type, int* const& >::value) );
  NT2_TEST((is_same< typename dereference_<base const&,3>::type, int const&  >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_1D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;

  iliffe_buffer<1,int,T,allocator<int> > tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );
  
  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-2;pos[0]<=2;++pos[0]) 
    dereference<1UL>(tab,pos) = 10*(1+pos[0]);

  for(pos[0]=-2;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_2D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;

  iliffe_buffer<2,int,T,allocator<int> > tab;

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::ptrdiff_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=-2;++pos[0])
      dereference<2UL>(tab,pos) = 10*(1+pos[1]) + (1+pos[0]);

  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=-2;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );
}


////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_3D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;

  iliffe_buffer<3,int,T,allocator<int> > tab;

  boost::array<std::size_t,3> sizes = {{2,2,2}};
  boost::array<std::size_t,3> bases = {{0,0,0}};
  boost::array<std::size_t,3> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
      dereference<3UL>(tab,pos) = 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]);

  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));
}
