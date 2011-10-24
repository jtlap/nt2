/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory composite_buffer as a Buffer"

#include <nt2/core/container/memory/adapted/array.hpp>
#include <nt2/core/container/memory/composite_buffer.hpp>
#include <nt2/core/container/meta/adapt_composite.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/array.hpp>

#include <boost/fusion/include/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct foo { double d; float f; char c; };
NT2_ADAPT_COMPOSITE(foo,(double,d)(float,f)(char,c))

////////////////////////////////////////////////////////////////////////////////
// composite_buffer has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( composite_buffer_dimensions )
{
  using boost::mpl::_;
  using boost::array;
  using nt2::meta::dimensions_of;
  using nt2::memory::composite_buffer;

  NT2_TEST_EQUAL((dimensions_of< composite_buffer<array<foo,4> > >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< composite_buffer<array<array<foo,4>,4> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< composite_buffer<array<array<array<foo,4>,4>,4> > >::value), 3UL);
}

////////////////////////////////////////////////////////////////////////////////
// composite_buffer can be dereferenced
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_reference )
{
  using boost::array;
  using boost::is_same;
  using nt2::meta::dereference_;
  using nt2::memory::composite_buffer;
  using boost::fusion::vector3;

  typedef composite_buffer< array<array<array<foo,2>,3>,4> > base;

  NT2_TEST((is_same< dereference_<base&,1>::type, vector3<array<array<double, 2>, 3>&, array<array<float, 2>, 3>&, array<array<char, 2>, 3>&> >::value) );
  NT2_TEST((is_same< dereference_<base&,2>::type, vector3<array<double, 2>&, array<float, 2>&, array<char, 2>&> >::value) );
  NT2_TEST((is_same< dereference_<base&,3>::type, vector3<double&, float&, char&> >::value) );

  NT2_TEST((is_same< dereference_<base const&,1>::type, vector3<array<array<double, 2>, 3> const&, array<array<float, 2>, 3> const&, array<array<char, 2>, 3> const&> >::value) );
  NT2_TEST((is_same< dereference_<base const&,2>::type, vector3<array<double, 2> const&, array<float, 2> const&, array<char, 2> const&> >::value) );
  NT2_TEST((is_same< dereference_<base const&,3>::type, vector3<double const&, float const&, char const&> >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// composite_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( composite_buffer_1D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::composite_buffer;

  composite_buffer< boost::array<foo,5> > tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::size_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // composite_buffer supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=0;pos[0]<5;++pos[0])
  {
    boost::fusion::at_c<0>(dereference<1UL>(tab,pos)) = double(pos[0]);
    boost::fusion::at_c<1>(dereference<1UL>(tab,pos)) = float(1+pos[0]);
    boost::fusion::at_c<2>(dereference<1UL>(tab,pos)) = char('A' + pos[0]);
  }

  for(pos[0]=0;pos[0]<5;++pos[0])
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(dereference<1UL>(tab,pos)), double(pos[0]));
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(dereference<1UL>(tab,pos)), float(1+pos[0]));
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(dereference<1UL>(tab,pos)), char('A' + pos[0]));
  }
}

////////////////////////////////////////////////////////////////////////////////
// composite_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_2D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  boost::array<boost::array<double,5>,2> tab;

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::size_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
      dereference<2UL>(tab,pos) = double(10*(1+pos[1]) + (1+pos[0]));

  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );
}
