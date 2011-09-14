/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory std::vector adaptation as a Buffer"

#include <nt2/core/container/memory/adapted/vector.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// vector type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_dimensions )
{
  using std::vector;
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL((dimensions_of< std::vector<int> >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< std::vector<std::vector<int> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< std::vector<std::vector<std::vector<int> > > >::value), 3UL);
}
////////////////////////////////////////////////////////////////////////////////
// vector type has some reference
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_reference )
{
  using std::vector;
  using boost::is_same;
  using nt2::meta::reference_;

  typedef vector<vector<vector<int> > > base;

  NT2_TEST((is_same< reference_<base,1>::type, vector< vector<int> >& >::value) );
  NT2_TEST((is_same< reference_<base,2>::type, vector<int>& >::value) );
  NT2_TEST((is_same< reference_<base,3>::type, int& >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// vector type has some cref
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_const_reference )
{
  using std::vector;
  using boost::is_same;
  using nt2::meta::const_reference_;

  typedef vector<vector<vector<int> > > base;

  NT2_TEST((is_same< const_reference_<base,1>::type, vector< vector<int> > const& >::value) );
  NT2_TEST((is_same< const_reference_<base,2>::type, vector<int> const& >::value) );
  NT2_TEST((is_same< const_reference_<base,3>::type, int const& >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_1D_as_buffer )
{
  using std::vector;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  vector<double> tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::size_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases);

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=0;pos[0]<5;++pos[0]) 
    dereference<1UL>(tab,pos) = 10*(1+pos[0]);

  for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );
}

////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_2D_as_buffer )
{
  using std::vector;  
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  vector< vector<double> > tab;

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::size_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases);

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
      dereference<2UL>(tab,pos) = 10*(1+pos[1]) + (1+pos[0]);

  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );
}

////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_3D_as_buffer )
{
  using std::vector;  
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  vector< vector< vector<double> > > tab;

  boost::array<std::size_t,3> sizes = {{2,2,3}};
  boost::array<std::size_t,3> bases = {{0,0,0}};
  boost::array<std::size_t,3> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases);

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
      dereference<3UL>(tab,pos) = 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]);

  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));
}
